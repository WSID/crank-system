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

#include <glib.h>
#include <glib/gi18n.h>

#include "crankdummy.h"
#include "config.h"

/**
 * SECTION:crankdummy
 * @short_description: 빌드 시스템을 세우면서 빌드 시스템을 돌려 볼 수 있는 더미
 * @title: 더미 모듈
 * @section_id:crankdummy
 * @stability: Unstable
 * @include: crankdummy.h
 *
 * 이 부분은 더미당 으헤헿헤헿ㅎ헿헤...
 *
 * 으앙 쥬금....
 */

/**
 * crank_dummy_init:
 */
void
crank_dummy_init (void)
{
  bindtextdomain (GETTEXT_PACKAGE, LOCALEDIR);
}

/**
 * crank_dummy_do:
 * 아무런 일을 하지 않습니다.
 * @input: 입력 값입니다.
 *
 * Returns: 숫자 4입니다.
 */
gint
crank_dummy_do (int input)
{
  g_print (_("I'm here!"));
	return 4;
}
