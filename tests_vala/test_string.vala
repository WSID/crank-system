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

int main (string[] args) {
	GLib.Test.init (ref args);
	
	GLib.Test.add_func (	"/crank/base/string/read/space",
							test_read_space	);
	
	GLib.Test.add_func (	"/crank/base/string/read/word",
							test_read_word	);
	
	GLib.Test.add_func (	"/crank/base/string/scan/word",
							test_scan_word	);
	
	GLib.Test.add_func (	"/crank/base/string/check/char",
							test_check_char	);
	
	GLib.Test.add_func (	"/crank/base/string/check/chars",
							test_check_chars	);
							
	GLib.Test.add_func (	"/crank/base/string/check/chars_str",
							test_check_chars_str	);
	
	GLib.Test.run ();
	
	return 0;
}

void
test_read_space () {
	string subject = "  A string!";
	uint pos = 0;
	uint space;
	
	assert (Crank.str_read_space (subject, ref pos, out space));
	assert (pos == 2);
	assert (space == 2);
	
	assert (! Crank.str_read_space (subject, ref pos, out space));
	assert (pos == 2);
	assert (space == 0);
	
	pos = 3;
	assert (Crank.str_read_space (subject, ref pos, out space));
	assert (pos == 4);
	assert (space == 1);
	
	pos = 7;
	assert (! Crank.str_read_space (subject, ref pos, out space));
	assert (pos == 7);
	assert (space == 0);
}

void
test_read_word () {
	string subject = "A quick brown fox jumps over the lazy dog";
	uint pos = 0;
	string word;
	
	assert (Crank.str_read_word (subject, ref pos, out word));
	assert (pos == 1);
	assert (word == "A");
	
	assert (! Crank.str_read_word (subject, ref pos, out word));
	
	pos = 10;
	assert (Crank.str_read_word (subject, ref pos, out word));
	assert (pos == 13);
	assert (word == "own");
	
	pos = 20;
	assert (Crank.str_read_word (subject, ref pos, out word));
	assert (pos == 23);
	assert (word == "mps");
}

void
test_scan_char () {
	string subject = "( : )";
	uint pos = 0;
	char sym;
	
	assert (Crank.str_scan_char (subject, ref pos, out sym));
	assert (sym == '(');
	
	assert (Crank.str_scan_char (subject, ref pos, out sym));
	assert (sym == ':');
	
	assert (Crank.str_scan_char (subject, ref pos, out sym));
	assert (sym == ')');
	
	assert (! Crank.str_scan_char (subject, ref pos, out sym));
}

void
test_scan_word () {
	string subject = "Cookie cake strawberry";
	uint pos = 0;
	string word;
	
	assert (Crank.str_scan_word (subject, ref pos, out word));
	assert (word == "Cookie");
	
	assert (Crank.str_scan_word (subject, ref pos, out word));
	assert (word == "cake");
	
	assert (Crank.str_scan_word (subject, ref pos, out word));
	assert (word == "strawberry");
}

void
test_check_char () {
	string subject = "( : )";
	uint pos = 0;
	
	assert (! Crank.str_check_char (subject, ref pos, ':'));
	assert (Crank.str_check_char (subject, ref pos, '('));
	assert (! Crank.str_check_char (subject, ref pos, ')'));
	assert (Crank.str_check_char (subject, ref pos, ':'));
	assert (Crank.str_check_char (subject, ref pos, ')'));
}

void
test_check_chars () {
	string subject = "( : ) ,";
	uint pos = 0;
	
	char chars[3] = { '(', ':', ')' };
	
	assert (0 == Crank.str_check_chars (subject, ref pos, chars));
	assert (1 == Crank.str_check_chars (subject, ref pos, chars));
	assert (2 == Crank.str_check_chars (subject, ref pos, chars));
	assert (-1 == Crank.str_check_chars (subject, ref pos, chars));
}

void
test_check_chars_str () {
	string subject = "( : ) ,";
	uint pos = 0;
	
	string chars = "(:)";
	
	assert (0 == Crank.str_check_chars_str (subject, ref pos, chars));
	assert (1 == Crank.str_check_chars_str (subject, ref pos, chars));
	assert (2 == Crank.str_check_chars_str (subject, ref pos, chars));
	assert (-1 == Crank.str_check_chars_str (subject, ref pos, chars));
}
