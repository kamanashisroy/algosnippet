

class SegmentTreeRMQ:
    '''
    segment_tree.py file is part of Algosnippet.
    Algosnippet is a collection of practice data-structures and algorithms
    Copyright (C) 2024  Kamanashis Roy
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

    def __init__(self, Ngiven:int):
        depth = 0
        while (1<<depth) < Ngiven:
            depth += 1

        INFLO = (-1,-1)
        self.N = 1<<depth
        self.nodes = [ INFLO for _ in range((self.N<<1)+2)]
        self.rightMost = [ i for i in range((self.N<<1)+2)]
        self.leftMost = [ i for i in range((self.N<<1)+2)]
        # N = 4
        # [ filler 0 ] [ root Node 1 ] 2 3 [ Internal nodes 4 5 6 7 ] [ Leaves 8 9 10 11 12 13 14 15 ]
        for i in range(self.N-1,0,-1):
            self.leftMost[i] = self.leftMost[i<<1]
            self.rightMost[i] = self.rightMost[(i<<1)+1]

    def fill(self,aNums):
        assert((self.N+len(aNums)-1) < len(self.nodes))
        for i,x in enumerate(aNums):
            self.nodes[i+self.N] = (x,i)
        
        for i in range(self.N-1,0,-1):
            self.nodes[i] = max(self.nodes[i<<1],self.nodes[(i<<1)+1])

    def __setitem__(self, i:int, givenVal:int) -> None:
        '''
        Procedure
        =========
            - sets the value at the leaf
            - go up towards the root and update the maximum value
        '''
        assert((self.N+i) < len(self.nodes))
        curr = self.N+i
        val = (givenVal,i)
        if val <= self.nodes[curr]:
            return # do not update
        self.nodes[curr] = val
        while curr > 1:
            # get parent
            parent = curr >> 1
            if  self.nodes[parent] >= val:
                break # do not update
            self.nodes[parent] = val
            curr = parent

    def __getitem__(self, i:int) -> int:
        assert((self.N+i) < len(self.nodes))
        return self.nodes[self.N+i]
    
    def queryMaxAll(self):
        return self.nodes[1]
    
    def queryMaxLeft(self, i:int) -> int:
        '''
        Return the max score saved in range of [0,i] inclusive
        '''
        curr = self.N+i
        result = self.nodes[curr]
        path = []
        while curr > 1:
            parent = curr >> 1
            path.append((parent,curr&1))
            curr = parent

        while path:
            curr,odd = path.pop()
            if odd:
                # when we are going for right child
                # take best result from left
                left = curr<<1
                result = max(result, self.nodes[left])
            else:
                # when we are going for left chld, we cannot take memo
                pass
        return result
    
    def queryMax(self, givenLeft, givenRight):
        '''
        Return the maximum value between beg and end
        '''
        assert(givenLeft <= givenRight)
        assert((self.N+givenRight) < len(self.nodes))
        
        ret = max(self.nodes[self.N+givenLeft],self.nodes[self.N+givenRight])
        stack = [1]
        while stack:
            cur = stack.pop()
            for child in (cur<<1,(cur<<1)+1):
                rightMost = self.rightMost[child]
                if rightMost < (self.N+givenLeft):
                    continue
                leftMost = self.leftMost[child]
                if leftMost > (self.N+givenRight):
                    continue

                if rightMost <= (self.N+givenRight) and leftMost >= (self.N+givenLeft):
                    ret = max(ret,self.nodes[child])
                    continue

                stack.append(child)
                
        return ret

