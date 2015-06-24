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
