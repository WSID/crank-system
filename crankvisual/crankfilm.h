#ifndef CRANKFILM_H
#define CRANKFILM_H

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
#error crankfilm.h cannot be included directly: include crankvisual.h
#endif

#include <glib.h>
#include <glib-object.h>
#include <cogl/cogl2-experimental.h>

//////// Type Declaration //////////////////////////////////////////////////////

#define CRANK_TYPE_FILM (crank_film_get_type())
G_DECLARE_FINAL_TYPE (CrankFilm,
                      crank_film,
                      CRANK, FILM,
                      GObject)

//////// Constructors //////////////////////////////////////////////////////////

CrankFilm    *crank_film_new (CoglContext  *cogl_context,
                              const guint   width,
                              const guint   height,
                              GError      **error);

//////// Properties ////////////////////////////////////////////////////////////

CoglContext  *crank_film_get_cogl_context (CrankFilm *film);

guint         crank_film_get_width (CrankFilm *film);

guint         crank_film_get_height(CrankFilm *film);


//////// Retrieve textures and framebuffers ////////////////////////////////////

CoglTexture    *crank_film_get_texture (CrankFilm   *film,
                                        const guint  index);

CoglOffscreen  *crank_film_get_framebuffer (CrankFilm   *film,
                                            const guint  index);

#endif