
class SegmentTree:
    '''
    segment_tree.py file is part of Algosnippet.
    Algosnippet is a collection of practice data-structures and algorithms
    Copyright (C) 2021  Kamanashis Roy
    Algosnippet is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    Algosnippet is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with Algosnippet.  If not, see <https://www.gnu.org/licenses/>.
    '''

    def __init__(self, N:int):
        depth = 0
        while (1<<depth) < N:
            depth += 1

        N = 1<<depth
        self.nodes = [ 0 for _ in range((N<<1)+2)]
        self.N = N
        # N = 4
        # [ filler 0 ] [ root Node 1 ] 2 3 [ Internal nodes 4 5 6 7 ] [ Leaves 8 9 10 11 12 13 14 15 ]

    def append(self, i:int) -> None:
        curr = self.N+i
        self.nodes[curr] += 1
        while curr > 1:
            # get parent
            parent = curr >> 1
            self.nodes[parent] += 1
            curr = parent

    def countSmaller(self, limit:int) -> int:
        if 0 == limit:
            return 0
        curr = self.N+limit-1
        deduct = 0
        while curr > 1:
            #print(curr,self.N,len(self.nodes))
            if curr&1 == 0: # in case even
                deduct += self.nodes[curr+1]
            # get parent
            parent = curr >> 1
            curr = parent
        return self.nodes[1] - deduct
