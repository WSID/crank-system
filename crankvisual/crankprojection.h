#ifndef CRANKPROJECTION_H
#define CRANKPROJECTION_H

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

#ifndef _CRANKVISUAL_INSIDE
#error crankprojection.h cannot be included directly: include crankvisual.h
#endif

#include <glib.h>
#include <glib-object.h>
#include <cogl/cogl2-experimental.h>

#include "crankbase.h"

//////// Type Declarations /////////////////////////////////////////////////////
typedef enum _CrankProjectionType CrankProjectionType;
typedef struct _CrankProjection CrankProjection;

/**
 * CrankProjectionType:
 * @CRANK_PROJECTION_ORTHO: Orthogonal projection.
 * @CRANK_PROJECTION_FRUSTUM: Frustum projection.
 *
 * Represents projection type.
 */

#define CRANK_TYPE_PROJECTION_TYPE (crank_projection_type_get_type())
GType crank_projection_type_get_type (void);
enum _CrankProjectionType
{
  CRANK_PROJECTION_ORTHO,
  CRANK_PROJECTION_FRUSTUM
};


/**
 * CrankProjection:
 * @_refc: A Reference Count.
 * @proj_type: A Projection type.
 * @left: Left of projection.
 * @right: Rigth of projection.
 * @bottom: Bottom of projection.
 * @top: Top of projection.
 * @near: Near of projection.
 * @far: Far of projection.
 * @matrix: A Projection matrix.
 * @matrix_t: Transpose of @matrix. This is for Cogl, which is column major.
 *
 * Represents a projection.
 */
#define CRANK_TYPE_PROJECTION (crank_projection_get_type())
struct _CrankProjection
{
  guint _refc;

  CrankProjectionType   proj_type;
  gfloat                left;
  gfloat                right;
  gfloat                bottom;
  gfloat                top;
  gfloat                near;
  gfloat                far;

  CrankMatFloat4        matrix;
  CrankMatFloat4        matrix_t;
};


//////// Constructor ///////////////////////////////////////////////////////////

CrankProjection *crank_projection_new (void);

CrankProjection *crank_projection_new_ortho (const gfloat left,
                                             const gfloat right,
                                             const gfloat bottom,
                                             const gfloat top,
                                             const gfloat near,
                                             const gfloat far);

CrankProjection *crank_projection_new_frustum (const gfloat left,
                                               const gfloat right,
                                               const gfloat bottom,
                                               const gfloat top,
                                               const gfloat near,
                                               const gfloat far);

CrankProjection *crank_projection_new_perspective (const gfloat fovy,
                                                   const gfloat aspect,
                                                   const gfloat near,
                                                   const gfloat far);

gpointer         crank_projection_ref (gpointer projection);

void             crank_projection_unref (gpointer projection);


//////// Setter ////////////////////////////////////////////////////////////////

void  crank_projection_set_identity (CrankProjection *projection);

void  crank_projection_set_ortho (CrankProjection *projection,
                                  const gfloat     left,
                                  const gfloat     right,
                                  const gfloat     bottom,
                                  const gfloat     top,
                                  const gfloat     near,
                                  const gfloat     far);

void  crank_projection_set_frustum (CrankProjection *projection,
                                    const gfloat     left,
                                    const gfloat     right,
                                    const gfloat     bottom,
                                    const gfloat     top,
                                    const gfloat     near,
                                    const gfloat     far);

void  crank_projection_set_perspective (CrankProjection *projection,
                                        const gfloat     fovy,
                                        const gfloat     aspect,
                                        const gfloat     near,
                                        const gfloat     far);

void  crank_projection_set_matrix (CrankProjection *projection,
                                   CrankMatFloat4  *matrix);


//////// Maintaining Constitency ///////////////////////////////////////////////

void  crank_projection_update_params (CrankProjection *projection);

void  crank_projection_update_matrix (CrankProjection *projection);


//////// GLSL Uniform Declaration //////////////////////////////////////////////

CoglSnippet* crank_projection_get_snippet_def (CoglSnippetHook hook);

void  crank_projection_get_uniform_locations (CoglPipeline *pipeline,
                                              const gchar  *uniform_name,
                                              gint         *locations);

void  crank_projection_set_uniform_value (CrankProjection *projection,
                                          CoglPipeline    *pipeline,
                                          const gint      *locations);

#endif
