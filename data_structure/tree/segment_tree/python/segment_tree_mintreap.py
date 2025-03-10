class SegmentTreeMinTreap:
    '''
    This file is part of Algosnippet.
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


    Min Treap built on top of segment-tree.
    '''


    def __init__(self, Ngiven:int, defaultVal:int = float('Inf')):
        depth = 0
        while (1<<depth) < Ngiven:
            depth += 1

        INFLO = (defaultVal,-1)
        self.N = 1<<depth
        self.defaultVal = defaultVal
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
            #self.nodes[i] = self.oper(self.nodes[i<<1],self.nodes[(i<<1)+1])
            self.nodes[i] = min(self.nodes[i<<1],self.nodes[(i<<1)+1])

    def clearAt(self, i:int) -> None:
        assert((self.N+i) < len(self.nodes))
        curr = self.N+i
        val = (self.defaultVal,i)
        self.nodes[curr] = val
        #print(self.nodes)
        while curr > 1:
            #print('ignore',val,self.nodes[curr],self.nodes)
            val = self.nodes[curr]
            # get parent
            parent = curr >> 1
            if  self.nodes[parent] > val:
                break # do not update
            left = parent<<1
            right = left+1
            self.nodes[parent] = min(self.nodes[left],self.nodes[right])
            curr = parent

    def __getitem__(self, i:int) -> int:
        assert((self.N+i) < len(self.nodes))
        return self.nodes[self.N+i][0]
    
    def printNodes(self, beg,end):
        print(self.nodes[self.N+beg:self.N+end])
        
    def findFirstOfGivenSizeOrSmaller(self, limit:int) ->int:
        curr = 1 # root node
        NN = self.N+self.N
        while curr < len(self.nodes):
            minval,idx = self.nodes[curr]
            #print('find limit',limit,'curr',curr,self.nodes[curr])
            if minval > limit:
                return -1
            
            left = (curr<<1)
            right = left+1
            if left >= NN or right >= NN:
                return idx
            minleft,unused = self.nodes[left]
            if minleft <= limit:
                curr = left
                continue
            curr = right
        return -1
 
