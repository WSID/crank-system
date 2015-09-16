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

/* This is Demo Application */

/*
 * # About Demo
 *
 * Crank System is capable to calculate matrices and vectors, from fixed size
 * by 2[x2], 3[x3], 4[x4] (generally for graphics), to variable sizes (for
 * modeling in-game world)
 *
 *
 * # Structure.
 *
 * #CrankDemoMatrixApp has code for primitive binary operations and advanced
 * operations.
 *
 * #CrankDemoMatPad has code for primitive unary operations and element access.
 */

#include <glib.h>
#include <glib-object.h>
#include <gio/gio.h>
#include <gtk/gtk.h>
#include <crankbase.h>

#include "crankdemomatpad.h"

//////// Declaration ///////////////////////////////////////////////////////////

typedef enum _CrankDemoOpType {
	CRANK_DEMO_OP_TYPE_NOP,
	CRANK_DEMO_OP_TYPE_ADD,
	CRANK_DEMO_OP_TYPE_SUB,
	CRANK_DEMO_OP_TYPE_MUL
} CrankDemoOpType;

typedef struct _CrankDemoMatrixApp {
	GtkApplication	_parent;
} CrankDemoMatrixApp;

typedef struct _CrankDemoMatrixAppPrivate {
	GtkApplicationWindow*	main_window;
	
	GtkInfoBar*				msgbar;
	GtkLabel*				msgbar_label;
	
	CrankDemoMatPad*		matpad_a;
	CrankDemoMatPad*		matpad_b;
	GtkButton*				eval;
	CrankDemoOpType			optype;
} CrankDemoMatrixAppPrivate;


#define CRANK_DEMO_TYPE_MATRIX_APP	crank_demo_matrix_app_get_type ()
G_DECLARE_FINAL_TYPE (CrankDemoMatrixApp, crank_demo_matrix_app, CRANK_DEMO, MATRIX_APP, GtkApplication)


CrankDemoMatrixApp*		crank_demo_matrix_app_new (void);


//////// Virtual function overriden from superclasses //////////////////////////

static void	_g_application_startup ( GApplication*	application );

static void	_g_application_activate ( GApplication*	application );

//////// Private functions /////////////////////////////////////////////////////

static void	crank_demo_matrix_app_set_optype (	CrankDemoMatrixApp*	self,
												CrankDemoOpType		optype	);

static gboolean	crank_demo_matrix_app_op_is_possible (	CrankDemoMatrixApp*	self	);


static void	crank_demo_matrix_app_show_message (	CrankDemoMatrixApp*	self,
													GtkMessageType		mtype,
													const gchar*		msg	);

//////// Callbacks /////////////////////////////////////////////////////////////

static void cb_sz_notify (	GObject*		object,
							GParamSpec*		pspec,	gpointer	user_data );

static void cb_action_failed(	CrankDemoMatPad*	pad,
								const gchar*		message,	gpointer	user_data );

static void	cb_op_add (	GtkToggleButton*	button,	gpointer	user_data );

static void	cb_op_sub (	GtkToggleButton*	button,	gpointer	user_data );

static void	cb_op_mul (	GtkToggleButton*	button,	gpointer	user_data );

static void	cb_eval (	GtkButton*	button,	gpointer user_data	);	


static void cb_lu (	GtkButton*	button,	gpointer	user_data	);

static void cb_ch (	GtkButton*	button,	gpointer	user_data	);

static void cb_qr (	GtkButton*	button,	gpointer	user_data	);

static void cb_eigen (GtkButton*	button,	gpointer	user_data	);




//////// Main //////////////////////////////////////////////////////////////////

gint main (gint argc, gchar** argv) {
	gint	result;

	// Make widget types are always available, so that GtkBuilder can construct
	// the widget.
	g_type_ensure (CRANK_DEMO_TYPE_MAT_PAD);

	CrankDemoMatrixApp*	app = crank_demo_matrix_app_new ();
	result = g_application_run (G_APPLICATION (app), argc, argv);
	
	g_object_unref (app);
}



//////// Definition for GType //////////////////////////////////////////////////

G_DEFINE_TYPE_WITH_PRIVATE (CrankDemoMatrixApp, crank_demo_matrix_app, GTK_TYPE_APPLICATION)

static void
crank_demo_matrix_app_init (CrankDemoMatrixApp*	self)
{
}

static void
crank_demo_matrix_app_class_init (CrankDemoMatrixAppClass*	c)
{
	GApplicationClass*	c_g_application;
	
	c_g_application = G_APPLICATION_CLASS (c);
	c_g_application->startup = _g_application_startup;
	c_g_application->activate = _g_application_activate;
}



//////// Definition for GApplication ///////////////////////////////////////////

static void
_g_application_startup (GApplication*	application)
{
	CrankDemoMatrixApp*	self = CRANK_DEMO_MATRIX_APP (application);
	CrankDemoMatrixAppPrivate*	priv = crank_demo_matrix_app_get_instance_private (self);
	
	GApplicationClass*	pc_g_application =
		G_APPLICATION_CLASS (crank_demo_matrix_app_parent_class);
	
	GtkBuilder*	builder;
	
	
	pc_g_application->startup (application);
	
	builder = gtk_builder_new ();
	
	gtk_builder_expose_object (builder, "App", G_OBJECT (self) );
	gtk_builder_add_callback_symbol (builder, "cb_sz_notify", G_CALLBACK (cb_sz_notify));
	gtk_builder_add_callback_symbol (builder, "cb_action_failed", G_CALLBACK (cb_action_failed));
	gtk_builder_add_callback_symbol (builder, "cb_op_add", G_CALLBACK (cb_op_add));
	gtk_builder_add_callback_symbol (builder, "cb_op_sub", G_CALLBACK (cb_op_sub));
	gtk_builder_add_callback_symbol (builder, "cb_op_mul", G_CALLBACK (cb_op_mul));
	gtk_builder_add_callback_symbol (builder, "cb_eval", G_CALLBACK (cb_eval));
	gtk_builder_add_callback_symbol (builder, "cb_lu", G_CALLBACK (cb_lu));
	gtk_builder_add_callback_symbol (builder, "cb_ch", G_CALLBACK (cb_ch));
	gtk_builder_add_callback_symbol (builder, "cb_qr", G_CALLBACK (cb_qr));
	gtk_builder_add_callback_symbol (builder, "cb_eigen", G_CALLBACK (cb_eigen));
	gtk_builder_add_from_resource (builder, "/crank/demo/matrix/crankdemomatrix.ui", NULL);
	gtk_builder_connect_signals (builder, self);
	
	priv->main_window = 
			GTK_APPLICATION_WINDOW( gtk_builder_get_object (builder, "main_window") );
			
	priv->msgbar = 
			GTK_INFO_BAR( gtk_builder_get_object (builder, "msgbar") );
			
	priv->msgbar_label = 
			GTK_LABEL( gtk_builder_get_object (builder, "msgbar_label") );
	
	priv->matpad_a =
			CRANK_DEMO_MAT_PAD ( gtk_builder_get_object (builder, "matpad_a") );
			
	priv->matpad_b =
			CRANK_DEMO_MAT_PAD ( gtk_builder_get_object (builder, "matpad_b") );

	priv->eval =
			GTK_BUTTON ( gtk_builder_get_object (builder, "eval") );
			
	gtk_widget_show_all ( GTK_WIDGET (priv->main_window) );
}

static void
_g_application_activate (GApplication*	application)
{
	CrankDemoMatrixApp*	self = CRANK_DEMO_MATRIX_APP (application);
	CrankDemoMatrixAppPrivate*	priv = crank_demo_matrix_app_get_instance_private (self);
	
	CrankMatCplxFloatN	mat;
	gchar*				matstr;
	
	GApplicationClass*	pc_g_application =
		G_APPLICATION_CLASS (crank_demo_matrix_app_parent_class);
	
	pc_g_application->activate (application);
	
	gtk_window_present (GTK_WINDOW (priv->main_window));
}




//////// Public Definition /////////////////////////////////////////////////////

CrankDemoMatrixApp*
crank_demo_matrix_app_new (void)
{
	CrankDemoMatrixApp*	self =
		g_object_new (CRANK_DEMO_TYPE_MATRIX_APP,
				"application-id", "crank.demo.matrix", NULL);
	
	return self;
}




//////// Private functions /////////////////////////////////////////////////////

static void
crank_demo_matrix_app_set_optype (	CrankDemoMatrixApp*	self,
									CrankDemoOpType		optype	)
{
	CrankDemoMatrixAppPrivate*	priv = crank_demo_matrix_app_get_instance_private (self);

	priv->optype = optype;
	
	gtk_widget_set_sensitive (	GTK_WIDGET (priv->eval),
								crank_demo_matrix_app_op_is_possible (self)	);
}

static gboolean
crank_demo_matrix_app_op_is_possible (	CrankDemoMatrixApp*	self	)
{
	CrankDemoMatrixAppPrivate*	priv = crank_demo_matrix_app_get_instance_private (self);
	
	guint	arn;
	guint	acn;
	guint	brn;
	guint	bcn;
	
	arn = crank_demo_mat_pad_get_nrow (priv->matpad_a);
	acn = crank_demo_mat_pad_get_ncol (priv->matpad_a);
	brn = crank_demo_mat_pad_get_nrow (priv->matpad_b);
	bcn = crank_demo_mat_pad_get_ncol (priv->matpad_b);
	
	if (arn == 0 || acn == 0 || brn == 0 || bcn == 0) return FALSE;
	
	switch (priv->optype) {
	case CRANK_DEMO_OP_TYPE_ADD:
	case CRANK_DEMO_OP_TYPE_SUB:
		return (arn == brn) && (acn == bcn);
	case CRANK_DEMO_OP_TYPE_MUL:
		return (acn == brn);
	default:
		return FALSE;
	}
}


static void
crank_demo_matrix_app_show_message (	CrankDemoMatrixApp*	self,
										GtkMessageType		mtype,
										const gchar*		msg	)
{
	CrankDemoMatrixAppPrivate*	priv = crank_demo_matrix_app_get_instance_private (self);
	
	gtk_info_bar_set_message_type (priv->msgbar, mtype);
	gtk_label_set_label (priv->msgbar_label, msg);
	gtk_widget_show (GTK_WIDGET (priv->msgbar));
	gtk_widget_show (GTK_WIDGET (priv->msgbar_label));
}


//////// Callback //////////////////////////////////////////////////////////////

static void
cb_action_failed (	CrankDemoMatPad*	pad,
					const gchar*		message,
					gpointer			user_data )
{
	CrankDemoMatrixApp*	self = CRANK_DEMO_MATRIX_APP (user_data);
	CrankDemoMatrixAppPrivate*	priv = crank_demo_matrix_app_get_instance_private (self);
	
	crank_demo_matrix_app_show_message (self,
			GTK_MESSAGE_ERROR,
			message	);
}


static void
cb_sz_notify (	GObject*	object,
				GParamSpec*	pspec,
				gpointer	user_data )
{
	CrankDemoMatrixApp*	self = CRANK_DEMO_MATRIX_APP (user_data);
	CrankDemoMatrixAppPrivate*	priv = crank_demo_matrix_app_get_instance_private (self);
	
	gtk_widget_set_sensitive (	GTK_WIDGET (priv->eval),
								crank_demo_matrix_app_op_is_possible (self)	);
}

static void
cb_op_add (	GtkToggleButton*	button,
			gpointer			user_data )
{
	if (gtk_toggle_button_get_active (button)) {
		CrankDemoMatrixApp*	self = CRANK_DEMO_MATRIX_APP (user_data);
		crank_demo_matrix_app_set_optype (self, CRANK_DEMO_OP_TYPE_ADD);
	}
}

static void
cb_op_sub (	GtkToggleButton*	button,
			gpointer			user_data )
{
	if (gtk_toggle_button_get_active (button)) {
		CrankDemoMatrixApp*	self = CRANK_DEMO_MATRIX_APP (user_data);
		crank_demo_matrix_app_set_optype (self, CRANK_DEMO_OP_TYPE_SUB);
	}
}

static void
cb_op_mul (	GtkToggleButton*	button,
			gpointer			user_data )
{
	if (gtk_toggle_button_get_active (button)) {
		CrankDemoMatrixApp*	self = CRANK_DEMO_MATRIX_APP (user_data);
		crank_demo_matrix_app_set_optype (self, CRANK_DEMO_OP_TYPE_MUL);
	}
}

static void
cb_eval (	GtkButton*	button,
			gpointer	user_data	)
{
	CrankDemoMatrixApp*	self = CRANK_DEMO_MATRIX_APP (user_data);
	CrankDemoMatrixAppPrivate*	priv = crank_demo_matrix_app_get_instance_private (self);
	
	CrankMatCplxFloatN	mat_a;
	CrankMatCplxFloatN	mat_b;
	
	crank_demo_mat_pad_get_mcf (priv->matpad_a, &mat_a);
	crank_demo_mat_pad_get_mcf (priv->matpad_b, &mat_b);
	
	
	// primitive operations can be done by add/sub/mul[_self] () functions.
	// each operations are defined only when some size requirements are met.
	//
	// If size is mismatched, these op is nop with warnings.
	
	switch (priv->optype) {
	case CRANK_DEMO_OP_TYPE_ADD:
		crank_mat_cplx_float_n_add_self (&mat_a, &mat_b);
		break;
	case CRANK_DEMO_OP_TYPE_SUB:
		crank_mat_cplx_float_n_sub_self (&mat_a, &mat_b);
		break;
	case CRANK_DEMO_OP_TYPE_MUL:
		crank_mat_cplx_float_n_mul_self (&mat_a, &mat_b);
		break;
	}
	
	crank_demo_mat_pad_set_mcf (priv->matpad_a, &mat_a);
	
	gtk_widget_set_sensitive (	GTK_WIDGET (priv->eval),
								crank_demo_matrix_app_op_is_possible (self)	);
	
	crank_mat_cplx_float_n_fini (&mat_a);
	crank_mat_cplx_float_n_fini (&mat_b);
}


static void
cb_lu (	GtkButton*	button,
		gpointer	user_data	)
{
	CrankDemoMatrixApp*	self = CRANK_DEMO_MATRIX_APP (user_data);
	CrankDemoMatrixAppPrivate*	priv = crank_demo_matrix_app_get_instance_private (self);
	
	CrankMatCplxFloatN	mat;
	CrankMatCplxFloatN	mat_a;
	CrankMatCplxFloatN	mat_b;
	
	crank_demo_mat_pad_get_mcf (priv->matpad_a, &mat);
	
	// Decomposition is provided as function that receives multiple pointers to
	// matrices.
	//
	// If decomposition was successful, it returns TRUE and sets decomposition
	// results.
	
	if (crank_lu_mat_cplx_float_n (&mat, &mat_a, &mat_b)) {
		crank_demo_mat_pad_set_mcf (priv->matpad_a, &mat_a);
		crank_demo_mat_pad_set_mcf (priv->matpad_b, &mat_b);
		crank_mat_cplx_float_n_fini (&mat_a);
		crank_mat_cplx_float_n_fini (&mat_b);
	}
	else {
		crank_demo_matrix_app_show_message (self,
				GTK_MESSAGE_INFO,
				"LU Decomposition failed."	);
	}
	
	gtk_widget_set_sensitive (	GTK_WIDGET (priv->eval),
								crank_demo_matrix_app_op_is_possible (self)	);
								
	crank_mat_cplx_float_n_fini (&mat);	
}


static void
cb_ch (	GtkButton*	button,
		gpointer	user_data	)
{
	CrankDemoMatrixApp*	self = CRANK_DEMO_MATRIX_APP (user_data);
	CrankDemoMatrixAppPrivate*	priv = crank_demo_matrix_app_get_instance_private (self);
	
	CrankMatCplxFloatN	mat;
	CrankMatCplxFloatN	mat_l;
	
	crank_demo_mat_pad_get_mcf (priv->matpad_a, &mat);

	// Crank system provides cholesky decomposition.
	//
	// This will be only valid if the matrix is hermitian and [semi-]positive
	// definite.
	
	if (! crank_mat_cplx_float_n_is_hermitian (&mat)) {
		crank_demo_matrix_app_show_message (self,
				GTK_MESSAGE_INFO,
				"Cholesky Decomposition: The matrix is not hermitian." );
	
		goto END_CB_CH;
	}

	if (crank_ch_mat_cplx_float_n (&mat, &mat_l)) {
		crank_demo_mat_pad_set_mcf (priv->matpad_a, &mat_l);

		gtk_widget_set_sensitive (	GTK_WIDGET (priv->eval),
									crank_demo_matrix_app_op_is_possible (self)	);
								
		crank_mat_cplx_float_n_fini (&mat_l);
	}
	
	else {
		crank_demo_matrix_app_show_message (self,
				GTK_MESSAGE_INFO,
				"Cholesky Decomposition: failed."	);
	}
	
	END_CB_CH:			
	crank_mat_cplx_float_n_fini (&mat);	
}


static void
cb_qr (	GtkButton*	button,
		gpointer	user_data	)
{
	CrankDemoMatrixApp*	self = CRANK_DEMO_MATRIX_APP (user_data);
	CrankDemoMatrixAppPrivate*	priv = crank_demo_matrix_app_get_instance_private (self);
	
	CrankMatCplxFloatN	mat;
	CrankMatCplxFloatN	mat_a;
	CrankMatCplxFloatN	mat_b;
	
	crank_demo_mat_pad_get_mcf (priv->matpad_a, &mat);
	
	// Crank system provides 3 type of QR Decomposition.
	//
	// Gram Schmidt returns both Q and R, but householder and givens returns
	// R only.
	
	if (crank_gram_schmidt_mat_cplx_float_n (&mat, &mat_a, &mat_b)) {
		crank_demo_mat_pad_set_mcf (priv->matpad_a, &mat_a);
		crank_demo_mat_pad_set_mcf (priv->matpad_b, &mat_b);
		crank_mat_cplx_float_n_fini (&mat_a);
		crank_mat_cplx_float_n_fini (&mat_b);
	}
	else {
		crank_demo_matrix_app_show_message (self,
				GTK_MESSAGE_INFO,
				"QR Decomposition failed."	);
	}
	
	gtk_widget_set_sensitive (	GTK_WIDGET (priv->eval),
								crank_demo_matrix_app_op_is_possible (self)	);
								
	crank_mat_cplx_float_n_fini (&mat);	
}


static void
cb_eigen (	GtkButton*	button,
			gpointer	user_data	)
{
	CrankDemoMatrixApp*	self = CRANK_DEMO_MATRIX_APP (user_data);
	CrankDemoMatrixAppPrivate*	priv = crank_demo_matrix_app_get_instance_private (self);
	
	CrankMatCplxFloatN	mat;
	
	crank_demo_mat_pad_get_mcf (priv->matpad_a, &mat);
	
	// Crank System provides eigenvalue algorithms for real matrices.
	//
	// Power method returns both eigenvalue and eigenvector, but returns only
	// dominant pair. (with most significant eigenvalue)
	//
	// QR method returns eigenvalues only. NaN is used in place of complex
	// eigenvalues.
	//
	// Crank System does not provide eigenvalue algorithms for complex matrices.
	
	if (crank_mat_cplx_float_n_is_pure_real (&mat)) {
		CrankMatFloatN	rmat;
		CrankVecFloatN	evals;
		
		crank_mat_cplx_float_n_get_real (&mat, &rmat);
		
		crank_eval_qr_mat_float_n (&rmat, &evals);
		crank_mat_cplx_float_n_fini (&mat);
		crank_mat_cplx_float_n_init_diag_ucv (&mat, &evals, NULL);
		
		crank_demo_mat_pad_set_mcf (priv->matpad_a, &mat);
		crank_mat_float_n_fini (&rmat);
		crank_vec_float_n_fini (&evals);
	}
	else {
		crank_demo_matrix_app_show_message (self,
				GTK_MESSAGE_INFO,
				"EVAL: Not supported for complex matrices"	);
	}
	
	crank_mat_cplx_float_n_fini (&mat);
}
