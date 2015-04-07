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

#include <glib.h>
#include <glib-object.h>

#include "cranksingular.h"

/**
 * SECTION: cranksingular
 * @short_description: 단일로 존재하는 객체들의 기반 클래스입니다.
 * @title: CrankSingular
 * @stability: Unstable
 * @include: crankbase.h
 *
 * 단일로 존재하는 객체들에 대한 기반 클래스입니다.
 *
 * 이 클래스는 다음의 기능을 제공합니다.
 *
 * - GObject 생성에서 싱글톤 기능 제공
 */



/* **** 내부 선언부 */

struct _CrankSingularClassPrivate {
	CrankSingular*	instance;
};

G_DEFINE_TYPE_WITH_CODE(CrankSingular, crank_singular, G_TYPE_OBJECT, {
	g_type_add_class_private (g_define_type_id,
			sizeof (CrankSingularClassPrivate)	);
});

// GObject에서 오버라이드 한 함수입니다.

static GObject*	crank_singular_g_object_constructor (
		GType					type,
		guint					n_construct_props,
		GObjectConstructParam*	construct_props	);

static GObject*	crank_singular_g_object_constructed (	GObject*	object	);




/* **** 구현부 */

// GTypeInstance 초기화 함수입니다.

static void
crank_singular_init (	CrankSingular*	self	)
{
	return;
}

static void
crank_singular_class_init	(	CrankSingularClass*	c	)
{
	return;
}


// GObject에서 오버라이드 한 함수입니다.

static GObject*	crank_singular_g_object_constructor (
		GType					type,
		guint					n_construct_props,
		GObjectConstructParam*	construct_props	);

static GObject*	crank_singular_g_object_constructed (	GObject*	object	);


// CrankSingular 함수입니다.

CrankSingular*
crank_singular_type_try_get (	GType	type	)
{
	return NULL;
}

void
crank_singular_type_setup (		GType	type,	...)
{
	return;
}

gboolean
crank_singular_type_teardown	(	GType	type	)
{
	return FALSE;
}

CrankSingular*
crank_singular_class_get (		CrankSingularClass*		c, ...)
{
	return NULL;
}

CrankSingular*
crank_singular_class_try_get (	CrankSingularClass*		c	)
{
	return NULL;
}

void
crank_singular_class_setup (	CrankSingularClass*		c, ...)
{
	return;
}

crank_singular_class_teardown (	CrankSingularClass*		c	)
{
	return FALSE;
}

