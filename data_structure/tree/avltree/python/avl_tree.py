#!python

'''
avl_tree.py file is part of Algosnippet.
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

from typing import TypeVar,Generic

AVLTREENODET = TypeVar('AVLTREENODET')

class avl_tree(Generic[AVLTREENODET]):
    '''
    AVL tree is self balancing binary tree
    '''
    __slots__ = ['root']
    def __init__(self, root:AVLTREENODET=None):
        self.root = root

    def insert(self, node:AVLTREENODET):
        top:AVLTREENODET = self.root
        if top is None:
            self.root = node
            return

        assert(top)
        assert(not top.parent)

        while top:
            if node.val == top.val:
                top.dup.append(node)
                break
            elif node.val < top.val:
                if top.left is None:
                    top.left = node
                    node.parent = top
                    break
                else:
                    top = top.left
            else:
                if top.right is None:
                    top.right = node
                    node.parent = top
                    break
                else:
                    top = top.right

        root:AVLTREENODET = top
        while top:
            top = avl_tree.balance(top)
            assert(top)
            root = top
            top = top.parent
            
        assert(root)
        assert(not root.parent)

        self.root = root # update root

            
    @staticmethod
    def balancing_factor(x:AVLTREENODET) -> int:
        rheight = -1 if x.right is None else x.right.height
        lheight = -1 if x.left is None else x.left.height
        return lheight - rheight
        
    @staticmethod
    def balance(node:AVLTREENODET) -> AVLTREENODET:
        '''
        Parameters:
            added_node The node containing the new value, it may not be the real
                       added-node. It can be some other swapped node
            return The node containing the added value.
        '''
        # calculate the balance factor
        bfactor = avl_tree.balancing_factor(node)
        #print("balancing factor of {node} is {bf}".format(node=repr(node),bf=bfactor))

        if bfactor >= -1 and bfactor <= 1:
            node.augment()
            return node # no balancing needed

        if bfactor > 0:
            # When insertion
            # left heavy
            #                 X < Y <
            #                /|       |\
            #               / |       |R\
            #              /  |       ----
            #             / L |
            #            /    |
            #           -------

            left = node.left
            assert(left is not None)
            left_bfactor = avl_tree.balancing_factor(left)
            if left_bfactor < 0:
                # middle heavy
                #                                           < Y <
                #                   < X <                         |\
                #                /|              < z <            | \
                #               /L|           /|      |\          |  \
                #              ----          / |      | \         | R \
                #                           /  |      |  \        |    \
                #                          /ML |      | MR\       -------
                #                         ------      ------
                #                                
                # rotate left and then right, swap Z and Y
                #                                 
                #                                < Z <
                #                   < X <                    < Y <  
                #                /|       |\             /|       |\
                #               /L|       | \           / |       | \
                #              ----       |  \         /  |       |  \
                #                         |ML \       / MR|       | R \ 
                #                         ------     ------       ------
                
                avl_tree.rotate_left(left)
            return avl_tree.rotate_right(node)
        else:
            # when insertion
            # right heavy
            #                   < Y < X
            #                /|       |\
            #               /L|       | \
            #              ----       |  \ 
            #                         | R \
            #                         |    \
            #                         -------
            right = node.right
            right_bfactor = avl_tree.balancing_factor(right)
            if right_bfactor > 0:
                # middle heavy
                # TODO diagram
                avl_tree.rotate_right(right)

            return avl_tree.rotate_left(node)
        return node

    @staticmethod
    def rotate_left(node:AVLTREENODET) -> AVLTREENODET:
        # right heavy
        #                   < Y < X
        #                /|       |\
        #               /L|       | \
        #              ----       |  \ 
        #                         | R \
        #                         |    \
        #                         -------
        head = node.right
        assert(head is not None)
        parent = node.parent
        middle = head.left

        node.right,head.left,head.parent,node.parent = middle,node,parent,head

        # fixup parent
        if parent:
            if node == parent.right:
                parent.right = head
            else:
                parent.left = head

        # fixup middle
        if middle:
            middle.parent = node

        node.augment()
        head.augment()
        #print('rotate left', repr(head))
        return head

    @staticmethod
    def rotate_right(node:AVLTREENODET) -> AVLTREENODET:
        # left heavy
        #                 X < Y <
        #                /|       |\
        #               / |       |R\
        #              /  |       ----
        #             / L |
        #            /    |
        #           -------
        head:AVLTREENODET = node.left
        assert(head)
        middle:AVLTREENODET = head.right
        parent:AVLTREENODET = node.parent

        node.left,head.right,head.parent,node.parent  = middle,node,parent,head

        # fixup parent
        if parent:
            if node == parent.right:
                parent.right = head
            else:
                parent.left = head
        # fixup middle
        if middle:
            middle.parent = node

        node.augment()
        head.augment()
        #print('rotate right', repr(head))
        return head


    def count_smaller(self, x) -> int:
        top:AVLTREENODET = self.root
        if top is None:
            return 0

        count = 0
        while top:
            if x < top.val:
                if top.left is None:
                    break
                else:
                    top = top.left
            else:
                if top.val < x:
                    count += len(top.dup)+1
                if top.left:
                    count += top.left.subtree
                if top.right is None:
                    break
                else:
                    top = top.right
        return count



ALGOTREENODE = TypeVar('ALGOTREENODE')

class algo_tree(Generic[ALGOTREENODE]):
    '''
              < X < 
           /|       |\
          / |       | \
         /  |       |  \
        / L |       | R \
       ------       ------

    Attributes:
        left        Left child
        right       Right child
        parent      Parent node
        height      Height of the tree
        subtree     number of nodes in the subtree
        dup         nodes with equal value
        
    '''
    # XXX subtree_size does not count duplicates
    __slots__ = ["left","right","parent", "val","height","subtree","dup"]
    def __init__(self,x:ALGOTREENODE):
        self.left = None
        self.right = None
        self.parent = None
        self.val = x
        self.dup = []
        self.height = 0
        self.subtree = 1 # subtree size is always > 1

    def augment(self):
        height,subtree = 0,1+len(self.dup)
        left,right = self.left,self.right
        if left:
            height = left.height+1
            subtree += left.subtree
        if right:
            height = max(height,right.height+1)
            subtree += right.subtree
        
        self.height,self.subtree = height,subtree

    '''
    Emulating Container
    '''
    def __len__(self) -> int:
        return self.subtree

    def __getitem__(self, idx) -> ALGOTREENODE:
        '''
        Return:
            algo_tree: the node with idx-th rank
        '''
        pass


    def __contains__(self,x) -> bool:
        return self.find(x) is not None

    def __iter__(self) -> None:
        '''
        Traverse inorder
        '''
        if self.left:
            for node in self.left:
                yield node
        yield self
        if self.right:
            for node in self.right:
                yield node

    '''
    Emulating neumeric types
    '''

    def __lshift__(self,other):
        return self.left

    def __rshift__(self,other):
        return self.right

    def __str__(self,depth:int=0) -> str:
        ret = ""
        if(self.left is None):
            ret += "\t"*(depth+2)+"None\n"
        else:
            ret += self.left.__str__(depth+1)
        ret += "\t"*(depth+1)+str(self.height)+','+str(self.val)+','+str(self.subtree)+"\n"
        if(self.right is None):
            ret += "\t"*(depth+2)+"None\n"
        else:
            ret += self.right.__str__(depth+1)
        return ret

    def __repr__(self) -> str:
        return '<algo_tree:val={val},left={left},right={right},parent={parent}>'.format(val=str(self.val),left=id(self.left),right=id(self.right),parent=id(self.parent))

    def assert_invariant(self):
        last = None
        for x in self:
            if last is not None:
                assert(x >= last)
            last = x


if __name__ == "__main__":
    tree = avl_tree()
    nums = [4,3,2,1,5,3]
    for x in nums:
        print(tree.count_smaller(x))
        node = algo_tree(x)
        tree.insert(node)

    print(tree.root)
            
