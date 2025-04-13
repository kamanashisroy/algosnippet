


class SegmentTreePrefixSum:
    '''
    segment_tree_prefixsum.py file is part of Algosnippet.
    Algosnippet is a collection of practice data-structures and algorithms
    Copyright (C) 2025  Kamanashis Roy
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


    def __init__(self, given):

        depth = 1
        while (1<<depth) < given:
            depth += 1
        # if given = 1, depth = 1, N = 2
        # if given = 3, depth = 2, N = 4
        
        self.N = 1<<depth
        self.nodes = [0]*(self.N+self.N)
        self.leftMost = [i for i in range(self.N+self.N)]
        self.rightMost = [i for i in range(self.N+self.N)]
        for i in range(self.N-1,0,-1):
            self.leftMost[i] = self.leftMost[i<<1]
            self.rightMost[i] = self.rightMost[(i<<1)+1]

    def __setitem__(self, i, x):
        cur = self.N+i
        self.nodes[cur] = x
        while cur > 1:
            parent = cur>>1
            self.nodes[parent] += x
            cur = parent
    
    def __delitem__(self,i):
        cur = self.N+i
        x = self.nodes[cur]
        self.nodes[cur] -= x
        while cur > 1:
            parent = cur>>1
            self.nodes[parent] -= x
            cur = parent
    
    def __getitem__(self,i):

        l = self.N
        r = self.N+i

        ret = 0
        stack = [1]
        while stack:
            
            cur = stack.pop()
            if self.rightMost[cur] < l or self.leftMost[cur] > r:
                continue
            
            if self.leftMost[cur] >= l and self.rightMost[cur] <= r:
                ret += self.nodes[cur]
                continue
            
            left = cur<<1
            if left < len(self.nodes):
                stack.append( left )
            right = left+1
            if right < len(self.nodes):
                stack.append( right )
        return ret


