#ifndef CRANKDEMORENDERABLETRIANGLE_H
#define CRANKDEMORENDERABLETRIANGLE_H

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

/* This is Part of demo */


#include <glib.h>
#include <glib-object.h>

#include <crankbase.h>
#include <crankcore.h>
#include <crankvisual.h>

//////// Type Definition ///////////////////////////////////////////////////////

#define CRANK_DEMO_TYPE_RENDERABLE_TRIANGLE (crank_demo_renderable_triangle_get_type())
G_DECLARE_FINAL_TYPE (CrankDemoRenderableTriangle,
                      crank_demo_renderable_triangle,
                      CRANK_DEMO, RENDERABLE_TRIANGLE,
                      CrankRenderablePrimitive)


//////// Constructor ///////////////////////////////////////////////////////////

CrankDemoRenderableTriangle*
crank_demo_renderable_triangle_new (CoglContext *context);

#endif
