/* Copyright (C) 2015, WSID   */

/* Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/**
 * SECTION: crankoctreeset
 * @title: Octree Set
 * @short_description: Octree based set.
 * @stability: Unstable
 * @include: crankshape.h
 *
 * This represents simple octree based set.
 *
 * Each octree node holds 0 or more elements. When a node holds much of elements,
 * it will breed child nodes and distribute its elements. When a node and its
 * childrens has too less elements, it may join all its children into itself.
 */

#define _CRANKSHAPE_INSIDE


#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "crankbox.h"
#include "crankoctreeset.h"


//////// Private macros ////////////////////////////////////////////////////////

#define NODE_THIS 8
#define NODE_PARENT 9

//////// Functions for private types ///////////////////////////////////////////

static CrankOctreeSetNode *crank_octree_set_node_alloc (void);

static void                crank_octree_set_node_dealloc (CrankOctreeSetNode *node);

static void                crank_octree_set_node_dealloc_all (CrankOctreeSetNode *node);


static guint              crank_octree_set_node_get_child_index (CrankOctreeSetNode *node,
                                                                 CrankVecFloat3     *position,
                                                                 gfloat              radius);



static void               crank_octree_set_node_add (CrankOctreeSetNode *node,
                                                     CrankOctreeSet     *set,
                                                     gpointer            data);

static void               crank_octree_set_node_add_part (CrankOctreeSetNode *node,
                                                          CrankOctreeSet     *set,
                                                          gpointer            data,
                                                          CrankVecFloat3     *position,
                                                          gfloat              radius);

static void               crank_octree_set_node_remove (CrankOctreeSetNode *node,
                                                        CrankOctreeSet     *set,
                                                        gpointer            data);




static gboolean           crank_octree_set_node_divide (CrankOctreeSetNode *node,
                                                        CrankOctreeSet     *set);

static void               crank_octree_set_node_join (CrankOctreeSetNode *node,
                                                      CrankOctreeSet     *set);



static GList*             crank_octree_set_node_list (CrankOctreeSetNode *node,
                                                      GList              *list);

static GList*             crank_octree_set_node_cull (CrankOctreeSetNode *node,
                                                      CrankOctreeSet     *set,
                                                      GList              *list,
                                                      CrankPlane3        *culls,
                                                      const guint         nculls);


//////// Type Definitions //////////////////////////////////////////////////////

struct _CrankOctreeSetNode
{
  CrankOctreeSetNode *parent;
  CrankOctreeSetNode *children[8];

  GPtrArray         *data_array;

  // Node props
  CrankBox3         boundary;
  CrankVecFloat3    middle;

  // Cache area
  guint             part_size;
  guint             depth;
};


struct _CrankOctreeSet
{
  guint               _refc;

  CrankOctreePosFunc  pos_func;
  gpointer            pos_func_data;
  GDestroyNotify      pos_func_destroy;

  CrankOctreeRadiusFunc  rad_func;
  gpointer               rad_func_data;
  GDestroyNotify         rad_func_destroy;

  CrankOctreeSetNode  *root;
  GHashTable          *map_data_node;

  guint               min_capacity;
  guint               max_capacity;

  guint               max_height;
};

G_DEFINE_BOXED_TYPE (CrankOctreeSet,
                     crank_octree_set,
                     crank_octree_set_ref,
                     crank_octree_set_unref);





///////// Private functions for private type ///////////////////////////////////

static CrankOctreeSetNode*
crank_octree_set_node_alloc (void)
{
  CrankOctreeSetNode *node = g_slice_new0 (CrankOctreeSetNode);

  node->data_array = g_ptr_array_new ();

  return node;
}


static void
crank_octree_set_node_dealloc (CrankOctreeSetNode *node)
{
  g_ptr_array_unref (node->data_array);

  g_slice_free (CrankOctreeSetNode, node);
}

static void
crank_octree_set_node_dealloc_all (CrankOctreeSetNode *node)
{
  if (node->children[0] != NULL)
    {
      crank_octree_set_node_dealloc_all (node->children[0]);
      crank_octree_set_node_dealloc_all (node->children[1]);
      crank_octree_set_node_dealloc_all (node->children[2]);
      crank_octree_set_node_dealloc_all (node->children[3]);
      crank_octree_set_node_dealloc_all (node->children[4]);
      crank_octree_set_node_dealloc_all (node->children[5]);
      crank_octree_set_node_dealloc_all (node->children[6]);
      crank_octree_set_node_dealloc_all (node->children[7]);
    }

  crank_octree_set_node_dealloc (node);
}


static guint
crank_octree_set_node_get_child_index (CrankOctreeSetNode *node,
                                       CrankVecFloat3     *position,
                                       gfloat              radius)
{
  CrankVecFloat3 displacement;
  CrankVecBool3 lm;

  crank_vec_float3_sub (position, & node->middle, &displacement);
  crank_vec_float3_cmpgreater (&displacement, crank_vec_float3_static_zero, &lm);


  if (((lm.x ? displacement.x : -displacement.x ) < radius) &&
      ((lm.y ? displacement.y : -displacement.y ) < radius) &&
      ((lm.z ? displacement.z : -displacement.z ) < radius) )
    return NODE_THIS;

  return (lm.x ? 1 : 0) | (lm.y ? 2 : 0) | (lm.z ? 4 : 0);
}


static void
crank_octree_set_node_add (CrankOctreeSetNode *node,
                           CrankOctreeSet     *set,
                           gpointer            data)
{
  g_hash_table_insert (set->map_data_node, data, node);
  g_ptr_array_add (node->data_array, data);
}

static void
crank_octree_set_node_add_part (CrankOctreeSetNode *node,
                                CrankOctreeSet     *set,
                                gpointer            data,
                                CrankVecFloat3     *pos,
                                gfloat              radius)
{
  CrankVecFloat3 dist;

  node->part_size++;

  crank_vec_float3_sub (& node->middle, pos, &dist);

  if ((node->depth + 1 < set->max_height) && (set->max_capacity <= node->part_size))
    {
      guint index;

      if (node->children[0] == NULL)
        {
          if (! crank_octree_set_node_divide (node, set))
            {
              crank_octree_set_node_add (node, set, data);
              return;
            }
        }

      index = crank_octree_set_node_get_child_index (node, pos, radius);

      if (index == NODE_THIS)
        crank_octree_set_node_add (node, set, data);
      else
        crank_octree_set_node_add_part (node->children[index],
                                        set,
                                        data,
                                        pos,
                                        radius);
    }
  else
    {
      crank_octree_set_node_add (node, set, data);
    }
}


static void
crank_octree_set_node_remove (CrankOctreeSetNode *node,
                              CrankOctreeSet     *set,
                              gpointer            data)
{
  CrankOctreeSetNode *niter;
  CrankOctreeSetNode *join_node;

  g_hash_table_remove (set->map_data_node, data);

  for (niter = node; niter != NULL; niter = niter->parent)
    {
      niter->part_size--;
      if (niter->part_size < set->min_capacity)
        join_node = niter;
    }

  crank_octree_set_node_join (niter, set);
}



static gboolean
crank_octree_set_node_divide (CrankOctreeSetNode *node,
                              CrankOctreeSet     *set)
{
  GPtrArray *n_data_array;

  guint depth1;
  guint i;

  depth1 = node->depth + 1;

  if (set->max_height <= depth1)
    return FALSE;


  // Allocate child nodes.

  node->children[0] = crank_octree_set_node_alloc ();
  node->children[1] = crank_octree_set_node_alloc ();
  node->children[2] = crank_octree_set_node_alloc ();
  node->children[3] = crank_octree_set_node_alloc ();
  node->children[4] = crank_octree_set_node_alloc ();
  node->children[5] = crank_octree_set_node_alloc ();
  node->children[6] = crank_octree_set_node_alloc ();
  node->children[7] = crank_octree_set_node_alloc ();

  node->children[0]->parent = node;
  node->children[1]->parent = node;
  node->children[2]->parent = node;
  node->children[3]->parent = node;
  node->children[4]->parent = node;
  node->children[5]->parent = node;
  node->children[6]->parent = node;
  node->children[7]->parent = node;

  node->children[0]->depth = depth1;
  node->children[1]->depth = depth1;
  node->children[2]->depth = depth1;
  node->children[3]->depth = depth1;
  node->children[4]->depth = depth1;
  node->children[5]->depth = depth1;
  node->children[6]->depth = depth1;
  node->children[7]->depth = depth1;

  crank_vec_float3_copy (& node->boundary.start, & node->children[0]->boundary.start);
  crank_vec_float3_copy (& node->middle, & node->children[0]->boundary.end);

  crank_box3_init_uvec (& node->children[1]->boundary,
      node->middle.x,         node->boundary.start.y, node->boundary.start.z,
      node->boundary.end.x,   node->middle.y,         node->middle.z);

  crank_box3_init_uvec (& node->children[2]->boundary,
      node->boundary.start.x, node->middle.y,       node->boundary.start.z,
      node->middle.x,         node->boundary.end.y, node->middle.z);

  crank_box3_init_uvec (& node->children[3]->boundary,
      node->middle.x,       node->middle.y,       node->boundary.start.z,
      node->boundary.end.x, node->boundary.end.y, node->middle.z);

  crank_box3_init_uvec (& node->children[4]->boundary,
      node->boundary.start.x, node->boundary.start.y, node->middle.z,
      node->middle.x,         node->middle.y,         node->boundary.end.z);

  crank_box3_init_uvec (& node->children[5]->boundary,
      node->middle.x,         node->boundary.start.y, node->middle.z,
      node->boundary.end.x,   node->middle.y,         node->boundary.end.z);

  crank_box3_init_uvec (& node->children[6]->boundary,
      node->boundary.start.x, node->middle.y,       node->middle.z,
      node->middle.x,         node->boundary.end.y, node->boundary.end.z);

  crank_vec_float3_copy (& node->middle, & node->children[7]->boundary.start);
  crank_vec_float3_copy (& node->boundary.end, & node->children[7]->boundary.end);

  for (i = 0; i < 8; i++)
    crank_box3_gets (&node->children[i]->boundary,
                     0.5, &node->children[i]->middle);


  // Distribute elements.

  n_data_array = g_ptr_array_new ();

  for (i = 0; i < node->data_array->len; i++)
    {
      gpointer data = node->data_array->pdata[i];
      guint child_index;

      CrankVecFloat3 *pos = set->pos_func (data, set->pos_func_data);
      gfloat          rad = set->rad_func (data, set->rad_func_data);

      child_index = crank_octree_set_node_get_child_index (node, pos, rad);

      // for data that does not belongs to child nodes.
      if (child_index == NODE_THIS)
        {
          g_ptr_array_add (n_data_array, data);
        }
      else
        {
          CrankOctreeSetNode *child = node->children[child_index];

          child->part_size ++;
          crank_octree_set_node_add (child, set, data);
        }
    }

  g_ptr_array_unref (node->data_array);
  node->data_array = n_data_array;

  // Propagate further

  for (i = 0; i < 8; i++)
    {
      if (set->max_capacity <= node->children[i]->part_size)
        crank_octree_set_node_divide (node->children[i], set);
    }

  return TRUE;
}


static void
crank_octree_set_node_join (CrankOctreeSetNode *node,
                            CrankOctreeSet     *set)
{
  guint i;
  guint j;

  if (node->children[0] != NULL)
    {
      for (i = 0; i < 8; i++)
        {
          crank_octree_set_node_join (node->children[i], set);

          for (j = 0; j < node->children[i]->data_array->len; j++)
            {
              gpointer data = node->children[i]->data_array->pdata[j];

              g_ptr_array_add (node->data_array, data);
              g_hash_table_insert (set->map_data_node, data, node);
            }

          crank_octree_set_node_dealloc (node->children[i]);
          node->children[i] = NULL;
        }
    }
}

static GList*
crank_octree_set_node_list (CrankOctreeSetNode *node,
                            GList              *list)
{
  guint i;

  if (node->children[0] != NULL)
    {
      for (i = 0; i < 8; i++)
        list = crank_octree_set_node_list (node->children[i], list);
    }


  for (i = 0; i < node->data_array->len; i++)
    {
      list = g_list_prepend (list, node->data_array->pdata[i]);
    }

  return list;
}

static GList*
crank_octree_set_node_cull (CrankOctreeSetNode *node,
                            CrankOctreeSet     *set,
                            GList              *list,
                            CrankPlane3        *culls,
                            const guint         nculls)
{
  gboolean partial = FALSE;
  guint i;
  guint j;

  // Check whether it is in cull.

  for (i = 0; i < nculls; i++)
    {
      gint sign = crank_box3_get_plane_sign (& node->boundary,
                                             culls + i);

      if (0 < sign)
        return list;

      else if (sign == 0)
        partial = TRUE;
    }

  if (partial)
    {
      for (i = 0; i < node->data_array->len; i++)
        {
          gpointer data = node->data_array->pdata[i];

          CrankVecFloat3 *pos = set->pos_func (data, set->pos_func_data);
          gfloat          rad = set->rad_func (data, set->rad_func_data);

          for (j = 0; j < nculls; j++)
            {
              if (rad < -crank_plane3_get_distance (culls + j, pos))
                break;
            }

          if (j == nculls)
            list = g_list_prepend (list, data);
        }

      if (node->children[0] != NULL)
        {
          for (i = 0; i < 8; i++)
            {
              list = crank_octree_set_node_cull (node->children[i], set, list, culls, nculls);
            }
        }
    }
  else
    {
      list = crank_octree_set_node_list (node, list);
    }

  return list;
}


//////// Constructors //////////////////////////////////////////////////////////

/**
 * crank_octree_set_new:
 * @boundary: Boundary of octree.
 * @pos_func: (scope notified): Position function.
 * @pos_func_data: (closure pos_func): Userdata for @pos_func.
 * @pos_func_destroy: (destroy pos_func_destroy): Destroyer for @pos_func_data
 * @rad_func: (scope notified): Radius function.
 * @rad_func_data: (closure rad_func): Userdata for @rad_func.
 * @rad_func_destroy: (destroy rad_func_destroy): Destroyer for @rad_func_data
 *
 * Constructs a octree.
 *
 * Returns: (transfer full): Newly constructed octree.
 */
CrankOctreeSet*
crank_octree_set_new (CrankBox3             *boundary,
                      CrankOctreePosFunc     pos_func,
                      gpointer               pos_func_data,
                      GDestroyNotify         pos_func_destroy,
                      CrankOctreeRadiusFunc  rad_func,
                      gpointer               rad_func_data,
                      GDestroyNotify         rad_func_destroy)
{
  CrankOctreeSet *set = g_slice_new (CrankOctreeSet);

  set->_refc = 1;
  set->pos_func = pos_func;
  set->pos_func_data = pos_func_data;
  set->pos_func_destroy = pos_func_destroy;

  set->rad_func = rad_func;
  set->rad_func_data = rad_func_data;
  set->rad_func_destroy = rad_func_destroy;

  set->root = crank_octree_set_node_alloc ();
  crank_box3_copy (boundary, & set->root->boundary);

  set->map_data_node = g_hash_table_new (g_direct_hash, g_direct_equal);

  set->min_capacity = 5;
  set->max_capacity = 10;
  set->max_height = G_MAXUINT;

  return set;
}

/**
 * crank_octree_set_ref:
 * @set: (transfer none): A Octree.
 *
 * Increase reference count of octree.
 *
 * Returns: (transfer full): @set with increased ref count.
 */
CrankOctreeSet*
crank_octree_set_ref (CrankOctreeSet *set)
{
  g_atomic_int_inc (& set->_refc);
  return set;
}

/**
 * crank_octree_set_unref:
 * @set: (transfer full): A Octree.
 *
 * Decrease reference count of octree.
 */
void
crank_octree_set_unref (CrankOctreeSet *set)
{
  if (g_atomic_int_dec_and_test (& set->_refc))
    {
      crank_octree_set_node_dealloc_all (set->root);

      set->pos_func_destroy (set->pos_func_data);
      set->rad_func_destroy (set->rad_func_data);

      g_slice_free (CrankOctreeSet, set);
    }
}


//////// Octreee Attributes ////////////////////////////////////////////////////

/**
 * crank_octree_set_get_size:
 * @set: An Octree set.
 *
 * Gets number of elements.
 *
 * Returns: Number of elements.
 */
guint
crank_octreee_set_get_size (CrankOctreeSet *set)
{
  return set->root->part_size;
}

/**
 * crank_octree_set_get_boundeary:
 * @set: An Octree set.
 * @boundary: (out): A Boundary of octree.
 *
 * Gets boundary of an octree set.
 */
void
crank_octree_set_get_boundary (CrankOctreeSet *set,
                               CrankBox3      *boundary)
{
  crank_box3_copy (& set->root->boundary, boundary);
}



//////// Element Add/Remove ////////////////////////////////////////////////////

/**
 * crank_octree_set_add:
 * @set: An octree set.
 * @data: A Data to add.
 *
 * Add data to an octree set.
 */
void
crank_octree_set_add (CrankOctreeSet *set,
                      gpointer        data)
{
  CrankVecFloat3 *pos = set->pos_func (data, set->pos_func_data);
  gfloat          rad = set->rad_func (data, set->rad_func_data);

  crank_octree_set_node_add_part (set->root, set, data, pos, rad);
}


/**
 * crank_octree_set_remove:
 * @set: An octree set.
 * @data: A data to remove.
 *
 * Removes a data from an octree set.
 *
 * Returns: Whether the data was removed.
 */
gboolean
crank_octree_set_remove (CrankOctreeSet *set,
                         gpointer        data)
{
  CrankOctreeSetNode *node = g_hash_table_lookup (set->map_data_node, data);

  if (node == NULL)
    return FALSE;

  crank_octree_set_node_remove (node, set, data);
  return TRUE;
}

/**
 * crank_octree_set_remove_all:
 * @set: An octree set.
 *
 * Removes all datas from an octree set.
 */
void
crank_octree_set_remove_all (CrankOctreeSet *set)
{
  crank_octree_set_node_dealloc_all (set->root);

  g_hash_table_remove_all (set->map_data_node);

  set->root = crank_octree_set_node_alloc ();
}

/**
 * crank_octree_set_contains:
 * @set: An octree set.
 * @data: A data to check contains.
 *
 * Checks whether this set contains @data.
 *
 * Returns: Whether @data is in @set.
 */
gboolean
crank_octree_set_contains (CrankOctreeSet *set,
                           gpointer        data)
{
  return g_hash_table_contains (set->map_data_node, data);
}



//////// Normal iteration //////////////////////////////////////////////////////

/**
 * crank_octree_set_foreach:
 * @set: An octree set.
 * @func: (scope call): A Function to iteration.
 * @userdata: (closure func): A userdata
 *
 * Iterate over @set with @func.
 */
void
crank_octree_set_foreach (CrankOctreeSet *set,
                          GFunc           func,
                          gpointer        userdata)
{
  GHashTableIter iter;
  gpointer        data;

  g_hash_table_iter_init (&iter, set->map_data_node);
  while (g_hash_table_iter_next (&iter, &data, NULL))
    func (data, userdata);
}

/**
 * crank_octree_set_get_data_list:
 * @set: An octree set.
 *
 * Gets #GList of elements in octree.
 *
 * Returns: (element-type gpointer) (transfer container): List of elements in octree.
 */
GList*
crank_octree_set_get_data_list (CrankOctreeSet *set)
{
  return g_hash_table_get_keys (set->map_data_node);
}


/**
 * crank_octree_get_culled_list:
 * @set: An octree set.
 * @culls: (array length=nculls): Culling plane.
 * @nculls: Number of @culls.
 *
 * Returns: (element-type gpointer) (transfer container): List of elements in octree.
 */
GList*
crank_octree_set_get_culled_list (CrankOctreeSet *set,
                                  CrankPlane3    *culls,
                                  const guint     nculls)
{
  return crank_octree_set_node_cull (set->root, set, NULL, culls, nculls);
}




//////// Getting nodes /////////////////////////////////////////////////////////

/**
 * crank_octree_set_get_root:
 * @set: An octree set.
 *
 * Gets root node of octree.
 *
 * Returns: (transfer none): A node.
 */
CrankOctreeSetNode*
crank_octree_set_get_root (CrankOctreeSet *set)
{
  return set->root;
}


/**
 * crank_octree_set_get_node:
 * @set: An octree set.
 * @data: A Data.
 *
 * Gets node associated to
 *
 * Returns: (transfer none) (nullable): A node.
 */
CrankOctreeSetNode*
crank_octree_set_get_node (CrankOctreeSet *set,
                           gpointer        data)
{
  return g_hash_table_lookup (set->map_data_node, data);
}



//////// Node Properties ///////////////////////////////////////////////////////

/**
 * crank_octree_set_node_get_boundary:
 * @node: A Node.
 * @boundary: (out): Boundary of node.
 *
 * Get boundary of node.
 */
void
crank_octree_set_node_get_boundary (CrankOctreeSetNode *node,
                                    CrankBox3          *boundary)
{
  crank_box3_copy (& node->boundary, boundary);
}

/**
 * crank_octree_set_node_get_middle:
 * @node: A Node.
 * @middle: (out): Middle of node.
 *
 * Get middle of node.
 */
void
crank_octree_set_node_get_middle (CrankOctreeSetNode *node,
                                  CrankVecFloat3     *middle)
{
  crank_vec_float3_copy (&node->middle, middle);
}



//////// Node children /////////////////////////////////////////////////////////

/**
 * crank_octree_set_node_has_children:
 * @node: A Node.
 *
 * Checks whether this has children.
 *
 * Returns: Whether this has children.
 */
gboolean
crank_octree_set_node_has_children (CrankOctreeSetNode *node)
{
  return node->children[0] != NULL;
}

/**
 * crank_octree_set_node_get_child:
 * @node: A Node.
 * @index: index of children.
 *
 * Get child node of this node.
 *
 * Returns: (nullable) (transfer none): Child node of this node, or %NULL if it
 *     does not have child node.
 */
CrankOctreeSetNode*
crank_octree_set_node_get_child (CrankOctreeSetNode *node,
                                 const guint         index)
{
  return node->children[index];
}


/**
 * crank_octree_set_node_get_child_pos:
 * @node: A Node.
 * @pos: Position of
 *
 * Get child node of this node, according to given position.
 *
 * Returns: (nullable) (transfer none): Child node of this node, or %NULL if it
 *     does not have child node.
 */
CrankOctreeSetNode*
crank_octree_set_node_get_child_pos (CrankOctreeSetNode *node,
                                     CrankVecFloat3     *pos)
{
  return node->children[crank_octree_set_node_get_child_index (node, pos, 0)];
}
