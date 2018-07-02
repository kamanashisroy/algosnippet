#!/bin/python3
# vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

import math
import os
import random
import re
import sys
import collections

class kary_heap:
    '''
    If the order is 1 then it is binary heap.
    If the order is 2 then the tree node has at most 4 children.
    If the order is 3 then the tree node has at most 8 children.
    '''
    def __init__(self,order):
        self.order = order
        self.shifter = (1 << self.order) - 1
        self.heap = []

    def __len__(self):
        return len(self.heap)
    
    #def __getitem__(self,index):
    #    return self.heap[index]
    
    def empty(self):
        return False if len(self.heap) > 0 else True

    def peek(self):
        if self.empty():
            return None
        return self.heap[0]
    
    def append(self,x):
        # sanity check
        if x is None:
            return False
        
        self.heap.append(x)
        self.__up_heap(len(self.heap)-1)
        return True

    def popleft(self):
        # sanity check
        if len(self.heap) == 0:
            # in case heap is empty
            return None
        result = self.heap[0]
        if len(self.heap) == 1:
            self.heap.pop()
        else:
            # swap with last
            self.__swap(0,len(self.heap)-1)

            # delete last
            self.heap.pop()

            # fixup
            self.__down_heap(0)
        return result
    
    def __fix_heap(self,loc):
        assert(-1 != loc)
        assert(loc < len(self.heap))
        if 0 != loc:
            parent_index = ((loc+self.shifter)>>self.order)-1
            if self.heap[parent_index] > self.heap[loc]:
                self.__up_heap(loc)
                return
        self.__down_heap(loc)

    def mydown_heap(self):
        self.__down_heap(0)

    def __up_heap_range(self,loc):
        assert(loc < len(self.heap))
        index = loc
        parent_index = ((index+self.shifter)>>self.order)-1
        
        while index > 0:
            yield index,parent_index
            index = parent_index
            parent_index = ((index+self.shifter)>>self.order)-1
    
    def __up_heap(self,loc):
        assert (loc != -1)
        assert (loc < len(self.heap))
        for i,p in self.__up_heap_range(loc):
            if self.heap[i] > self.heap[p]:
                break # heap property holds true
            self.__swap(i,p)
                
    def __down_heap_range(self,loc):
        assert(-1 != loc)
        # allow bigger imaginary leaves assert(loc < len(self.heap))
        first = (loc<<self.order)+1
        return first,(first+self.shifter)
            
    def __swap(self,x,y):
        assert(-1 != x)
        assert(-1 != y)
        assert(x < len(self.heap))
        assert(y < len(self.heap))
        if x == y:
            return
        tmp = self.heap[x]
        self.heap[x] = self.heap[y]
        self.heap[y] = tmp
    
    def __down_heap(self,loc):
        cur_loc = loc
        first,last = self.__down_heap_range(cur_loc)
        while first < len(self.heap):
            smallest_loc = first
            for i in range(first,min(len(self.heap),last+1)):
                if self.heap[smallest_loc] > self.heap[i]:
                    smallest_loc = i
            
            # check if heap property holds
            if self.heap[cur_loc] < self.heap[smallest_loc]:
                break # heap property is asserted

            # swap
            self.__swap(cur_loc,smallest_loc)
            cur_loc = smallest_loc
            first,last = self.__down_heap_range(cur_loc)

    def verify_heap(self):
        for loc in range(1,len(self.heap)):
            parent_index = ((loc+self.shifter)>>self.order)-1
            assert self.heap[loc] > self.heap[parent_index] ,str((loc,parent_index,str(self.heap)))


