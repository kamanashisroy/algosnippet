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
    __slots__ = ["segment_array","order","num_internal_nodes"]
    def __init__(self,order,num_leaves,defaultval=0):

        # this is necessary, because when there is no leaves, there is no tree
        #assert(num_leaves > 0)

        self.order = order
        # the tree size = (number of internal nodes) + (number of leaf nodes)
        #               = Sum_of_power(number_of_branches,num_levels)
        # when binary tree,
        # the tree size = 2^0 + 2^1 + 2^2 ... + 2^num_levels       .. eq(1)
        # 2*tree_size   = 2*(2^0 + 2^1 + 2^2 ... + 2^num_levels)
        #               = 2^1 + 2^2 + 2^3 .... + 2^(num_levels+1)  .. eq(2)
        # tree size     = 2^(num_levels+1) - 2^0                   .. eq(2) - eq(1)
        #               = 2^(num_levels+1) - 1
        #               = 2^(log(num_leaf)+1) - 1

        self.num_internal_nodes = 0
        x = 1
        while x < num_leaves:
            self.num_internal_nodes += x
            x <<= self.order

        self.segment_array = [defaultval]*(self.num_internal_nodes+num_leaves)

    def _child(self,idx):
        return (idx<<self.order)+1

    def _parent(self,idx):
        return (idx-1)>>self.order


    def update_min(self, idx, xval):

        # convert idx to leaf node
        idx += self.num_internal_nodes
        self.segment_array[idx] = xval

        # convert idx to internal nodes
        idx = self._parent(idx)

        while True:
            if xval < self.segment_array[idx]:
                self.segment_array[idx] = xval
            else:
                break # no more updates needed
            if 0 == idx:
                break # we reached the root
            idx = self._parent(idx)

    def query_min(self, start_idx, end_idx):
        # convert idx to internal nodes
        end_idx += self.num_internal_nodes
        start_idx += self.num_internal_nodes
        result = self.segment_array[start_idx]

        #print("query min", start_idx, end_idx)

        while start_idx < end_idx:
            left_parent_idx = self._parent(start_idx)
            right_parent_idx = self._parent(end_idx)

            # termination logic, when both end has single parent level-up stops
            if left_parent_idx == right_parent_idx:
                if start_idx == self._child(left_parent_idx) and end_idx == (self._child(right_parent_idx) + (1<<self.order) -1):
                    result = min(result, self.segment_array[left_parent_idx])
                else:
                    # both index have the same parent
                    for idx in range(start_idx,end_idx+1):
                        result = min(result, self.segment_array[idx])
                # end loop
                break

            if start_idx == self._child(left_parent_idx):
                #print("query min:left full parent", start_idx, left_parent_idx)
                # start-index is the fist child of it's parent
                result = min(result,self.segment_array[left_parent_idx])

                # go up
                start_idx = left_parent_idx
            else:
                #print("query min:left partial parent", start_idx, left_parent_idx)
                # loop through it
                for idx in range(start_idx,self._child(left_parent_idx) + (1<<self.order)):
                    result = min(result, self.segment_array[idx])

                start_idx = left_parent_idx+1

            if end_idx == (self._child(right_parent_idx) + (1<<self.order) -1):
                #print("query min:right full parent", end_idx, right_parent_idx)
                result = min(result,self.segment_array[right_parent_idx])
                end_idx = right_parent_idx
            else:
                #print("query min:right partial parent", end_idx, right_parent_idx)
                # loop through it
                for idx in range(self._child(right_parent_idx), end_idx+1):
                    result = min(result, self.segment_array[idx])
                end_idx = right_parent_idx-1


        #print(result)
        return result

    def update_sum(self, idx, xval):
        # convert idx to leaf node
        idx += self.num_internal_nodes
        self.segment_array[idx] = xval

        # convert to internal node
        idx = self._parent(idx)

        while True:
            self.segment_array[idx] += xval
            if 0 == idx:
                break # we reached the root
            idx = self._parent(idx)

    def query_sum(self, start_idx, end_idx):
        # convert idx to internal nodes
        end_idx += self.num_internal_nodes
        start_idx += self.num_internal_nodes
        result = 0

        #print("query sum", start_idx, end_idx)

        while start_idx <= end_idx:
            if start_idx == end_idx:
                result += self.segment_array[start_idx]
                break
            left_parent_idx = self._parent(start_idx)
            right_parent_idx = self._parent(end_idx)

            # termination logic, when both end has single parent level-up stops
            if left_parent_idx == right_parent_idx:
                if start_idx == self._child(left_parent_idx) and end_idx == (self._child(right_parent_idx) + (1<<self.order) -1):
                    result += self.segment_array[left_parent_idx]
                else:
                    # both index have the same parent
                    for idx in range(start_idx,end_idx+1):
                        result += self.segment_array[idx]
                # end loop
                break

            if start_idx == self._child(left_parent_idx):
                #print("query sum:left full parent", start_idx, left_parent_idx)
                # start-index is the fist child of it's parent
                result += self.segment_array[left_parent_idx]

                # go up
                start_idx = left_parent_idx+1
            else:
                #print("query sum:left partial parent", start_idx, left_parent_idx)
                # loop through it
                for idx in range(start_idx,self._child(left_parent_idx) + (1<<self.order)):
                    result += self.segment_array[idx]

                start_idx = left_parent_idx+1

            if end_idx == (self._child(right_parent_idx) + (1<<self.order) -1):
                #print("query sum:right full parent", end_idx, right_parent_idx)
                result += self.segment_array[right_parent_idx]
                end_idx = right_parent_idx-1
            else:
                #print("query sum:right partial parent", end_idx, right_parent_idx)
                # loop through it
                for idx in range(self._child(right_parent_idx), end_idx+1):
                    result += self.segment_array[idx]
                end_idx = right_parent_idx-1

        #print("query sum", start_idx, end_idx, result)

        return result

    def __repr__(self):
        return "[Segment-tree(" + str(self.segment_array) + ")]"

    def __str__(self):
        return "[Segment-tree(" + str(self.segment_array) + ")]"

if __name__ == "__main__":
    data = [1,3,4,8,6,1,4,2]
    print("Making Segment tree(1st order,sum) for", data)
    stree = segment_tree(1,len(data),0)
    for i,x in enumerate(data):
        stree.update_sum(i,x)
        print(stree)

    assert(stree.query_sum(0,0) == 1)
    assert(stree.query_sum(0,1) == 4)
    assert(stree.query_sum(0,2) == 8)
    assert(stree.query_sum(0,3) == 16)
    assert(stree.query_sum(0,4) == 22)
    assert(stree.query_sum(0,5) == 23)
    assert(stree.query_sum(0,6) == 27)
    assert(stree.query_sum(0,7) == 29)

    print("Making Segment tree(2nd order,sum) for", data)
    stree = segment_tree(2,len(data),0)
    for i,x in enumerate(data):
        stree.update_sum(i,x)
        print(stree)

    print("Making Segment tree(1st order,min) for", data)
    stree = segment_tree(1,len(data),max(data)+1)
    for i,x in enumerate(data):
        stree.update_min(i,x)
        print(stree)

    assert(stree.query_min(2,3) == 4)
    assert(stree.query_min(1,3) == 3)

    print("Making Segment tree(2nd order,min) for", data)
    stree = segment_tree(2,len(data),max(data)+1)
    for i,x in enumerate(data):
        stree.update_min(i,x)
        print(stree)

    print("successful")
