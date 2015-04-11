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
 * # GObject 생성에서 싱글톤 기능 제공
 *
 * #CrankSingular는 #GObjectClass.constructor()를 싱글톤 객체를 반환하는 함수로
 * 오버라이드 합니다. 이에 따라, 이를 기반으로 한 하위 클래스들은 g_object_new()
 * 등을 통해서 객체를 얻을 수 있습니다.
 *
 * 생성을 통해 싱글톤 객체를 얻지만, 여전히 constructor 함수가 적용되기 때문에,
 * 최대한 부수효과는 피해야 합니다.
 *
 * 처음 생성될 때에만 작동하는 부분은 #CrankSingularClass.first_construct()를
 * 오버라이드 하여 수행해야 합니다.
 *
 * 싱글톤 객체가 존재하는 경우 g_object_new()는 참조가 증가된 싱글톤 객체를
 * 반환 합니다. 사용이 끝나면 g_object_unref()로 해제하면 됩니다.
 *
 * <example>
 *   <title>Python에서 first_construct 오버라이드</title>
 *   <programlisting language="python">
 *		class SomeSingular (CrankBase.Singular):
 *			def do_first_construct (self):
 *				# 여기서 작업을 수행하면 됩니다.
 *				pass
 *    </programlisting>
 * </example>
 * <example>
 *   <title>Vala에서 first_construct 오버라이드</title>
 *   <programlisting language="Vala">
 *		public class SomeSingular: Crank.Singular {
 *			public override void first_construct() {
 *				// 여기서 작업을 수행하면 됩니다.
 *			}
 *		}
 *   </programlisting>
 * </example>
 * # 스레드 안전성
 *
 * 싱글톤 객체가 생성될 경우, 다른 스레드로부터의 접근을 막기 위해 #GMutex로
 * 생성을 잠급니다. 이는 여러개의 스레드가 서로 다른 객체를 생성하느 것을 막기
 * 위해서입니다.
 *
 * 싱글톤 객체 생성시 #GMutex는 #GObjectClass.constructor()에서 잠그고,
 * #GObject.constructed()에서 해제하므로, 해당 함수를 오버라이드 할 경우 체인
 * 업을 해야 합니다.
 *
 *
 * # 스크립트 언어 바인딩과 관련된 노트
 *
 * 스크립트 객체가 #GObject 객체를 감싸는 특성으로 인하여, g_object_new()의
 * 호출은 서로 다른 객체를 반환하게 됩니다. (예: 객체의 사전이 공유되지 않음)
 *
 * 따라서 여러 부분에서 사용한다면 주의가 요구됩니다.
 *
 * <programlisting language="python">
 *    singular_a = SomeSingular()
 *    singular_b = SomeSingular()
 *
 *    # GObject 속성은 서로 공유됩니다.
 *    singular_b.some_prop = 7
 *
 *    # Python 객체 사전은 공유되지 않습니다.
 *    singular_a.attr = 32
 *
 *    assert (singular_a == singular_b)
 *    assert (singular_a.some_prop == singular_b.some_prop)
 *    assert (! hasattr (singular_b, "attr"))
 * </programlisting>
 *
 * 이를 해소하기 위해서는 crank_singular_get() 을 주로 사용 하는 편이
 * 좋습니다.
 */


//////// 내부 선언부 ///////////////////////////////////////////////////////////

struct _CrankSingularClassPrivate {
	CrankSingular*	instance;
	GMutex			construct_mutex;
	gboolean		construct_mutex_locked;
};

G_DEFINE_TYPE_WITH_CODE(CrankSingular, crank_singular, G_TYPE_OBJECT, {
	g_type_add_class_private (g_define_type_id,
			sizeof (CrankSingularClassPrivate)	);
});

//////// GObject에서 오버라이드 한 함수입니다.

static GObject*	crank_singular_g_object_constructor (
		GType					type,
		guint					n_construct_props,
		GObjectConstructParam*	construct_props	);

static void		crank_singular_g_object_constructed (	GObject*	object	);
static void		crank_singular_g_object_dispose (		GObject*	object	);


//////// 내부 전용 함수

static inline void		crank_singular_class_lock_mutex (	CrankSingularClass* c	);
static inline void		crank_singular_class_unlock_mutex (	CrankSingularClass*	c	);


//////// 구현부 ////////////////////////////////////////////////////////////////

//////// GTypeInstance 초기화 함수입니다.

static void
crank_singular_init (	CrankSingular*	self	)
{
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
	c->priv->instance = NULL;
	c->priv->construct_mutex_locked = FALSE;
}


//////// GObject에서 오버라이드 한 함수입니다.

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


	c = CRANK_SINGULAR_CLASS(g_type_class_peek(type));

	if (c->priv->instance != NULL) return g_object_ref (c->priv->instance);

	else {
		// 생성을 잠급니다. 이는 추후 constructed 함수에서 언락합니다.
		crank_singular_class_lock_mutex (c);
		
		// 블록될 동안 객체가 생성되어 있으면, 스킵하고 잠금도 풉니다.
		if (c->priv->instance != NULL) {
			crank_singular_class_unlock_mutex (c);

			g_debug ("Singular: %s: Returning Existing Instance",
					g_type_name (type));

			return g_object_ref(c->priv->instance);
		}

		// 객체가 없는 경우 새로 만듭니다.
		else {
			parent_c_g_object = G_OBJECT_CLASS(crank_singular_parent_class);

			g_debug ("Singular: %s: Creating Instance", g_type_name (type));
			self_g_object = parent_c_g_object->constructor (type,
					n_construct_props,
					construct_props		);

			self = CRANK_SINGULAR(self_g_object);

			if (c->first_construct != NULL)
				c->first_construct (self);
			c->priv->instance = self;

			return self_g_object;
		}
	}
}

static void
crank_singular_g_object_constructed (	GObject*	object	)
{
	CrankSingularClass*		c;
	GObjectClass*			parent_c_g_object;
	
	c = CRANK_SINGULAR_GET_CLASS(object);
	parent_c_g_object = G_OBJECT_CLASS(crank_singular_parent_class);
	
	parent_c_g_object->constructed (object);
	crank_singular_class_unlock_mutex (c);
}


static void
crank_singular_g_object_dispose ( GObject*	object )
{
	CrankSingularClass*		c;
	GObjectClass*			parent_c_g_object;

	c = CRANK_SINGULAR_GET_CLASS(object);
  	c->priv->instance = NULL;
  	g_debug ("Singular: %s: Disposing Instance", G_OBJECT_TYPE_NAME(object));

	parent_c_g_object = G_OBJECT_CLASS(crank_singular_parent_class);
	
	parent_c_g_object->dispose (object);
}


//////// 내부 전용 함수들

static inline void
crank_singular_class_lock_mutex (	CrankSingularClass*	c	)
{
	g_mutex_lock (&c->priv->construct_mutex);
  	c->priv->construct_mutex_locked = TRUE;

  	g_debug ("Singular: %s: Locking construction lock",
  			G_OBJECT_CLASS_NAME(c));
}

static inline void
crank_singular_class_unlock_mutex (	CrankSingularClass* c	)
{
  	if (c->priv->construct_mutex_locked) {
		c->priv->construct_mutex_locked = FALSE;
		g_mutex_unlock (&c->priv->construct_mutex);

  		g_debug ("Singular: %s: Unlocking construction lock",
  				G_OBJECT_CLASS_NAME(c));
	}
}


//////// 외부 공개 함수들


/**
 * crank_singular_has:
 * @type: #CrankSingular가 존재하는지 확인할 타입입니다.
 *
 * 주어진 타입에 해당하는 Singular 객체가 존재하는지 확인합니다.
 *
 * Returns: 인스턴스가 존재하면 %TRUE
 */
gboolean
crank_singular_has (	GType	type	)
{
	CrankSingularClass*		c;
	
	g_return_val_if_fail ( g_type_is_a (type, CRANK_TYPE_SINGULAR), NULL);
	
	c = (CrankSingularClass*) g_type_class_peek (type);
	
	return (c != NULL) ? (c->priv->instance != NULL) : FALSE;
}


/**
 * crank_singular_get:
 * @type: #CrankSingular를 얻을 타입입니다.
 *
 * 이미 생성된 #CrankSingular를 얻습니다.
 *
 * 자동으로 생성해야 하는 경우 g_object_new()를 사용해야 합니다. g_object_new()
 * 는 #CrankSingular가 존재하는 경우 해당 객체를 반환합니다.
 *
 * Returns: (allow-none) (transfer full): 해당 타입의 인스턴스이거나, 없으면 NULL
 */
CrankSingular*
crank_singular_get (	GType	type	)
{
	CrankSingularClass*		c;
	
	g_return_val_if_fail ( g_type_is_a (type, CRANK_TYPE_SINGULAR), NULL);
	
	c = (CrankSingularClass*) g_type_class_peek (type);
	
	return (c != NULL) ? CRANK_SINGULAR(g_object_ref(c->priv->instance)) : NULL;
}


/**
 * crank_singular_peek:
 * @type: #CrankSingular를 얻을 타입입니다.
 *
 * 이미 생성된 #CrankSingular를 얻습니다. crank_singular_get()와 다른 것은
 * 참조를 가져오지 않는 것입니다.
 *
 * Returns: (allow-none) (transfer none): 해당 타입의 인스턴스이거나, 없으면 NULL
 */
CrankSingular*
crank_singular_peek (	GType	type	)
{
	CrankSingularClass*		c;
	
	g_return_val_if_fail ( g_type_is_a (type, CRANK_TYPE_SINGULAR), NULL);
	
	c = (CrankSingularClass*) g_type_class_peek (type);
	
	return (c != NULL) ? c->priv->instance : NULL;
}
