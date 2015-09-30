#ifndef CRANK128_H
#define CRANK128_H

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
#error crank128.h cannot be included directly.
#endif

#include <glib.h>

#include "crankbits.h"

/**
 * CrankUint128:
 * @h: 64 bits at high position.
 * @l: 64 bits at low position.
 *
 * Represents 128-bit unsigned integer.
 */
typedef struct _CrankUint128 {
	guint64	h;
	guint64	l;
} CrankUint128;



void	crank_uint128_init_add			(CrankUint128*	i,
										 guint64		a,
										 guint64		b	);

void	crank_uint128_init_mul			(CrankUint128*	i,
										 guint64		a,
										 guint64		b	);



void	crank_uint128_copy				(CrankUint128*	i,
										 CrankUint128*	r	);



void	crank_uint128_add64				(CrankUint128*	a,
										 guint64		b,
										 CrankUint128*	r	);

void	crank_uint128_add64_self		(CrankUint128*	a,
										 guint64		b	);

void	crank_uint128_add				(CrankUint128*	a,
										 CrankUint128*	b,
										 CrankUint128*	r	);

void	crank_uint128_add_self			(CrankUint128*	a,
										 CrankUint128*	b	);


void	crank_uint128_sub64				(CrankUint128*	a,
										 guint64		b,
										 CrankUint128*	r	);

void	crank_uint128_sub64_self		(CrankUint128*	a,
										 guint64		b	);

void	crank_uint128_sub				(CrankUint128*	a,
										 CrankUint128*	b,
										 CrankUint128*	r	);

void	crank_uint128_sub_self			(CrankUint128*	a,
										 CrankUint128*	b	);



void	crank_uint128_mul64				(CrankUint128*	a,
										 guint64		b,
										 CrankUint128*	r	);

void	crank_uint128_mul64_self		(CrankUint128*	a,
										 guint64		b	);

void	crank_uint128_div64				(CrankUint128*	a,
										 guint64		b,
										 CrankUint128*	r	);

void	crank_uint128_div64_self		(CrankUint128*	a,
										 guint64		b	);

void	crank_uint128_div32				(CrankUint128*	a,
							   			 guint32		b,
							   			 CrankUint128*	r	);

void	crank_uint128_div32_self		(CrankUint128*	a,
							   			 guint32		b	);


void	crank_uint128_lsh				(CrankUint128*	a,
							 			 const guint	b,
							 			 CrankUint128*	r	);

void	crank_uint128_lsh_self			(CrankUint128*	a,
							 			 const guint	b	);

void	crank_uint128_rsh				(CrankUint128*	a,
							 			 const guint	b,
							 			 CrankUint128*	r	);

void	crank_uint128_rsh_self			(CrankUint128*	a,
							 			 const guint	b	);

#define crank_uint128_init_add(i,a,b)	\
	(i)->h = CRANK_ADD_CARRY64(a,b,&((i)->l))

#define crank_uint128_copy(i,r)	\
		G_STMT_START {			\
			(r)->h = (i)->h;	\
			(r)->l = (i)->l;	\
		} G_STMT_END

#define crank_uint128_add64(a,b,r) 										\
		G_STMT_START {													\
			(r)->h = (a)->h + CRANK_ADD_CARRY64((a)->l, b, &((r)->l));	\
		} G_STMT_END

#define crank_uint128_add64_self(a,b)	 				\
		G_STMT_START {									\
			(a)->h += CRANK_IADD_CARRY64(&((a)->l), b);	\
		} G_STMT_END

#define crank_uint128_add(a,b,r) 									\
		G_STMT_START {												\
			(r)->h = (a)->h + (b)->h +								\
					 CRANK_ADD_CARRY64((a)->l, (b)->l, &((r)->l));	\
		} G_STMT_END

#define crank_uint128_add_self(a,b) 							\
		G_STMT_START {											\
			(a)->h += (b)->h +									\
					  CRANK_IADD_CARRY64(&((a)->l), (b)->l);	\
		} G_STMT_END

#define	crank_uint128_sub64(a,b,r)				\
		G_STMT_START {							\
			(r)->h = (a)->h - ((a)->l < (b));	\
			(r)->l = (a)->l - b;				\
		} G_STMT_END

#define crank_uint128_sub64_self(a,b,r)			\
		G_STMT_START {							\
			(a)->h -= ((a)->l < b);				\
			(a)->l -= (b);						\
		} G_STMT_END

#define crank_uint128_sub(a,b,r)							\
		G_STMT_START {										\
			(r)->h = (a)->h - (b)->h - ((a)->l < (b)->l);	\
			(r)->l = (a)->l - (b)->l;						\
		} G_STMT_END

#define crank_uint128_sub_self(a,b)						\
		G_STMT_START {									\
			(a)->h -= (b)->h + ((a)->l < (b)->l);		\
			(a)->l -= (b)->l;							\
		} G_STMT_END

#define crank_uint128_lsh(a,b,r)							\
		G_STMT_START {										\
			(r)->h = ((a)->h << (b)) | ((a)->l >> (64-(b)));	\
			(r)->l = ((a)->l << (b));							\
		} G_STMT_END

#define crank_uint128_lsh_self(a,b)							\
		G_STMT_START {											\
			(a)->h = ((a)->h << (b)) | ((a)->l >> (64-(b)));	\
			(a)->l <<= (b);										\
		} G_STMT_END

#define crank_uint128_rsh(a,b,r)							\
		G_STMT_START {										\
			(r)->h = (a)->h >> (b);							\
			(r)->l = ((a)->h << (64-b)) | ((a)->l >> (b));	\
		} G_STMT_END

#define crank_uint128_rsh_self(a,b)						\
		G_STMT_START {										\
			(a)->l = ((a)->h << (64-b)) | ((a)->l >> (b));	\
			(a)->h >>= (b);							\
		} G_STMT_END

 #endif //CRANK128_H
