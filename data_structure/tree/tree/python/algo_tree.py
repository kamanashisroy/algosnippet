#!/bin/python3
# vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

'''
algo_tree.py file is part of Algosnippet.
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

class algo_tree:
    '''
              < X < 
           /|       |\
          / |       | \
         /  |       |  \
        / L |       | R \
       ------       ------

    Attributes:
        root        Root of the tree
        left        Left child
        right       Right child
        parent      Parent node
        dup_list    The elements that are compared equal to root
        height      Height of the tree
        
    '''
    # XXX subtree_size does not count duplicates
    __slots__ = ["root","left","right","parent","dup_list","height","subtree_size"]
    def __init__(self,x=None,parent=None):
        self.root = x
        self.left = None
        self.right = None
        self.parent = parent
        self.dup_list = []
        self.height = 0
        self.subtree_size = 1 # subtree size is always > 1
    
    def insert_neighbor_non_recursive(self,x,maintain_dup_list=True,new_node=None):
        node = self
        while True:
            if node.parent is None:
                return node._insert_non_recursive(x,maintain_dup_list,new_node)
            else:
                if node.root == x:
                    return node._insert_non_recursive(x, maintain_dup_list,new_node)
                elif node.root < x:
                    # we should add x to the right
                    # check if we are left subtree
                    if node == node.parent.left:
                        if x < node.parent.root:
                            # node.root < x < node.parent.left
                            # the insertion have to be in the right-subtree
                            return node._insert_non_recursive(x, maintain_dup_list,new_node)
                        else:
                            node = node.parent
                            continue
                    else: # when we are right subtree
                        # node.parent.left < node.right < x
                        # return node._insert_non_recursive(x, maintain_dup_list,new_node)
                        node = node.parent
                        continue
                elif x < node.root:
                    # we should add x to the left
                    if node == node.parent.right:
                        # we are right child of parent
                        # that means we are greater than parent
                        if node.parent.root < x:
                            # node.parent.root < x < node.root
                            return node._insert_non_recursive(x, maintain_dup_list,new_node)
                        else:
                            node = node.parent
                            continue
                    else:
                        # we are left child of parent
                        # x < node.root < node.parent.root
                        # return node._insert_non_recursive(x, maintain_dup_list,new_node)
                        node = node.parent

    
    def insert_non_recursive(self,x,maintain_dup_list=True,new_node=None):
        assert(self.parent is None)
        return self._insert_non_recursive(x,maintain_dup_list,new_node)
        
    def _insert_non_recursive(self,x,maintain_dup_list=True,new_node=None):
        node = self
        if new_node is None:
            new_node = algo_tree(x)
            
        while True:
            if node.root is None:
                node.root = x
                return node,False

            if x == node.root:
                if maintain_dup_list:
                    node.dup_list.append(x)
                    return node,True
                return node,True
            
            if x < node.root:
                if node.left is None:
                    node.left = new_node
                    new_node.parent = node
                    break # done inserting
                else:
                    node = node.left
            else: # x > node.root
                if node.right is None:
                    # set as right node
                    node.right = new_node
                    new_node.parent = node
                    break # done inserting
                else:
                    node = node.right
        
        added_node = new_node
        node = new_node
        while node is not None:
            added_node = node.insert_non_recursive_after(added_node)
            node = node.parent
        return added_node,False
        
    def insert_recursive(self,x,maintain_dup_list=True,new_node = None):
        '''
            Insert an element in the binary-tree

            Params:
                x (obj): The value to insert
                maintain_dup_list (bool): Indicate if we should insert dup_list value
            Return:
                tuple(node,bool): (Inserted node(None when failed),bool indicating duplicate)
        '''

        if self.root is None:
            # when root is empty, set the root as x
            self.root = x
            return self,False

        if x == self.root:
            if maintain_dup_list:
                self.dup_list.append(x)
                return self,True
            return self,True
            
        elif(x < self.root):
            if self.left is None:
                # when the left is empty, set it as x
                if new_node is None:
                    new_node = algo_tree(x,self)
                else:
                    new_node.parent = self
                self.left = new_node
                self.insert_left_after(self.left,False)
                return self.left,False
            else:
                # cascade left
                result_node,is_duplicate = self.left.insert_recursive(x,maintain_dup_list,new_node)
                assert(is_duplicate or x == result_node.root)
                self.insert_left_after(result_node,is_duplicate)
                return result_node,is_duplicate
        elif(x > self.root):

            if(self.right is None):
                # when the right is empty set it as x
                if new_node is None:
                    new_node = algo_tree(x,self)
                else:
                    new_node.parent = self
                self.right = new_node
                self.insert_right_after(self.right,False)
                return self.right,False
            else:
                # cascade right
                result_node,is_duplicate = self.right.insert_recursive(x,maintain_dup_list,new_node)
                assert(is_duplicate or x == result_node.root)
                self.insert_right_after(result_node,is_duplicate)
                return result_node,is_duplicate

        raise AssertionError("Unreachable code:" + repr(x) + "<>" + repr(self.root))
        
        
    def insert_left_after(self, result_node, is_duplicate):
        '''
        after left-insert
        NOTE tree-rotation may cause the tree-augmentation to be rebuilt.
        '''
        self.fix_height()
        self.fix_subtree_size()
        if self.left is not None:
            assert(self.left.parent == self)
        if self.right is not None:
            assert(self.right.parent == self)
    
    def insert_right_after(self, result_node, is_duplicate):
        '''
        after left-insert
        NOTE tree-rotation may cause the tree-augmentation to be rebuilt.
        '''
        self.fix_height()
        self.fix_subtree_size()
        if self.left is not None:
            # print(repr(self),repr(self.right))
            assert(self.left.parent == self)
        if self.right is not None:
            assert(self.right.parent == self)

    def insert_non_recursive_after(self, added_node):
        self.fix_height()
        self.fix_subtree_size()
        return added_node
    
    def swap(self,other):
        '''
        every value is swapped except the parent
        '''
        self.root,other.root = other.root,self.root
        self.left,other.left = other.left,self.left
        self.right,other.right = other.right,self.right
        self.dup_list,other.dup_list = other.dup_list,self.dup_list
        self.height,other.height = other.height,self.height
        self.subtree_size,other.subtree_size = other.subtree_size,self.subtree_size
        # fix pointers
        if self.right is not None:
            self.right.parent = self
        if other.right is not None:
            other.right.parent = other
        if self.left is not None:
            self.left.parent = self
        if other.left is not None:
            other.left.parent = other

    def fix_height(self):
        left_height = 0 if self.left is None else (self.left.height + 1)
        right_height = 0 if self.right is None else (self.right.height + 1)
        height = max(left_height,right_height)
        if self.height != height:
            # update
            self.height = height
            if self.parent is not None:
                self.parent.fix_height()
    
    def fix_subtree_size(self):
        self.subtree_size = 1
        if self.left is not None:
            self.subtree_size += self.left.subtree_size
        if self.right is not None:
            self.subtree_size += self.right.subtree_size

    def unlink_helper(self,replacement):
        if self.parent is None: # root has no parent
            # cannot unlink root
            self.root = None
            return

        if self == self.parent.right:
            # unlink right
            self.parent.right = replacement
        elif self == self.parent.left:
            # unlink left
            self.parent.left = replacement
        else:
            raise AssertionError("Unreachable code")

        parent = self.parent
        self.parent = None # unlink the parent(for safety)
        if replacement is not None:
            replacement.parent = parent
            replacement._fix_augmentation() # fix-height is recursive
            
        elif parent is not None:
            parent._fix_augmentation()

    def unlink(self):
        '''
        Unlink the tree from it's parent
        NOTE unlink is only possible if either the left or right is None
        '''
        if self.left is None:
            if self.right is None:
                # when both left and right is None
                self.unlink_helper(None)
            else:
                # when right subtree is available
                self.unlink_helper(self.right)
        elif self.right is None:
            # when right subtree is not avaialble
            if self.left is None:
                raise AssertionError("Unreachable code")
            else:
                # when left subtree is available
                self.unlink_helper(self.left)
        else:
            raise AssertionError("Cannot unlink an internal node when both left and right subree is not empty")
                    

    def delete(self,x):
        '''
            Delete the minimum value of the left tree or maximum value of the right tree and swap with target node.

                    X
               /|       |\
              / |       | \
             /  |       |  \
            / L |       | R \
           ------       ------

            To delete X, replace X with maxLeft() or minRight()

        Params:
            x obj: The value to be deleted

        Return:
            tuple(x,algo_tree): (x,node_containing_x)
        '''
        node = self.find(x)
        if node is None:
            # when the node is not found
            return None
        elif len(node.dup_list) > 0:
            # The node does not need to be deleted, it can be popped
            return (node.dup_list.pop(),node)
        elif node.right is None:
            # when there is no right tree
            if node.left is None:
                # when the node does not have a child
                node.unlink()
                return (x,node)
            else:
                # when there is left subtree

                # No right tree
                #
                #     predecessor   < X <
                #                /|       None
                #               / |
                #              /  |
                #             / L |
                #            /    |
                #           -------
                # replace node with predecessor
                predecessor = node.left
                node.swap(predecessor)
                predecessor.unlink()
                # node._fix_augmentation()
                return (x,predecessor)
        elif node.left is None:
            # when there is no left tree
            if node.right is None:
                raise AssertionError("Unreachable code")
            # Right heavy tree:

            #                   < X < Successor
            #             None        |\
            #                         | \
            #                         |  \ 
            #                         | R \
            #                         |    \
            #                         -------
            # swap node with successor
            successor = node.right
            node.swap(successor)
            successor.unlink()
            # node._fix_augmentation()
            return (x,successor)
        else:
            # check the height of left and right tree
            # and balance the tree while deletion
            if(node.left.height > node.right.height):

                # Left heavy tree:

                #     predecessor   < X <
                #                /|       |\
                #               / |       |R\
                #              /  |       ----
                #             / L |
                #            /    |
                #           -------

                # when the tree is left-heavy
                predecessor = node.left.max()
                predecessor.unlink()
                node.root = predecessor.root
                # node._fix_augmentation()
                return (x,predecessor)
            else:

                # Right heavy tree:

                #                   < X < Successor
                #                /|       |\
                #               /L|       | \
                #              ----       |  \ 
                #                         | R \
                #                         |    \
                #                         -------
                # when the tree is right-heavy or balanced
                successor = node.right.min()
                successor.unlink()
                node.root = successor.root
                return (x,successor)
        raise AssertionError("Unreachable code")

    def _fix_augmentation(self):
        self.fix_height()
        self.fix_subtree_size()

    def max(self):
        '''
        TODO make a non-recursive API
        '''
        result = self
        if self.root is None:
            return result
        elif self.right is None:
            return result
        else:
            return self.right.max()
        

    def min(self):
        '''
        TODO make a non-recursive API
        '''
        result = self
        if self.root is None:
            return result
        elif self.left is None:
            return result
        else:
            return self.left.min()

    def find(self,x):
        '''
        Find the Node containing the value x
        Params:
            x (obj): The target value to delete

        Return:
            algo_tree: the node that has `x` value as root
        '''
        if(self.root is None):
            # when tree is empty
            return None
        elif(x == self.root):
            # found
            return self
        elif(x < self.root):
            # when the element is in the left subtree
            if(self.left is None):
                # not found
                return None
            else:
                assert(self.left.parent == self)
                # cascade left
                return self.left.find(x)
        else:
            # when the element is in right subtree
            if(self.right is None):
                # not found
                return None
            else:
                assert(self.right.parent == self)
                # cascade right
                return self.right.find(x)

    def traverse(self,order=1):
        '''
        Traverse the tree in generator pattern.

        Params:
            order (int): 0 = preorder,1 = inorder, 2 = postorder, 3 = both preorder and postorder
        '''

        if 1 == order:
            # when inorder
            if self.left is not None:
                assert(self.left.parent == self);
                self.left.traverse(order)

        if 2 != order:
            # when NOT postorder
            yield self


        if 1 != order:
            # when preorder
            if self.left is not None:
                assert(self.left.parent == self);
                self.left.traverse(order)

        if self.right is not None:
            assert self.right.parent == self, str([repr(self), repr(self.right), repr(self.right.parent)])
            self.right.traverse(order)

        if 2 == order or 3 == order:
            # when postorder
            yield self


    '''
    Emulating types
    '''
    def __bool__(self):
        return False if self.root is None else True

    '''
    Emulating Container
    '''

    def __len__(self):
        pass # TODO

    def __delitem__(self,x):
        '''
        Delete the node containing the value `x`

        Params:
            x (obj): The target value to delete

        Return:
            algo_tree: the node that has `x` value as root
        '''
        return self.delete(x)

    def __getitem__(self,x):
        '''
        Return:
            algo_tree: the node that has `x` value as root
        '''
        return self.find(x)


    def __contains__(self,x):
        return self.find(x) is not None

    def __iter__(self):
        '''
        Traverse inorder
        '''
        for node in self.traverse():
            yield node.root
            for x in node.dup_list:
                yield x

    '''
    Emulating neumeric types
    '''

    def __lshift__(self,other):
        return self.left

    def __rshift__(self,other):
        return self.right

    def __str__(self,depth=0):
        ret = ""
        if(self.left is None):
            ret += "\t"*(depth+2)+"None\n"
        else:
            ret += self.left.__str__(depth+1)
        ret += "\t"*(depth+1)+str(self.height)+','+str(self.root)+','+str(self.subtree_size)+"\n"
        if(self.right is None):
            ret += "\t"*(depth+2)+"None\n"
        else:
            ret += self.right.__str__(depth+1)
        return ret

    def __repr__(self):
        return '<algo_tree:root={root},left={left},right={right},parent={parent}>'.format(root=str(self.root),left=id(self.left),right=id(self.right),parent=id(self.parent))

    def assert_invariant(self):
        last = None
        for x in self.traverse():
            if last is not None:
                assert(x >= last)
            last = x

if __name__ == "__main__":
    tree = algo_tree()
    tree.insert_recursive(4)
    tree.assert_invariant()
    tree.insert_recursive(3)
    tree.assert_invariant()
    tree.insert_non_recursive(5)
    tree.assert_invariant()
    tree.insert_recursive(6)
    tree.assert_invariant()
    tree.traverse() # it checks the health
    print(str(tree))
    print("==================================")
    tree.delete(4)
    print(str(tree))
    tree.assert_invariant()
    print("==================================")
    tree.traverse() # it checks the health
    tree.insert_recursive(10)
    tree.assert_invariant()
    tree.delete(11)
    tree.assert_invariant()
    tree.insert_non_recursive(9)
    tree.assert_invariant()
    tree.insert_recursive(7)
    tree.insert_non_recursive(4)
    tree.assert_invariant()
    print(str(tree))
    print("==================================")
    tree.delete(10)
    print(str(tree))
    print("==================================")
    

