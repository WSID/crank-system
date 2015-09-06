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

	GSimpleActionGroup*	agroup;
	GMenu*				menuset;

	GtkAdjustment*	rowadj;
	GtkAdjustment*	coladj;

	GtkMenuButton*	set;		// Menu Button to set matrix
	GtkButton*		addrow;		// Add row.
	GtkButton*		addcol;		// Add col
	GtkMenuButton*	resize;		// Popover Button to set size
	GtkPopover*		resizepo;	// A Popover to set size.
	GtkSpinButton*	resizerow;
	GtkSpinButton*	resizecol;
	GtkButton*		resizeaccept;
} CrankDemoMatPadPrivate;


enum {
	PROP_0,
	PROP_NROW,
	PROP_NCOL,
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


static GActionEntry actions[] = {
	{"zero",		activate_zero, NULL, NULL, NULL},
	{"identity",	activate_identity, NULL, NULL, NULL}
};

//////// Private Functions /////////////////////////////////////////////////////

static GtkEntry*	create_entry (CrankDemoMatPad*			pad);

static GtkButton*	create_row_remover (CrankDemoMatPad*	pad);

static GtkButton*	create_col_remover (CrankDemoMatPad*	pad);

static void			parse_complex (	const gchar*	string,
									CrankCplxFloat*	cplx	);

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

CrankDemoMatPad*
crank_demo_mat_pad_new (void)
{
	return CRANK_DEMO_MAT_PAD (g_object_new (CRANK_DEMO_TYPE_MAT_PAD, NULL));
}

CrankDemoMatPad*
crank_demo_mat_pad_new_with_size (guint	row, guint col)
{
	return CRANK_DEMO_MAT_PAD (g_object_new (CRANK_DEMO_TYPE_MAT_PAD,
			"nrow", row, "ncol", col, NULL));
}

CrankDemoMatPad*	crank_demo_mat_pad_new_with_mf (CrankMatFloatN*	mf);

CrankDemoMatPad*	crank_demo_mat_pad_new_with_mcf (CrankMatCplxFloatN*	mcf);



//////// Properties ////////////////////////////////////////////////////////////

guint
crank_demo_mat_pad_get_nrow (	CrankDemoMatPad*	self)
{
	CrankDemoMatPadPrivate*	priv = crank_demo_mat_pad_get_instance_private (self);
	
	return priv->nrow;
}

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

guint
crank_demo_mat_pad_get_ncol (	CrankDemoMatPad*	self)
{
	CrankDemoMatPadPrivate*	priv = crank_demo_mat_pad_get_instance_private (self);
	
	return priv->ncol;
}

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

//////// Methods ///////////////////////////////////////////////////////////////

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
	
	g_object_notify_by_pspec (G_OBJECT (self), pspecs[PROP_NROW]);
}


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
	
	g_object_notify_by_pspec (G_OBJECT (self), pspecs[PROP_NCOL]);
}

void
crank_demo_mat_pad_remove_row (	CrankDemoMatPad*	self,
								guint				index )
{
	CrankDemoMatPadPrivate*	priv = crank_demo_mat_pad_get_instance_private (self);
	
	gtk_grid_remove_row (GTK_GRID (self), index + 1);
	priv->nrow --;
}

void
crank_demo_mat_pad_remove_col (	CrankDemoMatPad*	self,
								guint				index )
{
	CrankDemoMatPadPrivate*	priv = crank_demo_mat_pad_get_instance_private (self);
	
	gtk_grid_remove_column (GTK_GRID (self), index + 1);
	priv->ncol --;
}

void
crank_demo_mat_pad_resize (	CrankDemoMatPad*	self,
							guint				nrow,
							guint				ncol	)
{
	crank_demo_mat_pad_set_nrow (self, nrow);
	crank_demo_mat_pad_set_ncol (self, ncol);
}



GtkEntry*
crank_demo_mat_pad_get_entry (	CrankDemoMatPad*	self,
								guint				row,
								guint				col )
{
	GtkGrid*	self_gtk_grid = GTK_GRID (self);
	
	return GTK_ENTRY (gtk_grid_get_child_at (self_gtk_grid, col + 1, row + 1) );
}

void
crank_demo_mat_pad_create_value (CrankDemoMatPad*	self,
								CrankMatCplxFloatN*	value	)
{
	guint i;
	guint j;
	
	guint	nrow = crank_demo_mat_pad_get_nrow (self);
	guint	ncol = crank_demo_mat_pad_get_ncol (self);
	
	crank_mat_cplx_float_n_init_fill_uc (value, nrow, ncol, 0.0f, 0.0f);
	
	for (i = 0; i < nrow; i++) {
		for (j = 0; j < ncol; j++) {
			GtkEntry*		entry = crank_demo_mat_pad_get_entry (self, i, j);
			
			parse_complex (	gtk_entry_get_text (entry),
							crank_mat_cplx_float_n_peek (value, i, j) );
		}
	}
}

//////// Instance, Class Init Functions ////////////////////////////////////////

static void
crank_demo_mat_pad_init (CrankDemoMatPad*	self)
{
	CrankDemoMatPadPrivate*	priv = crank_demo_mat_pad_get_instance_private (self);
	
	priv->nrow = 1;
	priv->ncol = 1;
}

static void
crank_demo_mat_pad_class_init (CrankDemoMatPadClass*	c)
{
	GObjectClass*	c_g_object;
	
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
	
	g_object_class_install_properties (c_g_object, PROP_COUNT, pspecs);
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
	
	GtkImage*	image_addrow;
	GtkImage*	image_addcol;
	
	
	GtkLabel*	resizerowl;
	GtkLabel*	resizecoll;
	
	GtkPopover*	resizepop;
	GtkGrid*	resizegrid;
	
	G_OBJECT_CLASS (crank_demo_mat_pad_parent_class)->constructed (self_g_object);
	
	GtkGrid*	self_gtk_grid = GTK_GRID (self_g_object);
	
	// Constructs a simple UI
	
	image_addrow = GTK_IMAGE (gtk_image_new_from_icon_name ("list-add-symbolic", GTK_ICON_SIZE_BUTTON));
	image_addcol = GTK_IMAGE (gtk_image_new_from_icon_name ("list-add-symbolic", GTK_ICON_SIZE_BUTTON));
	
	//resizepop = GTK_POPOVER (gtk_popover_new (GTK_WIDGET (priv->resize)));
	resizegrid = GTK_GRID (gtk_grid_new ());
	
	resizerowl = GTK_LABEL (gtk_label_new ("Row"));
	resizecoll = GTK_LABEL (gtk_label_new ("Col"));
	
	priv->agroup = g_simple_action_group_new ();
	priv->menuset = g_menu_new ();
	
	g_menu_insert (priv->menuset, 0, "Zero", "pad.zero");
	g_menu_insert (priv->menuset, 1, "Identity", "pad.identity");
	
	priv->rowadj = gtk_adjustment_new (1, 1, 128, 1, 3, 3);
	priv->coladj = gtk_adjustment_new (1, 1, 128, 1, 3, 3);
	
	priv->set = GTK_MENU_BUTTON (gtk_menu_button_new ());
	priv->addrow = GTK_BUTTON (gtk_button_new ());
	priv->addcol = GTK_BUTTON (gtk_button_new ());
	priv->resize = GTK_MENU_BUTTON (gtk_menu_button_new ());
	
	priv->resizepo = GTK_POPOVER (gtk_popover_new (GTK_WIDGET (priv->resize)));
	priv->resizerow = GTK_SPIN_BUTTON (gtk_spin_button_new (priv->rowadj, 1, 0));
	priv->resizecol = GTK_SPIN_BUTTON (gtk_spin_button_new (priv->coladj, 1, 0));
	priv->resizeaccept = GTK_BUTTON (gtk_button_new_with_label ("Accept"));
	
	
	// Setup UI
	g_action_map_add_action_entries (G_ACTION_MAP (priv->agroup), actions, G_N_ELEMENTS (actions), self);
	
	gtk_widget_insert_action_group (GTK_WIDGET (self), "pad", G_ACTION_GROUP (priv->agroup));
	
	gtk_menu_button_set_use_popover (priv->set, TRUE);
	gtk_menu_button_set_menu_model (priv->set, G_MENU_MODEL(priv->menuset));
	
	gtk_button_set_image (GTK_BUTTON(priv->addrow), GTK_WIDGET (image_addrow));
	gtk_button_set_image (GTK_BUTTON(priv->addcol), GTK_WIDGET (image_addcol));
	
	gtk_menu_button_set_direction (priv->set, GTK_ARROW_NONE);
	gtk_menu_button_set_direction (priv->resize, GTK_ARROW_NONE);
	
	// Builds a simple UI
	
	gtk_container_add (GTK_CONTAINER (priv->resizepo), GTK_WIDGET (resizegrid));
	gtk_menu_button_set_popover (priv->resize, GTK_WIDGET (priv->resizepo));
	
	gtk_grid_attach (self_gtk_grid,	GTK_WIDGET (priv->set),0, 0, 1, 1);
	gtk_grid_attach (self_gtk_grid,	GTK_WIDGET (priv->addrow),0, 1 + priv->nrow, 1 + priv->ncol, 1);
	gtk_grid_attach (self_gtk_grid,	GTK_WIDGET (priv->addcol),1 + priv->ncol, 0, 1, 1 + priv->nrow);
	gtk_grid_attach (self_gtk_grid,	GTK_WIDGET (priv->resize),1 + priv->ncol, 1 + priv->nrow, 1, 1);
	
	gtk_grid_attach (resizegrid, GTK_WIDGET (resizerowl), 0, 0, 1, 1);
	gtk_grid_attach (resizegrid, GTK_WIDGET (resizecoll), 0, 1, 1, 1);
	gtk_grid_attach (resizegrid, GTK_WIDGET (priv->resizerow), 1, 0, 1, 1);
	gtk_grid_attach (resizegrid, GTK_WIDGET (priv->resizecol), 1, 1, 1, 1);
	gtk_grid_attach (resizegrid, GTK_WIDGET (priv->resizeaccept), 0, 2, 2, 1);
	
	gtk_widget_show_all (GTK_WIDGET (resizegrid));
	
	// Hook up signals
	g_signal_connect_swapped (priv->addrow, "clicked", G_CALLBACK (crank_demo_mat_pad_append_row), self);
	g_signal_connect_swapped (priv->addcol, "clicked", G_CALLBACK (crank_demo_mat_pad_append_col), self);
	g_signal_connect (priv->resizepo, "show", G_CALLBACK (cb_show_resize), self);
	g_signal_connect (priv->resizeaccept, "clicked", G_CALLBACK (cb_resize_accept), self);
	
	
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

//////// Private functions /////////////////////////////////////////////////////

static GtkEntry*
create_entry (CrankDemoMatPad* self)
{
	GtkEntry*	entry = GTK_ENTRY (gtk_entry_new ());
	
	gtk_entry_set_has_frame (entry, FALSE);
	gtk_entry_set_placeholder_text (entry, "0");
	
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
	
	gtk_spin_button_set_value (priv->resizerow, priv->nrow);
	gtk_spin_button_set_value (priv->resizecol, priv->ncol);
}

static void
cb_resize_accept (GtkButton*	button,
					gpointer	user_data	)
{
	CrankDemoMatPad*		self = CRANK_DEMO_MAT_PAD (user_data);
	CrankDemoMatPadPrivate*	priv = crank_demo_mat_pad_get_instance_private (self);
	
	crank_demo_mat_pad_resize (self,
			(guint) gtk_spin_button_get_value (priv->resizerow),
			(guint) gtk_spin_button_get_value (priv->resizecol) );
	
	gtk_widget_hide ( GTK_WIDGET (priv->resizepo) );
}
