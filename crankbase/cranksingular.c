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
 * - 다소 스레드 안전함 - 객체 생성시 Mutex로 보호됨
 */



/* **** 내부 선언부 */

struct _CrankSingularPrivate {
	gboolean		is_new;
};

struct _CrankSingularClassPrivate {
	CrankSingular*	instance;
	GMutex			construct_mutex;
	gboolean		construct_mutex_locked;
};

G_DEFINE_TYPE_WITH_CODE(CrankSingular, crank_singular, G_TYPE_OBJECT, {
	G_ADD_PRIVATE(CrankSingular);
	g_type_add_class_private (g_define_type_id,
			sizeof (CrankSingularClassPrivate)	);
});

// GObject에서 오버라이드 한 함수입니다.

static GObject*	crank_singular_g_object_constructor (
		GType					type,
		guint					n_construct_props,
		GObjectConstructParam*	construct_props	);

static void		crank_singular_g_object_constructed (	GObject*	object	);
static void		crank_singular_g_object_dispose (		GObject*	object	);



/* **** 구현부 */

// GTypeInstance 초기화 함수입니다.

static void
crank_singular_init (	CrankSingular*	self	)
{
	self->priv = G_TYPE_INSTANCE_GET_PRIVATE (self,
			CRANK_TYPE_SINGULAR,
			CrankSingularPrivate);
	
	self->priv->is_new = TRUE;
}

static void
crank_singular_class_init	(	CrankSingularClass*	c	)
{
	GObjectClass*		c_g_object;
	
	c_g_object = G_OBJECT_CLASS(c);
	
	c_g_object->constructor = crank_singular_g_object_constructor;
	c_g_object->constructed = crank_singular_g_object_constructed;
	c_g_object->dispose = crank_singular_g_object_dispose;
	
	
	// CrankSingular
	c->priv = G_TYPE_CLASS_GET_PRIVATE (c, CRANK_TYPE_SINGULAR,
			CrankSingularClassPrivate	);
	
	g_mutex_init (&c->priv->construct_mutex);
}


// GObject에서 오버라이드 한 함수입니다.

static GObject*
crank_singular_g_object_constructor (
		GType					type,
		guint					n_construct_props,
		GObjectConstructParam*	construct_props	)
{
	CrankSingularClass*			c;
	GObjectClass*				parent_c_g_object;
	
	CrankSingular*				self;
	GObject*					self_g_object;
	
	//NOTE for construction
	//
	// 생성 속성 (Construction Property) 들은 GObject construct에서 처리가
	// 됩니다.
	// 만일 ...
	
	if (c->priv->instance != NULL) return g_object_ref (c->priv->instance);
	
	else {
		// 생성을 잠급니다. 이는 추후 constructed 함수에서 언락합니다.
		g_mutex_lock (&c->priv->construct_mutex);
		c->priv->construct_mutex_locked = TRUE;
		g_debug ("Singular: Locked for %s", g_type_name (type));
		
		if (c->priv->instance != NULL) {
		
			// 이미 객체가 생성되어 있으면, 스킵하고 잠금도 풉니다.
			g_debug ("Singular: Unlocked for %s", g_type_name (type));
			c->priv->construct_mutex_locked = FALSE;
			g_mutex_unlock(&c->priv->construct_mutex);
			
			return g_object_ref(c->priv->instance);
		}
		
		parent_c_g_object = G_OBJECT_CLASS(g_type_class_peek_parent (c));
		
		g_debug ("Singular: Creating %s", g_type_name (type));
		self_g_object = parent_c_g_object->constructor (type,
				n_construct_props,
				construct_props		);
		
		self = CRANK_SINGULAR(self_g_object);
		return self_g_object;
	}
}

static void
crank_singular_g_object_constructed (	GObject*	object	)
{
	CrankSingularClass*		c;
	GObjectClass*			parent_c_g_object;
	
	CrankSingular*			self;
	
	c = CRANK_SINGULAR_GET_CLASS(object);
	parent_c_g_object = G_OBJECT_CLASS(g_type_class_peek_parent(c));
	
	
	parent_c_g_object->constructed (object);
	
	self = CRANK_SINGULAR(object);
	self->priv->is_new = FALSE;
	
	if (c->priv->construct_mutex_locked) {
	
		g_debug ("Singular: Unlocked for %s", G_OBJECT_TYPE_NAME(object));
		c->priv->construct_mutex_locked = FALSE;
		g_mutex_unlock (&c->priv->construct_mutex);
	}
}

static void
crank_singular_g_object_dispose ( GObject*	object )
{
	CrankSingularClass*		c;
	GObjectClass*			parent_c_g_object;
	
	c = CRANK_SINGULAR_GET_CLASS(object);
	
	c->priv->instance = NULL;
	
	parent_c_g_object = G_OBJECT_CLASS(g_type_class_peek_parent(c));
	
	parent_c_g_object->dispose (object);
}


// CrankSingular 함수입니다.

/**
 * crank_singular_type_get:
 * @type: #CrankSingular를 얻을 타입입니다.
 *
 * 이미 생성된 #CrankSingular를 얻습니다.
 *
 * 자동으로 생성해야 하는 경우 g_object_new()를 사용해야 합니다. g_object_new()
 * 는 #CrankSingular가 존재하는 경우 해당 객체를 반환합니다.
 *
 * Returns: (allow-none) (transfer full): #CrankSingular
 */
CrankSingular*
crank_singular_type_get (	GType	type	)
{
	CrankSingularClass*		c;
	
	c = CRANK_SINGULAR_CLASS(g_type_class_peek (type));
	
	return (c != NULL) ? crank_singular_class_get (c) : NULL;
}

/**
 * crank_singular_type_peek:
 * @type: #CrankSingular를 얻을 타입입니다.
 *
 * 이미 생성된 #CrankSingular를 얻습니다. crank_singular_type_get()와 다른 것은
 * 참조를 가져오지 않는 것입니다.
 *
 * Returns: (allow-none) (transfer none): #CrankSingular
 */
CrankSingular*
crank_singular_type_peek (	GType	type	)
{
	CrankSingularClass*		c;
	
	c = CRANK_SINGULAR_CLASS(g_type_class_peek (type));
	
	return (c != NULL) ? crank_singular_class_peek (c) : NULL;
}



/**
 * crank_singular_class_get:
 * @c: #CrankSingular를 얻을 클래스입니다.
 *
 * 클래스에서 가지고 있는 #CrankSingular를 얻습니다.
 *
 * 자동으로 생성되어야 하는 경우, crank_singular_class_new()를 사용해야 합니다.
 *
 * Returns: (allow-none) (transfer full): #CrankSingular 타입
 */
CrankSingular*
crank_singular_class_get (		CrankSingularClass*		c	)
{
	return CRANK_SINGULAR(g_object_ref(c->priv->instance));
}

/**
 * crank_singular_class_peek:
 * @c: #CrankSingular를 얻을 클래스입니다.
 *
 * 클래스에서 가지고 있는 #CrankSingular를 얻습니다. 참조를 가져오지 않습니다.
 *
 * Returns: (allow-none) (transfer none): #CrankSingular 타입
 */
CrankSingular*
crank_singular_class_peek (	CrankSingularClass*		c	)
{
	return CRANK_SINGULAR(c->priv->instance);
}



/**
 * crank_singular_is_new:
 * @self: 확인할 객체입니다.
 *
 * #GObject.constructor 함수를 구성할 때 주어진 객체가 새로 생성되는 객체인지,
 * 아니면 기존에 생성된 객체인지 확인합니다.
 *
 * constructor 함수 내부에서 사용되도록 만들어졌습니다.
 *
 * Returns: 주어진 @singular가 새로운 객체인지 아닌지.
 */
gboolean
crank_singular_is_new (	CrankSingular*	self ) {
	return self->priv->is_new;
}
