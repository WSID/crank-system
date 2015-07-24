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
