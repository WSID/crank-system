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

//////// Public functions //////////////////////////////////////////////////////

CrankFilm    *crank_film_new ();

void          crank_film_add_texture (CrankFilm   *film,
                                      CoglTexture *texture);

void          crank_film_remove_texture (CrankFilm   *film,
                                         CoglTexture *texture);

CoglTexture  *crank_film_get_texture (CrankFilm   *film,
                                      const guint  index);

guint         crank_film_get_n_textures (CrankFilm *film);


void          crank_film_allocate (CrankFilm  *film,
                                   GError    **error);



CoglOffscreen  *crank_film_get_framebuffer (CrankFilm   *film,
                                            const guint  index);

#endif
