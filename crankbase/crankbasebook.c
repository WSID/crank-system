/* Copyright (C) 2015, WSID   */

/* This file is part of Crank System.
 *
 *  Crank System is free software: you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation, either
 *  version 3 of the License, or (at your option) any later version.
 *
 *  Crank System is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with Crank System.
 *  If not, see <http://www.gnu.org/licenses/>.
 */
#define _CRANKBASE_INSIDE

#include "crankfuncholder.h"
#include "crankbasebook.h"
#include "crankvalue.h"

/**
 * SECTION: crankbasebook
 * @title: Crank Base basic function book.
 * @short_description: Basic function book on Crank Base.
 * @stability: Unstable
 * @include: crankbase.h
 *
 * This defines basic operations in form of GValue functions.
 */


static CrankFuncHolder*		_crank_base_holder_add;
static CrankFuncHolder*		_crank_base_holder_sub;
static CrankFuncHolder*		_crank_base_holder_mul;
static CrankFuncHolder*		_crank_base_holder_div;
static CrankFuncHolder*		_crank_base_holder_neg;
static CrankFuncHolder*		_crank_base_holder_inc;
static CrankFuncHolder*		_crank_base_holder_dec;
static CrankFuncHolder*		_crank_base_holder_lshift;
static CrankFuncHolder*		_crank_base_holder_rshift;
static CrankFuncHolder*		_crank_base_holder_less;
static CrankFuncHolder*		_crank_base_holder_leq;
static CrankFuncHolder*		_crank_base_holder_eq;
static CrankFuncHolder*		_crank_base_holder_geq;
static CrankFuncHolder*		_crank_base_holder_greater;

// Macros that define functions.

#define FNAME(T, name)	name ## _ ## T
#define DEFINE_UOP(T, name, op) static T FNAME(T, name) (T a) { return op a; }
#define DEFINE_BOP(T, name, op)	static T FNAME(T, name) (T a, T b) { return a op b; }

#define DEFINE_AIRTH(T) \
		DEFINE_BOP(T, add, +) \
		DEFINE_BOP(T, sub, -) \
		DEFINE_BOP(T, mul, *) \
		DEFINE_BOP(T, div, /)

#define DEFINE_INCDEC(T) \
		DEFINE_UOP(T, inc, ++) \
		DEFINE_UOP(T, dec, --)

#define DEFINE_SHIFTS(T) \
		static T FNAME(T, lshift) (T a, guint b) { return a << b; } \
		static T FNAME(T, rshift) (T a, guint b) { return a >> b; }

#define DEFINE_COMPARES(T) \
		static gboolean FNAME(T, less) (T a, T b) { return a < b; } \
		static gboolean FNAME(T, leq) (T a, T b) { return a <= b; } \
		static gboolean FNAME(T, eq) (T a, T b) { return a == b; } \
		static gboolean FNAME(T, geq) (T a, T b) { return a >= b; } \
		static gboolean FNAME(T, greater) (T a, T b) { return a > b; }

#define DEFINE_COMPARES_FUNC(T, cmp) \
		static gboolean FNAME(T, less) (T a, T b) { return cmp(a, b) < 0; } \
		static gboolean FNAME(T, leq) (T a, T b) { return cmp(a, b) <= 0; } \
		static gboolean FNAME(T, eq) (T a, T b) { return cmp(a, b) == 0; } \
		static gboolean FNAME(T, geq) (T a, T b) { return cmp(a, b) >= 0; } \
		static gboolean FNAME(T, greater) (T a, T b) { return cmp(a, b) > 0; }


// Macros that register functions.

#define SETF(T, FT, name) crank_func_holder_set_func ( \
		_crank_base_holder_ ## name, \
		FT, \
		(CrankCallback)FNAME (T, name), NULL, NULL, NULL )

#define SETUOP(T, name) SETF (T, ftype_ ## T ## __ ## T , name)
#define SETBOP(T, name) SETF (T, ftype_ ## T ## __ ## T ## _ ## T, name)

#define SETAIRTH(T) \
	SETBOP (T, add); \
	SETBOP (T, sub); \
	SETBOP (T, mul); \
	SETBOP (T, div)

#define SETINCDEC(T) \
	SETUOP (T, inc); \
	SETUOP (T, dec)

#define SETSHIFTS(T) \
	SETF(T, ftype_ ## T ## __ ## T ## _ ## guint , lshift); \
	SETF(T, ftype_ ## T ## __ ## T ## _ ## guint , rshift)

#define SETCOMPARES(T) \
	SETF(T, ftype_ ## gboolean ## __ ## T ## _ ## T, less); \
	SETF(T, ftype_ ## gboolean ## __ ## T ## _ ## T, leq); \
	SETF(T, ftype_ ## gboolean ## __ ## T ## _ ## T, eq); \
	SETF(T, ftype_ ## gboolean ## __ ## T ## _ ## T, geq); \
	SETF(T, ftype_ ## gboolean ## __ ## T ## _ ## T, greater)



DEFINE_AIRTH(gchar)
DEFINE_AIRTH(gint)
DEFINE_AIRTH(glong)
DEFINE_AIRTH(gint64)
DEFINE_AIRTH(gfloat)
DEFINE_AIRTH(gdouble)

DEFINE_UOP(gchar, neg, -)
DEFINE_UOP(gint, neg, -)
DEFINE_UOP(glong, neg, -)
DEFINE_UOP(gint64, neg, -)
DEFINE_UOP(gfloat, neg, -)
DEFINE_UOP(gdouble, neg, -)

DEFINE_INCDEC(gchar)
DEFINE_INCDEC(gint)
DEFINE_INCDEC(glong)
DEFINE_INCDEC(gint64)

DEFINE_SHIFTS (gchar)
DEFINE_SHIFTS (gint)
DEFINE_SHIFTS (glong)
DEFINE_SHIFTS (gint64)

DEFINE_COMPARES (gchar)
DEFINE_COMPARES (gint)
DEFINE_COMPARES (glong)
DEFINE_COMPARES (gint64)
DEFINE_COMPARES (gfloat)
DEFINE_COMPARES (gdouble)

/**
 * CRANK_BOOK_BASE:
 *
 * A #CrankFuncBook defines basic operations, including airthmetics.
 */


CrankFuncBook*
crank_base_get_book (void)
{
	static CrankFuncBook* book = NULL;

	if (G_UNLIKELY(book == NULL)) {
		CrankFuncType*	ftype_gchar__gchar_gchar;
		CrankFuncType*	ftype_gint__gint_gint;
		CrankFuncType*	ftype_glong__glong_glong;
		CrankFuncType*	ftype_gint64__gint64_gint64;

		CrankFuncType*	ftype_gfloat__gfloat_gfloat;
		CrankFuncType*	ftype_gdouble__gdouble_gdouble;

		CrankFuncType*	ftype_gchar__gchar;
		CrankFuncType*	ftype_gint__gint;
		CrankFuncType*	ftype_glong__glong;
		CrankFuncType*	ftype_gint64__gint64;

		CrankFuncType*	ftype_gfloat__gfloat;
		CrankFuncType*	ftype_gdouble__gdouble;


		CrankFuncType*	ftype_gchar__gchar_guint;
		CrankFuncType*	ftype_gint__gint_guint;
		CrankFuncType*	ftype_glong__glong_guint;
		CrankFuncType*	ftype_gint64__gint64_guint;

		CrankFuncType*	ftype_gboolean__gchar_gchar;
		CrankFuncType*	ftype_gboolean__gint_gint;
		CrankFuncType*	ftype_gboolean__glong_glong;
		CrankFuncType*	ftype_gboolean__gint64_gint64;
		CrankFuncType*	ftype_gboolean__gfloat_gfloat;
		CrankFuncType*	ftype_gboolean__gdouble_gdouble;

		_crank_base_holder_add = crank_func_holder_new ("add");
		_crank_base_holder_sub = crank_func_holder_new ("sub");
		_crank_base_holder_mul = crank_func_holder_new ("mul");
		_crank_base_holder_div = crank_func_holder_new ("div");
		_crank_base_holder_neg = crank_func_holder_new ("neg");
		_crank_base_holder_inc = crank_func_holder_new ("inc");
		_crank_base_holder_dec = crank_func_holder_new ("dec");
		_crank_base_holder_lshift = crank_func_holder_new ("lshift");
		_crank_base_holder_rshift = crank_func_holder_new ("rshift");
		_crank_base_holder_less = crank_func_holder_new ("less");
		_crank_base_holder_leq = crank_func_holder_new ("leq");
		_crank_base_holder_eq = crank_func_holder_new ("eq");
		_crank_base_holder_geq = crank_func_holder_new ("geq");
		_crank_base_holder_greater = crank_func_holder_new ("greater");

		book = crank_func_book_new_with_name ("crank-base");

		crank_func_book_set (book, CRANK_BASE_BOOK_ADD, _crank_base_holder_add);
		crank_func_book_set (book, CRANK_BASE_BOOK_SUB, _crank_base_holder_sub);
		crank_func_book_set (book, CRANK_BASE_BOOK_MUL, _crank_base_holder_mul);
		crank_func_book_set (book, CRANK_BASE_BOOK_DIV, _crank_base_holder_div);
		crank_func_book_set (book, CRANK_BASE_BOOK_NEG, _crank_base_holder_neg);
		crank_func_book_set (book, CRANK_BASE_BOOK_INC, _crank_base_holder_inc);
		crank_func_book_set (book, CRANK_BASE_BOOK_DEC, _crank_base_holder_dec);
		crank_func_book_set (book, CRANK_BASE_BOOK_LSHIFT, _crank_base_holder_lshift);
		crank_func_book_set (book, CRANK_BASE_BOOK_RSHIFT, _crank_base_holder_rshift);
		crank_func_book_set (book, CRANK_BASE_BOOK_LESS, _crank_base_holder_less);
		crank_func_book_set (book, CRANK_BASE_BOOK_LEQ, _crank_base_holder_leq);
		crank_func_book_set (book, CRANK_BASE_BOOK_EQ, _crank_base_holder_eq);
		crank_func_book_set (book, CRANK_BASE_BOOK_GEQ, _crank_base_holder_geq);
		crank_func_book_set (book, CRANK_BASE_BOOK_GREATER, _crank_base_holder_greater);

		ftype_gchar__gchar_gchar = crank_func_type_new (G_TYPE_CHAR,
				G_TYPE_CHAR, G_TYPE_CHAR, G_TYPE_NONE );

		ftype_gint__gint_gint = crank_func_type_new (G_TYPE_INT,
				G_TYPE_INT, G_TYPE_INT, G_TYPE_NONE );

		ftype_glong__glong_glong = crank_func_type_new (G_TYPE_LONG,
				G_TYPE_LONG, G_TYPE_LONG, G_TYPE_NONE );

		ftype_gint64__gint64_gint64 = crank_func_type_new (G_TYPE_INT64,
				G_TYPE_INT64, G_TYPE_INT64, G_TYPE_NONE );


		ftype_gfloat__gfloat_gfloat = crank_func_type_new (G_TYPE_FLOAT,
				G_TYPE_FLOAT, G_TYPE_FLOAT, G_TYPE_NONE );

		ftype_gdouble__gdouble_gdouble = crank_func_type_new (G_TYPE_DOUBLE,
				G_TYPE_DOUBLE, G_TYPE_DOUBLE, G_TYPE_NONE );


		ftype_gchar__gchar = crank_func_type_new (G_TYPE_CHAR,
			G_TYPE_CHAR, G_TYPE_NONE);

		ftype_gint__gint = crank_func_type_new (G_TYPE_INT,
			G_TYPE_INT, G_TYPE_NONE);

		ftype_glong__glong = crank_func_type_new (G_TYPE_LONG,
			G_TYPE_LONG, G_TYPE_NONE);

		ftype_gint64__gint64 = crank_func_type_new (G_TYPE_INT64,
			G_TYPE_INT64, G_TYPE_NONE);

		ftype_gfloat__gfloat = crank_func_type_new (G_TYPE_FLOAT,
			G_TYPE_FLOAT, G_TYPE_NONE);

		ftype_gdouble__gdouble = crank_func_type_new (G_TYPE_DOUBLE,
			G_TYPE_DOUBLE, G_TYPE_NONE);


		ftype_gchar__gchar_guint = crank_func_type_new (G_TYPE_CHAR,
			G_TYPE_CHAR, G_TYPE_UINT, G_TYPE_NONE);

		ftype_gint__gint_guint = crank_func_type_new (G_TYPE_INT,
			G_TYPE_INT, G_TYPE_UINT, G_TYPE_NONE);

		ftype_glong__glong_guint = crank_func_type_new (G_TYPE_LONG,
			G_TYPE_LONG, G_TYPE_UINT, G_TYPE_NONE);

		ftype_gint64__gint64_guint = crank_func_type_new (G_TYPE_INT64,
			G_TYPE_INT64, G_TYPE_UINT, G_TYPE_NONE);


		ftype_gboolean__gchar_gchar = crank_func_type_new (G_TYPE_BOOLEAN,
			G_TYPE_CHAR, G_TYPE_CHAR, G_TYPE_NONE);

		ftype_gboolean__gint_gint = crank_func_type_new (G_TYPE_BOOLEAN,
			G_TYPE_INT, G_TYPE_INT, G_TYPE_NONE);

		ftype_gboolean__glong_glong = crank_func_type_new (G_TYPE_BOOLEAN,
			G_TYPE_LONG, G_TYPE_LONG, G_TYPE_NONE);

		ftype_gboolean__gint64_gint64 = crank_func_type_new (G_TYPE_BOOLEAN,
			G_TYPE_INT64, G_TYPE_INT64, G_TYPE_NONE);

		ftype_gboolean__gfloat_gfloat = crank_func_type_new (G_TYPE_BOOLEAN,
			G_TYPE_FLOAT, G_TYPE_FLOAT, G_TYPE_NONE);

		ftype_gboolean__gdouble_gdouble = crank_func_type_new (G_TYPE_BOOLEAN,
			G_TYPE_DOUBLE, G_TYPE_DOUBLE, G_TYPE_NONE);

		SETAIRTH (gchar);
		SETAIRTH (gint);
		SETAIRTH (glong);
		SETAIRTH (gint64);

		SETAIRTH (gfloat);
		SETAIRTH (gdouble);

		SETUOP (gchar, neg);
		SETUOP (gint, neg);
		SETUOP (glong, neg);
		SETUOP (gint64, neg);
		SETUOP (gfloat, neg);
		SETUOP (gdouble, neg);

		SETINCDEC (gchar);
		SETINCDEC (gint);
		SETINCDEC (glong);
		SETINCDEC (gint64);

		SETSHIFTS (gchar);
		SETSHIFTS (gint);
		SETSHIFTS (glong);
		SETSHIFTS (gint64);

		SETCOMPARES (gchar);
		SETCOMPARES (gint);
		SETCOMPARES (glong);
		SETCOMPARES (gint64);
		SETCOMPARES (gfloat);
		SETCOMPARES (gdouble);

		crank_func_type_unref (ftype_gchar__gchar_gchar);
		crank_func_type_unref (ftype_gint__gint_gint);
		crank_func_type_unref (ftype_glong__glong_glong);
		crank_func_type_unref (ftype_gint64__gint64_gint64);

		crank_func_type_unref (ftype_gchar__gchar_guint);
		crank_func_type_unref (ftype_gint__gint_guint);
		crank_func_type_unref (ftype_glong__glong_guint);
		crank_func_type_unref (ftype_gint64__gint64_guint);

		crank_func_type_unref (ftype_gfloat__gfloat_gfloat);
		crank_func_type_unref (ftype_gdouble__gdouble_gdouble);

		crank_func_type_unref (ftype_gboolean__gchar_gchar);
		crank_func_type_unref (ftype_gboolean__gint_gint);
		crank_func_type_unref (ftype_gboolean__glong_glong);
		crank_func_type_unref (ftype_gboolean__gint64_gint64);
		crank_func_type_unref (ftype_gboolean__gfloat_gfloat);
		crank_func_type_unref (ftype_gboolean__gdouble_gdouble);
	}

	return book;
}

/**
 * crank_base_add:
 * @r: (out): Result.
 * @a: A value
 * @b: A value
 *
 * Adds @b on @a and stores it to @r. ( @r = @a + @b )
 *
 * Returns: %TRUE If the adding function exists.
 */
gboolean
crank_base_add (GValue* r, GValue* a, GValue* b)
{
	return crank_func_book_invokev_overwrite (
			CRANK_BOOK_BASE,
			CRANK_BASE_BOOK_ADD,
			r,
			NULL,
			2, a, b);
}

/**
 * crank_base_sub:
 * @r: (out): Result.
 * @a: A value
 * @b: A value
 *
 * Subtract @b from @a and stores it to @r. ( @r = @a - @b )
 *
 * Returns: %TRUE if the subtracting function exists.
 */
gboolean
crank_base_sub (GValue* r, GValue* a, GValue* b)
{
	return crank_func_book_invokev_overwrite (
			CRANK_BOOK_BASE,
			CRANK_BASE_BOOK_SUB,
			r,
			NULL,
			2, a, b);
}

/**
 * crank_base_mul:
 * @r: (out): Result.
 * @a: A value
 * @b: A value
 *
 * Multiple @a by @b and stores it to @r. ( @r = @a * @b )
 *
 * Returns: %TRUE if the multiplying function exists.
 */
gboolean
crank_base_mul (GValue* r, GValue* a, GValue* b)
{
	return crank_func_book_invokev_overwrite (
			CRANK_BOOK_BASE,
			CRANK_BASE_BOOK_MUL,
			r,
			NULL,
			2, a, b);
}

/**
 * crank_base_div:
 * @r: (out): Result.
 * @a: A value
 * @b: A value
 *
 * Divide @a by @b and stores it to @r. ( @r = @a / @b )
 *
 * Returns: %TRUE if the dividing function exists.
 */
gboolean
crank_base_div (GValue* r, GValue* a, GValue* b)
{
	return crank_func_book_invokev_overwrite (
			CRANK_BOOK_BASE,
			CRANK_BASE_BOOK_DIV,
			r,
			NULL,
			2, a, b);
}


/**
 * crank_base_neg:
 * @r: (out): Result.
 * @a: A value
 *
 * Stores negation of @a to @r. ( @r = -@a )
 *
 * Generally this means @a multiplied by -1, or subtract 0 by @a.
 *
 * Returns: %TRUE if the negation function exists.
 */
gboolean
crank_base_neg (GValue* r, GValue* a)
{
	return crank_func_book_invokev_overwrite (
			CRANK_BOOK_BASE,
			CRANK_BASE_BOOK_NEG,
			r,
			NULL,
			1, a);
}

/**
 * crank_base_inc:
 * @r: (out): Result.
 * @a: A value
 *
 * Increase value of @a by one unit and stores it to @r. ( @r = ++@a )
 *
 * For values of most type, it means adding by 1.
 *
 * Returns: %TRUE if the increase function exists.
 */
gboolean
crank_base_inc (GValue* r, GValue* a)
{
	return crank_func_book_invokev_overwrite (
			CRANK_BOOK_BASE,
			CRANK_BASE_BOOK_INC,
			r,
			NULL,
			1, a);
}


/**
 * crank_base_dec:
 * @r: (out): Result
 * @a: A value
 *
 * Decrease value of @a by one unit and stores it to @r. ( @r = --@a )
 *
 * For values of most type, it means subtracting by 1.
 *
 * Returns: %TRUE if the decrease function exists.
 */
gboolean
crank_base_dec (GValue* r, GValue* a)
{
	return crank_func_book_invokev_overwrite (
			CRANK_BOOK_BASE,
			CRANK_BASE_BOOK_DEC,
			r,
			NULL,
			1, a);
}

/**
 * crank_base_lshift:
 * @r: (out): Result.
 * @a: A value
 * @b: Shift amount
 *
 * Shifts value of @a by @b and stores it to @r. ( @r = @a << @b )
 *
 * Generally type of @b is #guint.
 *
 * Returns: %TRUE if the shift function exists.
 */
gboolean
crank_base_lshift (GValue* r, GValue* a, GValue* b)
{
	return crank_func_book_invokev_overwrite (
			CRANK_BOOK_BASE,
			CRANK_BASE_BOOK_LSHIFT,
			r,
			NULL,
			2, a, b);
}


/**
 * crank_base_rshift:
 * @r: (out): Result.
 * @a: A value
 * @b: Shift amount
 *
 * Shifts value of @a by @b and stores it to @r. ( @r = @a >> @b )
 *
 * Generally type of @b is #guint.
 *
 * Returns: %TRUE if the shift function exists.
 */
gboolean
crank_base_rshift (GValue* r, GValue* a, GValue* b)
{
	return crank_func_book_invokev_overwrite (
			CRANK_BOOK_BASE,
			CRANK_BASE_BOOK_RSHIFT,
			r,
			NULL,
			2, a, b);
}


/**
 * crank_base_less:
 * @r: (out): Result.
 * @a: A value
 * @b: A value
 *
 * Checks @a is less than @b and stores it to @r. ( @r = @a < @b )
 *
 * Generally #gboolean is stored in @r.
 *
 * Returns: %TRUE if comparsion function exists.
 */
gboolean
crank_base_less (GValue* r, GValue* a, GValue* b)
{
	return crank_func_book_invokev_overwrite (
			CRANK_BOOK_BASE,
			CRANK_BASE_BOOK_LESS,
			r,
			NULL,
			2, a, b);
}

/**
 * crank_base_leq:
 * @r: (out): Result.
 * @a: A value
 * @b: A value
 *
 * Checks @a is less or equal to @b and stores it to @r  ( @r = @a <= @b )
 *
 * Generally #gboolean is stored in @r.
 *
 * Returns: %TRUE if comparsion function exists.
 */
gboolean
crank_base_leq (GValue* r, GValue* a, GValue* b)
{
	return crank_func_book_invokev_overwrite (
			CRANK_BOOK_BASE,
			CRANK_BASE_BOOK_LEQ,
			r,
			NULL,
			2, a, b);
}


/**
 * crank_base_eq:
 * @r: (out): Result.
 * @a: A value
 * @b: A value
 *
 * Checks @a is equal to @b and stores it to @r. ( @r = @a == @b )
 *
 * Generally #gboolean is stored in @r.
 *
 * Returns: %TRUE if comparsion function exists.
 */
gboolean
crank_base_eq (GValue* r, GValue* a, GValue* b)
{
	return crank_func_book_invokev_overwrite (
			CRANK_BOOK_BASE,
			CRANK_BASE_BOOK_EQ,
			r,
			NULL,
			2, a, b);
}

/**
 * crank_base_geq:
 * @r: (out): Result.
 * @a: A value
 * @b: A value
 *
 * Checks @a is greater or equal to @b and stores it to @r. ( @r = @a >= @b )
 *
 * Generally #gboolean is stored in @r.
 *
 * Returns: %TRUE if comparsion function exists.
 */
gboolean
crank_base_geq (GValue* r, GValue* a, GValue* b)
{
	return crank_func_book_invokev_overwrite (
			CRANK_BOOK_BASE,
			CRANK_BASE_BOOK_GEQ,
			r,
			NULL,
			2, a, b);
}

/**
 * crank_base_greater:
 * @r: (out): Result.
 * @a: A value
 * @b: A value
 *
 * Checks @a is greater than @b and stores it to @r. ( @r = @a >= @b )
 *
 * Generally #gboolean is stored in @r.
 *
 * Returns: %TRUE if comparsion function exists.
 */
gboolean
crank_base_greater (GValue* r, GValue* a, GValue* b)
{
	return crank_func_book_invokev_overwrite (
			CRANK_BOOK_BASE,
			CRANK_BASE_BOOK_GREATER,
			r,
			NULL,
			2, a, b);
}




/**
 * crank_base_std_lshift:
 * @r: (out): Result.
 * @a: A value
 * @b: Shift amount.
 *
 * Shifts value of @a by @b.
 *
 * If function does not exist, @r is unsetted.
 */
void
crank_base_std_lshift (GValue* r, GValue* a, guint b)
{
	GValue values[2] = { {0}, {0} };

	crank_value_overwrite (values + 0, a);
	g_value_init (values + 1, G_TYPE_UINT);
	g_value_set_uint (values + 1, b);

	crank_func_book_invoke_overwrite (
			CRANK_BOOK_BASE, CRANK_BASE_BOOK_LSHIFT, r, 2, values, NULL);

	g_value_unset (values + 0);
	g_value_unset (values + 1);
}

/**
 * crank_base_std_rshift:
 * @r: (out): Result.
 * @a: A value
 * @b: Shift amount.
 *
 * Shifts value of @a by @b.
 *
 * If function does not exist, @r is unsetted.
 */
void
crank_base_std_rshift (GValue* r, GValue* a, guint b)
{
	GValue values[2] = { {0}, {0} };

	crank_value_overwrite (values + 0, a);
	g_value_init (values + 1, G_TYPE_UINT);
	g_value_set_uint (values + 1, b);

	crank_func_book_invoke_overwrite (
			CRANK_BOOK_BASE, CRANK_BASE_BOOK_RSHIFT, r, 2, values, NULL);

	g_value_unset (values + 0);
	g_value_unset (values + 1);
}



/**
 * crank_base_std_less:
 * @a: A value
 * @b: A value
 *
 * Checks @a is less than @b, and transform result into #gboolean.
 *
 * If function is not found or the result cannot transformed into #gboolean,
 * %FALSE is returned.
 *
 * Returns: @a is less than @b?
 */
gboolean
crank_base_std_less (GValue* a, GValue* b)
{
	GValue r = {0};
	GValue t = {0};

	if (crank_base_less (&r, a, b)) {
		g_value_init (&t, G_TYPE_BOOLEAN);

		if (g_value_transform (&r, &t)) return g_value_get_boolean (&t);
	}
	return FALSE;
}

/**
 * crank_base_std_leq:
 * @a: A value
 * @b: A value
 *
 * Checks @a is less or equal to @b, and transform the result into #gboolean.
 *
 * If function is not found or the result cannot transformed into #gboolean,
 * %FALSE is returned.
 *
 * Returns: @a is less or equal to @b?
 */
gboolean
crank_base_std_leq (GValue* a, GValue* b)
{
	GValue r = {0};
	GValue t = {0};

	if (crank_base_leq (&r, a, b)) {
		g_value_init (&t, G_TYPE_BOOLEAN);

		if (g_value_transform (&r, &t)) return g_value_get_boolean (&t);
	}
	return FALSE;
}

/**
 * crank_base_std_eq:
 * @a: A value
 * @b: A value
 *
 * Checks @a is equal to @b, and transform the result into #gboolean.
 *
 * If function is not found or the result cannot transformed into #gboolean,
 * %FALSE is returned.
 *
 * Returns: @a is equal to @b?
 */
gboolean
crank_base_std_eq (GValue* a, GValue* b)
{
	GValue r = {0};
	GValue t = {0};

	if (crank_base_eq (&r, a, b)) {
		g_value_init (&t, G_TYPE_BOOLEAN);

		if (g_value_transform (&r, &t)) return g_value_get_boolean (&t);
	}
	return FALSE;
}

/**
 * crank_base_std_geq:
 * @a: A value
 * @b: A value
 *
 * Checks @a is greater or equal to @b, and transform the result into #gboolean.
 *
 * If function is not found or the result cannot transformed into #gboolean,
 * %FALSE is returned.
 *
 * Returns: @a is less than @b?
 */
gboolean
crank_base_std_geq (GValue* a, GValue* b)
{
	GValue r = {0};
	GValue t = {0};

	if (crank_base_geq (&r, a, b)) {
		g_value_init (&t, G_TYPE_BOOLEAN);

		if (g_value_transform (&r, &t)) return g_value_get_boolean (&t);
	}
	return FALSE;
}

/**
 * crank_base_std_greater:
 * @a: A value
 * @b: A value
 *
 * Checks @a is greater than @b.
 *
 * If function is not found or the result cannot transformed into #gboolean,
 * %FALSE is returned.
 *
 * Returns: @a is less than @b?
 */
gboolean
crank_base_std_greater (GValue* a, GValue* b)
{
	GValue r = {0};
	GValue t = {0};

	if (crank_base_greater (&r, a, b)) {
		g_value_init (&t, G_TYPE_BOOLEAN);

		if (g_value_transform (&r, &t)) return g_value_get_boolean (&t);
	}
	return FALSE;
}
