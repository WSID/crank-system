#ifndef CRANKOCTREESET_H
#define CRANKOCTREESET_H

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

#ifndef _CRANKSHAPE_INSIDE
#error crankoctreeset.h cannot be included directly: include crankshape.h
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "crankbox.h"
#include "crankshapemisc.h"

G_BEGIN_DECLS

//////// Type Declarations /////////////////////////////////////////////////////

/**
 * CrankOctreePosFunc:
 * @data: A Data of octree item.
 * @userdata: (closure): A Userdata.
 *
 * Function for getting position of each data.
 *
 * Returns: (transfer none): Position of @data.
 */
typedef CrankVecFloat3 *(*CrankOctreePosFunc) (gpointer data,
                                               gpointer userdata);

/**
 * CrankOctreeRadiusFunc:
 * @data: A Data of octree item.
 * @userdata: (closure): A userdata.
 *
 * Function for getting radius of each data.
 *
 * Returns: Radius of @data.
 */
typedef gfloat          (*CrankOctreeRadiusFunc) (gpointer data,
                                                  gpointer userdata);

typedef struct _CrankOctreeSet CrankOctreeSet;

typedef struct _CrankOctreeSetNode CrankOctreeSetNode;

#define CRANK_TYPE_OCTREE_SET (crank_octree_set_get_type())
GType crank_octree_set_get_type(void);

/**
 * CrankOctreeSet:
 *
 * Represents an octree based set.
 */

/**
 * CrankOctreeSetNode:
 *
 * Represents node of octree for a set.
 */

//////// Constructors //////////////////////////////////////////////////////////

CrankOctreeSet *crank_octree_set_new (CrankBox3            *boundary,
                                      CrankOctreePosFunc    pos_func,
                                      gpointer              pos_func_data,
                                      GDestroyNotify        pos_func_destroy,
                                      CrankOctreeRadiusFunc rad_func,
                                      gpointer              rad_func_data,
                                      GDestroyNotify        rad_func_destroy);

CrankOctreeSet *crank_octree_set_ref (CrankOctreeSet *set);

void            crank_octree_set_unref (CrankOctreeSet *set);


//////// Octree attributes /////////////////////////////////////////////////////

guint       crank_octree_set_get_size (CrankOctreeSet *set);

void        crank_octree_set_get_boundary (CrankOctreeSet *set,
                                           CrankBox3      *boundary);





//////// Element add/remove ////////////////////////////////////////////////////

void        crank_octree_set_add (CrankOctreeSet *set,
                                  gpointer        data);

gboolean    crank_octree_set_remove (CrankOctreeSet *set,
                                     gpointer        data);

void        crank_octree_set_remove_all (CrankOctreeSet *set);


gboolean    crank_octree_set_contains (CrankOctreeSet *set,
                                       gpointer        data);



//////// Normal iteration //////////////////////////////////////////////////////

void        crank_octree_set_foreach (CrankOctreeSet *set,
                                      GFunc           func,
                                      gpointer        userdata);

void        crank_octree_set_cull_foreach (CrankOctreeSet    *set,
                                           const CrankPlane3 *culls,
                                           const guint        nculls,
                                           GFunc              func,
                                           gpointer           userdata);


GList      *crank_octree_set_get_data_list (CrankOctreeSet *set);

GPtrArray  *crank_octree_set_add_data_array(CrankOctreeSet *set,
                                            GPtrArray      *array);


//////// Culled iterations /////////////////////////////////////////////////////

GList      *crank_octree_set_get_culled_list (CrankOctreeSet    *set,
                                              const CrankPlane3 *culls,
                                              const guint        nculls);

GPtrArray  *crank_octree_set_add_culled_array(CrankOctreeSet    *set,
                                              GPtrArray         *array,
                                              const CrankPlane3 *culls,
                                              const guint        nculls);


//////// Getting nodes /////////////////////////////////////////////////////////

CrankOctreeSetNode *crank_octree_set_get_root (CrankOctreeSet *set);

CrankOctreeSetNode *crank_octree_set_get_node (CrankOctreeSet *set,
                                               gpointer        data);



//////// Node Properties ///////////////////////////////////////////////////////

void                crank_octree_set_node_get_boundary (CrankOctreeSetNode *node,
                                                        CrankBox3          *boundary);

void                crank_octree_set_node_get_middle (CrankOctreeSetNode *node,
                                                      CrankVecFloat3     *middle);


//////// Node children /////////////////////////////////////////////////////////

gboolean            crank_octree_set_node_has_children (CrankOctreeSetNode *node);

CrankOctreeSetNode *crank_octree_set_node_get_child    (CrankOctreeSetNode *node,
                                                        const guint         index);

CrankOctreeSetNode *crank_octree_set_node_get_child_pos (CrankOctreeSetNode *node,
                                                         CrankVecFloat3     *pos);

G_END_DECLS

#endif
