#!/bin/python3
# vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

'''
binomial_heap.py file is part of Algosnippet.

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

from collections import defaultdict

debugBinomialHeap = False
class binomial_heap:
    '''
    It is a list of binomial tree of different order
    '''
    __slots__ = ["sub"]
    def __init__(self):
        self.sub = defaultdict(list)

    def __bool__(self):
        return bool(self.sub)

    def append(self,x):
        '''
        It creates a binomial tree and melds with existing same order tree.
        Complexity Theta(1) amortised.
        '''
        treeNode = binomial_tree(x)
        self.__append_binomial_tree(treeNode)
        return treeNode

    def __append_binomial_tree(self,xtree):
        self.sub[xtree.order].append(xtree)
        order = xtree.order
        # now find another binomial tree of same order and meld
        while True:
            if order in self.sub:
                tobe_joined = self.sub[order]
                if 1 == len(tobe_joined):
                    break # we are done
                else:
                    del self.sub[order]
                    result = tobe_joined[0].consume(tobe_joined[1])
                    self.sub[order+1].append(result)
                    order += 1
            else:
                break
       
        if debugBinomialHeap:
            for ordKey,tree in self.sub.items():
                if tree:
                    assert( 1 == len(tree) )
                    assert( ordKey == tree[0].order )


    def popleft(self):
        # find min in O(log n) time
        output = None
        for order,nodes in self.sub.items():
            if output is None:
                output = nodes[0]
            elif nodes[0].elem < output.elem:
                output = nodes[0]

        if output is None:
            return None

        del self.sub[output.order]

        # we have found a valid min
        x = output.left_child
        while x is not None:
            sibling,x.right_sibling = x.right_sibling,None
            self.__append_binomial_tree(x)
            x = sibling
        output.left_child = None
        return output.elem

    def __str__(self):
        ret = "binomial-heap\n"
        for order,nodes in self.sub.items():
            ret += str(nodes[0])
        ret += "--------------------\n"
        return ret

class binomial_tree:
    __slots__ = ["order", "elem", "left_child", "right_sibling"]
    def __init__(self, elem):
        self.order = 1
        self.elem = elem
        self.left_child = None
        self.right_sibling = None

    def consume(self,other):
        '''
        fuse/meld other with this heap

        Both of the heaps has to be of same order
        '''
        assert(self.order == other.order)
        assert(None == other.right_sibling)
        assert(None == self.right_sibling)
        if other.elem < self.elem:
            return other.consume(self)
    
        #old_order = self.order
        self.order += 1 # order is increased after meld
        
        self.left_child,other.right_sibling = other,self.left_child
        return self

    def __repr__(self):
        return "<binomial-order={order},{elem}>".format(order=self.order,elem=str(self.elem))

    def __str__(self, depth=0):
        ret = ""
        if(self.left_child is not None):
            ret += self.left_child.__str__(depth+1)
        ret += "\t"*(depth)+self.__repr__()+"\n"
        if(self.right_sibling is not None):
            ret += self.right_sibling.__str__(depth)
        return ret

    def increaseHeapProp(self, new_elem, updateTreeNode):
        assert(self.elem <= new_elem)
        old_elem = self.elem
        self.elem = new_elem
        # check all left-child
        
        smallest = self
        other = self.left_child
        while other is not None:
            if other.elem < smallest.elem: # we need to swap
                smallest = other
            other = other.right_sibling

        # now swap with smallest
        if smallest != self:
            smallest.elem,self.elem = self.elem,smallest.elem
            updateTreeNode(smallest.elem, smallest)
            updateTreeNode(self.elem, self)
            smallest.increaseHeapProp(smallest.elem, updateTreeNode)
            
 


if __name__ == '__main__':
    heap_key = [32,14,12,523,13,1,7,23,7,2,7,4,89,8,3,26,94]
    heap = binomial_heap()
    for x in heap_key:
        print("appending ",x)
        heap.append(x)
        print(str(heap))

    print(str(heap))

    st = []
    while heap:
        st.append(heap.popleft())
    print(st)
