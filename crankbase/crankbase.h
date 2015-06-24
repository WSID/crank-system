#ifndef CRANKBASE_H
#define CRANKBASE_H

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

#include "crankbasemacro.h"
#include "crankstring.h"
#include "crankvala.h"
#include "crankvalue.h"

#include "crankdigraph.h"
#include "crankvecbool.h"
#include "crankvecint.h"
#include "crankvecfloat.h"

#include "crankadvgraph.h"


#undef _CRANKBASE_INSIDE


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

#endif /* CRANKBASE_H */
