#ifndef CRANKCAMERA_H
#define CRANKCAMERA_H

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
#error crankcamera.h cannot be included directly: include crankvisual.h
#endif

#include <glib.h>
#include <glib-object.h>
#include <cogl/cogl2-experimental.h>


#include "crankbase.h"
#include "crankcore.h"

#include "crankprojection.h"
#include "crankfilm.h"

//////// Type Declaration //////////////////////////////////////////////////////

#define CRANK_TYPE_CAMERA (crank_camera_get_type())
G_DECLARE_FINAL_TYPE (CrankCamera,
                      crank_camera,
                      CRANK, CAMERA,
                      GObject)

//////// Constructors //////////////////////////////////////////////////////////

CrankCamera *crank_camera_new (void);



//////// Properties ////////////////////////////////////////////////////////////

CrankFilm *crank_camera_get_film (CrankCamera *camera);

void       crank_camera_set_film (CrankCamera *camera,
                                  CrankFilm   *film);


CrankEntity3 *crank_camera_get_entity (CrankCamera *camera);

void          crank_camera_set_entity (CrankCamera  *camera,
                                       CrankEntity3 *entity);


CrankProjection *crank_camera_get_projection (CrankCamera *camera);

void             crank_camera_set_projection (CrankCamera     *camera,
                                              CrankProjection *projection);


CrankProjectionType crank_camera_get_projection_type (CrankCamera *camera);

void                crank_camera_set_projection_type (CrankCamera         *camera,
                                                      CrankProjectionType  projection_type);



gfloat  crank_camera_get_left (CrankCamera *camera);

void    crank_camera_set_left (CrankCamera  *camera,
                               const gfloat  cleft);


gfloat  crank_camera_get_right (CrankCamera *camera);

void    crank_camera_set_right (CrankCamera  *camera,
                                const gfloat  cright);



gfloat  crank_camera_get_bottom (CrankCamera *camera);

void    crank_camera_set_bottom (CrankCamera  *camera,
                                 const gfloat  cbottom);


gfloat  crank_camera_get_top (CrankCamera *camera);

void    crank_camera_set_top (CrankCamera *camera,
                              const gfloat ctop);



gfloat  crank_camera_get_near (CrankCamera *camera);

void    crank_camera_set_near (CrankCamera *camera,
                               const gfloat cnear);


gfloat  crank_camera_get_far (CrankCamera *camera);

void    crank_camera_set_far (CrankCamera *camera,
                              const gfloat cfar);

void    crank_camera_get_matrix (CrankCamera    *camera,
                                 CrankMatFloat4 *mat);

void    crank_camera_set_matrix (CrankCamera    *camera,
                                 CrankMatFloat4 *mat);

//////// Public Functions //////////////////////////////////////////////////////

void    crank_camera_ortho (CrankCamera *camera,
                            const gfloat left,
                            const gfloat right,
                            const gfloat bottom,
                            const gfloat top,
                            const gfloat nval,
                            const gfloat fval);


void    crank_camera_frustum (CrankCamera *camera,
                              const gfloat left,
                              const gfloat right,
                              const gfloat bottom,
                              const gfloat top,
                              const gfloat nval,
                              const gfloat fval);

void    crank_camera_perspective (CrankCamera *camera,
                                  const gfloat fovy,
                                  const gfloat aspect,
                                  const gfloat nval,
                                  const gfloat fval);


//////// Signal Emitter ////////////////////////////////////////////////////////

void    crank_camera_rendered (CrankCamera *camera);

#endif
