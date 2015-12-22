#ifndef CRANKPOLYSTRUCT3_H
#define CRANKPOLYSTRUCT3_H

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
#error crankpolystruct3.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

//////// Type Declaration //////////////////////////////////////////////////////

#define CRANK_TYPE_POLY_STRUCT3 crank_poly_struct3_get_type()
GType   crank_poly_struct3_get_type (void);


typedef struct _CrankPolyStruct3 CrankPolyStruct3;

typedef struct _CrankPolyStruct3VData CrankPolyStruct3VData;

typedef struct _CrankPolyStruct3EData CrankPolyStruct3EData;

typedef struct _CrankPolyStruct3FData CrankPolyStruct3FData;

/**
 * CrankPolyStruct3:
 *
 * A Struct represents structure of polyhedral shape. In other words, it stores
 * relationship of vertices, edges, and faces.
 */


/**
 * CrankPolyStruct3VData:
 * @nedges: Number of edges.
 * @edges: (transfer full) (array length=nedges): Edges.
 * @nfaces: Number of faces.
 * @faces: (transfer full) (array length=nfaces): Faces
 *
 * Vertex data for #CrankPolyStruct3.
 *
 * Generally it is internal structure.
 */
struct _CrankPolyStruct3VData
{
  guint nedges;
  guint *edges;
  guint nfaces;
  guint *faces;
};

/**
 * CrankPolyStruct3EData:
 * @vertices: (array fixed-size=2): Vertices.
 * @nfaces: Number of faces.
 * @faces: (array length=nfaces): Faces
 *
 * Edge data for #CrankPolyStruct3.
 *
 * Generally it is internal structure.
 */
struct _CrankPolyStruct3EData
{
  guint vertices[2];
  guint nfaces;
  guint *faces;
};


/**
 * CrankPolyStruct3FData:
 * @nvertices: Number of vertices and edges.
 * @vertices: (array length=nvertices): Vertices
 * @edges: (array length=nvertices): Edges.
 *
 * Edge data for #CrankPolyStruct3.
 *
 * Generally it is internal structure.
 */
struct _CrankPolyStruct3FData
{
  guint nvertices;
  guint *vertices;
  guint *edges;
};


//////// Constructors //////////////////////////////////////////////////////////

CrankPolyStruct3   *crank_poly_struct3_new (void);

CrankPolyStruct3   *crank_poly_struct3_ref (CrankPolyStruct3 *pstruct);

void                crank_poly_struct3_unref (CrankPolyStruct3 *pstruct);


CrankPolyStruct3   *crank_poly_struct3_dup (CrankPolyStruct3 *pstruct);


//////// Properties ////////////////////////////////////////////////////////////

guint               crank_poly_struct3_get_nvertices (CrankPolyStruct3 *pstruct);

guint               crank_poly_struct3_get_nedges (CrankPolyStruct3 *pstruct);

guint               crank_poly_struct3_get_nfaces (CrankPolyStruct3 *pstruct);


//////// Getting associations //////////////////////////////////////////////////

guint              *crank_poly_struct3_get_vertex_edges (CrankPolyStruct3 *pstruct,
                                                         const guint       vid,
                                                         guint            *neids);

guint              *crank_poly_struct3_get_vertex_faces (CrankPolyStruct3 *pstruct,
                                                         const guint       vid,
                                                         guint            *nfids);

void                crank_poly_struct3_get_edge_vertices (CrankPolyStruct3 *pstruct,
                                                          const guint       eid,
                                                          guint            *vids);

guint              *crank_poly_struct3_get_edge_faces    (CrankPolyStruct3 *pstruct,
                                                          const guint       eid,
                                                          guint            *nfids);

guint              *crank_poly_struct3_get_face_vertices (CrankPolyStruct3 *pstruct,
                                                          const guint       fid,
                                                          guint            *nvids);

guint              *crank_poly_struct3_get_face_edges    (CrankPolyStruct3 *pstruct,
                                                          const guint       fid,
                                                          guint            *neids);


gint                crank_poly_struct3_get_edge_by_vertices (CrankPolyStruct3 *pstruct,
                                                             const guint      *vids);


//////// Manipulation //////////////////////////////////////////////////////////

void                crank_poly_struct3_set_nvertices (CrankPolyStruct3 *pstruct,
                                                      const guint       nvertices);

gint                crank_poly_struct3_add_edge (CrankPolyStruct3 *pstruct,
                                                 const guint       a,
                                                 const guint       b);

gint                crank_poly_struct3_add_face_vertices (CrankPolyStruct3 *pstruct,
                                                          const guint       nvertices,
                                                          ...);

gint                crank_poly_struct3_add_face_edges (CrankPolyStruct3 *pstruct,
                                                       guint            nedges,
                                                       ...);

gint                crank_poly_struct3_add_face_vertex_array (CrankPolyStruct3 *pstruct,
                                                              const guint      *vertices,
                                                              const guint       nvertices);

gint                crank_poly_struct3_add_face_edge_array (CrankPolyStruct3 *pstruct,
                                                            const guint      *edges,
                                                            const guint       nedges);


//////// Validation ////////////////////////////////////////////////////////////

gboolean            crank_poly_struct3_check_valid (CrankPolyStruct3 *pstruct);

#endif
