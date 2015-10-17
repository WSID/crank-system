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
 
int main (string[] args) {
	GLib.Test.init (ref args);
	
	GLib.Test.add_func (	"/crank/base/string/read/space",
							test_read_space	);
	
	GLib.Test.add_func (	"/crank/base/string/read/word",
							test_read_word	);
							
	GLib.Test.add_func (	"/crank/base/string/read/uint64",
							test_read_uint64	);
							
	GLib.Test.add_func (	"/crank/base/string/read/int64",
							test_read_int64	);
	
	GLib.Test.add_func (	"/crank/base/string/read/double",
							test_read_double	);
	
	GLib.Test.add_func (	"/crank/base/string/read/path",
							test_read_path	);

	GLib.Test.add_func (	"/crank/base/string/scan/char",
							test_scan_char	);
	
	GLib.Test.add_func (	"/crank/base/string/scan/word",
							test_scan_word	);
	
	GLib.Test.add_func (	"/crank/base/string/check/char",
							test_check_char	);
	
	GLib.Test.add_func (	"/crank/base/string/check/chars",
							test_check_chars	);
							
	GLib.Test.add_func (	"/crank/base/string/check/chars_str",
							test_check_chars_str	);
							
	GLib.Test.add_func (	"/crank/base/string/check/words",
							test_check_words	);
	
	GLib.Test.run ();
	
	return 0;
}

private void test_read_space () {
	string subject = "  A string!";
	uint pos = 0;
	uint space;
	
	assert (Crank.Str.read_space (subject, ref pos, out space));
	assert (pos == 2);
	assert (space == 2);
	
	assert (! Crank.Str.read_space (subject, ref pos, out space));
	assert (pos == 2);
	assert (space == 0);
	
	pos = 3;
	assert (Crank.Str.read_space (subject, ref pos, out space));
	assert (pos == 4);
	assert (space == 1);
	
	pos = 7;
	assert (! Crank.Str.read_space (subject, ref pos, out space));
	assert (pos == 7);
	assert (space == 0);
}

private void test_read_word () {
	string subject = "A quick brown fox jumps over the lazy dog";
	uint pos = 0;
	string word;
	
	assert (Crank.Str.read_word (subject, ref pos, out word));
	assert (pos == 1);
	assert (word == "A");
	
	assert (! Crank.Str.read_word (subject, ref pos, out word));
	
	pos = 10;
	assert (Crank.Str.read_word (subject, ref pos, out word));
	assert (pos == 13);
	assert (word == "own");
	
	pos = 20;
	assert (Crank.Str.read_word (subject, ref pos, out word));
	assert (pos == 23);
	assert (word == "mps");
}

private void test_read_uint64 () {
	string	subject = "12 seven 1948889382 18446744073709551615 19073283471829393945";
	uint	pos = 0;
	uint64	value;
	bool	overflow;
	
	assert (Crank.Str.read_uint64 (subject, ref pos, out value, out overflow));
	assert (pos == 2);
	assert (value == 12);
	assert (overflow == false);
	
	pos = 3;
	assert (! Crank.Str.read_uint64 (subject, ref pos, out value, out overflow));
	
	pos = 9;
	assert (Crank.Str.read_uint64 (subject, ref pos, out value, out overflow));
	assert (pos == 19);
	assert (value == 1948889382L);
	assert (overflow == false);
	
	pos = 20;
	assert (Crank.Str.read_uint64 (subject, ref pos, out value, out overflow));
	assert (pos == 40);
	assert (value == 18446744073709551615L);
	assert (overflow == false);
	
	pos = 41;
	assert (Crank.Str.read_uint64 (subject, ref pos, out value, out overflow));
	assert (pos == 61);
	assert (value == uint64.MAX);
	assert (overflow == true);
}

private void test_read_int64 () {
	string	subject = "EE -492 +32948398 555518394892988392 -38293887837878789218884";
	uint	pos = 0;
	int64	value;
	int		overflow;
	
	assert (! Crank.Str.read_int64 (subject, ref pos, out value, out overflow));
	
	pos = 3;
	assert (Crank.Str.read_int64 (subject, ref pos, out value, out overflow));
	assert (pos == 7);
	assert (value == -492);
	assert (overflow == 0);
	
	pos = 8;
	assert (Crank.Str.read_int64 (subject, ref pos, out value, out overflow));
	assert (pos == 17);
	assert (value == 32948398L);
	assert (overflow == 0);
	
	pos = 18;
	assert (Crank.Str.read_int64 (subject, ref pos, out value, out overflow));
	assert (pos == 36);
	assert (value == 555518394892988392L);
	assert (overflow == 0);
	
	pos = 37;
	assert (Crank.Str.read_int64 (subject, ref pos, out value, out overflow));
	assert (pos == 61);
	assert (value == int64.MIN);
	assert (overflow < 0);
}

private void test_read_double () {
	string subject =
		"INF nemo 15 +3.141259 88e52 -1.433e-670 7.49292e-310 1.999e275";
	
	uint				pos;
	double				value;
	Crank.ReadDecResult	result;

	pos = 0;
	assert ( Crank.Str.read_double (subject, ref pos, out value, out result));
	assert (pos == 3);
	assert (value.is_infinity () == 1);
	assert ((result & Crank.ReadDecResult.SYMBOL) != 0);
	
	pos = 4;
	assert (!Crank.Str.read_double (subject, ref pos, out value, out result));
	
	pos = 9;
	assert ( Crank.Str.read_double (subject, ref pos, out value, out result));
	assert (pos == 11);
	assert (value == 15);
	
	pos = 12;
	assert ( Crank.Str.read_double (subject, ref pos, out value, out result));
	assert (pos == 21);
	assert (value == 3.141259);
	
	pos = 22;
	assert ( Crank.Str.read_double (subject, ref pos, out value, out result));
	assert (pos == 27);
	assert (value == 8.8e53);
	
	pos = 28;
	assert ( Crank.Str.read_double (subject, ref pos, out value, out result));
	assert (pos == 39);
	assert (value == 0);
	assert ((result & Crank.ReadDecResult.UNDERFLOW) != 0);
	
	pos = 40;
	assert ( Crank.Str.read_double (subject, ref pos, out value, out result));
	assert (pos == 52);
	message (value.to_string ());
	assert (7.4929199e-310 <= value <= 7.4929201e-310);
	
	pos = 53;
	assert ( Crank.Str.read_double (subject, ref pos, out value, out result));
	assert (pos == 62);
	assert (value == 1.999e275);
}

private void test_read_path () {
	string subject = "/home/wsid/Downloads/Incoming/";
	uint pos = 0;
	string[] pathlist;

	assert (Crank.Str.read_path (
			subject,
			ref pos,
			out pathlist,
			Crank.Str.read_word));

	assert (pathlist.length == 6);
	assert (pathlist[0] == "");
	assert (pathlist[1] == "home");
	assert (pathlist[2] == "wsid");
	assert (pathlist[3] == "Downloads");
	assert (pathlist[4] == "Incoming");
	assert (pathlist[5] == "");
	assert (pos == 30);

	subject = "Documents/projects/crank-system/configure-ac";
	pos = 0;

	assert (Crank.Str.read_path (
			subject,
			ref pos,
			out pathlist,
			Crank.Str.read_canonical_word));

	assert (pathlist.length == 4);
	assert (pathlist[0] == "Documents");
	assert (pathlist[1] == "projects");
	assert (pathlist[2] == "crank-system");
	assert (pathlist[3] == "configure-ac");
	assert (pos == 44);

	subject = "/";
	pos = 0;

	assert (Crank.Str.read_path (
			subject,
			ref pos,
			out pathlist,
			Crank.Str.read_canonical_word));

	assert (pathlist.length == 2);
	assert (pathlist[0] == "");
	assert (pathlist[1] == "");
	assert (pos == 1);
}
	

private void test_scan_char () {
	string subject = "( : )";
	uint pos = 0;
	char sym;
	
	assert (Crank.Str.scan_char (subject, ref pos, out sym));
	assert (sym == '(');
	
	assert (Crank.Str.scan_char (subject, ref pos, out sym));
	assert (sym == ':');
	
	assert (Crank.Str.scan_char (subject, ref pos, out sym));
	assert (sym == ')');
	
	assert (! Crank.Str.scan_char (subject, ref pos, out sym));
}

private void test_scan_word () {
	string subject = "Cookie cake strawberry";
	uint pos = 0;
	string word;
	
	assert (Crank.Str.scan_word (subject, ref pos, out word));
	assert (word == "Cookie");
	
	assert (Crank.Str.scan_word (subject, ref pos, out word));
	assert (word == "cake");
	
	assert (Crank.Str.scan_word (subject, ref pos, out word));
	assert (word == "strawberry");
}

private void test_check_char () {
	string subject = "( : )";
	uint pos = 0;
	
	assert (! Crank.Str.check_char (subject, ref pos, ':'));
	assert (Crank.Str.check_char (subject, ref pos, '('));
	assert (! Crank.Str.check_char (subject, ref pos, ')'));
	assert (Crank.Str.check_char (subject, ref pos, ':'));
	assert (Crank.Str.check_char (subject, ref pos, ')'));
}

private void test_check_chars () {
	string subject = "( : ) ,";
	uint pos = 0;
	
	char chars[3] = { '(', ':', ')' };
	
	assert (0 == Crank.Str.check_chars (subject, ref pos, chars));
	assert (1 == Crank.Str.check_chars (subject, ref pos, chars));
	assert (2 == Crank.Str.check_chars (subject, ref pos, chars));
	assert (-1 == Crank.Str.check_chars (subject, ref pos, chars));
}

private void test_check_chars_str () {
	string subject = "( : ) ,";
	uint pos = 0;
	
	string chars = "(:)";
	
	assert (0 == Crank.Str.check_chars_str (subject, ref pos, chars));
	assert (1 == Crank.Str.check_chars_str (subject, ref pos, chars));
	assert (2 == Crank.Str.check_chars_str (subject, ref pos, chars));
	assert (-1 == Crank.Str.check_chars_str (subject, ref pos, chars));
}

private void test_check_words () {
	string subject = "Apple pie and strawberry shortcake or graph juice";
	uint	pos = 0;
	
	string[]	fruits = {
		"apple",
		"graph",
		"orange",
		"pear",
		"strawberry"
	};
	
	assert (-1 == Crank.Str.check_words (subject, ref pos, fruits, 0));
	assert (0 == Crank.Str.check_words (subject, ref pos, fruits,
										Crank.StrCheckFlags.CI_IN_LOWERCASE));
	
	assert (-1 == Crank.Str.check_words (subject, ref pos, fruits, 0));
	
	pos = 9;
	assert (-1 == Crank.Str.check_words (subject, ref pos, fruits, 0));
	
	pos = 13;
	assert (4 == Crank.Str.check_words (subject, ref pos, fruits, 0));
	
	assert (-1 == Crank.Str.check_words (subject, ref pos, fruits, 0));
	
	pos = 34;
	assert (-1 == Crank.Str.check_words (subject, ref pos, fruits, 0));
	
	pos = 37;
	assert (1 == Crank.Str.check_words (subject, ref pos, fruits, 0));
	assert (-1 == Crank.Str.check_words (subject, ref pos, fruits, 0));
}
