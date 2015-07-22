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

//////// Adding meta-testcases /////////////////////////////////////////////////

void	crank_test_add_func_expected_fail (	const gchar* 	path,
											GTestFunc		func	);


//////// Assertions ////////////////////////////////////////////////////////////

/**
 * crank_assert_eqarray_float: (skip)
 * @a: (element-type gfloat) (array length=an): A array
 * @an: (type guint): Length of elements.
 * @b: (element-type gfoat) (array length=bn): A array
 * @bn: (type guint): Length of elements.
 *
 * Asserts two float arrays are equals.
 */
#define crank_assert_eqarray_float(a,an,b,bn)	\
	_crank_assert_eqarray(gfloat,a,an,b,bn,crank_float_equal,crank_float_to_string,NULL)


/**
 * crank_assert_eqarray_float_imm: (skip)
 * @a: (element-type gfloat) (array length=an): A array
 * @an: (type guint): Length of elements.
 * @...: Variadic list to compare with @a.
 *
 * Asserts a given float array has same element with @....
 */
#define crank_assert_eqarray_float_imm(a,an,...)	\
	_crank_assert_eqarray_imm (gfloat,a,an,crank_float_equal,crank_float_to_string,NULL,__VA_ARGS__)

/**
 * crank_assert_eqarray_pointer: (skip)
 * @a: (element-type gpointer) (array length=an): A array
 * @an: (type guint): Length of elements.
 * @b: (element-type gpointer) (array length=bn): A array
 * @bn: (type guint): Length of elements.
 *
 * Asserts two pointer arrays are equals.
 */
#define crank_assert_eqarray_pointer(a,an,b,bn) \
	_crank_assert_eqparray(a,an,b,bn,g_direct_equal,crank_pointer_to_string,NULL)

/**
 * crank_assert_eqarray_pointer_imm: (skip)
 * @a: (element-type gpointer) (array length=an): A array
 * @an: (type guint): Length of elements.
 * @...: Variadic list to compare with @a.
 *
 * Asserts a given pointer array has same elements with @....
 */
#define crank_assert_eqarray_pointer_imm(a,an,...) \
	_crank_assert_eqparray_imm(a,an,g_direct_equal,crank_pointer_to_string,NULL,__VA_ARGS__)


/**
 * crank_assert_eq_glist_imm: (skip)
 * @a: (type GList): A #GList
 * @...: Variadic list to compare with @a.
 *
 * Asserts a given GList has same elements with given variadic list.
 */
#define crank_assert_eq_glist_imm(a,...) \
	_crank_assert_eqp_collection_imm( \
			GList*, \
			(a),g_list_length(a),G_STRINGIFY(a),g_list_nth_data, \
			g_direct_equal, crank_pointer_to_string, NULL, __VA_ARGS__)

/**
 * crank_assert_eq_gptrarray_imm: (skip)
 * @a: (type GPtrArray): A #GPtrArray
 * @...: Variadic list to compare with @a.
 *
 * Asserts a given GPtrArray has same elements with given variadic list.
 */
#define crank_assert_eq_gptrarray_imm(a,...) \
	_crank_assert_eqp_collection_imm( \
			gpointer*, \
			((a)->pdata),((a)->len),G_STRINGIFY(a),_crank_array_index, \
			g_direct_equal, crank_pointer_to_string, NULL, __VA_ARGS__)
			


/**
 * crank_assert_eq_vecfloat2_imm: (skip)
 * @a: (type CrankVecFloat2): A #CrankVecFloat2
 * ...: Variadic list to compare with @a.
 */
#define crank_assert_eq_vecfloat2_imm(a,x,y) \
	crank_assert_eqarray_float_imm((gfloat*)(a), 2, x,y)
/**
 * crank_assert_eq_vecfloat3_imm: (skip)
 * @a: (type CrankVecFloat3): A #CrankVecFloat3
 * ...: Variadic list to compare with @a.
 */
#define crank_assert_eq_vecfloat3_imm(a,x,y,z) \
	crank_assert_eqarray_float_imm((gfloat*)(a), 3, x,y,z)
/**
 * crank_assert_eq_vecfloat4_imm: (skip)
 * @a: (type CrankVecFloat4): A #CrankVecFloat4
 * ...: Variadic list to compare with @a.
 */
#define crank_assert_eq_vecfloat4_imm(a,x,y,z,w) \
	crank_assert_eqarray_float_imm((gfloat*)(a), 4, x,y,z,w)
/**
 * crank_assert_eq_vecfloat_n_imm: (skip)
 * @a: (type CrankVecFloatN): A #CrankVecFloatN
 * ...: Variadic list to compare with @a.
 */
#define crank_assert_eq_vecfloat_n_imm(a,...) \
	crank_assert_eqarray_float_imm((a)->data, (a)->n, __VA_ARGS__)




		
		
/**
 * crank_assert_cmpfloat: (skip)
 * @a: (type gfloat): A #gfloat
 * @cmp: A comparsion operator.
 * @b: (type gfloat): A #gfloat
 *
 * Asserts comparsion of two #gfloat with tolerance of 0.0001f of error.
 */
#define crank_assert_cmpfloat(a,cmp,b)	crank_assert_cmpfloat_d (a,cmp,b,0.0001f)

/**
 * crank_assert_cmpfloat_d: (skip)
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
 * crank_assert_eqcplxfloat: (skip)
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
 * crank_assert_eqcplxfloat_cimm: (skip)
 * @a: (type CrankCplxFloat): A complex
 * @r: (type gfloat): A real part.
 * @i: (type gfloat): A imaginary part.
 *
 * Asserts a given #CrankCplxFloat has same data with tolerance of 0.0001f of
 * error.
 *
 * The difference is calculated from distance on complex plane.
 */
#define crank_assert_eqcplxfloat_cimm(a,r,i) crank_assert_eqcplxfloat_d_cimm(a,r,i,0.0001f)

/**
 * crank_assert_eqcplxfloat_d: (skip)
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
			CrankCplxFloat*	na; \
			CrankCplxFloat*	nb; \
			CrankCplxFloat	diff; \
			gfloat nd = (d); \
			gfloat diff_norm; \
			na = a; \
			nb = b; \
			crank_cplx_float_sub (nb, na, &diff); \
			diff_norm = crank_cplx_float_get_norm (&diff); \
			if (G_UNLIKELY((diff_norm < - nd) || (nd < diff_norm))) { \
				gchar*	nastr = crank_cplx_float_to_string (na); \
				gchar*	nbstr = crank_cplx_float_to_string (nb); \
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
/**
 * crank_assert_eqcplxfloat_d_cimm: (skip)
 * @a: (type CrankCplxFloat): A complex
 * @r: (type gfloat): A real part.
 * @i: (type gfloat): A imaginary part.
 * @d: (type gfloat): Delta
 *
 * Asserts a given #CrankCplxFloat has same data with tolerance of given delta of
 * error.
 *
 * The difference is calculated from distance on complex plane.
 */
#define crank_assert_eqcplxfloat_d_cimm(a,r,i,d) \
		G_STMT_START { \
			CrankCplxFloat	b = {r,i}; \
			crank_assert_eqcplxfloat_d (a, &b, d); \
		} G_STMT_END
		
		

//////// Private Macros ////////////////////////////////////////////////////////

#define	_crank_array_index(a,i)	((a)[i])

#define _crank_array_add(a,i) ((a) + i)

#define _crank_append_collection_content(s,a,n,aname,getter,strf,strfu) \
		G_STMT_START { \
			gchar*	item_str; \
			guint	i; \
			\
			g_string_append_printf ( s, \
					"\n\tContent of %s (length: %u)", \
					aname, n); \
			\
			for (i = 0; i < n; i++) { \
				item_str = strf (getter (a, i), strfu); \
				g_string_append_printf (s, "\n\t\t%s", item_str); \
				g_free (item_str); \
			} \
		} G_STMT_END

#define _crank_assert_eq_collection(G,AT,BT,a,an,aname,agetter,b,bn,bname,bgetter,eqf,strf,strfu)	\
		G_STMT_START { \
			gboolean	fails = FALSE; \
			AT			na = 	(a); \
			guint		nan = 	(an); \
			BT			nb = 	(b); \
			guint		nbn = 	(bn); \
			gpointer	nstrfu = (strfu); \
			guint i; \
			if (nan != nbn) fails = TRUE; \
			else for (i = 0; i < nan; i++) { \
				if (! eqf (agetter(na,i), bgetter(nb,i))) { \
					fails = TRUE; \
					break; \
				} \
			} \
			if (fails) { \
				GString*	msg_build = g_string_new (NULL); \
				g_string_printf (msg_build, "%s == %s", \
						G_STRINGIFY(a), G_STRINGIFY(b) ); \
				\
				_crank_append_collection_content( msg_build, na, nan, aname, agetter, strf, nstrfu); \
				_crank_append_collection_content( msg_build, nb, nbn, bname, bgetter, strf, nstrfu); \
				g_assertion_message (G_LOG_DOMAIN, __FILE__, __LINE__, G_STRFUNC, \
					msg_build->str); \
				g_string_free (msg_build, TRUE); \
				\
			} \
		} G_STMT_END

#define	_crank_assert_eq_collection_imm(G,AT,a,an,aname,agetter,eqf,strf,strfu,...) \
		G_STMT_START { \
			G		b[] = { __VA_ARGS__ }; \
			guint	bn = G_N_ELEMENTS (b); \
			\
			_crank_assert_eq_collection ( \
					G,AT,G*, \
					a,an,aname,agetter, \
					b,bn,"list",_crank_array_add, \
					eqf, strf, strfu ); \
			\
		} G_STMT_END

#define _crank_assert_eqp_collection_imm(AT,a,an,aname,agetter,eqf,strf,strfu,...) \
		G_STMT_START { \
			gpointer	b[] = { __VA_ARGS__ }; \
			guint		bn = G_N_ELEMENTS (b); \
			\
			_crank_assert_eq_collection ( \
					gpointer, AT, gpointer*, \
					a,an,aname,agetter, \
					b,bn,"list",_crank_array_index, \
					eqf, strf, strfu ); \
			\
		} G_STMT_END



#define _crank_assert_eqarray(G,a,an,b,bn,eqf,strf,strfu) \
		_crank_assert_eq_collection( \
				G,G*,G*, \
				a,an,G_STRINGIFY(a),_crank_array_add, \
				b,bn,G_STRINGIFY(b),_crank_array_add, \
				eqf, strf, strfu )

#define _crank_assert_eqarray_imm(G,a,an,eqf,strf,strfu,...) \
		_crank_assert_eq_collection_imm( \
				G,G*, \
				a,an,G_STRINGIFY(a),_crank_array_add, \
				eqf, strf, strfu, \
				__VA_ARGS__ )



#define _crank_assert_eqparray(a,an,b,bn,eqf,strf,strfu) \
		_crank_assert_eq_collection( \
				gpointer, gpointer*, gpointer*, \
				a,an,G_STRINGIFY(a),_crank_array_index, \
				b,bn,G_STRINGIFY(b),_crank_array_index, \
				eqf, strf, strfu )
				
#define _crank_assert_eqparray_imm(a,an,eqf,strf,strfu,...) \
		_crank_assert_eqp_collection_imm( \
				gpointer*, \
				a,an,G_STRINGIFY(a),_crank_array_index, \
				eqf, strf, strfu, __VA_ARGS__ )

//////// Vala support //////////////////////////////////////////////////////////

/**
 * crank_assert_lefloat:
 * @a: (type gfloat): A float value.
 * @b: (type gfloat): A float value.
 * @d: (type gfloat): A acceptable error size.
 *
 * Asserts a is less than b. (a < b)
 *
 * This is used for Vala, which does not support operation as argument.
 */
#define crank_assert_lefloat(a,b,d)	crank_assert_cmpfloat_d(a, <, b, d)

/**
 * crank_assert_eqfloat:
 * @a: (type gfloat): A float value.
 * @b: (type gfloat): A float value.
 * @d: (type gfloat): A acceptable error size.
 *
 * Asserts a is equal to b. (a == b)
 *
 * This is used for Vala, which does not support operation as argument.
 */
#define crank_assert_eqfloat(a,b,d)	crank_assert_cmpfloat_d(a, ==, b, d)

/**
 * crank_assert_gefloat:
 * @a: (type gfloat): A float value.
 * @b: (type gfloat): A float value.
 * @d: (type gfloat): A acceptable error size.
 *
 * Asserts a is greater than b. (a > b)
 *
 * This is used for Vala, which does not support operation as argument.
 */
#define crank_assert_gefloat(a,b,d)	crank_assert_cmpfloat_d(a, >, b, d)

G_END_DECLS

#endif
