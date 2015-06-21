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
#include "crankvalue.h"
#include "cranktypesgraph.h"
#include "crankfuncholder.h"

/**
 * SECTION: crankfuncholder
 * @short_description: Stores functions by types of parameters.
 * @title: CrankFuncHolder
 * @stability: Unstable
 * @include: crankbase.h
 *
 * #CrankFuncHolder stores functions by types of parameters.
 * #CrankFuncBook stores #CrankFuncHolder by names.
 */



//////// Internal Declaration
static void			_transform_crank_func_type_string (	const GValue* value_ftype,
														GValue* value_string	);
/**
 * CrankFuncType:
 * 
 * Stores return type and parameter types.
 */
struct _CrankFuncType {
	GType	return_type;
	GType*	param_types;
	guint	nparam_types;
	
	guint	_refc;
};

G_DEFINE_BOXED_TYPE_WITH_CODE (
        CrankFuncType,
        crank_func_type,
        crank_func_type_ref,
        crank_func_type_unref,
        {
			g_value_register_transform_func (
			        g_define_type_id,
			        G_TYPE_STRING,
			        _transform_crank_func_type_string);
		} );





/**
 * crank_func_type_new:
 * @return_type: Return type.
 * @...: Parameter types. Ends with %G_TYPE_NONE.
 * 
 * Constructs a #CrankFuncType.
 * 
 * Returns: (transfer full): New CrankFuncType.
 */
CrankFuncType*
crank_func_type_new (const GType return_type, ...)
{
	CrankFuncType*  ftype;
	va_list			varargs;

	va_start (varargs, return_type);
	ftype = crank_func_type_new_va (return_type, varargs);
	va_end (varargs);

	return ftype;
}


/**
 * crank_func_type_new_va:
 * @return_type: Return type.
 * @varargs: va_list of parameter types. Ends with %G_TYPE_NONE.
 * 
 * Constructs a #CrankFuncType.
 * 
 * Returns: (transfer full): New CrankFuncType.
 */
CrankFuncType*
crank_func_type_new_va (const GType return_type, va_list varargs)
{
	CrankFuncType*  ftype;
	guint			param_types_alloc;
	guint			i;
	
	ftype = g_new(CrankFuncType, 1);

	ftype->return_type = return_type;
	
	param_types_alloc = 0;
	ftype->param_types = NULL;
	ftype->nparam_types = 0;

	CRANK_FOREACH_VALIST_BEGIN (varargs, GType, varargs_type, G_TYPE_NONE)
		CRANK_ARRAY_ADD (GType,
						ftype->param_types,
						ftype->nparam_types,
						param_types_alloc,
						varargs_type);
	CRANK_FOREACH_VALIST_END

	ftype->param_types = g_renew (GType, ftype->param_types, ftype->nparam_types);

	ftype->_refc = 1;

	return ftype;
}


/**
 * crank_func_type_new_with_types:
 * @return_type: Return type.
 * @param_types: (array length=nparam_types): Parameter types.
 * @nparam_types: Length of @param_types.
 * 
 * Constructs a #CrankFuncType.
 * 
 * Returns: (transfer full): New #CrankFuncType.
 */
CrankFuncType*
crank_func_type_new_with_types (
         const GType return_type,
         const GType* param_types,
         const guint nparam_types)
{
	CrankFuncType*  ftype;
	guint			i;
	
	ftype = g_new(CrankFuncType, 1);

	ftype->return_type = return_type;
	
	ftype->nparam_types = nparam_types;
	ftype->param_types = CRANK_ARRAY_DUP (param_types, GType, nparam_types);
	
	ftype->_refc = 1;

	return ftype;
}



/**
 * crank_func_type_ref:
 * @ftype: A #CrankFuncType
 *
 * Increase reference count by 1.
 *
 * Returns: @ftype with increased reference count.
 */
CrankFuncType*
crank_func_type_ref (CrankFuncType* ftype)
{
	g_atomic_int_inc (&ftype->_refc);
	return ftype;
}

/**
 * crank_func_type_unref:
 * @ftype: A #CrankFuncType
 *
 * Decrease reference count by 1. If reference count reaches 0, @ftype will be
 * freed.
 */
void
crank_func_type_unref (CrankFuncType* ftype)
{
	if (g_atomic_int_dec_and_test(&ftype->_refc)) {
		g_free (ftype->param_types);
		g_free (ftype);
	}
}



/**
 * crank_func_type_hash:
 * @v: (type CrankFuncType): A #CrankFuncType
 *
 * Gets hash value of a #CrankFuncType.
 * This function can be used when using #CrankFuncType as key of #GHashTable.
 * 
 * Returns: Hash value of @v.
 */
guint
crank_func_type_hash (gconstpointer v)
{
	CrankFuncType* ftype;
	guint hash;
	guint i;

	ftype = (CrankFuncType*)v;
	hash = 0;

	hash += g_direct_hash ((gconstpointer) ftype->return_type);

	for (i = 0; i < ftype->nparam_types; i++) 
		hash += g_direct_hash ((gconstpointer) ftype->param_types[i]);

	hash += g_direct_hash (GINT_TO_POINTER(ftype->nparam_types));
	return hash;
}

/**
 * crank_func_type_equal:
 * @a: (type CrankFuncType): A #CrankFuncType
 * @b: (type CrankFuncType): A #CrankFuncType
 *
 * Compares two types and check equality.
 * This function can be used when using #CrankFuncType as key of #GHashTable.
 * 
 * Returns: Whether two types are equal.
 */
gboolean
crank_func_type_equal (gconstpointer a, gconstpointer b) {
	CrankFuncType* ftype_a;
	CrankFuncType* ftype_b;
	guint i;

	ftype_a = (CrankFuncType*)a;
	ftype_b = (CrankFuncType*)b;

	if (ftype_a->return_type != ftype_b->return_type) return FALSE;

	if (ftype_a->nparam_types != ftype_b->nparam_types) return FALSE;
	for (i = 0; i < ftype_a->nparam_types; i++)
		if (ftype_a->param_types[i] != ftype_b->param_types[i]) return FALSE;
	

	return TRUE;
}

/**
 * crank_func_type_to_string:
 * @ftype: A  #CrankFuncType
 * 
 * Stringify a #CrankFuncType. The format is,
 * 
 * |[
 * RTYPE (PARAM, PARAM)
 * ]|
 *
 * If a #CrankFuncType represents gchar* (*)(gint, gint), is stringified, then
 * the result is,
 * 
 * |[
 * guchararray (gint, gint)
 * ]|
 *
 * Returns: (transfer full): A string representation. Free with g_free().
 */
gchar*
crank_func_type_to_string (const CrankFuncType* ftype) {
	GString*	result;
	gchar*		result_str;
	guint		i;

	result = g_string_new (NULL);

	g_string_append (result, g_type_name (ftype->return_type));
	g_string_append (result, " (");

	if (ftype->nparam_types != 0)
	    g_string_append (result, g_type_name (ftype->param_types[0]));
	
	for (i = 1; i < ftype->nparam_types; i++) {
		g_string_append (result, ", ");
		g_string_append (result, g_type_name(ftype->param_types[i]));
	}
	
	g_string_append_c (result, ')');

	result_str = result->str;

	g_string_free (result, FALSE);
	
	return result_str;
}




/**
 * crank_func_type_get_return_type:
 * @ftype: A #CrankFuncType
 *
 * Gets return type of @ftype.
 * 
 * Returns: The return type of @ftype.
 */
GType
crank_func_type_get_return_type (const CrankFuncType* ftype) {
	return ftype->return_type;
}

/**
 * crank_func_type_get_param_type:
 * @ftype: A #CrankFuncType
 * @index: A index.
 *
 * Gets a parameter type at @index.
 *
 * Returns: The parameter type at @index. %G_TYPE_NONE if out of bound.
 */
GType
crank_func_type_get_param_type (const CrankFuncType* ftype,
        const guint index)
{
	return (index < ftype->nparam_types) ? ftype->param_types[index] : G_TYPE_NONE;
}

/**
 * crank_func_type_get_nparam_types:
 * @ftype: A #CrankFuncType
 * 
 * Gets length of parameter types.
 *
 * Returns: Length of parameter types.
 */
guint
crank_func_type_get_nparam_types (const CrankFuncType* ftype)
{
	return ftype->nparam_types;
}

/**
 * crank_func_type_get_param_types:
 * @ftype: A #CrankFuncType
 * @length (out): Length of parameter types.
 * 
 * Gets parameter types.
 *
 * Returns: (array length=length) (transfer container):
 *         Parameter types. Free with g_free().
 */
GType*
crank_func_type_get_param_types (const CrankFuncType* ftype,
        guint* length)
{
	if (length != NULL) *length = ftype->nparam_types;

	return CRANK_ARRAY_DUP (ftype->param_types, GType, ftype->nparam_types);
}


/**
 * crank_func_type_compatible_to:
 * @from: A #CrankFuncType.
 * @to: A #CrankFuncType.
 *
 * Compares two type and checks function with type @from can be used as function
 * with type @to.
 *
 * The criteria is listed at below.
 *
 * - return type of @from "is a" return type of @to.
 * - @from has less or equal number of parameter compared to @to.
 * - Each parameter type of @to is a parameter type of @from at same position.
 *
 * it is simply is-a relations.
 *
 * Returns: Whether @to is compatible to @from.
 */
gboolean
crank_func_type_compatible_to  (	const CrankFuncType* from,
    								const CrankFuncType* to		)
{
	guint i;
	guint i_end;

	if (	(! g_type_is_a (from->return_type, to->return_type)) ||
	        (to->nparam_types < from->nparam_types)				)
		return FALSE;
	
	i_end = from->nparam_types;

	for (i = 0; i < i_end; i++) {
		if (! g_type_is_a (to->param_types[i], from->param_types[i]))
			return FALSE;
	}
	return TRUE;	
}
	

/**
 * crank_func_type_arg_match_exactually:
 * @ftype: A #CrankFuncType.
 * @args: (array length=arg_length): Argument types.
 * @arg_length: Length of @args.
 *
 * Compares argument types and checks whether two are exactually match.
 *
 * Returns: Whether parameter types of @ftype matches into @args.
 */
gboolean
crank_func_type_arg_match_exactually (	const CrankFuncType* ftype,
										const GType*		 args,
										const uint			 arg_length	)
{
	if (ftype->nparam_types != arg_length) return FALSE;
	
	return (CRANK_ARRAY_CMP (ftype->param_types, args, GType, arg_length) == 0);
}

/**
 * crank_func_type_arg_match:
 * @ftype: A #CrankFuncType.
 * @args: (array length=arg_length): Argument types.
 * @arg_length: Length of @args.
 *
 * Compares argument types and checks whether each parameter type of @ftype, is
 * a argument type at same position.
 *
 * Returns: Whether each parameter type of @ftype is a one of @args at same
 *         position.
 */
gboolean
crank_func_type_arg_match (	const CrankFuncType* ftype,
							const GType*		 args,
							const guint			 arg_length	)
{
	gint i;
	
	if (ftype->nparam_types != arg_length) return FALSE;
	
	for (i = 0; i < arg_length; i ++) {
		if (! g_type_is_a (args[i], ftype->param_types[i]))
			return FALSE;
	}
	return TRUE;
}

/**
 * crank_func_type_arg_match_transformable:
 * @ftype: A #CrankFuncType.
 * @args: (array length=arg_length): Argument types.
 * @arg_length: Length of @args.
 *
 * Compares argument types and checks whether each parameter type of @ftype, can
 * be transformable to argument type at same position.
 *
 * Returns: Whether each parameter type of @ftypes can be transformed to one of
 *        @args at same position.
 */
gboolean
crank_func_type_arg_match_transformable (	const CrankFuncType* ftype,
											const GType*		 args,
											const guint			 arg_length	)
{
	gint i;
	
	if (ftype->nparam_types != arg_length) return FALSE;
	
	for (i = 0; i < arg_length; i ++) {
		if (! g_value_type_transformable (args[i], ftype->param_types[i]))
			return FALSE;
	}
	return TRUE;
}



static void
_transform_crank_func_type_string (	const GValue* value_ftype,
									GValue* value_string	)
{
	CrankFuncType* ftype;

	ftype = g_value_get_boxed (value_ftype);
	g_value_take_string (value_string, crank_func_type_to_string (ftype));
}



//////// CrankFuncHolderData ///////////////////////////////////////////////////
typedef struct _CrankFuncHolderData {
	CrankFuncType*		ftype;
	GClosure*			closure;
} CrankFuncHolderData;

G_GNUC_MALLOC
static CrankFuncHolderData*	crank_func_holder_data_new (	CrankFuncType*	type,
															GClosure* 		closure	);
G_GNUC_MALLOC
static CrankFuncHolderData*	crank_func_holder_data_copy (	CrankFuncHolderData*	data);

static void					crank_func_holder_data_free (	CrankFuncHolderData*	data);

#define CRANK_TYPE_FUNC_HOLDER_DATA (crank_func_holder_data_get_type())
G_DEFINE_BOXED_TYPE(CrankFuncHolderData, crank_func_holder_data,
		crank_func_holder_data_copy, crank_func_holder_data_free);


G_GNUC_MALLOC static CrankFuncHolderData*
crank_func_holder_data_new (	CrankFuncType*	ftype,
								GClosure*		closure	)
{
	CrankFuncHolderData*	data = g_new (CrankFuncHolderData, 1);
	
	data->ftype = crank_func_type_ref (ftype);
	data->closure = g_closure_ref (closure);
	
	return data;
}

G_GNUC_MALLOC static CrankFuncHolderData*
crank_func_holder_data_copy (	CrankFuncHolderData*	data	)
{
	return crank_func_holder_data_new (data->ftype, data->closure);
}

static void
crank_func_holder_data_free (	CrankFuncHolderData*	data	)
{
	crank_func_type_unref (data->ftype);
	g_closure_unref (data->closure);
	
	g_free (data);
}


//////// CrankFuncHolder ///////////////////////////////////////////////////////

/**
 * CrankFuncHolder:
 *
 * This structure stores functions as #GClosure. Functions can be retrieved by
 * parameter types, and invoked by #GValue.
 */
struct _CrankFuncHolder {
	GQuark				name;
	CrankTypesGraph*	types_graph;
	
	GHashTable*			table_ftype_data;	//<CrankFuncType*, CrankFuncHolderData>

  	guint				_refc;
};

G_DEFINE_BOXED_TYPE (CrankFuncHolder, crank_func_holder,
		crank_func_holder_ref,
		crank_func_holder_unref)


CrankFuncHolderData*	crank_func_holder_get_data_by_param_types (CrankFuncHolder*		holder,
											const GType*		param_types,
											const guint			nparam_types	);
											
CrankFuncHolderData*	crank_func_holder_get_data (CrankFuncHolder*		holder,
											CrankFuncType*		ftype	);
											
CrankFuncHolderData*	crank_func_holder_lookup_data_by_param_types (CrankFuncHolder*		holder,
											const GType*		param_types,
											const guint			nparam_types	);
											
CrankFuncHolderData*	crank_func_holder_lookup_data (CrankFuncHolder*		holder,
											CrankFuncType*		ftype	);

GType		crank_func_holder_get_actual_type (	const GValue*	value);



//////// Internal Definition

CrankFuncHolderData*
crank_func_holder_get_data_by_param_types (	CrankFuncHolder*		holder,
											const GType*		param_types,
											const guint			nparam_types	)
{
	GValue		value = G_VALUE_INIT;
	
	g_value_init (&value, G_TYPE_POINTER);
	
	if (crank_types_graph_get (holder->types_graph, param_types, nparam_types, &value)) {
		CrankFuncHolderData* result =
			(CrankFuncHolderData*) g_value_get_pointer (&value);
			
		g_value_unset (&value);
		
		return result;
	}
	else {
		return NULL;
	}
}

CrankFuncHolderData*
crank_func_holder_get_data (	CrankFuncHolder*	holder,
								CrankFuncType*		ftype	)
{
	return g_hash_table_lookup (holder->table_ftype_data, ftype);
}



CrankFuncHolderData*
crank_func_holder_lookup_data_by_param_types (	CrankFuncHolder*		holder,
												const GType*		param_types,
												const guint			nparam_types	)
{
	GValue		value = G_VALUE_INIT;
	
	g_value_init (&value, G_TYPE_POINTER);
	
	if (crank_types_graph_lookup (holder->types_graph, param_types, nparam_types, &value)) {
		CrankFuncHolderData* result =
			(CrankFuncHolderData*) g_value_get_pointer (&value);
		
		g_value_unset (&value);
		
		return result;
	}
	else {
		return NULL;
	}
}

CrankFuncHolderData*
crank_func_holder_lookup_data (	CrankFuncHolder*	holder,
								CrankFuncType*		ftype	)
{
	CrankFuncHolderData*	data;
	
	guint					nparam_types;
	GType*					param_types;
	
	data = g_hash_table_lookup (holder->table_ftype_data, ftype);
	
	if (data != NULL) return data;
	
	param_types = crank_func_type_get_param_types (ftype, &nparam_types);
	
	data = crank_func_holder_lookup_data_by_param_types (holder, param_types, nparam_types);
	
	if (data != NULL) {
		GType	rtype_self =crank_func_type_get_return_type (data->ftype);
		GType	rtype_in =	crank_func_type_get_return_type (ftype);
		
		if (g_type_is_a (rtype_self, rtype_in)) return data;
	}
	return NULL;

}

GType
crank_func_holder_get_actual_type (const GValue*		value)
{
	GType value_type;
	GType actual_type;

	value_type = G_VALUE_TYPE(value);
	actual_type = value_type;

	if (G_TYPE_IS_DERIVABLE (value_type) | G_TYPE_IS_DEEP_DERIVABLE (value_type)) {
		if (g_type_is_a (value_type, G_TYPE_OBJECT))
			actual_type = G_OBJECT_TYPE (g_value_get_object(value));
		else if (g_type_is_a (value_type, G_TYPE_PARAM))
			actual_type = G_PARAM_SPEC_TYPE (g_value_get_param (value));
	}
	return actual_type;
}



//////// Function Definition

/**
 * crank_func_holder_new:
 * @name: Name of holder. Used by #CrankFuncBook
 *
 * Constructs #CrankFuncHolder with given name.
 *
 * Returns: (transfer full): Newly created #CrankFuncHolder
 */
G_GNUC_MALLOC CrankFuncHolder*
crank_func_holder_new (	const gchar*	name	)
{
	GQuark qname = g_quark_from_string (name);
	return crank_func_holder_new_quark (qname);
}


/**
 * crank_func_holder_new_quark:
 * @name: Name of holder. Used by #CrankFuncBook.
 *
 * Constructs #CrankFuncHolder with given name.
 *
 * Returns: (transfer full): Newly created #CrankFuncHolder
 */
G_GNUC_MALLOC CrankFuncHolder*
crank_func_holder_new_quark (	const GQuark	name	)
{
  	CrankFuncHolder* holder = g_new (CrankFuncHolder, 1);

	holder->name = name;
	holder->types_graph = crank_types_graph_new ();
	
	holder->table_ftype_data = g_hash_table_new_full (
			crank_func_type_hash,
			crank_func_type_equal,
			NULL,
			(GDestroyNotify) crank_func_holder_data_free);
	
	holder->_refc = 1;

	return holder;
}

/**
 * crank_func_holder_ref:
 * @holder: A #CrankFuncHolder.
 *
 * Increases reference counter by 1.
 *
 * Returns: (transfer full): @holder with increased reference count.
 */
CrankFuncHolder*
crank_func_holder_ref (	CrankFuncHolder*	holder	)
{
	g_atomic_int_inc (&holder->_refc);
 	return holder;
}

/**
 * crank_func_holder_unref:
 * @holder: A #CrankFuncHolder.
 *
 * Decreases reference counter by 1. When reference count reaches 0, then
 * @holder will be freed.
 */
void
crank_func_holder_unref (	CrankFuncHolder*	holder	)
{
	if (g_atomic_int_dec_and_test (&holder->_refc)) {
		crank_types_graph_unref (holder->types_graph);
		g_hash_table_unref (holder->table_ftype_data);
		g_free (holder);
	}
}

/**
 * crank_func_holder_get_name:
 * @holder: A #CrankFuncHolder
 *
 * Gets name of #CrankFuncHolder as string.
 *
 * Returns: Name of the @holder.
 */
const gchar*
crank_func_holder_get_name (	CrankFuncHolder*	holder	)
{
	return g_quark_to_string (holder->name);
}

/**
 * crank_func_holder_set_name:
 * @holder: A CrankFuncHolder
 * @name: New name of @holder.
 *
 * Sets name of #CrankFuncHolder.
 */
void
crank_func_holder_set_name (	CrankFuncHolder*	holder,
								const gchar*		name	)
{
	holder->name = g_quark_from_string (name);
}


/**
 * crank_func_holder_get_qname:
 * @holder: A CrankFuncHolder
 *
 * Gets name of #CrankFuncHolder as #GQuark.
 *
 * Returns: Name of the @holder.
 */
GQuark
crank_func_holder_get_qname (	CrankFuncHolder*	holder	)
{
	return holder->name;
}

/**
 * crank_func_holder_set_qname:
 * @holder: A CrankFuncHolder
 * @name: New name of @holder
 *
 * Set name of #CrankFuncHolder.
 */
void
crank_func_holder_set_qname (	CrankFuncHolder*	holder,
								const GQuark		name	)
{
	holder->name = name;
}

/**
 * crank_func_holder_set:
 * @holder: A CrankFuncHolder
 * @ftype: A function type.
 * @closure: A #GClosure holds function.
 *
 * Sets a function with given function type. crank_func_holder_invoke() will
 * invoke appropriate type of funciton set here.
 *
 * Note:
 * If another function is registered by same function type but different return
 * type, then the function will replace previously registered function.
 */
void
crank_func_holder_set (	CrankFuncHolder*	holder,
						CrankFuncType*		ftype,
					   	GClosure*			closure	)
{
	CrankFuncHolderData*	data;
	GValue					value = G_VALUE_INIT;
	
	GType*					types;
	guint					ntypes;
	
	
	types = crank_func_type_get_param_types (ftype, &ntypes);
	
	data = crank_func_holder_get_data_by_param_types (holder, types, ntypes);
	
	if (data != NULL) {
		g_hash_table_remove (holder->table_ftype_data, data->ftype);
	}


	data = crank_func_holder_data_new (ftype, closure);
  	g_value_init (&value, G_TYPE_POINTER);
  	g_value_set_pointer (&value, data);
  	
	crank_types_graph_set (holder->types_graph, types, ntypes, &value);
	g_hash_table_insert (holder->table_ftype_data, ftype, data);

  	g_value_unset (&value);
}

/**
 * crank_func_holder_set_func: (skip)
 * @holder: A CrankFuncHolder
 * @ftype: A function type.
 * @func: A function.
 * @userdata: A userdata.
 * @userdata_destroy: A destroyer to free @userdata.
 * @marshal: (nullable): A #GClosureMarshal.
 *
 * Sets a function with given function type. This function is provided for
 * convenience for C, by wrapping C functions into GClosure.
 *
 * When %NULL is passed as @marshal, g_cclosure_marshal_generic() will be used
 * instead.
 *
 * Note:
 * If another function is registered by same function type but different return
 * type, then the function will replace previously registered function.
 */
void
crank_func_holder_set_func (	CrankFuncHolder*	holder,
								CrankFuncType*		ftype,
							   	CrankCallback		func,
							   	gpointer			userdata,
							   	GDestroyNotify		userdata_destroy,
							   	GClosureMarshal		marshal	)
{
	GClosure*		closure =
			g_cclosure_new ((GCallback)func, userdata, (GClosureNotify)userdata_destroy);
			
	g_closure_set_marshal (closure,
			(marshal != NULL) ? marshal : g_cclosure_marshal_generic);
	
	crank_func_holder_set (holder, ftype, closure);
	
	g_closure_unref (closure);
}

/**
 * crank_func_holder_set_simple: (skip)
 * @holder: A CrankFuncHolder
 * @ftype: A function type.
 * @func: A function.
 * @marshal: (nullable): A #GClosureMarshal.
 *
 * More simpler version of crank_func_holder_set_func().
 */
void
crank_func_holder_set_simple (	CrankFuncHolder*	holder,
								CrankFuncType*		ftype,
							   	GCallback			func,
							   	GClosureMarshal		marshal	)
{
	crank_func_holder_set_func (holder, ftype, (CrankCallback)func, NULL, NULL, marshal);
}

/**
 * crank_func_holder_get:
 * @holder: A CrankFuncHolder
 * @ftype: A function type.
 *
 * Get registered function by function type.
 *
 * Returns: (nullable) (transfer none): A function as a #GClosure.
 */
GClosure*
crank_func_holder_get ( CrankFuncHolder*	holder,
					   	CrankFuncType*		ftype	)
{
  	CrankFuncHolderData*	data;
  	
  	data = crank_func_holder_get_data (holder, ftype);
  	
  	return (data != NULL) ? data->closure : NULL;
}

/**
 * crank_func_holder_get_by_param_types:
 * @holder: A CrankFuncHolder
 * @param_types: (array length=nparam_types): Parameter types.
 * @nparam_types: Length of @param_types.
 *
 * Gets registered function by parameter types. In this case, return type is not
 * part of consideration.
 *
 * Returns: (nullable) (transfer none): A function as a #GClosure.
 */
GClosure*
crank_func_holder_get_by_param_types ( 	CrankFuncHolder*	holder,
										const GType*		param_types,
										const guint			nparam_types	)
{
  	CrankFuncHolderData*	data;
  	
  	data = crank_func_holder_get_data_by_param_types (holder, param_types, nparam_types);
  	
  	return (data != NULL) ? data->closure : NULL;
}


/**
 * crank_func_holder_lookup:
 * @holder: A CrankFuncHolder
 * @ftype: A function type.
 *
 * Gets registered function that can be matched with function type.
 * (#GBinding, #GObject) can be matched with (#GObject, #GObject).
 *
 * Returns: (nullable) (transfer none): A function that can be used as @ftype.
 */
GClosure*
crank_func_holder_lookup (	CrankFuncHolder*	holder,
							CrankFuncType*		ftype	)
{
	CrankFuncHolderData*	data;
	
	data = crank_func_holder_lookup_data (holder, ftype);
	
	return (data != NULL) ? data->closure : NULL;
}

/**
 * crank_func_holder_lookup_by_param_types:
 * @holder: A CrankFuncHolder
 * @param_types: (array length=nparam_types): Parammeter types.
 * @nparam_types: Length of @param_types.
 *
 * Gets registered function that can be matched with parameter types.
 * (#GBinding, #GObject) can be matched with (#GObject, #GObject).
 *
 * Returns: (nullable) (transfer none): A function that is compatible with
 *         parameter types.
 */
GClosure*
crank_func_holder_lookup_by_param_types (	CrankFuncHolder*	holder,
							const GType*		param_types,
							const guint			nparam_types	)
{
	CrankFuncHolderData*	data;
	
	data = crank_func_holder_lookup_data_by_param_types (holder,
			param_types, nparam_types);
	
	return (data != NULL) ? data->closure : NULL;
}

/**
 * crank_func_holder_lookup_return_type:
 * @holder: A CrankFuncHolder
 * @param_types: (array length=nparam_types): Parameter types.
 * @nparam_types: Length of @param_types.
 *
 * Gets return type of registered function type that can be matched with
 * parameter type.
 *
 * Returns: Return type of function type, or %G_TYPE_INVALID if no function type
 *         is matching.
 */
GType
crank_func_holder_lookup_return_type (	CrankFuncHolder*	holder,
										const GType*		param_types,
										const guint			nparam_types	)
{
	CrankFuncHolderData*	data;
	
	data = crank_func_holder_lookup_data_by_param_types (holder,
			param_types, nparam_types);
	
	return (data != NULL) ? crank_func_type_get_return_type (data->ftype) : G_TYPE_INVALID;
}

/**
 * crank_func_holder_remove:
 * @holder: A CrankFuncHolder
 * @ftype: A function type to remove.
 *
 * Removes a function type from holder.
 *
 * Returns: %TRUE if function type existed and removed.
 */
gboolean
crank_func_holder_remove (	CrankFuncHolder*	holder,
							CrankFuncType*		ftype	)
{
  	CrankFuncHolderData*	data;
  	
  	data = g_hash_table_lookup(holder->table_ftype_data, ftype);
  	
  	if (data != NULL) {
  		GType*		param_types;
  		guint		nparam_types;
  		
  		param_types = crank_func_type_get_param_types (ftype, &nparam_types);
  		
  		crank_types_graph_remove (holder->types_graph, param_types, nparam_types);
  		g_hash_table_remove (holder->table_ftype_data, ftype);
  		return TRUE;
  	}
  	else return FALSE;
}

/**
 * crank_func_holder_remove_by_param_types:
 * @holder: A CrankFuncHolder
 * @param_types: (array length=nparam_types): Parameter types.
 * @nparam_types: Length of @param_types.
 *
 * Removes a function type with given parameter types.
 *
 * This function does NOT look for matching function. So caller should know the
 * exact parameter types.
 *
 * Returns: %TRUE if a function type with given parameter types existed and removed.
 */
gboolean
crank_func_holder_remove_by_param_types (	CrankFuncHolder*	holder,
											const GType*		param_types,
											const guint			nparam_types	)
{
	CrankFuncHolderData*	data;
	
	data = crank_func_holder_get_data_by_param_types (holder, param_types, nparam_types);
	
	if (data == NULL) return FALSE;
	
	crank_types_graph_remove (holder->types_graph, param_types, nparam_types);
	g_hash_table_remove (holder->table_ftype_data, data->ftype);
	return TRUE;
}

/**
 * crank_func_holder_invoke:
 * @holder: A CrankFuncHolder.
 * @return_value: A #GValue to store return value.
 * @narg_values: Length of @arg_values.
 * @arg_values: (array length=narg_values): Array of GValue with arguments.
 * @invocation_hint: (nullable): Invocation hint for backing #GClosure.
 *
 * Invokes a function which matches types of @arg_values.
 *
 * @return_value should be initialized with appropriate type. Type can be
 * obtained from crank_func_holder_lookup_return_type().
 *
 * Returns: %TRUE if the function exists and invoked.
 */
gboolean
crank_func_holder_invoke (CrankFuncHolder*	holder,
                          GValue*			return_value,
                          const guint   	narg_values,
                          const GValue*		arg_values,
                          gpointer			invocation_hint)
{
	// 1. Find matching GClosure.
	GClosure*			closure;

	GType*	types = g_new(GType, narg_values);

	gint i;
	for (i = 0; i < narg_values; i++)
		types[i] = crank_func_holder_get_actual_type (arg_values + i);

  	closure = crank_func_holder_lookup_by_param_types (holder, types, narg_values);
	// 2. Invoke it.
	if (closure != NULL)
		g_closure_invoke (closure, return_value, narg_values, arg_values, invocation_hint);

	g_free (types);

  	return (closure != NULL);
}


/**
 * crank_func_holder_invokev:
 * @holder: A CrankFuncHolder.
 * @return_value: A #GValue to store return value.
 * @invocation_hint: (nullable): Invocation hint for backing #GClosure
 * @narg_values: Length of @....
 * @...: variadic of #GValue with arguments.
 *
 * Invokes a function which matches types of @....
 *
 * @return_value should be initialized with appropriate type. Type can be
 * obtained from crank_func_holder_lookup_return_type().
 *
 * Returns: %TRUE if the function exists and invoked.
 */
gboolean
crank_func_holder_invokev (	CrankFuncHolder*	holder,
							GValue*				return_value,
							gpointer			invocation_hint,
							guint				narg_values,
							...	)
{
	va_list		varargs;
	gboolean	result;
	
	va_start (varargs, narg_values );
	
	result = crank_func_holder_invoke_va (	holder,
											return_value,
											invocation_hint,
											narg_values,
											varargs	);
	
	va_end (varargs);
	
	return result;
}

/**
 * crank_func_holder_invoke_va:
 * @holder: A CrankFuncHolder.
 * @return_value: A #GValue to store return value.
 * @invocation_hint: (nullable): Invocation hint for backing #GClosure.
 * @narg_values: Length of @varargs.
 * @varargs: va_list of #GValue with arguments.
 *
 * Invokes a function which matches types of @varargs.
 *
 * @return_value should be initialized with appropriate type. Type can be
 * obtained from crank_func_holder_lookup_return_type().
 *
 * Returns: %TRUE if the function exists and invoked.
 */
gboolean
crank_func_holder_invoke_va (	CrankFuncHolder*	holder,
								GValue*				return_value,
								gpointer			invocation_hint,
								guint				narg_values,
								va_list				varargs	)
{
	GValue*		arg_values;
	guint 		i;
	
	gboolean	result;
	
	arg_values = g_new0 (GValue, narg_values);
	
	crank_value_array_overwrite_va (arg_values, narg_values, varargs);
	
	result = crank_func_holder_invoke (
			holder,
			return_value,
			narg_values,
			arg_values,
			invocation_hint );
	
	crank_value_array_unset (arg_values, narg_values);
	
	g_free (arg_values);
	
	return result;
}



/**
 * crank_func_holder_invoke_overwrite:
 * @holder: A CrankFuncHolder.
 * @return_value: (out): A #GValue to store return value.
 * @narg_values: Length of @arg_values.
 * @arg_values: (array length=narg_values): Array of #GValue with arguments.
 * @invocation_hint: (nullable): Invocation hint for backing #GClosure.
 *
 * Invokes a function which matches types of @arg_values.
 *
 * @return_value will be overriden and reinitialized by registered return type.
 * If no function found, or return type is %G_TYPE_VOID, then @return_value
 * will be left unset.
 *
 * Returns: %TRUE if the function exists and invoked.
 */
gboolean
crank_func_holder_invoke_overwrite (CrankFuncHolder*	holder,
				                  GValue*			return_value,
				                  const guint   	narg_values,
				                  const GValue*		arg_values,
				                  gpointer			invocation_hint)
{
	CrankFuncHolderData* data;

	GType*	types = g_new(GType, narg_values);

	gint i;
	for (i = 0; i < narg_values; i++)
		types[i] = crank_func_holder_get_actual_type (arg_values + i);

  	data = crank_func_holder_lookup_data_by_param_types (holder, types, narg_values);


	if (data != NULL) {
		crank_value_overwrite_init (
				return_value,
				crank_func_type_get_return_type (data->ftype)	);
										
		g_closure_invoke (
				data->closure,
				return_value,
				narg_values,
				arg_values,
				invocation_hint);
	}
	
	g_free (types);

  	return (data != NULL);
}


/**
 * crank_func_holder_invokev_overwrite:
 * @holder: A CrankFuncHolder.
 * @return_value: (out): A #GValue to store return value.
 * @invocation_hint: (nullable): Invocation hint for backing #GClosure.
 * @narg_values: Length of @...
 * @...: Variadic arguments of #GValue with arguments
 *
 * Invokes a function which matches types of @....
 *
 * @return_value will be overriden and reinitialized by registered return type.
 * If no function found, or return type is %G_TYPE_VOID, then @return_value
 * will be left unset.
 *
 * Returns: %TRUE if the function exists and invoked.
 */
gboolean
crank_func_holder_invokev_overwrite (	CrankFuncHolder*	holder,
										GValue*				return_value,
										gpointer			invocation_hint,
										guint				narg_values,
										...	)
{
	va_list		varargs;
	gboolean	result;
	
	va_start (varargs, narg_values );
	
	result = crank_func_holder_invoke_va_overwrite (	holder,
														return_value,
														invocation_hint,
														narg_values,
														varargs	);
	
	va_end (varargs);
	
	return result;
}

/**
 * crank_func_holder_invoke_va_overwrite:
 * @holder: A CrankFuncHolder.
 * @return_value: (out): A #GValue to store return value.
 * @invocation_hint: (nullable): Invocation hint for backing #GClosure.
 * @narg_values: Length of @varargs.
 * @varargs: va_list of #GValue with arguments.
 *
 * Invokes a function which matches types of @varargs.
 *
 * @return_value will be overriden and reinitialized by registered return type.
 * If no function found, or return type is %G_TYPE_VOID, then @return_value
 * will be left unset.
 *
 * Returns: %TRUE if the function exists and invoked.
 */
gboolean
crank_func_holder_invoke_va_overwrite (	CrankFuncHolder*	holder,
										GValue*				return_value,
										gpointer			invocation_hint,
										guint				narg_values,
										va_list				varargs	)
{
	GValue*		arg_values;
	guint 		i;
	
	gboolean	result;
	
	arg_values = g_new0 (GValue, narg_values);
	
	crank_value_array_overwrite_va (arg_values, narg_values, varargs);
	
	result = crank_func_holder_invoke_overwrite (
			holder,
			return_value,
			narg_values,
			arg_values,
			invocation_hint );
	
	crank_value_array_unset (arg_values, narg_values);
	
	g_free (arg_values);
	
	return result;
}

//////// CrankFuncBook /////////////////////////////////////////////////////////

/**
 * CrankFuncBook:
 *
 * Stores multiple #CrankFuncHolder by their names. Generally, it is used for
 * grouping related #CrankFuncHolder.
 */
struct _CrankFuncBook {
	GQuark				name;
	GPtrArray*			func_holders;
	GHashTable*			table_index;		// CrankFuncHolder -> guint
	GHashTable*			table_name_holder;	// GQuark -> CrankFuncHolder
	
	guint				_refc;
};

G_DEFINE_BOXED_TYPE(CrankFuncBook, crank_func_book,
		crank_func_book_ref,
		crank_func_book_unref);


//////// 외부 공개 함수

/**
 * crank_func_book_new:
 *
 * Constructs a nameless function book.
 *
 * Returns: (transfer full): Newly created function book.
 */
CrankFuncBook*
crank_func_book_new (void) {
	return crank_func_book_new_with_qname (0);
}

/**
 * crank_func_book_new_with_name:
 * @name: (nullable): Name of function book.
 *
 * Constructs a function book with string name.
 *
 * Returns: (transfer full): Newly created function book.
 */
CrankFuncBook*
crank_func_book_new_with_name (	const gchar*	name	)
{
	return crank_func_book_new_with_qname (g_quark_from_string(name));
}

/**
 * crank_func_book_new_with_qname:
 * @name: Name of function book.
 *
 * Constructs a function book with quark name.
 *
 * Returns: (transfer full): Newly created function book.
 */
CrankFuncBook*
crank_func_book_new_with_qname (	const GQuark	name	)
{
	CrankFuncBook* book = g_new (CrankFuncBook, 1);
	
	book->name = name;
	book->func_holders = g_ptr_array_new ();
	
	book->table_index = g_hash_table_new (
			g_direct_hash,
			g_direct_equal	);
	
	book->table_name_holder = g_hash_table_new (
			g_direct_hash,
			g_direct_equal	);
	
	book->_refc = 1;
	return book;
}



/**
 * crank_func_book_ref:
 * @book: A function book.
 *
 * Increases reference count by 1.
 *
 * Returns: (transfer full): @book with increased reference count.
 */
CrankFuncBook*
crank_func_book_ref (	CrankFuncBook*		book	)
{
	g_atomic_int_inc(&book->_refc);
	return book;
}

/**
 * crank_func_book_unref:
 * @book: A function book.
 *
 * Decrease reference count by 1. If reference count reaches 0, function book
 * will be freed.
 */
void
crank_func_book_unref (	CrankFuncBook*		book	)
{
	if (g_atomic_int_dec_and_test(&book->_refc)) {
		g_hash_table_unref (book->table_name_holder);
		g_hash_table_unref (book->table_index);
		g_ptr_array_unref (book->func_holders);
		g_free (book);
	}
}

/**
 * crank_func_book_set_name:
 * @book: A function book.
 * @name: (nullable): Name of function book.
 *
 * Sets name of function book by string.
 */
void
crank_func_book_set_name (	CrankFuncBook*		book,
							const gchar*		name	)
{
	book->name = g_quark_from_string (name);
}

/**
 * crank_func_book_get_name:
 * @book: A function book.
 *
 * Gets name of function book as string.
 *
 * Returns: (nullable): A name of function book.
 */
const gchar*
crank_func_book_get_name (	CrankFuncBook*		book	)
{
	g_message ("get name: %ld: %s", (glong)book->name, g_quark_to_string(book->name));
	return g_quark_to_string (book->name);
}


/**
 * crank_func_book_set_qname:
 * @book: A function book.
 * @name: Name of function book.
 *
 * Sets name of function book by #GQuark.
 */
void
crank_func_book_set_qname (	CrankFuncBook*		book,
							const GQuark		name	)
{
	book->name = name;
}

/**
 * crank_func_book_get_qname:
 * @book: A function book.
 *
 * Gets name of function book as #GQuark.
 *
 * Returns: A name of function book.
 */
GQuark
crank_func_book_get_qname (	CrankFuncBook*		book	)
{
	return book->name;
}


/**
 * crank_func_book_set:
 * @book: A function book.
 * @index: Index of function book.
 * @holder: (nullable): A function holder
 *
 * Sets a function holder to index.
 */
void
crank_func_book_set (	CrankFuncBook*		book,
						const guint			index,
						CrankFuncHolder*	holder	)
{
	g_hash_table_insert (book->table_name_holder,
			GINT_TO_POINTER (holder->name),
			holder									);
	
	g_hash_table_insert (book->table_index,
			holder,
			GINT_TO_POINTER (index)					);
	
	if (book->func_holders->len <= index) {
		g_ptr_array_set_size (book->func_holders, index + 1);
	}

	
	if (book->func_holders->pdata[index] != NULL)
		crank_func_holder_unref (book->func_holders->pdata[index]);

	book->func_holders->pdata[index] = crank_func_holder_ref (holder);
}

/**
 * crank_func_book_get:
 * @book: A function book.
 * @index: Index of function book.
 *
 * Gets a function holder at given index.
 *
 * Returns: (nullable): Function holder at given index or %NULL if not.
 */
CrankFuncHolder*
crank_func_book_get (	CrankFuncBook*		book,
						const guint			index	)
{
	
	if (index < (book->func_holders->len))
		return book->func_holders->pdata[index];
	
	return NULL;
}

/**
 * crank_func_book_index_of:
 * @book: A function book.
 * @holder: A function holder.
 *
 * Gets index of given function holder.
 *
 * Returns: Function index of given function holder, or -1 if holder is not in
 *         function book.
 */
gint
crank_func_book_index_of (	CrankFuncBook*		book,
							CrankFuncHolder*	holder	)
{
	if (g_hash_table_contains (book->table_index, holder))
		return GPOINTER_TO_INT (g_hash_table_lookup (book->table_index, holder));
	return -1;
}

/**
 * crank_func_book_get_by_name:
 * @book: A function book.
 * @name: Name of function holder.
 *
 * Look for a function holder by name.
 *
 * Returns: (nullable): A function holder with given name, or %NULL if it does
 *         not exists.
 */
CrankFuncHolder*
crank_func_book_get_by_name (	CrankFuncBook*	book,
								const gchar*	name	)
{
	GQuark	qname = g_quark_try_string (name);
	
	if (qname == 0) return NULL;
	
	return g_hash_table_lookup (book->table_name_holder, GINT_TO_POINTER(qname));
}

/**
 * crank_func_book_get_by_qname:
 * @book: A function book.
 * @name: Name of function book.
 *
 * Looks for a function holder by name.
 *
 * Returns: (nullable): A function holder with given name, or %NULL if it does
 *         not exists.
 */
CrankFuncHolder*
crank_func_book_get_by_qname (	CrankFuncBook*	book,
								const GQuark	name	)
{
	return g_hash_table_lookup (book->table_name_holder, GINT_TO_POINTER(name));
}

/**
 * crank_func_book_remove:
 * @book: A function book.
 * @index: Index to remove.
 *
 * Removes a function holder at given index.
 *
 * Returns: Whether the holder is removed.
 */
gboolean
crank_func_book_remove (	CrankFuncBook*	book,
							const guint		index	)
{
	CrankFuncHolder* holder =
		(CrankFuncHolder*) book->func_holders->pdata[index];
	
	if (holder != NULL) {
		g_hash_table_remove (book->table_index, holder);
		g_hash_table_remove (book->table_name_holder,
			GINT_TO_POINTER (crank_func_holder_get_qname(holder))	);
		
		book->func_holders->pdata[index] = NULL;
		
		crank_func_holder_unref (holder);
		return TRUE;
	}
	else return FALSE;
}

/**
 * crank_func_book_remove_by_name:
 * @book: A function book.
 * @name: Name of function holder.
 *
 * Removes a function holder by its name.
 *
 * Returns: Whether the holder existed and removed.
 */
gboolean
crank_func_book_remove_by_name (CrankFuncBook*		book,
								const gchar*		name	)
{
	GQuark	qname = g_quark_try_string (name);
	
	if (qname == 0) return FALSE;
	
	return crank_func_book_remove_by_qname (book, qname);
}

/**
 * crank_func_book_remove_by_qname:
 * @book: A function book.
 * @name: Name of function holder.
 *
 * Removes a function holder by its name.
 *
 * Returns: Whether the holder existed and removed.
 */
gboolean
crank_func_book_remove_by_qname (	CrankFuncBook*		book,
									const GQuark		name	)
{
	CrankFuncHolder*	holder;
	guint				index;
	
	holder = g_hash_table_lookup (book->table_name_holder,
			GINT_TO_POINTER (name)	);
	
	if (holder != NULL) {
		index = GPOINTER_TO_INT (g_hash_table_lookup (book->table_index, holder));
	
		g_hash_table_remove (book->table_index, holder);
		g_hash_table_remove (book->table_name_holder,
			GINT_TO_POINTER (crank_func_holder_get_qname(holder))	);
		
		book->func_holders->pdata[index] = NULL;
		
		crank_func_holder_unref (holder);
		return TRUE;
	}
	
	else return FALSE;
}


/**
 * crank_func_book_invoke:
 * @book: A function book.
 * @index: A index of function holder.
 * @return_value: (optional): A GValue to store return value.
 * @narg_values: Length of @arg_values.
 * @arg_values: (array length=narg_values): Array of GValue with arguments.
 * @invocation_hint: (nullable): Invocation hint for backing #GClosure.
 *
 * Invokes function holder at given index.
 *
 * Returns: Whether the function holder was invoked.
 */
gboolean
crank_func_book_invoke (	CrankFuncBook*		book,
							const guint			index,
							GValue*				return_value,
							const guint			narg_values,
							const GValue*		arg_values,
							gpointer			invocation_hint	)
{
	CrankFuncHolder* holder =
			(CrankFuncHolder*) book->func_holders->pdata[index];
	
	if (holder != NULL) {
		return crank_func_holder_invoke (	holder,
				return_value,
				narg_values, arg_values,
				invocation_hint);
	}
	return FALSE;
}


/**
 * crank_func_book_invoke_name:
 * @book: A function book.
 * @name: Name of function holder.
 * @return_value: (optional): A GValue to store return value.
 * @narg_values: Length of @arg_values.
 * @arg_values: (array length=narg_values): Array of GValue with arguments.
 * @invocation_hint: (nullable): Invocation hint for backing #GClosure.
 *
 * Invokes function holder at given index.
 *
 * Returns: Whether the function holder was invoked.
 */
gboolean
crank_func_book_invoke_name (	CrankFuncBook*		book,
								const gchar*		name,
								GValue*				return_value,
								const guint			narg_values,
								const GValue*		arg_values,
								gpointer			invocation_hint	)
{
	CrankFuncHolder*	holder;
	GQuark				qname;
	
	qname = g_quark_try_string (name);
	
	if (qname == 0) return FALSE;
	
	
	holder = (CrankFuncHolder*) g_hash_table_lookup (
			book->table_name_holder,
			GINT_TO_POINTER (qname)	);
	
	if (holder != NULL) {
		return crank_func_holder_invoke (	holder,
				return_value,
				narg_values, arg_values,
				invocation_hint);
	}
	return FALSE;
}


/**
 * crank_func_book_invoke_qname:
 * @book: A function book.
 * @name: Name of function holder.
 * @return_value: (optional): A GValue to store return value.
 * @narg_values: Length of @arg_values.
 * @arg_values: (array length=narg_values): Array of GValue with arguments.
 * @invocation_hint: (nullable): Invocation hint for backing #GClosure.
 *
 * Invokes function holder at given index.
 *
 * Returns: Whether the function holder was invoked.
 */
gboolean
crank_func_book_invoke_qname (	CrankFuncBook*		book,
								const GQuark		name,
								GValue*				return_value,
								const guint			narg_values,
								const GValue*		arg_values,
								gpointer			invocation_hint	)
{
	CrankFuncHolder*	holder = (CrankFuncHolder*) g_hash_table_lookup (
			book->table_name_holder,
			GINT_TO_POINTER (name)	);
	
	if (holder != NULL) {
		return crank_func_holder_invoke (	holder,
				return_value,
				narg_values, arg_values,
				invocation_hint);
	}
	return FALSE;
}


/**
 * crank_func_book_invoke_overwrite:
 * @book: A function book.
 * @index: A index of function holder.
 * @return_value: (optional): A GValue to store return value.
 * @narg_values: Length of @arg_values.
 * @arg_values: (array length=narg_values): Array of GValue with arguments.
 * @invocation_hint: (nullable): Invocation hint for backing #GClosure.
 *
 * Invokes function holder at given index.
 *
 * Returns: Whether the function holder was invoked.
 */
gboolean
crank_func_book_invoke_overwrite (	CrankFuncBook*		book,
									const guint			index,
									GValue*				return_value,
									const guint			narg_values,
									const GValue*		arg_values,
									gpointer			invocation_hint	)
{
	CrankFuncHolder* holder =
			(CrankFuncHolder*) book->func_holders->pdata[index];
	
	if (holder != NULL) {
		return crank_func_holder_invoke_overwrite (
				holder,
				return_value,
				narg_values, arg_values,
				invocation_hint);
	}
	return FALSE;
}

/**
 * crank_func_book_invoke_overwrite_name:
 * @book: A function book.
 * @name: Name of function holder.
 * @return_value: (optional): A GValue to store return value.
 * @narg_values: Length of @arg_values.
 * @arg_values: (array length=narg_values): Array of GValue with arguments.
 * @invocation_hint: (nullable): Invocation hint for backing #GClosure.
 *
 * Invokes function holder at given index.
 *
 * Returns: Whether the function holder was invoked.
 */
gboolean
crank_func_book_invoke_overwrite_name (	CrankFuncBook*		book,
										const gchar*		name,
										GValue*				return_value,
										const guint			narg_values,
										const GValue*		arg_values,
										gpointer			invocation_hint	)
{
	CrankFuncHolder*	holder;
	GQuark				qname;
	
	qname = g_quark_try_string (name);
	
	if (qname == 0) return FALSE;
	
	
	holder = (CrankFuncHolder*) g_hash_table_lookup (
			book->table_name_holder,
			GINT_TO_POINTER (qname)	);
	
	if (holder != NULL) {
		return crank_func_holder_invoke_overwrite (
				holder,
				return_value,
				narg_values, arg_values,
				invocation_hint);
	}
	return FALSE;
}


/**
 * crank_func_book_invoke_overwrite_qname:
 * @book: A function book.
 * @name: Name of function holder.
 * @return_value: (optional): A GValue to store return value.
 * @narg_values: Length of @arg_values.
 * @arg_values: (array length=narg_values): Array of GValue with arguments.
 * @invocation_hint: (nullable): Invocation hint for backing #GClosure.
 *
 * Invokes function holder at given index.
 *
 * Returns: Whether the function holder was invoked.
 */
gboolean
crank_func_book_invoke_overwrite_qname (	CrankFuncBook*		book,
								const GQuark		name,
								GValue*				return_value,
								const guint			narg_values,
								const GValue*		arg_values,
								gpointer			invocation_hint	)
{
	CrankFuncHolder*	holder = (CrankFuncHolder*) g_hash_table_lookup (
			book->table_name_holder,
			GINT_TO_POINTER (name)	);
	
	if (holder != NULL) {
		return crank_func_holder_invoke_overwrite (
				holder,
				return_value,
				narg_values, arg_values,
				invocation_hint);
	}
	return FALSE;
}


/**
 * crank_func_book_invokev:
 * @book: A function book.
 * @index: A index of function holder.
 * @return_value: (optional): A GValue to store return value.
 * @invocation_hint: (nullable): Invocation hint for backing #GClosure.
 * @narg_values: Length of @....
 * @...: Variadic Arguments of GValue with arguments.
 *
 * Invokes function holder at given index.
 *
 * Returns: Whether the function holder was invoked.
 */
gboolean
crank_func_book_invokev (		CrankFuncBook*		book,
								const guint			index,
								GValue*				return_value,
								gpointer			invocation_hint,
								const guint			narg_values,
								...	)
{
	va_list varargs;
	gboolean	result;
	
	va_start (varargs, narg_values);
	
	result = crank_func_book_invoke_va (book, index, return_value, invocation_hint, narg_values, varargs);
	
	va_end (varargs);
	
	return result;
}


/**
 * crank_func_book_invoke_va:
 * @book: A function book.
 * @index: A index of function holder.
 * @return_value: (optional): A GValue to store return value.
 * @narg_values: Length of @arg_values.
 * @varargs: Variadic Arguments with arguments.
 * @invocation_hint: (nullable): Invocation hint for backing #GClosure.
 *
 * Invokes function holder at given index.
 *
 * Returns: Whether the function holder was invoked.
 */
gboolean
crank_func_book_invoke_va (		CrankFuncBook*		book,
								const guint			index,
								GValue*				return_value,
								gpointer			invocation_hint,
								const guint			narg_values,
								va_list				varargs	)
{
	CrankFuncHolder* holder =
			(CrankFuncHolder*) book->func_holders->pdata[index];
	
	return crank_func_holder_invoke_va (holder, return_value, invocation_hint, narg_values, varargs);
}


/**
 * crank_func_book_invokev_overwrite:
 * @book: A function book.
 * @index: A index of function holder.
 * @return_value: (optional): A GValue to store return value.
 * @invocation_hint: (nullable): Invocation hint for backing #GClosure.
 * @narg_values: Length of @arg_values.
 * @...: Variadic Arguments of GValue with arguments.
 *
 * Invokes function holder at given index.
 *
 * Returns: Whether the function holder was invoked.
 */
gboolean
crank_func_book_invokev_overwrite (		CrankFuncBook*		book,
										const guint			index,
										GValue*				return_value,
										gpointer			invocation_hint,
										const guint			narg_values,
										...	)
{
	va_list varargs;
	gboolean	result;
	
	va_start (varargs, narg_values);
	
	result = crank_func_book_invoke_va_overwrite (	book,
													index,
													return_value,
													invocation_hint,
													narg_values,
													varargs	);
	
	va_end (varargs);
	
	return result;
}


/**
 * crank_func_book_invoke_va_overwrite:
 * @book: A function book.
 * @index: A index of function holder.
 * @return_value: (optional): A GValue to store return value.
 * @invocation_hint: (nullable): Invocation hint for backing #GClosure.
 * @narg_values: Length of @arg_values.
 * @varargs: va_list of GValue with arguments.
 *
 * Invokes function holder at given index.
 *
 * Returns: Whether the function holder was invoked.
 */
gboolean
crank_func_book_invoke_va_overwrite (		CrankFuncBook*		book,
											const guint			index,
											GValue*				return_value,
											gpointer			invocation_hint,
											const guint			narg_values,
											va_list				varargs	)
{
	CrankFuncHolder* holder =
			(CrankFuncHolder*) book->func_holders->pdata[index];
	
	return crank_func_holder_invoke_va_overwrite (	holder,
													return_value,
													invocation_hint,
													narg_values,
													varargs	);
}
