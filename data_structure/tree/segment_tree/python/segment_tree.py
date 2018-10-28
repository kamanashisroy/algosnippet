#!/bin/python3
# vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

'''
segment_tree.py file is part of Algosnippet.
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



class segment_tree:
    '''
    This segment tree implementation is implicit
    '''
    __slots__ = ["segment_array","order"]
    def __init__(self,order,max_size,defaultval=0):
        self.order = order
        self.segment_array = [defaultval]*max_size

    def _child(self,idx):
        return (idx<<self.order)+1

    def _parent(self,idx):
        return (idx-1)>>self.order


    def update_min(self, idx, xval):
        while True:
            if xval < self.segment_array[idx]:
                self.segment_array[idx] = xval
            else:
                break # no more updates needed
            if 0 == idx:
                break # we reached the root
            idx = self._parent(idx)

    def query_min(self, start_idx, end_idx):
        # very tricky
        pass

    def update_sum(self, idx, xval):
        while True:
            self.segment_array[idx] += xval
            if 0 == idx:
                break # we reached the root
            idx = self._parent(idx)

    def query_sum(self, idx):
        pass
            
    def __repr__(self):
        return "[Segment-tree(" + str(self.segment_array) + ")]"

    def __str__(self):
        return "[Segment-tree(" + str(self.segment_array) + ")]"

if __name__ == "__main__":
    data = [1,3,4,8,6,1,4,2]
    print("Making Segment tree for", data)
    stree = segment_tree(1,len(data),0)
    for i,x in enumerate(data):
        stree.update_sum(i,x)
        print(stree)

    #assert(stree.query_sum(0) == 1)
    #assert(stree.query_sum(1) == 4)
    #assert(stree.query_sum(2) == 8)
    #assert(stree.query_sum(3) == 16)
    #assert(stree.query_sum(4) == 22)
    #assert(stree.query_sum(5) == 23)
    #assert(stree.query_sum(6) == 27)
    #assert(stree.query_sum(7) == 29)

    print("successful")
