#ifndef CRANKBASEBOOK_H
#define CRANKBASEBOOK_H

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

#include <stdarg.h>
#include <glib.h>
#include <glib-object.h>

#include "crankbasemacro.h"
#include "crankfuncholder.h"

G_BEGIN_DECLS

typedef enum _CrankBaseBookFunc {
	CRANK_BASE_BOOK_ADD,
	CRANK_BASE_BOOK_SUB,
	CRANK_BASE_BOOK_MUL,
	CRANK_BASE_BOOK_DIV,
	
	CRANK_BASE_BOOK_NEG,
	
	CRANK_BASE_BOOK_INC,
	CRANK_BASE_BOOK_DEC,
	
	CRANK_BASE_BOOK_LSHIFT,
	CRANK_BASE_BOOK_RSHIFT,
	
	CRANK_BASE_BOOK_LESS,
	CRANK_BASE_BOOK_LEQ,
	CRANK_BASE_BOOK_EQ,
	CRANK_BASE_BOOK_GEQ,
	CRANK_BASE_BOOK_GREATER
} CrankBaseBookFunc;

#define CRANK_BOOK_BASE (crank_base_get_book())
CrankFuncBook*			crank_base_get_book (void);

gboolean				crank_base_add (GValue*	r, GValue* a, GValue* b);
gboolean				crank_base_sub (GValue* r, GValue* a, GValue* b);
gboolean				crank_base_mul (GValue* r, GValue* a, GValue* b);
gboolean				crank_base_div (GValue* r, GValue* a, GValue* b);

gboolean				crank_base_neg (GValue* r, GValue* a);

gboolean				crank_base_inc (GValue* r, GValue* a);
gboolean				crank_base_dec (GValue* r, GValue* a);

gboolean				crank_base_lshift (GValue* r, GValue* a, GValue* b);
gboolean				crank_base_rshift (GValue* r, GValue* a, GValue* b);

gboolean				crank_base_less (GValue* r, GValue* a, GValue* b);
gboolean				crank_base_leq (GValue* r, GValue* a, GValue* b);
gboolean				crank_base_eq (GValue* r, GValue* a, GValue* b);
gboolean				crank_base_geq (GValue* r, GValue* a, GValue* b);
gboolean				crank_base_greater (GValue* r, GValue* a, GValue* b);

void					crank_base_std_lshift (GValue* r, GValue* a, guint b);
void					crank_base_std_rshift (GValue* r, GValue* a, guint b);

gboolean				crank_base_std_less (GValue* a, GValue* b);
gboolean				crank_base_std_leq (GValue* a, GValue* b);
gboolean				crank_base_std_eq (GValue* a, GValue* b);
gboolean				crank_base_std_geq (GValue* a, GValue* b);
gboolean				crank_base_std_greater (GValue* a, GValue* b);

G_END_DECLS

#endif //CRANKBASEBOOK_H
