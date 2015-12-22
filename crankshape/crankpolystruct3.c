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

#define _CRANKSHAPE_INSIDE

#include <stdarg.h>

#include <glib.h>
#include <glib-object.h>

#include "crankpolystruct3.h"


/**
 * SECTION: crankpolystruct3
 * @title: Polyhedral structure descriptor.
 * @short_description: Describe association of each vertices, edges and faces.
 * @stability: Unstable
 * @include: crankshape.h
 *
 * This structure describes overall association of each vertices, edges, and
 * faces, apart from detailed position informations.
 */

//////// Private Functions /////////////////////////////////////////////////////
static void                   crank_poly_struct3_vdata_fini (CrankPolyStruct3VData *data);

static void                   crank_poly_struct3_edata_fini (CrankPolyStruct3EData *data);

static void                   crank_poly_struct3_fdata_fini (CrankPolyStruct3FData *data);


static CrankPolyStruct3VData *crank_poly_struct3_get_vdata (CrankPolyStruct3 *self,
                                                            const guint       vid);

static CrankPolyStruct3EData *crank_poly_struct3_get_edata (CrankPolyStruct3 *self,
                                                            const guint       eid);

static CrankPolyStruct3FData *crank_poly_struct3_get_fdata (CrankPolyStruct3 *self,
                                                            const guint       fid);

static gboolean               crank_poly_struct3_is_rarray_equal (const guint  len,
                                                                  const guint *a,
                                                                  const guint *b);

static gboolean               crank_poly_struct3_edges_to_vertices (CrankPolyStruct3 *self,
                                                                    const guint       len,
                                                                    const guint      *edges,
                                                                    guint            *vertices);

static gboolean               crank_poly_struct3_array_contains (const guint  len,
                                                                 const guint *array,
                                                                 const guint  item);


//////// Type Definitions //////////////////////////////////////////////////////

G_DEFINE_BOXED_TYPE (CrankPolyStruct3,
                     crank_poly_struct3,
                     crank_poly_struct3_ref,
                     crank_poly_struct3_unref);

struct _CrankPolyStruct3 {
  guint       _ref;

  GArray     *vertices;
  GArray     *edges;
  GArray     *faces;
};

//////// Private functions /////////////////////////////////////////////////////

static void
crank_poly_struct3_vdata_fini (CrankPolyStruct3VData *data)
{
  g_free (data->edges);
  g_free (data->faces);
}

static void
crank_poly_struct3_edata_fini (CrankPolyStruct3EData *data)
{
  g_free (data->faces);
}

static void
crank_poly_struct3_fdata_fini (CrankPolyStruct3FData *data)
{
  g_free (data->vertices);
  g_free (data->edges);
}


static CrankPolyStruct3VData*
crank_poly_struct3_get_vdata (CrankPolyStruct3 *self,
                              const guint       vid)
{
  return & g_array_index (self->vertices, CrankPolyStruct3VData, vid);
}

static CrankPolyStruct3EData*
crank_poly_struct3_get_edata (CrankPolyStruct3 *self,
                              const guint       eid)
{
  return & g_array_index (self->edges, CrankPolyStruct3EData, eid);
}

static CrankPolyStruct3FData*
crank_poly_struct3_get_fdata (CrankPolyStruct3 *self,
                              const guint       fid)
{
  return & g_array_index (self->faces, CrankPolyStruct3FData, fid);
}

static gboolean
crank_poly_struct3_is_rarray_equal (const guint  len,
                                    const guint *a,
                                    const guint *b)
{
  guint i;
  guint s;
  guint sn;
  guint sp;
  guint n;

  // Filter out special cases.
  if (len == 0)
    return TRUE;
  else if (len == 1)
    return (a[0] == b[0]);

  // Getting starting point, which b[s] == a[0]
  for (s = 0; s < len; s++)
    {
      if (b[s] == a[0])
        break;
    }

  // Geting incremental.
  sn = s + 1;
  sn = (sn == len) ? 0 : sn;
  sp = (s == 0) ? (len - 1) : s - 1;

  if (b[sn] == a[1])
    {
      n = len - s;
      for (i = 1; i < n; i++)
        {
          if (b[i + s] != a[i])
            return FALSE;
        }
      for (i = 0; i < s; i++)
        {
          if (b[i] != a[i + n])
            return FALSE;
        }
    }
  else if (b[sp] == a[1])
    {
      n = len - s;
      for (i = 1; i < s; i++)
        {
          if (b[s - i] == a[i])
            return FALSE;
        }
      for (i = 0; i < n; i++)
        {
          if (b[len - i] == a[s + i])
            return FALSE;
        }
    }
  else
    {
      return FALSE;
    }

  return TRUE;
}

static gboolean
crank_poly_struct3_edges_to_vertices (CrankPolyStruct3 *pstruct,
                                      const guint       len,
                                      const guint      *edges,
                                      guint            *vertices)
{
  CrankPolyStruct3EData *edata;
  guint i, j, n1, n2;

  if (len < 3)
    {
      g_warning ("A Valid face should have at least 3 edges.");
      return FALSE;
    }

  n1 = len - 1;
  n2 = n1 - 1;

  edata = crank_poly_struct3_get_edata (pstruct, edges[n1]);

  vertices[n1] = edata->vertices[0];
  vertices[0] = edata->vertices[1];
  for (i = 0; i < n2; i++)
    {
      edata = crank_poly_struct3_get_edata (pstruct, edges[i]);

      if (edata->vertices[0] == vertices[i])
        vertices[i + 1] = edata->vertices[1];
      else if (edata->vertices[1] == vertices[i])
        vertices[i + 1] = edata->vertices[0];
      else
        return FALSE;
    }

  edata = crank_poly_struct3_get_edata (pstruct, edges[n2]);

  if (edata->vertices[0] == vertices[n2])
    return (vertices[n1] == edata->vertices[1]);
  else if (edata->vertices[1] == vertices[n2])
    return (vertices[n1] == edata->vertices[0]);
  else
    return FALSE;
}

static gboolean
crank_poly_struct3_array_contains (const guint  len,
                                   const guint *array,
                                   const guint  item)
{
  guint i;

  for (i = 0; i < len; i++)
    {
      if (array[i] == item)
        return TRUE;
    }
  return FALSE;
}





//////// Constructors //////////////////////////////////////////////////////////

/**
 * crank_poly_struct3_new:
 *
 * Constructs an empty poly struct.
 *
 * Returns: (transfer full): Newly constructed poly struct.
 */
CrankPolyStruct3*
crank_poly_struct3_new (void)
{
  CrankPolyStruct3 *self = g_slice_new (CrankPolyStruct3);

  self->_ref = 1;
  self->vertices = g_array_new (TRUE, TRUE, sizeof (CrankPolyStruct3VData));
  self->edges = g_array_new (FALSE, FALSE, sizeof (CrankPolyStruct3EData));
  self->faces = g_array_new (FALSE, FALSE, sizeof (CrankPolyStruct3FData));

  g_array_set_clear_func (self->vertices,
                          (GDestroyNotify)crank_poly_struct3_vdata_fini);
  g_array_set_clear_func (self->edges,
                          (GDestroyNotify)crank_poly_struct3_edata_fini);
  g_array_set_clear_func (self->faces,
                          (GDestroyNotify)crank_poly_struct3_fdata_fini);

  return self;
}

/**
 * crank_poly_struct3_ref:
 * @pstruct: A poly struct.
 *
 * Increases reference count for a poly struct.
 *
 * Returns: (transfer full): @pstruct with increased reference count.
 */
CrankPolyStruct3*
crank_poly_struct3_ref (CrankPolyStruct3 *pstruct)
{
  g_atomic_int_inc (& pstruct->_ref);
  return pstruct;
}

/**
 * crank_poly_struct3_unref:
 * @pstruct: A poly struct.
 *
 * Decrease reference count for a poly struct.
 */
void
crank_poly_struct3_unref (CrankPolyStruct3 *pstruct)
{
  if (g_atomic_int_dec_and_test (& pstruct->_ref))
    {
      g_array_unref (pstruct->vertices);
      g_array_unref (pstruct->edges);
      g_array_unref (pstruct->faces);
    }
}

/**
 * crank_poly_struct3_dup:
 * @pstruct: A Poly struct.
 *
 * Duplicates a poly struct.
 *
 * Returns: (transfer full): Duplicated poly struct.
 */
CrankPolyStruct3*
crank_poly_struct3_dup (CrankPolyStruct3 *pstruct)
{
  CrankPolyStruct3 *result = crank_poly_struct3_new ();
  guint i;

  g_array_set_size (result->vertices, pstruct->vertices->len);
  g_array_set_size (result->edges, pstruct->edges->len);
  g_array_set_size (result->faces, pstruct->faces->len);

  for (i = 0; i < pstruct->vertices->len; i++)
    {
      CrankPolyStruct3VData *vdata;
      CrankPolyStruct3VData *rdata;

      vdata = crank_poly_struct3_get_vdata (pstruct, i);
      rdata = crank_poly_struct3_get_vdata (result, i);

      rdata->nedges = vdata->nedges;
      rdata->edges = g_memdup (vdata->edges, sizeof (guint) * rdata->nedges);
      rdata->nfaces = vdata->nfaces;
      rdata->faces = g_memdup (vdata->faces, sizeof (guint) * rdata->nfaces);
    }

  for (i = 0; i < pstruct->edges->len; i++)
    {
      CrankPolyStruct3EData *edata;
      CrankPolyStruct3EData *rdata;

      edata = crank_poly_struct3_get_edata (pstruct, i);
      rdata = crank_poly_struct3_get_edata (result, i);

      rdata->vertices[0] = edata->vertices[0];
      rdata->vertices[1] = edata->vertices[1];
      rdata->nfaces = edata->nfaces;
      rdata->faces = g_memdup (edata->faces, sizeof (guint) * rdata->nfaces);
    }

  for (i = 0; i < pstruct->faces->len; i++)
    {
      CrankPolyStruct3FData *fdata;
      CrankPolyStruct3FData *rdata;

      fdata = crank_poly_struct3_get_fdata (pstruct, i);
      rdata = crank_poly_struct3_get_fdata (result, i);

      rdata->nvertices = fdata->nvertices;
      rdata->vertices = g_memdup (fdata->vertices, sizeof (guint) * rdata->nvertices);
      rdata->edges = g_memdup (fdata->edges, sizeof (guint) * rdata->nvertices);
    }

  return result;
}


//////// Properties ////////////////////////////////////////////////////////////

/**
 * crank_poly_struct3_get_nvertices:
 * @pstruct: A poly struct.
 *
 * Get number of vertices in a poly struct.
 *
 * Returns: Numbers of vertices.
 */
guint
crank_poly_struct3_get_nvertices (CrankPolyStruct3 *pstruct)
{
  return pstruct->vertices->len;
}

/**
 * crank_poly_struct3_get_nedges:
 * @pstruct: A poly struct.
 *
 * Get number of edges in a poly struct.
 *
 * Returns: Numbers of edges.
 */
guint
crank_poly_struct3_get_nedges (CrankPolyStruct3 *pstruct)
{
  return pstruct->edges->len;
}

/**
 * crank_poly_struct3_get_nfaces:
 * @pstruct: A Poly struct.
 *
 * Get number of faces in a poly struct.
 *
 * Returns: Number of faces.
 */
guint
crank_poly_struct3_get_nfaces (CrankPolyStruct3 *pstruct)
{
  return pstruct->faces->len;
}


//////// Getting associations //////////////////////////////////////////////////

/**
 * crank_poly_struct3_get_vertex_edges:
 * @pstruct: A Poly struct.
 * @vid: A vertex id.
 * @neids: (out): Number of edges associated to @vid.
 *
 * Gets edges associated to a vertex @vid.
 *
 * Returns: (array length=neids) (transfer full): Edges associated to a vertex.
 */
guint*
crank_poly_struct3_get_vertex_edges (CrankPolyStruct3 *pstruct,
                                     const guint       vid,
                                     guint            *neids)
{
  CrankPolyStruct3VData *vdata = crank_poly_struct3_get_vdata (pstruct, vid);

  *neids = vdata->nedges;
  return g_memdup (vdata->edges, sizeof (guint) * vdata->nedges);
}

/**
 * crank_poly_struct3_get_vertex_faces:
 * @pstruct: A Poly struct.
 * @vid: A vertex id.
 * @nfids: (out): Number of faces associated to @vid.
 *
 * Gets faces associated to a vertex @vid.
 *
 * Returns: (array length=nfids) (transfer full): Faces associated to a vertex.
 */
guint*
crank_poly_struct3_get_vertex_faces (CrankPolyStruct3 *pstruct,
                                     const guint       vid,
                                     guint            *nfids)
{
  CrankPolyStruct3VData *vdata = crank_poly_struct3_get_vdata (pstruct, vid);

  *nfids = vdata->nfaces;
  return g_memdup (vdata->faces, sizeof (guint) * vdata->nfaces);
}

/**
 * crank_poly_struct3_get_edge_vertices:
 * @pstruct: A Poly struct.
 * @eid: A Edge id.
 * @vids: (out) (array fixed-size=2): Vertices associated to an edge.
 *
 * Gets vertices associated to an edge @eid.
 */
void
crank_poly_struct3_get_edge_vertices (CrankPolyStruct3 *pstruct,
                                      const guint       eid,
                                      guint            *vids)
{
  CrankPolyStruct3EData *edata = crank_poly_struct3_get_edata (pstruct, eid);

  vids[0] = edata->vertices[0];
  vids[1] = edata->vertices[1];
}

/**
 * crank_poly_struct3_get_edge_faces:
 * @pstruct: A Poly struct.
 * @eid: A Edge id.
 * @nfids: (out): Number of faces associated to an edge.
 *
 * Gets faces associated to an edge @eid.
 *
 * Returns: (array length=nfids) (transfer full): Faces associated to an edge.
 */
guint*
crank_poly_struct3_get_edge_faces (CrankPolyStruct3 *pstruct,
                                   const guint       eid,
                                   guint            *nfids)
{
  CrankPolyStruct3EData *edata = crank_poly_struct3_get_edata (pstruct, eid);

  *nfids = edata->nfaces;
  return g_memdup (edata->faces, sizeof (guint) * edata->nfaces);
}

/**
 * crank_poly_struct3_get_face_vertices:
 * @pstruct: A Poly struct.
 * @fid: A Face id.
 * @nvids: (out): Number of vertices associated to a face.
 *
 * Gets vertices associated to a face @fid.
 *
 * Returns: (array length=nvids) (transfer full): Vertices associated to a face.
 */
guint*
crank_poly_struct3_get_face_vertices (CrankPolyStruct3 *pstruct,
                                      const guint       fid,
                                      guint            *nvids)
{
  CrankPolyStruct3FData *fdata = crank_poly_struct3_get_fdata (pstruct, fid);

  *nvids = fdata->nvertices;
  return g_memdup (fdata->vertices, sizeof (guint) * fdata->nvertices);
}

/**
 * crank_poly_struct3_get_face_edges:
 * @pstruct: A Poly struct.
 * @fid: A Face id.
 * @neids: (out): Number of edges associated to a face.
 *
 * Gets edges associated to a face @fid.
 *
 * Returns: (array length=neids) (transfer full): Edges associated to a face.
 */
guint*
crank_poly_struct3_get_face_edges    (CrankPolyStruct3 *pstruct,
                                      const guint       fid,
                                      guint            *neids)
{
  CrankPolyStruct3FData *fdata = crank_poly_struct3_get_fdata (pstruct, fid);

  *neids = fdata->nvertices;
  return g_memdup (fdata->edges, sizeof (guint) * fdata->nvertices);
}


/**
 * crank_poly_struct3_get_edge_by_vertices:
 * @pstruct: A Poly struct.
 * @vids: (array fixed-size=2): Vertices to get edges.
 *
 * Gets a edge, which has two vertices as end points.
 *
 * Returns: A edge associated to both vertices, or -1 if such does not exist.
 */
gint
crank_poly_struct3_get_edge_by_vertices (CrankPolyStruct3 *pstruct,
                                         const guint      *vids)
{
  CrankPolyStruct3VData *vdata = crank_poly_struct3_get_vdata (pstruct, vids[0]);

  guint i;

  for (i = 0; i < vdata->nedges; i++)
    {
      guint eid = vdata->edges[i];
      CrankPolyStruct3EData *edata = crank_poly_struct3_get_edata (pstruct, eid);

      if (edata->vertices[0] == vids[0])
        {
          if (edata->vertices[1] == vids[1])
            return eid;
        }
      else if (edata->vertices[0] == vids[1])
        {
          return eid;
        }
    }
  return -1;
}

/**
 * crank_poly_struct3_get_face_by_vertices:
 * @pstruct: A Poly struct.
 * @vertices: (array length=nvertices): Vertices associated to a face, in winding order.
 * @nvertices: Number of vertices.
 *
 * Gets a face, which has vertices as its vertices.
 *
 * Returns: A Face associated to all vertices or -1 if vertices are not in right
 *     order or if such does not exist.
 */
gint
crank_poly_struct3_get_face_by_vertices (CrankPolyStruct3 *pstruct,
                                         const guint      *vertices,
                                         guint             nvertices)
{
  CrankPolyStruct3VData *vdata;
  guint i, j, k;

  if (nvertices < 3)
    {
      g_warning ("A Valid face should has at least 3 vertices");
      return -1;
    }

  vdata = crank_poly_struct3_get_vdata (pstruct, vertices[0]);

  for (i = 0; i < vdata->nfaces; i++)
    {
      guint fid;
      CrankPolyStruct3FData *fdata;

      fid = vdata->faces[i];
      fdata = crank_poly_struct3_get_fdata (pstruct, fid);

      if (fdata->nvertices != nvertices)
        continue;

      if (crank_poly_struct3_is_rarray_equal (nvertices,
                                              fdata->vertices,
                                              vertices))
        return fid;
    }
  return -1;
}

/**
 * crank_poly_struct3_get_face_by_edges:
 * @pstruct: A Poly struct.
 * @edges: (array length=nedges): Edges associated to a face, in winding order.
 * @nedges: Number of edges.
 *
 * Gets a face, which has edges as ist edges.
 *
 * Returns: A Face associated to all edges or -1 if edges are not in right order
 *     or if such does not exist.
 */
gint
crank_poly_struct3_get_face_by_edges (CrankPolyStruct3 *pstruct,
                                      const guint      *edges,
                                      const guint       nedges)
{
  CrankPolyStruct3EData *edata;
  guint i;

  if (nedges < 3)
    {
      g_warning ("A Valid face should have at least 3 edges");
      return -1;
    }

  edata = crank_poly_struct3_get_edata (pstruct, edges[0]);

  for (i = 0; i < edata->nfaces; i++)
    {
      CrankPolyStruct3FData *fdata;
      guint fid = edata->faces[i];

      fdata = crank_poly_struct3_get_fdata (pstruct, fid);

      if (fdata->nvertices != nedges)
        continue;

      if (crank_poly_struct3_is_rarray_equal (nedges, edges, fdata->edges))
        return fid;
    }

  return -1;
}

//////// Manipulation //////////////////////////////////////////////////////////

/**
 * crank_poly_struct3_set_nvertices:
 * @pstruct: A Poly struct.
 * @nvertices: Number of vertices.
 *
 * Sets number of vertices for pstruct.
 */
void
crank_poly_struct3_set_nvertices (CrankPolyStruct3 *pstruct,
                                  const guint       nvertices)
{
  g_array_set_size (pstruct->vertices, nvertices);
}

/**
 * crank_poly_struct3_add_edge:
 * @pstruct: A Poly struct.
 * @a: A Vertex.
 * @b: Another vertex.
 *
 * Adds a edge or returns existing edge.
 *
 * Returns: edge id of newly created edge or existing one.
 */
gint
crank_poly_struct3_add_edge (CrankPolyStruct3 *pstruct,
                             const guint       a,
                             const guint       b)
{
  guint vids[2] = {a, b};
  gint eid = crank_poly_struct3_get_edge_by_vertices (pstruct, vids);

  if (eid == -1)
    {
      CrankPolyStruct3EData edata;
      CrankPolyStruct3VData *adata;
      CrankPolyStruct3VData *bdata;

      adata = crank_poly_struct3_get_vdata (pstruct, a);
      bdata = crank_poly_struct3_get_vdata (pstruct, b);

      eid = pstruct->edges->len;

      edata.vertices[0] = a;
      edata.vertices[1] = b;

      edata.nfaces = 0;
      edata.faces = NULL;

      adata->edges = g_renew (guint, adata->edges, adata->nedges + 1);
      adata->edges [adata->nedges] = eid;
      adata->nedges++;

      bdata->edges = g_renew (guint, bdata->edges, bdata->nedges + 1);
      bdata->edges [bdata->nedges] = eid;
      bdata->nedges++;

      g_array_append_val (pstruct->edges, edata);

    }

  return eid;
}

/**
 * crank_poly_struct3_add_face_vertices:
 * @pstruct: A Poly struct.
 * @nvertices: Number of vertices.
 * @...: Vertices to associate to a face.
 *
 * Adds a face or returns existing one.
 *
 * Note: This might return -1 for when this operation is invalid.
 *
 * Returns: Face id of newly created face or existing one.
 */
gint
crank_poly_struct3_add_face_vertices (CrankPolyStruct3 *pstruct,
                                      const guint       nvertices,
                                      ...)
{
  guint *vert_arr;

  va_list vararg;
  guint i;

  vert_arr = g_newa (guint, nvertices);

  va_start (vararg, nvertices);

  for (i = 0; i < nvertices; i++)
    vert_arr[i] = va_arg (vararg, guint);

  va_end (vararg);

  return crank_poly_struct3_add_face_vertex_array (pstruct, vert_arr, nvertices);
}

/**
 * crank_poly_struct3_add_face_edges:
 * @pstruct: A Poly struct.
 * @nedges: Number of edges.
 * @...: Edges to associate to a face.
 *
 * Adds a face or returns existing one.
 *
 * Note: This might return -1 for when this operation is invalid.
 *
 * Returns: Face id of newly created face or existing one.
 */
gint
crank_poly_struct3_add_face_edges (CrankPolyStruct3 *pstruct,
                                   const guint       nedges,
                                   ...)
{
  guint *edge_arr;

  va_list vararg;
  guint i;

  edge_arr = g_newa (guint, nedges);

  va_start (vararg, nedges);

  for (i = 0; i < nedges; i++)
    edge_arr[i] = va_arg (vararg, guint);

  va_end (vararg);

  return crank_poly_struct3_add_face_edge_array (pstruct, edge_arr, nedges);
}

/**
 * crank_poly_struct3_add_face_vertex_array:
 * @pstruct: A Poly struct.
 * @vertices: (array length=nvertices): Vertices to associate to a face.
 * @nvertices: Number of vertices.
 *
 * Adds a face or returns existing one.
 *
 * Note: This might return -1 for when this operation is invalid.
 *
 * Returns: Face id of newly created face or existing one.
 */
gint
crank_poly_struct3_add_face_vertex_array (CrankPolyStruct3 *pstruct,
                                          const guint      *vertices,
                                          guint             nvertices)
{
  gint fid;

  fid = crank_poly_struct3_get_face_by_vertices (pstruct, vertices, nvertices);

  if (fid == -1)
    {
      CrankPolyStruct3FData fdata;
      guint i, n1;

      fid = pstruct->faces->len;
      fdata.nvertices = nvertices;
      fdata.vertices = g_memdup (vertices, sizeof (guint) * nvertices);
      fdata.edges = g_new (guint, nvertices);

      n1 = nvertices - 1;

      for (i = 0; i < n1; i++)
        {
          fdata.edges[i] = crank_poly_struct3_add_edge (pstruct,
                                                        vertices[i],
                                                        vertices[i + 1]);
        }

      fdata.edges[n1] = crank_poly_struct3_add_edge (pstruct,
                                                    vertices[n1],
                                                    vertices[0]);


      for (i = 0; i < nvertices; i++)
        {
          CrankPolyStruct3VData *vdata;
          guint n;

          vdata = crank_poly_struct3_get_vdata (pstruct, vertices[i]);
          n = vdata->nfaces;

          vdata->nfaces++;
          vdata->faces = g_renew (guint, vdata->faces, vdata->nfaces);
          vdata->faces[n] = fid;
        }

      for (i = 0; i < nvertices; i++)
        {
          CrankPolyStruct3EData *edata;
          guint n;

          edata = crank_poly_struct3_get_edata (pstruct, fdata.edges[i]);
          n = edata->nfaces;

          edata->nfaces++;
          edata->faces = g_renew (guint, edata->faces, edata->nfaces);
          edata->faces[n] = fid;
        }
      g_array_append_val (pstruct->faces, fdata);
    }
  return fid;
}

/**
 * crank_poly_struct3_add_face_edge_array:
 * @pstruct: A Poly struct.
 * @edges: (array length=nedges): Edges to associate to a face.
 * @nedges: Number of edges.
 *
 * Adds a face or returns existing one.
 *
 * Note: This might return -1 for when this operation is invalid.
 *
 * Returns: Face id of newly created face or existing one.
 */
gint
crank_poly_struct3_add_face_edge_array (CrankPolyStruct3 *pstruct,
                                        const guint      *edges,
                                        const guint       nedges)
{
  gint fid;

  fid = crank_poly_struct3_get_face_by_edges (pstruct, edges, nedges);

  if (fid == -1)
    {
      CrankPolyStruct3FData fdata;
      guint i;

      fid = pstruct->faces->len;
      fdata.nvertices = nedges;
      fdata.vertices = g_new (guint, nedges);

      if (! crank_poly_struct3_edges_to_vertices (pstruct,
                                                  nedges,
                                                  edges,
                                                  fdata.vertices))
        {
          g_free (fdata.vertices);
          return -1;
        }

      fdata.edges = g_memdup (edges, sizeof (guint) * nedges);

      g_array_append_val (pstruct->faces, fdata);
    }
  return fid;
}


//////// Validation ////////////////////////////////////////////////////////////

/**
 * crank_poly_struct3_check_valid:
 * @pstruct: A Poly struct.
 *
 * Checks each elements are valid.
 *
 * Returns: Whether the poly struct is valid.
 */
gboolean
crank_poly_struct3_check_valid (CrankPolyStruct3 *pstruct)
{
  CrankPolyStruct3VData *vdata;
  CrankPolyStruct3EData *edata;
  CrankPolyStruct3FData *fdata;
  guint i, j;

  // Check vertices
  for (i = 0; i < pstruct->vertices->len; i++)
    {
      vdata = crank_poly_struct3_get_vdata (pstruct, i);

      for (j = 0; j < vdata->nedges; j++)
        {
          edata = crank_poly_struct3_get_edata (pstruct, vdata->edges[j]);
          if ((edata->vertices[0] != i) && (edata->vertices[1] != i))
            {
              return FALSE;
            }
        }

      for (j = 0; j < vdata->nfaces; j++)
        {
          fdata = crank_poly_struct3_get_fdata (pstruct, vdata->faces[j]);
          if (! crank_poly_struct3_array_contains (fdata->nvertices, fdata->vertices, i))
            {
              return FALSE;
            }
        }
    }

  // Check edges
  for (i = 0; i < pstruct->edges->len; i++)
    {
      edata = crank_poly_struct3_get_edata (pstruct, i);
      vdata = crank_poly_struct3_get_vdata (pstruct, edata->vertices[0]);
      if (! crank_poly_struct3_array_contains (vdata->nedges, vdata->edges, i))
        return FALSE;

      vdata = crank_poly_struct3_get_vdata (pstruct, edata->vertices[1]);
      if (! crank_poly_struct3_array_contains (vdata->nedges, vdata->edges, i))
        return FALSE;

      for (j = 0; j < edata->nfaces; j++)
        {
          fdata = crank_poly_struct3_get_fdata (pstruct, edata->faces[j]);
          if (! crank_poly_struct3_array_contains (fdata->nvertices, fdata->edges, i))
            return FALSE;
        }
    }

  // Check faces.
  for (i = 0; i < pstruct->faces->len; i++)
    {
      guint n1;

      fdata = crank_poly_struct3_get_fdata (pstruct, i);

      n1 = fdata->nvertices - 1;

      if (fdata->nvertices < 3)
        return FALSE;

      for (j = 0; j < n1; j++)
        {
          edata = crank_poly_struct3_get_edata (pstruct, fdata->edges[j]);

          if (edata->vertices[0] == fdata->vertices[j])
            {
              if (edata->vertices[1] != fdata->vertices[j + 1])
                return FALSE;
            }
          else if (edata->vertices[1] == fdata->vertices[j])
            {
              if (edata->vertices[0] != fdata->vertices[j + 1])
                return FALSE;
            }
          else
            {
              return FALSE;
            }
        }

      edata = crank_poly_struct3_get_edata (pstruct, fdata->edges[n1]);

      if (edata->vertices[0] == fdata->vertices[n1])
        {
          if (edata->vertices[1] != fdata->vertices[0])
            return FALSE;
        }
      else if (edata->vertices[0] == fdata->vertices[0])
        {
          if (edata->vertices[1] != fdata->vertices[n1])
            return FALSE;
        }
      else
        {
          return FALSE;
        }
    }

  return TRUE;
}
