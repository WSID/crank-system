#ifndef CRANKRENDERLAYERCLUSTER_H
#define CRANKRENDERLAYERCLUSTER_H

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
#error crankrenderlayercluster.h cannot be included directly: include crankvisual.h
#endif

#include <glib.h>
#include <glib-object.h>
#include <gio/gio.h>

#include "crankbase.h"
#include "crankshape.h"
#include "crankcore.h"

#include "crankprojection.h"
#include "crankvisible.h"

#include "crankrenderlayer.h"

G_BEGIN_DECLS

//////// Type Declarations /////////////////////////////////////////////////////

#define CRANK_TYPE_RENDER_LAYER_CLUSTER (crank_render_layer_cluster_get_type())
G_DECLARE_FINAL_TYPE (CrankRenderLayerCluster,
                      crank_render_layer_cluster,
                      CRANK, RENDER_LAYER_CLUSTER,
                      CrankRenderLayer)

/**
 * CrankRenderLayerCluster:
 *
 * Represents a layer backed with clusters.
 */
struct _CrankRenderLayerCluster {
  CrankRenderLayer _parent;

  guint           width;
  guint           height;
  guint           depth;

  CrankCellSpace3 *cluster;

  CrankPlane3     *planes_w;
  CrankPlane3     *planes_h;
  CrankPlane3     *planes_d;
};









//////// Constructors //////////////////////////////////////////////////////////

CrankRenderLayerCluster *crank_render_layer_cluster_new     (const guint  width,
                                                             const guint  height,
                                                             const guint  depth);










//////// Properties ////////////////////////////////////////////////////////////

guint   crank_render_layer_cluster_get_width    (CrankRenderLayerCluster*   layer);

guint   crank_render_layer_cluster_get_height   (CrankRenderLayerCluster*   layer);

guint   crank_render_layer_cluster_get_depth    (CrankRenderLayerCluster*   layer);








//////// Prepare for projection ////////////////////////////////////////////////

void        crank_render_layer_cluster_prepare      (CrankRenderLayerCluster *layer,
                                                     CrankTrans3             *position,
                                                     CrankProjection         *projection);








//////// Operations ////////////////////////////////////////////////////////////

void        crank_render_layer_cluster_add_entity   (CrankRenderLayerCluster *layer,
                                                     CrankPairPointer        *pair);

GPtrArray*  crank_render_layer_cluster_get_array    (CrankRenderLayerCluster *layer,
                                                     const guint              wi,
                                                     const guint              hi,
                                                     const guint              di);

void        crank_render_layer_cluster_clear        (CrankRenderLayerCluster *layer);






G_END_DECLS

#endif
