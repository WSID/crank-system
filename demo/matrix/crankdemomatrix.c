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

/* Crank System is capable to calculate matrices and vectors, from fixed size
 * by 2[x2], 3[x3], 4[x4] (generally for graphics), to variable sizes (for
 * modeling in-game world)
 */

#include <glib.h>
#include <glib-object.h>
#include <gio/gio.h>
#include <gtk/gtk.h>
#include <crankbase.h>

#include "crankdemomatpad.h"

//////// Declaration ///////////////////////////////////////////////////////////

typedef struct _CrankDemoMatrixApp {
	GtkApplication	_parent;
} CrankDemoMatrixApp;

typedef struct _CrankDemoMatrixAppPrivate {
	GtkApplicationWindow*	main_window;
	CrankDemoMatPad*		matpad;
} CrankDemoMatrixAppPrivate;


#define CRANK_DEMO_TYPE_MATRIX_APP	crank_demo_matrix_app_get_type ()
G_DECLARE_FINAL_TYPE (CrankDemoMatrixApp, crank_demo_matrix_app, CRANK_DEMO, MATRIX_APP, GtkApplication)


CrankDemoMatrixApp*		crank_demo_matrix_app_new (void);


//////// Main //////////////////////////////////////////////////////////////////

gint main (gint argc, gchar** argv) {
	gint	result;
	
	CrankDemoMatrixApp*	app = crank_demo_matrix_app_new ();
	
	result = g_application_run (G_APPLICATION (app), argc, argv);
	
	g_object_unref (app);
}


//////// VF Definition /////////////////////////////////////////////////////////

static void	_g_application_startup ( GApplication*	application );

static void	_g_application_activate ( GApplication*	application );

//////// Definition for GType //////////////////////////////////////////////////

G_DEFINE_TYPE_WITH_PRIVATE (CrankDemoMatrixApp, crank_demo_matrix_app, GTK_TYPE_APPLICATION)

static void
crank_demo_matrix_app_init (CrankDemoMatrixApp*	self)
{
}


//////// Definition for GApplication ///////////////////////////////////////////

static void
crank_demo_matrix_app_class_init (CrankDemoMatrixAppClass*	c)
{
	GApplicationClass*	c_g_application;
	
	c_g_application = G_APPLICATION_CLASS (c);
	c_g_application->startup = _g_application_startup;
	c_g_application->activate = _g_application_activate;
}

static void
_g_application_startup (GApplication*	application)
{
	CrankDemoMatrixApp*	self = CRANK_DEMO_MATRIX_APP (application);
	CrankDemoMatrixAppPrivate*	priv = crank_demo_matrix_app_get_instance_private (self);
	
	GApplicationClass*	pc_g_application =
		G_APPLICATION_CLASS (crank_demo_matrix_app_parent_class);
	
	
	pc_g_application->startup (application);
	
	priv->main_window = 
			GTK_APPLICATION_WINDOW( gtk_application_window_new (
					GTK_APPLICATION (application) ) );
	
	priv->matpad =
			crank_demo_mat_pad_new_with_size (4, 2);
			
	gtk_container_add ( GTK_CONTAINER (priv->main_window), GTK_WIDGET (priv->matpad) );

					
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
	
	crank_demo_mat_pad_create_value (priv->matpad, &mat);
	matstr = crank_mat_cplx_float_n_to_string (&mat);
	
	g_message ("Matrix:\n  %s", matstr);
	g_free (matstr);
	crank_mat_cplx_float_n_fini (&mat);
	
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
