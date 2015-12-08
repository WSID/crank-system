# Copyright (C) 2015, WSID

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

import unittest

class TestPolyStruct (unittest.TestCase):
    def test_tetrahedron (self):
        pstruct = CrankShape.PolyStruct ()

        pstruct.set_nvertices (4)

        pstruct.add_face_vertices ([0, 2, 1])
        pstruct.add_face_vertices ([3, 0, 1])
        pstruct.add_face_vertices ([3, 1, 2])
        pstruct.add_face_vertices ([3, 2, 0])

        self.assertEqual (pstruct.get_nvertices (), 4)
        self.assertEqual (pstruct.get_nedges (), 6)
        self.assertEqual (pstruct.get_nfaces (), 4)

        assert (pstruct.check_valid ())

    def test_cube (self):
        pstruct = CrankShape.PolyStruct ()

        pstruct.set_nvertices (8)

        pstruct.add_face_vertices ([0, 1, 2, 3])
        pstruct.add_face_vertices ([0, 4, 5, 1])
        pstruct.add_face_vertices ([1, 5, 6, 2])
        pstruct.add_face_vertices ([2, 6, 7, 3])
        pstruct.add_face_vertices ([3, 7, 4, 0])
        pstruct.add_face_vertices ([7, 6, 5, 4])

        self.assertEqual (pstruct.get_nvertices (), 8)
        self.assertEqual (pstruct.get_nedges (), 12)
        self.assertEqual (pstruct.get_nfaces (), 6)

        assert (pstruct.check_valid ())
