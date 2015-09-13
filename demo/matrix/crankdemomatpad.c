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

#include <stdlib.h>
#include <math.h>

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <crankbase.h>

#include "crankdemomatpad.h"

typedef struct _CrankDemoMatPadPrivate {
	guint	nrow;
	guint	ncol;

	// Actions and menus
	GSimpleActionGroup*	agroup;
	GMenu*				menuset;

	// Adjustments
	GtkAdjustment*	resize_adjrow;
	GtkAdjustment*	resize_adjcol;

	// A UI Components
	GtkMenuButton*	setter;		// Menu Button to set matrix
	GtkButton*		addrow;		// Add row.
	GtkButton*		addcol;		// Add col
	GtkMenuButton*	resize;		// Popover Button to set size
	GtkPopover*		resize_popover;
	
	// Actions
	GList*			action_list;
} CrankDemoMatPadPrivate;


enum {
	PROP_0,
	PROP_NROW,
	PROP_NCOL,
	PROP_MCF,
	PROP_COUNT
};

static GParamSpec* pspecs [PROP_COUNT] = {NULL};



G_DEFINE_TYPE_WITH_PRIVATE (CrankDemoMatPad, crank_demo_mat_pad, GTK_TYPE_GRID)



//////// Virtual Functions overriden from super class //////////////////////////

static void _g_object_get_property (GObject*		self_g_object,
									guint			property_id,
									GValue*			value,
									GParamSpec*		pspec	);
									
static void _g_object_set_property (GObject*		self_g_object,
									guint			property_id,
									const GValue*	value,
									GParamSpec*		pspec	);

static void _g_object_constructed (GObject*	self_g_object);


//////// Action Entries ////////////////////////////////////////////////////////

static void activate_zero (	GSimpleAction*	action,
							GVariant*		parameter,
							gpointer		user_data	);

static void activate_identity (	GSimpleAction*	action,
								GVariant*		parameter,
								gpointer		user_data	);

static void activate_negate (	GSimpleAction*	action,
								GVariant*		parameter,
								gpointer		user_data	);

static void activate_inverse (	GSimpleAction*	action,
								GVariant*		parameter,
								gpointer		user_data	);

static void activate_transpose (	GSimpleAction*	action,
									GVariant*		parameter,
									gpointer		user_data	);

static void enable_nonempty	(	GSimpleAction*	action,
								GVariant*		value,
								gpointer		user_data	);

static void enable_square	(	GSimpleAction*	action,
								GVariant*		value,
								gpointer		user_data	);


static GActionEntry actions[] = {
	{"zero",		activate_zero, NULL, "@(uu) (1, 1)", enable_nonempty},
	{"identity",	activate_identity, NULL, "@(uu) (1, 1)", enable_square},
	{"negate",		activate_negate, NULL, "@(uu) (1, 1)", enable_nonempty},
	{"inverse",		activate_inverse, NULL, "@(uu) (1, 1)", enable_square},
	{"transpose",	activate_transpose, NULL, "@(uu) (1, 1)", enable_nonempty},
	{NULL}
};

//////// Private Functions /////////////////////////////////////////////////////

static GtkEntry*	create_entry (CrankDemoMatPad*			pad);

static GtkButton*	create_row_remover (CrankDemoMatPad*	pad);

static GtkButton*	create_col_remover (CrankDemoMatPad*	pad);

static void			on_size_change ( CrankDemoMatPad*		pad);

static void			parse_complex (	const gchar*	string,
									CrankCplxFloat*	cplx	);

static gchar*		str_complex ( CrankCplxFloat*	cplx	);

static void			cb_remove_row (	GtkButton*	button,
									gpointer	user_data	);
									
static void			cb_remove_col (	GtkButton*	button,
									gpointer	user_data	);
									
static void			cb_show_resize (GtkWidget*	widget,
									gpointer	user_data	);

static void			cb_resize_accept (GtkButton*	widget,
									gpointer		user_data	);



//////// Implementations ///////////////////////////////////////////////////////

//////// Constructors //////////////////////////////////////////////////////////

/*  crank_demo_mat_pad_new:
 * 
 * Constructs a matrix pad, which holds 1x1 zero matrix.
 *
 * Returns: (transfer full): A new matrix pad.
 */
CrankDemoMatPad*
crank_demo_mat_pad_new (void)
{
	return CRANK_DEMO_MAT_PAD (g_object_new (CRANK_DEMO_TYPE_MAT_PAD, NULL));
}

/*  crank_demo_mat_pad_new_with_size:
 * @row: Row count.
 * @col: Col count.
 * 
 * Constructs a matrix pad, which holds a zero matrix.
 *
 * Returns: (transfer full): A new matrix pad.
 */
CrankDemoMatPad*
crank_demo_mat_pad_new_with_size (guint	row, guint col)
{
	return CRANK_DEMO_MAT_PAD (g_object_new (CRANK_DEMO_TYPE_MAT_PAD,
			"nrow", row, "ncol", col, NULL));
}

/*  crank_demo_mat_pad_new_with_mf:
 * @mf: A Matrix
 * 
 * Constructs a matrix pad, which holds a given matrix.
 *
 * Returns: (transfer full): A new matrix pad.
 */
CrankDemoMatPad*	crank_demo_mat_pad_new_with_mf (CrankMatFloatN*	mf);


/*  crank_demo_mat_pad_new_with_mcf:
 * @mf: A Matrix
 * 
 * Constructs a matrix pad, which holds a given matrix.
 *
 * Returns: (transfer full): A new matrix pad.
 */
CrankDemoMatPad*	crank_demo_mat_pad_new_with_mcf (CrankMatCplxFloatN*	mcf)
{
	return CRANK_DEMO_MAT_PAD (g_object_new (CRANK_DEMO_TYPE_MAT_PAD,
			"mcf", mcf, NULL));
}

//////// Properties ////////////////////////////////////////////////////////////

/*  crank_demo_mat_pad_get_nrow:
 * @self: A Matrix pad.
 *
 * Gets number of rows.
 *
 * Returns: Row count of a matrix pad.
 */
guint
crank_demo_mat_pad_get_nrow (	CrankDemoMatPad*	self)
{
	CrankDemoMatPadPrivate*	priv = crank_demo_mat_pad_get_instance_private (self);
	
	return priv->nrow;
}

/*  crank_demo_mat_pad_set_nrow:
 * @self: A Matrix pad.
 * @nrow: Row count.
 *
 * Sets number of rows. When decreasing row count, the rows are removed from the
 * end, When increasing row count, new rows are filled with 0. 
 */
void
crank_demo_mat_pad_set_nrow (	CrankDemoMatPad*	self,
								guint				nrow)
{
	CrankDemoMatPadPrivate*	priv = crank_demo_mat_pad_get_instance_private (self);
	
	if (priv->nrow < nrow) {
		while (priv->nrow < nrow) crank_demo_mat_pad_append_row (self);
	}
	else if (priv->nrow > nrow) {
		while (priv->nrow > nrow) crank_demo_mat_pad_remove_row (self, nrow);
	}
}

/*  crank_demo_mat_pad_get_ncol:
 * @self: A Matrix pad.
 *
 * Gets number of columns.
 *
 * Returns: Column count of a matrix pad.
 */
guint
crank_demo_mat_pad_get_ncol (	CrankDemoMatPad*	self)
{
	CrankDemoMatPadPrivate*	priv = crank_demo_mat_pad_get_instance_private (self);
	
	return priv->ncol;
}

/*  crank_demo_mat_pad_set_ncol:
 * @self: A Matrix pad.
 * @ncol: Row count.
 *
 * Sets number of columns. When decreasing column count, the columns are removed
 * from the end, When increasing column count, new columns are filled with 0. 
 */
void
crank_demo_mat_pad_set_ncol (	CrankDemoMatPad*	self,
								guint				ncol)
{
	CrankDemoMatPadPrivate*	priv = crank_demo_mat_pad_get_instance_private (self);
	
	if (priv->ncol < ncol) {
		while (priv->ncol < ncol) crank_demo_mat_pad_append_col (self);
	}
	else if (priv->ncol > ncol) {
		while (priv->ncol > ncol) crank_demo_mat_pad_remove_col (self, ncol);
	}
}

/*  crank_demo_mat_pad_get_mcf:
 * @self: A Matrix pad.
 * @value: (out): A Matrix that pad holds.
 *
 * Retreive value of a matrix pad as a complex matrix.
 */
void
crank_demo_mat_pad_get_mcf (CrankDemoMatPad*	self,
							CrankMatCplxFloatN*	value	)
{
	guint i;
	guint j;
	
	guint	nrow = crank_demo_mat_pad_get_nrow (self);
	guint	ncol = crank_demo_mat_pad_get_ncol (self);
	
	crank_mat_cplx_float_n_init_fill_uc (value, nrow, ncol, 0.0f, 0.0f);
	
	
	// Filling Matrix with each text in GtkEntry.
	// Elements pointers can be obtained by crank_mat_cplx_float_n_peek()
	// which can be used to store vlaues.
	
	for (i = 0; i < nrow; i++) {
		for (j = 0; j < ncol; j++) {
			GtkEntry*		entry = crank_demo_mat_pad_get_entry (self, i, j);
			
			parse_complex (	gtk_entry_get_text (entry),
							crank_mat_cplx_float_n_peek (value, i, j) );
		}
	}
}

/*  crank_demo_mat_pad_set_mcf:
 * @self: A Matrix pad.
 * @value: A Matrix.
 *
 * Set value of a matrix pad by a complex matrix.
 */
void
crank_demo_mat_pad_set_mcf (	CrankDemoMatPad*	self,
								CrankMatCplxFloatN*	value	)
{
	guint i;
	guint j;
	
	guint	nrow = value->rn;
	guint	ncol = value->cn;
	
	crank_demo_mat_pad_resize (self, nrow, ncol);
	
	
	// Filling GtkEntry with each elements.
	// Elements pointers can be obtained by crank_mat_cplx_float_n_peek()
	
	for (i = 0; i < nrow; i++) {
		for (j = 0; j < ncol; j++) {
			GtkEntry*		entry = crank_demo_mat_pad_get_entry (self, i, j);
			CrankCplxFloat*	element = crank_mat_cplx_float_n_peek (value, i, j);
			gchar*			element_str;
			
			if (crank_cplx_float_is_zero (element))
				gtk_entry_set_text (entry, "");
			else {
				element_str = str_complex (element);
				gtk_entry_set_text (entry, element_str);
				g_free (element_str);
			}
		}
	}
}

//////// Methods ///////////////////////////////////////////////////////////////

/*  crank_demo_mat_pad_append_row:
 * @self: A Matrix.
 *
 * Append a row filled with 0.
 */
void
crank_demo_mat_pad_append_row (CrankDemoMatPad*	self)
{
	CrankDemoMatPadPrivate*	priv = crank_demo_mat_pad_get_instance_private (self);
	
	GtkGrid* self_gtk_grid = GTK_GRID (self);
	
	guint i;
	// Add row at the end of matrix.
	
	gtk_grid_insert_row (self_gtk_grid, priv->nrow + 1);
	
	for (i = 0; i < priv->ncol; i++) {
		gtk_grid_attach (self_gtk_grid, GTK_WIDGET (create_entry (self)),
				i + 1, priv->nrow + 1, 1, 1	);
	}
	
	gtk_grid_attach (self_gtk_grid, GTK_WIDGET (create_row_remover (self)),
			0, priv->nrow + 1, 1, 1);
	
	gtk_container_child_set (GTK_CONTAINER(self_gtk_grid), GTK_WIDGET (priv->addcol),
			"height", priv->nrow + 2, NULL);
	
	priv->nrow++;
	
	on_size_change (self);
	g_object_notify_by_pspec (G_OBJECT (self), pspecs[PROP_NROW]);
}

/*  crank_demo_mat_pad_append_col:
 * @self: A Matrix.
 *
 * Append a column filled with 0.
 */
void
crank_demo_mat_pad_append_col (CrankDemoMatPad*	self)
{
	CrankDemoMatPadPrivate*	priv = crank_demo_mat_pad_get_instance_private (self);
	
	GtkGrid* self_gtk_grid = GTK_GRID (self);
	
	guint i;
	// Add row at the end of matrix.
	
	gtk_grid_insert_column (self_gtk_grid, priv->ncol + 1);
	
	for (i = 0; i < priv->nrow; i++) {
		gtk_grid_attach (self_gtk_grid, GTK_WIDGET (create_entry (self)),
				priv->ncol + 1, i + 1, 1, 1	);
	}
	
	gtk_grid_attach (self_gtk_grid, GTK_WIDGET (create_col_remover (self)),
			priv->ncol + 1, 0, 1, 1);
	
	gtk_container_child_set (GTK_CONTAINER(self_gtk_grid), GTK_WIDGET (priv->addrow),
			"width", priv->ncol + 2, NULL);
	
	priv->ncol++;
	
	on_size_change (self);
	g_object_notify_by_pspec (G_OBJECT (self), pspecs[PROP_NCOL]);
}

/*  crank_demo_mat_pad_remove_row:
 * @self: A Matrix.
 * @index: A index to remove row.
 *
 * Remove a row at the @index.
 */
void
crank_demo_mat_pad_remove_row (	CrankDemoMatPad*	self,
								guint				index )
{
	CrankDemoMatPadPrivate*	priv = crank_demo_mat_pad_get_instance_private (self);
	
	gtk_grid_remove_row (GTK_GRID (self), index + 1);
	priv->nrow --;
	
	on_size_change (self);
	g_object_notify_by_pspec (G_OBJECT (self), pspecs[PROP_NROW]);
}

/*  crank_demo_mat_pad_remove_col:
 * @self: A Matrix.
 * @index: A index to remove column.
 *
 * Remove a column at the @index.
 */
void
crank_demo_mat_pad_remove_col (	CrankDemoMatPad*	self,
								guint				index )
{
	CrankDemoMatPadPrivate*	priv = crank_demo_mat_pad_get_instance_private (self);
	
	gtk_grid_remove_column (GTK_GRID (self), index + 1);
	priv->ncol --;
	
	on_size_change (self);
	g_object_notify_by_pspec (G_OBJECT (self), pspecs[PROP_NCOL]);
}

/*  crank_demo_mat_pad_resize:
 * @self: A Matrix.
 * @nrow: Number of rows.
 * @ncol: Number of columns.
 *
 * Resize a matrix.
 */
void
crank_demo_mat_pad_resize (	CrankDemoMatPad*	self,
							guint				nrow,
							guint				ncol	)
{
	crank_demo_mat_pad_set_nrow (self, nrow);
	crank_demo_mat_pad_set_ncol (self, ncol);
}

/*  crank_demo_mat_pad_negate:
 * @self: A Matrix.
 *
 * Negate a matrix pad.
 */
void
crank_demo_mat_pad_negate (	CrankDemoMatPad*	self )
{
	CrankMatCplxFloatN	mcf;
	
	crank_demo_mat_pad_get_mcf (self, &mcf);
	
	// A Matrix can be negated by ..._neg[_self] () functions.
	crank_mat_cplx_float_n_neg_self (&mcf);
	
	crank_demo_mat_pad_set_mcf (self, &mcf);
	
	crank_mat_cplx_float_n_fini (&mcf);
}

/*  crank_demo_mat_pad_inverse:
 * @self: A Matrix.
 *
 * Inverse a matrix pad.
 */
void
crank_demo_mat_pad_inverse (	CrankDemoMatPad*	self )
{
	CrankMatCplxFloatN	mcf;
	
	crank_demo_mat_pad_get_mcf (self, &mcf);
	
	// A Matrix can be inversed by ..._inverse[_self] () functions.
	crank_mat_cplx_float_n_inverse_self (&mcf);
	
	crank_demo_mat_pad_set_mcf (self, &mcf);
	
	crank_mat_cplx_float_n_fini (&mcf);
}

/*  crank_demo_mat_pad_transpose:
 * @self: A Matrix.
 *
 * Transpose a matrix pad.
 */
void
crank_demo_mat_pad_transpose (	CrankDemoMatPad*	self )
{
	CrankMatCplxFloatN	mcf;
	
	crank_demo_mat_pad_get_mcf (self, &mcf);
	
	// A Matrix can be transposed by ..._transpose[_self] () functions.
	crank_mat_cplx_float_n_transpose_self (&mcf);
	
	crank_demo_mat_pad_set_mcf (self, &mcf);
	
	crank_mat_cplx_float_n_fini (&mcf);
}

/*  crank_demo_mat_pad_get_entry:
 * @self: A Matrix.
 *
 * Transpose a matrix pad.
 *
 * Returns: A #GtkEntry for given position.
 */
GtkEntry*
crank_demo_mat_pad_get_entry (	CrankDemoMatPad*	self,
								guint				row,
								guint				col )
{
	GtkGrid*	self_gtk_grid = GTK_GRID (self);
	
	return GTK_ENTRY (gtk_grid_get_child_at (self_gtk_grid, col + 1, row + 1) );
}



//////// Instance, Class Init Functions ////////////////////////////////////////

static void
crank_demo_mat_pad_init (CrankDemoMatPad*	self)
{
	CrankDemoMatPadPrivate*	priv = crank_demo_mat_pad_get_instance_private (self);
	
	priv->nrow = 1;
	priv->ncol = 1;
	
	gtk_widget_init_template (GTK_WIDGET (self));
}

static void
crank_demo_mat_pad_class_init (CrankDemoMatPadClass*	c)
{
	GObjectClass*	c_g_object;
	GtkWidgetClass*	c_gtk_widget;
	
	c_g_object = G_OBJECT_CLASS (c);
	c_g_object->get_property = _g_object_get_property;
	c_g_object->set_property = _g_object_set_property;
	c_g_object->constructed = _g_object_constructed;
	
	pspecs[PROP_NROW] = g_param_spec_uint ("nrow", "nrow", "Number of rows",
			1, 128, 1,
			G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS );
			
	pspecs[PROP_NCOL] = g_param_spec_uint ("ncol", "ncol", "Number of columns",
			1, 128, 1,
			G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS );
			
	pspecs[PROP_MCF] = g_param_spec_boxed ("mcf", "matrix-complex", "Complex float matrix value",
			CRANK_TYPE_MAT_CPLX_FLOAT_N,
			G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS );
	
	g_object_class_install_properties (c_g_object, PROP_COUNT, pspecs);
	
	
	c_gtk_widget = GTK_WIDGET_CLASS (c);
	gtk_widget_class_set_template_from_resource (c_gtk_widget, "/crank/demo/matrix/crankdemomatpad.ui");
	
	gtk_widget_class_bind_template_child_private (c_gtk_widget, CrankDemoMatPad, resize_adjrow);
	gtk_widget_class_bind_template_child_private (c_gtk_widget, CrankDemoMatPad, resize_adjcol);
	
	gtk_widget_class_bind_template_child_private (c_gtk_widget, CrankDemoMatPad, setter);
	gtk_widget_class_bind_template_child_private (c_gtk_widget, CrankDemoMatPad, addrow);
	gtk_widget_class_bind_template_child_private (c_gtk_widget, CrankDemoMatPad, addcol);
	gtk_widget_class_bind_template_child_private (c_gtk_widget, CrankDemoMatPad, resize);
	gtk_widget_class_bind_template_child_private (c_gtk_widget, CrankDemoMatPad, resize_popover);
	
	gtk_widget_class_bind_template_callback (c_gtk_widget, cb_show_resize);
	gtk_widget_class_bind_template_callback (c_gtk_widget, cb_resize_accept);
	gtk_widget_class_bind_template_callback (c_gtk_widget, crank_demo_mat_pad_append_row);
	gtk_widget_class_bind_template_callback (c_gtk_widget, crank_demo_mat_pad_append_col);
}




//////// Virtual Function overriden from super class ///////////////////////////

static void
_g_object_get_property (GObject*		self_g_object,
						guint			property_id,
						GValue*			value,
						GParamSpec*		pspec)
{
	CrankDemoMatPad* self = CRANK_DEMO_MAT_PAD (self_g_object);

	switch (property_id) {
	case PROP_NROW:
		g_value_set_uint (value, crank_demo_mat_pad_get_nrow (self));
		break;
	case PROP_NCOL:
		g_value_set_uint (value, crank_demo_mat_pad_get_ncol (self));
		break;
	
	case PROP_MCF:
		{
			CrankMatCplxFloatN*	mat = g_new (CrankMatCplxFloatN, 1);
			crank_demo_mat_pad_get_mcf (self, mat);
			g_value_take_boxed (value, mat);
		}
		break;
		
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(self_g_object, property_id, pspec);
	}
}

static void
_g_object_set_property (GObject*		self_g_object,
						guint			property_id,
						const GValue*	value,
						GParamSpec*		pspec)
{
	CrankDemoMatPad* self = CRANK_DEMO_MAT_PAD (self_g_object);
	CrankDemoMatPadPrivate*	priv =
		crank_demo_mat_pad_get_instance_private (self);

	switch (property_id) {
	case PROP_NROW:
		crank_demo_mat_pad_set_nrow (self, g_value_get_uint (value));
		break;
	case PROP_NCOL:
		crank_demo_mat_pad_set_ncol (self, g_value_get_uint (value));
		break;
	
	case PROP_MCF:
		crank_demo_mat_pad_set_mcf (self, (CrankMatCplxFloatN*) g_value_get_boxed (value));
		break;
	
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(self_g_object, property_id, pspec);
	}
}

static void
_g_object_constructed (GObject*	self_g_object)
{
	CrankDemoMatPad* self = CRANK_DEMO_MAT_PAD (self_g_object);
	CrankDemoMatPadPrivate*	priv =
		crank_demo_mat_pad_get_instance_private (self);
	
	guint	i;
	guint	j;
	
	G_OBJECT_CLASS (crank_demo_mat_pad_parent_class)->constructed (self_g_object);
	
	GtkGrid*	self_gtk_grid = GTK_GRID (self_g_object);
	
	// Build a action group for menu.
	priv->agroup = g_simple_action_group_new ();
	g_action_map_add_action_entries (G_ACTION_MAP (priv->agroup), actions, -1, self);
	gtk_widget_insert_action_group (GTK_WIDGET (self), "pad", G_ACTION_GROUP (priv->agroup));
	
	
	
	// Adds entry for elements.
	for (i = 0; i < priv->nrow; i++) {
		for (j = 0; j < priv->ncol; j++) {
			gtk_grid_attach (self_gtk_grid, GTK_WIDGET (create_entry (self)),
					j + 1, i + 1, 1, 1	);
		}
	}
	
	// Adds remove buttons for each row and cols.
	for (i = 0; i < priv->nrow; i++) {
		gtk_grid_attach (self_gtk_grid, GTK_WIDGET (create_row_remover (self)),
				0, 1 + i, 1, 1);
	}
	
	for (i = 0; i < priv->ncol; i++) {
		gtk_grid_attach (self_gtk_grid, GTK_WIDGET (create_col_remover (self)), i + 1, 0, 1, 1);
	}
	
	
	priv->action_list = NULL;
	for (i = 0; actions[i].name != NULL; i++) {
		priv->action_list = g_list_append (priv->action_list,
			g_action_map_lookup_action (G_ACTION_MAP (priv->agroup), actions[i].name) );
	}
}



//////// Action Entries ////////////////////////////////////////////////////////

static void
activate_zero (	GSimpleAction*	action,
				GVariant*		parameter,
				gpointer		user_data	)
{
	CrankDemoMatPad*	self = CRANK_DEMO_MAT_PAD (user_data);
	
	guint	nrow = crank_demo_mat_pad_get_nrow (self);
	guint	ncol = crank_demo_mat_pad_get_ncol (self);
	
	guint i;
	guint j;
	
	for (i = 0; i < nrow; i++) {
		for (j = 0; j < ncol; j++) {
			GtkEntry*	entry = crank_demo_mat_pad_get_entry (self, i, j);
			
			gtk_entry_set_text (entry, "");
		}
	}
}

static void
activate_identity (	GSimpleAction*	action,
					GVariant*		parameter,
					gpointer		user_data	)
{
	CrankDemoMatPad*	self = CRANK_DEMO_MAT_PAD (user_data);
	
	guint	nrow = crank_demo_mat_pad_get_nrow (self);
	guint	ncol = crank_demo_mat_pad_get_ncol (self);
	
	guint	n = MAX (nrow, ncol);
	
	guint i;
	guint j;
	
	crank_demo_mat_pad_resize (self, n, n);
	
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			GtkEntry*	entry = crank_demo_mat_pad_get_entry (self, i, j);
			
			gtk_entry_set_text (entry, (i == j) ? "1" : "");
		}
	}
}

static void
activate_negate (		GSimpleAction*	action,
						GVariant*		parameter,
						gpointer		user_data	)
{
	CrankDemoMatPad*	self = CRANK_DEMO_MAT_PAD (user_data);
	
	crank_demo_mat_pad_negate (self);
}

static void
activate_inverse (		GSimpleAction*	action,
						GVariant*		parameter,
						gpointer		user_data	)
{
	CrankDemoMatPad*	self = CRANK_DEMO_MAT_PAD (user_data);
	
	crank_demo_mat_pad_inverse (self);
}


static void
activate_transpose (	GSimpleAction*	action,
						GVariant*		parameter,
						gpointer		user_data	)
{
	CrankDemoMatPad*	self = CRANK_DEMO_MAT_PAD (user_data);
	
	crank_demo_mat_pad_transpose (self);
}


static void
enable_nonempty	(	GSimpleAction*	action,
					GVariant*		value,
					gpointer		user_data	)
{
	guint	rn;
	guint	cn;
	
	//g_return_if_fail ( g_variant_n_children (value) != 2 );
	
	g_variant_get (value, "(uu)", &rn, &cn);
	
	g_simple_action_set_enabled (action, (rn != 0) && (cn != 0));
}

static void
enable_square	(	GSimpleAction*	action,
					GVariant*		value,
					gpointer		user_data	)
{
	guint	rn;
	guint	cn;
	
	//g_return_if_fail ( g_variant_n_children (value) != 2 );
	
	g_variant_get (value, "(uu)", &rn, &cn);
	
	g_simple_action_set_enabled (action, (rn != 0) && (cn != 0) && (rn == cn));
}
//////// Private functions /////////////////////////////////////////////////////

static GtkEntry*
create_entry (CrankDemoMatPad* self)
{
	GtkEntry*	entry = GTK_ENTRY (gtk_entry_new ());
	
	gtk_entry_set_placeholder_text (entry, "0");
	gtk_entry_set_width_chars (entry, 10);

	gtk_widget_show (GTK_WIDGET (entry));
	
	return entry;
}

static GtkButton*
create_row_remover (CrankDemoMatPad* self)
{
	GtkButton*	button = GTK_BUTTON (gtk_button_new ());
	GtkImage*	image = GTK_IMAGE (gtk_image_new_from_icon_name (
			"list-remove-symbolic", GTK_ICON_SIZE_BUTTON ) );
	
	gtk_button_set_image (button, GTK_WIDGET (image));
	gtk_widget_show (GTK_WIDGET (button));
	
	g_signal_connect (button, "clicked", G_CALLBACK (cb_remove_row), self);
	
	return button;
}

static GtkButton*
create_col_remover (CrankDemoMatPad* self)
{
	GtkButton*	button = GTK_BUTTON (gtk_button_new ());
	GtkImage*	image = GTK_IMAGE (gtk_image_new_from_icon_name (
			"list-remove-symbolic", GTK_ICON_SIZE_BUTTON ) );
	
	gtk_button_set_image (button, GTK_WIDGET (image));
	gtk_widget_show (GTK_WIDGET (button));
	
	g_signal_connect (button, "clicked", G_CALLBACK (cb_remove_col), self);
	
	return button;
}

static void
cb_on_size_change_foreach (	gpointer	data,
							gpointer	user_data	)
{
	guint*		size = (guint*) user_data;
	
	GVariant*	state = g_variant_new ("(uu)", size[0], size[1]);
	
	g_action_change_state (G_ACTION (data), state);
}

static void
on_size_change (	CrankDemoMatPad*	self)
{
	CrankDemoMatPadPrivate*	priv = crank_demo_mat_pad_get_instance_private (self);
	
	guint	size[2] = { priv->nrow, priv->ncol };
	
	g_list_foreach (priv->action_list, cb_on_size_change_foreach, size);
}

static void
parse_complex (	const gchar*	str,
				CrankCplxFloat*	cplx	)
{
	gchar		scan;
	guint		pos = 0;
	
	gboolean	positive;
	gfloat		strtof_value;
	gchar*		strtof_endptr;
	
	crank_cplx_float_init (cplx, 0.0f, 0.0f);
	
	{
		strtof_value = strtof (str, &strtof_endptr);
		
		if (strtof_endptr != str) {
			pos = CRANK_PTR_DIFF (strtof_endptr, str);
			
			if (crank_str_check_char (str, &pos, 'i'))
				cplx->imag = strtof_value;
			else
				cplx->real = strtof_value;
		}
	}
	
	while (crank_str_scan_char (str, &pos, &scan)) {
		
		if (scan == '+') 		positive = TRUE;
		else if (scan == '-')	positive = FALSE;
		else {
			crank_cplx_float_init (cplx, NAN, NAN);
			return;
		}
		
		strtof_value = strtof (str + pos, &strtof_endptr);
		
		if (strtof_endptr != str) {
			pos = CRANK_PTR_DIFF (strtof_endptr, str);
			
			if (crank_str_check_char (str, &pos, 'i'))
				cplx->imag += (positive) ? strtof_value : -strtof_value;
			else
				cplx->real += (positive) ? strtof_value : -strtof_value;
		}
	}
}

static gchar*
str_complex ( CrankCplxFloat*	cplx )
{
	GString*	strb = g_string_new (NULL);
	gchar*		str;
	gboolean	first = TRUE;
	
	if (cplx->real != 0) {
		first = FALSE;
		g_string_append_printf (strb, "%g", cplx->real);
	}
	if (cplx->imag != 0) {
		if (! first)
			g_string_append_printf (strb, "%+gi", cplx->imag);
		else
			g_string_append_printf (strb, "%gi", cplx->imag);
	}
	str = strb->str;
	g_string_free (strb, FALSE);
	return str;
}


static void
cb_remove_row (GtkButton*	button, gpointer user_data) {
	CrankDemoMatPad*	self = CRANK_DEMO_MAT_PAD (user_data);
	guint		rowp;
	
	gtk_container_child_get (GTK_CONTAINER (self), GTK_WIDGET (button),
			"top-attach", &rowp, NULL);
	
	crank_demo_mat_pad_remove_row (self, rowp - 1);
}

static void
cb_remove_col (GtkButton*	button, gpointer user_data) {
	CrankDemoMatPad*	self = CRANK_DEMO_MAT_PAD (user_data);
	guint		colp;
	
	gtk_container_child_get (GTK_CONTAINER (self), GTK_WIDGET (button),
			"left-attach", &colp, NULL);
	
	crank_demo_mat_pad_remove_col (self, colp - 1);
}

static void
cb_show_resize (GtkWidget*	widget,
				gpointer	user_data	)
{
	CrankDemoMatPad*		self = CRANK_DEMO_MAT_PAD (user_data);
	CrankDemoMatPadPrivate*	priv = crank_demo_mat_pad_get_instance_private (self);
	
	gtk_adjustment_set_value (priv->resize_adjrow, priv->nrow);
	gtk_adjustment_set_value (priv->resize_adjcol, priv->ncol);
	gtk_adjustment_value_changed (priv->resize_adjrow);
	gtk_adjustment_value_changed (priv->resize_adjcol);
}

static void
cb_resize_accept (GtkButton*	button,
					gpointer	user_data	)
{
	CrankDemoMatPad*		self = CRANK_DEMO_MAT_PAD (user_data);
	CrankDemoMatPadPrivate*	priv = crank_demo_mat_pad_get_instance_private (self);
	
	crank_demo_mat_pad_resize (self,
			(guint) gtk_adjustment_get_value (priv->resize_adjrow),
			(guint) gtk_adjustment_get_value (priv->resize_adjcol) );
	
	gtk_widget_hide ( GTK_WIDGET (priv->resize_popover) );
}
