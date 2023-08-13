#!/bin/python3
# vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

'''
kary_heap.py file is part of Algosnippet.

Algosnippet is a collection of practice data-structures and algorithms
Copyright (C) 2018  Kamanashis Roy

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

# Check this problem https://leetcode.com/contest/biweekly-contest-100/problems/find-score-of-an-array-after-marking-all-elements/

class kary_heap:
    '''
    Algosnippet is a collection of practice data-structures and algorithms
    Copyright (C) 2018  Kamanashis Roy

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

    If the order is 1 then it is binary heap.
    If the order is 2 then the tree node has at most 4 children.
    If the order is 3 then the tree node has at most 8 children.
    '''
    __slots__ = ["_ORDER","_NUM_CHILDREN","heap"]
    def __init__(self,order:int):
        self._ORDER = order
        self._NUM_CHILDREN = (1 << self._ORDER)
        self.heap = []
        
    def __len__(self):
        return len(self.heap)

    def __bool__(self) -> bool:
        return bool(self.heap)
    
    #def __getitem__(self,index):
    #    return self.heap[index]
    
    def empty(self) -> bool:
        return not self.heap

    def peek(self):
        return self.heap[0] if self.heap else None
    
    def append(self,x) -> bool:
        '''
        Parameters:
            x       An object that has __le__() defined
        '''
        # sanity check
        if x is None:
            return False
        
        self.heap.append(x)
        self.heap[-1].heap_loc = len(self.heap)-1
        self.__up_heap(len(self.heap)-1)
        return True

    def popleft(self):
        # sanity check
        if len(self.heap) == 0:
            # in case heap is empty
            return None
        result = self.heap[0]
        if len(self.heap) == 1:
            # delete last
            self.heap[-1].heap_loc = None
            self.heap.pop()
        else:
            # swap with last
            self.heap[-1],self.heap[0] = self.heap[0],self.heap[-1]
            self.heap[0].heap_loc = 0
            self.heap[-1].heap_loc = None

            # delete last
            self.heap.pop()

            # fixup
            self.__down_heap(0)
        return result
    
    def fixat(self,loc: int):
        '''
        This is useful after relaxation in dijkstra
        '''
        self.__fix_heap(loc)
    
    def __fix_heap(self, loc: int):
        assert(-1 != loc)
        assert(loc is not None)
        assert(loc < len(self.heap))
        if 0 != loc:
            parent_index = (loc-1)>>self._ORDER
            if self.heap[loc] < self.heap[parent_index]:
                self.__up_heap(loc)
                return
        self.__down_heap(loc)

    #def mydown_heap(self):
    #    self.__down_heap(0)

    def __up_heap_range(self,loc: int):
        assert(loc < len(self.heap))
        index = loc
        
        while index > 0:
            parent_index = (index-1)>>self._ORDER
            yield index,parent_index
            index = parent_index
    
    def __up_heap(self,loc : int):
        assert (loc != -1)
        assert (loc < len(self.heap))
        for i,p in self.__up_heap_range(loc):
            if self.heap[p] <= self.heap[i]:
                break # heap property holds true
            # swap
            self.heap[i],self.heap[p] = self.heap[p],self.heap[i]
            self.heap[i].heap_loc = i
            self.heap[p].heap_loc = p
                
    def __down_heap_range(self,loc: int) -> int:
        assert(-1 != loc)
        # allow bigger imaginary leaves assert(loc < len(self.heap))
        return (loc<<self._ORDER)+1
            
    def __down_heap(self,loc : int):
        cur_loc = loc
        first = self.__down_heap_range(cur_loc)
        while first < len(self.heap):
            smallest_loc = first
            for i in range(first,min(len(self.heap),first+self._NUM_CHILDREN)):
                if self.heap[i] < self.heap[smallest_loc]:
                    smallest_loc = i
            
            # check if heap property holds
            if self.heap[cur_loc] <= self.heap[smallest_loc]:
                break # heap property is asserted

            # swap
            self.heap[cur_loc],self.heap[smallest_loc] = self.heap[smallest_loc],self.heap[cur_loc]
            self.heap[cur_loc].heap_loc = cur_loc
            self.heap[smallest_loc].heap_loc = smallest_loc
            
            cur_loc = smallest_loc
            first = self.__down_heap_range(cur_loc)

    def verify_heap(self):
        for loc in range(1,len(self.heap)):
            parent_index = (loc-1)>>self._ORDER
            assert self.heap[parent_index] <= self.heap[loc] ,str((loc,parent_index,str(self.heap)))
            assert self.heap[loc].loc == loc

    def poploc(self, loc):
        if loc is None or loc >= len(self.heap):
            return None
        # swap with last
        result = self.heap[loc]
        if (len(self.heap)-1) == loc:
            # delete last
            self.heap[-1].heap_loc = None
            self.heap.pop()
        else:
            # swap with last
            self.heap[-1],self.heap[loc] = self.heap[loc],self.heap[-1]
            self.heap[loc].heap_loc = loc
            self.heap[-1].heap_loc = None

            # delete last
            self.heap.pop()

            # fixup
            
            self.fixat(loc)
        return result
    

class kary_node:
    __slots__ = ["score","pos","heap_loc"]
    def __init__(self,pos,score):
        self.score = score
        self.pos = pos
        self.heap_loc = 0
    
    def __lt__(self,other):
        return (self.score > other.score)

    def __le__(self,other):
        return (self.score >= other.score)

    def __repr__(self):
        return str(self.score)

