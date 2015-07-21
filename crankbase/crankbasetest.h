#ifndef CRANKBASETEST_H
#define CRANKBASETEST_H

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

#ifndef _CRANKBASE_INSIDE
#error crankbasetest.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

G_BEGIN_DECLS

//////// Assertions ////////////////////////////////////////////////////////////

/**
 * SECTION: crankbasetest
 * @title: Testing with Base.
 * @short_description: Testing with base structures.
 * @usability: unstable
 * @include: crankbase.h
 *
 * Crank System provides testing functions for convenience.
 *
 * For now, this provides assertions to check structures has right values.
 */

/**
 * crank_assert_eqarray_float:
 * @a: (element-type gfloat) (array length=an): A array
 * @an: (type guint): Length of elements.
 * @b: (element-type gfoat) (array length=bn): A array
 * @bn: (type guint): Length of elements.
 * @format: (type gchar*): A Format.
 *
 * Asserts two float arrays are equals.
 */
#define crank_assert_eqarray_float(a,an,b,bn,format)	\
	crank_assert_eqarray(gfloat,a,an,b,bn,crank_float_equal,crank_float_to_string,format)


/**
 * crank_assert_eqarray:
 * @G: Type of element.
 * @a: (element-type G) (array length=an): A array
 * @an: (type guint): Length of elements.
 * @b: (element-type G) (array length=bn): A array
 * @bn: (type guint): Length of elements.
 * @eqf: (type GEqualFunc): Equality functions.
 * @strf: (type CrankStrPtrFunc): stringification functions.
 * @strfu: (closure): Userdata for @strf
 *
 * Asserts two arrays are equals.
 *
 * This checks arrays with given type (like #gfloat or #gdouble), so functions
 * will be used with pointers pointing array element.
 */
#define crank_assert_eqarray(G,a,an,b,bn,eqf,strf,strfu)	\
		G_STMT_START { \
			gboolean	fails = FALSE; \
			G*		na = (a); \
			guint	nan = (an); \
			G*		nb = (b); \
			guint	nbn = (bn); \
			guint i; \
			if (nan != nbn) fails = TRUE; \
			else for (i = 0; i < nan; i++) { \
				if (! eqf (na + i, nb + i)) { \
					fails = TRUE; \
					break; \
				} \
			} \
			if (fails) { \
				GString*	msg_build = g_string_new (NULL); \
				gchar*		item_str = NULL; \
				g_string_printf (msg_build, \
						"%s == %s" \
						"\n\tContent of %s (length: %u)", \
						G_STRINGIFY(a), G_STRINGIFY(b), \
						G_STRINGIFY(a), nan); \
				for (i = 0; i < nan; i++) { \
					item_str = ((CrankStrPtrFunc)strf) (na + i, (strfu)); \
					g_string_append_printf (msg_build, "\n\t\t%s", item_str); \
					g_free (item_str); \
				} \
				g_string_append_printf ( msg_build, \
						"\n\tContent of %s (length: %u)", \
						G_STRINGIFY(b), nbn); \
				for (i = 0; i < nbn; i++) { \
					item_str = ((CrankStrPtrFunc)strf) (nb + i, (strfu)); \
					g_string_append_printf (msg_build, "\n\t\t%s", item_str); \
					g_free (item_str); \
				} \
				g_assertion_message (G_LOG_DOMAIN, __FILE__, __LINE__, G_STRFUNC, \
					msg_build->str); \
				g_string_free (msg_build, TRUE); \
				\
			} \
		} G_STMT_END
		
/**
 * crank_assert_eqparray:
 * @a: (element-type gpointer) (array length=an): A array
 * @an: (type guint): Length of elements.
 * @b: (element-type gpointer) (array length=bn): A array
 * @bn: (type guint): Length of elements.
 * @eqf: (type GEqualFunc): Equality functions.
 * @strf: (type CrankStrPtrFunc): stringification functions.
 * @strfu: (closure): Userdata for @strf
 *
 * Asserts two arrays are equals.
 *
 * This checks arrays with pointer type (like #GString,...), so functions
 * will be used with elements which are pointer itself.
 */
#define crank_assert_eqparray(a,an,b,bn,eqf,strf,strfu)	\
		G_STMT_START { \
			gboolean	fails = FALSE; \
			G*		na = (a); \
			guint	nan = (an); \
			G*		nb = (b); \
			guint	nbn = (bn); \
			guint i; \
			if (nan != nbn) fails = TRUE; \
			else for (i = 0; i < nan; i++) { \
				if (! eqf (na[i], nb[i])) { \
					fails = TRUE; \
					break; \
				} \
			} \
			if (fails) { \
				GString*	msg_build = g_string_new (NULL); \
				gchar*		item_str = NULL; \
				g_string_printf (msg_build, \
						"%s == %s" \
						"\n\tContent of %s (length: %u)", \
						G_STRINGIFY(a), G_STRINGIFY(b), \
						G_STRINGIFY(a), nan); \
				for (i = 0; i < nan; i++) { \
					item_str = ((CrankStrPtrFunc)strf) (na[i], (strfu)); \
					g_string_append_printf (msg_build, "\n\t\t%s", item_str); \
					g_free (item_str); \
				} \
				g_string_append_printf ( msg_build, \
						"\n\tContent of %s (length: %u)", \
						G_STRINGIFY(b), nbn); \
				for (i = 0; i < nbn; i++) { \
					item_str = ((CrankStrPtrFunc)strf) (nb[i], (strfu)); \
					g_string_append_printf (msg_build, "\n\t\t%s", item_str); \
					g_free (item_str); \
				} \
				g_assertion_message (G_LOG_DOMAIN, __FILE__, __LINE__, G_STRFUNC, \
					msg_build->str); \
				g_string_free (msg_build, TRUE); \
				\
			} \
		} G_STMT_END

/**
 * crank_assert_cmpfloat:
 * @a: (type gfloat): A #gfloat
 * @cmp: A comparsion operator.
 * @b: (type gfloat): A #gfloat
 *
 * Asserts comparsion of two #gfloat with tolerance of 0.0001f of error.
 */
#define crank_assert_cmpfloat(a,cmp,b)	crank_assert_cmpfloat_d (a,cmp,b,0.0001f)

/**
 * crank_assert_cmpfloat_d:
 * @a: (type gfloat): A #gfloat
 * @cmp: A comparsion operator.
 * @b: (type gfloat): A #gfloat
 * @d: (type gfloat): Delta
 *
 * Asserts comparsion of two #gfloat with tolerance of given delta of error.
 */
#define crank_assert_cmpfloat_d(a,cmp,b,d)	\
		G_STMT_START { \
			gfloat na = (a); \
			gfloat nb = (b); \
			gfloat diff = (nb - na); \
			gfloat nd = (d); \
			gint cres = (diff < -nd) - (nd < diff); \
			if (G_UNLIKELY(! (cres cmp 0))) { \
				gchar* message = g_strdup_printf ( \
			            "%s %s %s" \
			            "\n\tActual: %g %s %g (with diff = %g)", \
			            G_STRINGIFY(a), \
			            G_STRINGIFY(cmp), \
			            G_STRINGIFY(b), \
						na, G_STRINGIFY(cmp), nb, diff ); \
				g_assertion_message ( \
						G_LOG_DOMAIN, __FILE__, __LINE__, G_STRFUNC, \
						message); \
				g_free (message); \
			} \
		} G_STMT_END

/**
 * crank_assert_eqcplxfloat:
 * @a: (type CrankCplxFloat): A complex
 * @b: (type CrankCplxFloat): A complex
 *
 * Asserts comparsion of two #CrankCplxFloat with tolerance of 0.0001f of
 * error.
 *
 * The difference is calculated from distance on complex plane.
 */
#define crank_assert_eqcplxfloat(a,b) crank_assert_eqcplxfloat_d(a,b,0.0001f)

/**
 * crank_assert_eqcplxfloat_d:
 * @a: (type CrankCplxFloat): A complex
 * @b: (type CrankCplxFloat): A complex
 * @d: (type gfloat): Delta
 *
 * Asserts comparsion of two #CrankCplxFloat with tolerance of given delta of
 * error.
 *
 * The difference is calculated from distance on complex plane.
 */
#define crank_assert_eqcplxfloat_d(a,b,d) \
		G_STMT_START { \
			CrankCplxFloat	na; \
			CrankCplxFloat	nb; \
			CrankCplxFloat	diff; \
			gfloat nd = (d); \
			gfloat diff_norm; \
			crank_cplx_float_copy ((a), &na); \
			crank_cplx_float_copy ((b), &nb); \
			crank_cplx_float_sub (&nb, &na, &diff); \
			diff_norm = crank_cplx_float_get_norm (&diff); \
			if (G_UNLIKELY((diff_norm < - nd) || (nd < diff_norm))) { \
				gchar*	nastr = crank_cplx_float_to_string (&na); \
				gchar*	nbstr = crank_cplx_float_to_string (&nb); \
				gchar*	diffstr = crank_cplx_float_to_string (&diff); \
				gchar*	message = g_strdup_printf ( \
						"%s == %s"\
						"\n\tActual: %s == %s (with diff = %s, norm = %g)", \
			            G_STRINGIFY(a), \
			            G_STRINGIFY(b), \
			            nastr, nbstr, diffstr, diff_norm); \
			    g_assertion_message ( \
			    		G_LOG_DOMAIN, __FILE__, __LINE__, G_STRFUNC, \
			    		message); \
			   	g_free (message); \
				g_free (nastr); \
				g_free (nbstr); \
				g_free (diffstr); \
			} \
		} G_STMT_END

G_END_DECLS

#endif
