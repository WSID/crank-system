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
 * @short_description: Base class for classes that have at most one instances.
 * @title: CrankSingular
 * @stability: Unstable
 * @include: crankbase.h
 *
 * This class is base class for classes that have single instance.
 *
 * # Singleton construction as GObject
 *
 * #CrankSingular overrides #GObjectClass.constructor() as a function returns
 * the singleton instance. Therefore, instances of subclasses can be retrieved
 * by g_object_new().
 *
 * Singleton instances can be obtained by construction, but as constructor
 * function is still in action, side effects should be avoided.
 *
 * #CrankSingularClass.first_construct() is invoked only once per instance.
 * Subclasses may override this function to initialization function.
 *
 * If singleton instance exists, g_object_new() will return it with increased
 * reference count. Free with g_object_unref(), just as it was newly created
 * instance.
 *
 * <example>
 *   <title>Override first_construct in Python</title>
 *   |[<!-- language="python" -->
 *		class SomeSingular (CrankBase.Singular):
 *			def do_first_construct (self):
 *				# Do your initialization here.
 *				pass
 *   ]|
 * </example>
 * <example>
 *   <title>Override first_construct in Vala</title>
 *   |[<!-- language="vala" -->
 *		public class SomeSingular: Crank.Singular {
 *			public override void first_construct() {
 *				// Do your initialization here.
 *			}
 *		}
 *   ]|
 * </example>
 * # Thread Safety
 *
 * When singleton instance is created, Construction is locked by #GMutex, to
 * prevent multiple instances are created.
 *
 * When instance is created, the mutex is locked in #GObjectClass.constructor(),
 * and unlocked in #GObjectClass.constructed(). If these are overrided, they
 * should be chained up.
 *
 * # Notes about bindings for scripts
 *
 * As script objects wraps #GObject objects, Call of g_object_new() returns
 * different wrapping objects. As a result, two object does not shares dictionary.
 *
 * So, using this class in script, requires caution.
 *
 * <programlisting language="python">
 *    singular_a = SomeSingular()
 *    singular_b = SomeSingular()
 *
 *    # GObject properties are shared.
 *    singular_b.some_prop = 7
 *
 *    # Python dictionaries are not shared.
 *    singular_a.attr = 32
 *
 *    assert (singular_a == singular_b)
 *    assert (singular_a.some_prop == singular_b.some_prop)
 *    assert (! hasattr (singular_b, "attr"))
 * </programlisting>
 *
 * To resort this problem, try use crank_singular_get() as possible.
 */

/**
 * CrankSingular:
 *
 * This structure does not have anything.
 *
 * Because of characteristic of this class, the class has more data than the
 * instance.
 */

/**
 * CrankSingularClass:
 * @first_construct: Invoked when instance is created. If instance already
 *           exists, it is not invoked.
 *
 * The class structure of #CrankSingular.
 */

//////// Internal Declaration //////////////////////////////////////////////////

struct _CrankSingularClassPrivate {
	CrankSingular*	instance;
	GMutex			construct_mutex;
	gboolean		construct_mutex_locked;
};

G_DEFINE_TYPE_WITH_CODE(CrankSingular, crank_singular, G_TYPE_OBJECT, {
	g_type_add_class_private (g_define_type_id,
			sizeof (CrankSingularClassPrivate)	);
});

//////// Overriden function for GObject

static GObject*	crank_singular_g_object_constructor (
		GType					type,
		guint					n_construct_props,
		GObjectConstructParam*	construct_props	);

static void		crank_singular_g_object_constructed (	GObject*	object	);
static void		crank_singular_g_object_dispose (		GObject*	object	);


//////// Internal only function

static inline void		crank_singular_class_lock_mutex (	CrankSingularClass* c	);
static inline void		crank_singular_class_unlock_mutex (	CrankSingularClass*	c	);


//////// 구현부 ////////////////////////////////////////////////////////////////

//////// GTypeInstance Initialization Function.

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


//////// Overriden function for GObject

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
		// Locks construction, it is unlocked at constructed().
		crank_singular_class_lock_mutex (c);
		
		// If object is constructd while locked, skip construction and unlock.
		if (c->priv->instance != NULL) {
			crank_singular_class_unlock_mutex (c);

			g_debug ("Singular: %s: Returning Existing Instance",
					g_type_name (type));

			return g_object_ref(c->priv->instance);
		}

		// If object is not constructed, create instance.
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


//////// Internal only functions.

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
 * @type: #CrankSingular derived type to check existence.
 *
 * Check whether instance of given @type exists.
 *
 * Returns: %TRUE if instance of @type exists.
 */
gboolean
crank_singular_has (	GType	type	)
{
	CrankSingularClass*		c;
	
	g_return_val_if_fail ( g_type_is_a (type, CRANK_TYPE_SINGULAR), FALSE);
	
	c = (CrankSingularClass*) g_type_class_peek (type);
	
	return (c != NULL) ? (c->priv->instance != NULL) : FALSE;
}


/**
 * crank_singular_get:
 * @type: #CrankSingular derived type to get instance.
 *
 * Gets already created #CrankSingular instance.
 *
 * If instance needs to be ensured, you should use g_object_new().
 * g_object_new() will return instance when it exists.
 *
 * Returns: (nullable) (transfer full): The instance or %NULL if not exists.
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
 * @type: #CrankSingular derived type to peek instance.
 *
 * Gets already created #CrankSingular. Unlike crank_singular_get(), it does
 * not increase reference count.
 *
 * Returns: (nullable) (transfer none): The instance or %NULL if not exists.
 */
CrankSingular*
crank_singular_peek (	GType	type	)
{
	CrankSingularClass*		c;
	
	g_return_val_if_fail ( g_type_is_a (type, CRANK_TYPE_SINGULAR), NULL);
	
	c = (CrankSingularClass*) g_type_class_peek (type);
	
	return (c != NULL) ? c->priv->instance : NULL;
}
