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

#ifndef CRANK_DEMO_MAT_PAD_H
#define CRANK_DEMO_MAT_PAD_H
 
#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <crankbase.h>

typedef struct _CrankDemoMatPad {
	GtkGrid		_parent;
} CrankDemoMatPad;

#define CRANK_DEMO_TYPE_MAT_PAD	crank_demo_mat_pad_get_type ()
G_DECLARE_FINAL_TYPE(
		CrankDemoMatPad,
		crank_demo_mat_pad,
		CRANK_DEMO,
		MAT_PAD,
		GtkGrid	)

//////// Constructors //////////////////////////////////////////////////////////

CrankDemoMatPad*	crank_demo_mat_pad_new (void);

CrankDemoMatPad*	crank_demo_mat_pad_new_with_size (guint	row, guint col);

CrankDemoMatPad*	crank_demo_mat_pad_new_with_mf (CrankMatFloatN*	mf);

CrankDemoMatPad*	crank_demo_mat_pad_new_with_mcf (CrankMatCplxFloatN*	mcf);

//////// Properties ////////////////////////////////////////////////////////////

guint				crank_demo_mat_pad_get_nrow (	CrankDemoMatPad*	self);

void				crank_demo_mat_pad_set_nrow (	CrankDemoMatPad*	self,
													guint				nrow);

guint				crank_demo_mat_pad_get_ncol (	CrankDemoMatPad*	self);

void				crank_demo_mat_pad_set_ncol (	CrankDemoMatPad*	self,
													guint				ncol);
													
void				crank_demo_mat_pad_get_mcf (	CrankDemoMatPad*	self,
													CrankMatCplxFloatN*	value	);
													
void				crank_demo_mat_pad_set_mcf (	CrankDemoMatPad*	self,
													CrankMatCplxFloatN*	value	);
													
//////// Signals ///////////////////////////////////////////////////////////////

void				crank_demo_mat_pad_action_failed (	CrankDemoMatPad*	self,
														GQuark				detail,
														const gchar*		message	);

//////// Methods ///////////////////////////////////////////////////////////////

void				crank_demo_mat_pad_append_row (CrankDemoMatPad*	self);

void				crank_demo_mat_pad_append_col (CrankDemoMatPad*	self);

void				crank_demo_mat_pad_remove_row (	CrankDemoMatPad*	self,
													guint				index );

void				crank_demo_mat_pad_remove_col (	CrankDemoMatPad*	self,
													guint				index );

void				crank_demo_mat_pad_resize (	CrankDemoMatPad*	self,
												guint				nrow,
												guint				ncol	);

void				crank_demo_mat_pad_negate 	(	CrankDemoMatPad*	self );

void				crank_demo_mat_pad_inverse	(	CrankDemoMatPad*	self );

void				crank_demo_mat_pad_transpose (	CrankDemoMatPad*	self );


GtkEntry*			crank_demo_mat_pad_get_entry (	CrankDemoMatPad*	self,
													guint				row,
													guint				col );



#endif
