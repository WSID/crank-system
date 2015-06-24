#ifndef _CRANK_FUNCTION_HEADER
#define _CRANK_FUNCTION_HEADER

#ifndef _CRANKBASE_INSIDE
#error "crankfunction.h cannot be directly included."
#endif

#include <glib.h>

/**
 * CrankCallback: (skip)
 * @userdata: (closure): A userdata for callback.
 *
 * It represents any functions that accept @userdata.
 *
 * This is not used for actual callback type, but a placeholder for any function
 * type.
 */
typedef void		(*CrankCallback) (	gpointer	userdata	);

#endif
