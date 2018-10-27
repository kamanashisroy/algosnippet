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


class kary_heap:
    '''
    If the order is 1 then it is binary heap.
    If the order is 2 then the tree node has at most 4 children.
    If the order is 3 then the tree node has at most 8 children.
    '''
    __slots__ = ["order","num_children","heap","location"]
    def __init__(self,order,maxnode = None):
        self.order = order
        self.num_children = (1 << self.order)
        self.heap = []
        
        # location is not important if we do not want to delete randomly
        #self.location = [None]*maxnode

    def __len__(self):
        return len(self.heap)

    def __bool__(self):
        return bool(self.heap)
    
    #def __getitem__(self,index):
    #    return self.heap[index]
    
    def empty(self):
        return not self.heap

    def peek(self):
        return self.heap[0] if self.heap else None
    
    def append(self,x):
        '''
        Parameters:
            x       An object that has __le__() defined
        '''
        # sanity check
        if x is None:
            return False
        
        self.heap.append(x)
        #self.location[x.idx] = len(self.heap)-1
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
            #self.location[self.heap[-1].idx] = None
            self.heap.pop()
        else:
            # swap with last
            self.heap[-1],self.heap[0] = self.heap[0],self.heap[-1]
            #self.location[self.heap[0].idx] = 0

            # delete last
            #self.location[self.heap[-1].idx] = None
            self.heap.pop()

            # fixup
            self.__down_heap(0)
        return result
    
    def __fix_heap(self,loc):
        assert(-1 != loc)
        assert(loc is not None)
        assert(loc < len(self.heap))
        if 0 != loc:
            parent_index = (loc-1)>>self.order
            if self.heap[loc] < self.heap[parent_index]:
                self.__up_heap(loc)
                return
        self.__down_heap(loc)

    #def mydown_heap(self):
    #    self.__down_heap(0)

    def __up_heap_range(self,loc):
        assert(loc < len(self.heap))
        index = loc
        
        while index > 0:
            parent_index = (index-1)>>self.order
            yield index,parent_index
            index = parent_index
    
    def __up_heap(self,loc):
        assert (loc != -1)
        assert (loc < len(self.heap))
        for i,p in self.__up_heap_range(loc):
            if self.heap[p] <= self.heap[i]:
                break # heap property holds true
            # swap
            self.heap[i],self.heap[p] = self.heap[p],self.heap[i]
            #self.location[self.heap[i].idx] = i
            #self.location[self.heap[p].idx] = p
                
    def __down_heap_range(self,loc):
        assert(-1 != loc)
        # allow bigger imaginary leaves assert(loc < len(self.heap))
        return (loc<<self.order)+1
            
    def __down_heap(self,loc):
        cur_loc = loc
        first = self.__down_heap_range(cur_loc)
        while first < len(self.heap):
            smallest_loc = first
            for i in range(first,min(len(self.heap),first+self.num_children)):
                if self.heap[i] < self.heap[smallest_loc]:
                    smallest_loc = i
            
            # check if heap property holds
            if self.heap[cur_loc] <= self.heap[smallest_loc]:
                break # heap property is asserted

            # swap
            self.heap[cur_loc],self.heap[smallest_loc] = self.heap[smallest_loc],self.heap[cur_loc]
            #self.location[self.heap[cur_loc].idx] = cur_loc
            #self.location[self.heap[smallest_loc].idx] = smallest_loc
            
            cur_loc = smallest_loc
            first = self.__down_heap_range(cur_loc)

    def verify_heap(self):
        for loc in range(1,len(self.heap)):
            parent_index = (loc-1)>>self.order
            assert self.heap[parent_index] <= self.heap[loc] ,str((loc,parent_index,str(self.heap)))
            #assert self.location[self.heap[loc].idx] == loc
            #assert self.location[self.heap[parent_index].idx] == parent_index


