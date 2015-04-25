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

#include <string.h>
#include <glib.h>

#include "crankbase.h"
#include "crankstring.h"

void	test_read_space (void);

void	test_read_word (void);

void	test_scan_char (void);

void	test_scan_word (void);

void	test_check_char (void);

void	test_check_chars (void);

void	test_check_chars_str (void);

gint
main	(gint argc, gchar** argv)
{
	g_test_init (&argc, &argv, NULL);

	g_test_add_func (	"/crank/base/string/read/space",
						test_read_space);

	g_test_add_func (	"/crank/base/string/read/word",
						test_read_word);

	g_test_add_func (	"/crank/base/string/scan/char",
						test_scan_char);

	g_test_add_func (	"/crank/base/string/scan/word",
						test_scan_word);

	g_test_add_func (	"/crank/base/string/check/char",
						test_check_char);

	g_test_add_func (	"/crank/base/string/check/chars",
						test_check_chars);

	g_test_add_func (	"/crank/base/string/check/chars_str",
						test_check_chars_str);

	g_test_run ();

}

void
test_read_space (void) {

	const gchar* subject = "  A string!";
	guint pos = 0;
	guint space = 0;

	g_assert (crank_str_read_space (subject, &pos, &space));
	g_assert_cmpuint (pos, ==, 2);
	g_assert_cmpuint (space, ==, 2);

	g_assert (! crank_str_read_space (subject, &pos, &space));
	g_assert_cmpuint (pos, ==, 2);
	g_assert_cmpuint (space, ==, 0);

	pos = 3;
	g_assert (crank_str_read_space (subject, &pos, &space));
	g_assert_cmpuint (pos, ==, 4);
	g_assert_cmpuint (space, ==, 1);

	pos = 7;
	g_assert (! crank_str_read_space (subject, &pos, &space));
	g_assert_cmpuint (pos, ==, 7);
	g_assert_cmpuint (space, ==, 0);
}

void
test_read_word (void) {
	const gchar*	subject = 	"A quick brown fox jumps over the lazy dog";
	guint			pos = 		0;
	gchar*			word;

	g_assert (crank_str_read_word (subject, &pos, &word));
	g_assert_cmpuint (pos, ==, 1);
	g_assert_cmpstr (word, ==, "A");
	g_free (word);

	g_assert (! crank_str_read_word (subject, &pos, &word));

	pos = 10;
	g_assert (crank_str_read_word (subject, &pos, &word));
	g_assert_cmpuint (pos, ==, 13);
	g_assert_cmpstr (word, ==, "own");
	g_free (word);

	pos = 20;
	g_assert (crank_str_read_word (subject, &pos, &word));
	g_assert_cmpuint (pos, ==, 23);
	g_assert_cmpstr (word, ==, "mps");
	g_free (word);
}

void
test_scan_char (void) {
	const gchar*	subject =	"( : )";
	guint			pos =		0;
	gchar			sym;

	g_assert (crank_str_scan_char (subject, &pos, &sym));
	g_assert_cmpint (sym, ==, '(');

	g_assert (crank_str_scan_char (subject, &pos, &sym));
	g_assert_cmpint (sym, ==, ':');

	g_assert (crank_str_scan_char (subject, &pos, &sym));
	g_assert_cmpint (sym, ==, ')');
	
	g_assert (! crank_str_scan_char (subject, &pos, &sym));
}

void
test_scan_word (void) {
	const gchar*	subject =	"Cookie cake strawberry";
	guint			pos =		0;
	gchar*			word;

	g_assert (crank_str_scan_word (subject, &pos, &word));
	g_assert_cmpstr (word, ==, "Cookie");
	g_free (word);

	g_assert (crank_str_scan_word (subject, &pos, &word));
	g_assert_cmpstr (word, ==, "cake");
	g_free (word);

	g_assert (crank_str_scan_word (subject, &pos, &word));
	g_assert_cmpstr (word, ==, "strawberry");
	g_free (word);
}

void
test_check_char (void) {
	const gchar*	subject = 	"( : )";
	guint 			pos = 		0;

	g_assert (! crank_str_check_char (subject, &pos, ':'));
	g_assert (crank_str_check_char (subject, &pos, '('));
	g_assert (! crank_str_check_char (subject, &pos, ')'));
	g_assert (crank_str_check_char (subject, &pos, ':'));
	g_assert (crank_str_check_char (subject, &pos, ')'));
}

void
test_check_chars (void) {
	const gchar*	subject =	"( : ) ,";
	guint			pos =		0;

	static gchar*	chars = "(:)";

	g_assert_cmpint (0, ==, crank_str_check_chars (subject, &pos, chars, 3));
	g_assert_cmpint (1, ==, crank_str_check_chars (subject, &pos, chars, 3));
	g_assert_cmpint (2, ==, crank_str_check_chars (subject, &pos, chars, 3));
	g_assert_cmpint (-1, ==, crank_str_check_chars (subject, &pos, chars, 3));

}

void
test_check_chars_str (void) {
	const gchar*	subject =	"( : ) ,";
	guint			pos =		0;

	static gchar*	chars = "(:)";

	g_assert_cmpint (0, ==, crank_str_check_chars_str (subject, &pos, chars));
	g_assert_cmpint (1, ==, crank_str_check_chars_str (subject, &pos, chars));
	g_assert_cmpint (2, ==, crank_str_check_chars_str (subject, &pos, chars));
	g_assert_cmpint (-1, ==, crank_str_check_chars_str (subject, &pos, chars));

}
