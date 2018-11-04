#!/bin/python3
# vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

'''
avl_tree.py file is part of Algosnippet.
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


import algo_tree

def upgrade_x_left(x,y):
    #print("Doing upgrade_x_left")
    assert(y.left == x)
    # left heavy
    #                              < Y <
    #
    #                                     |\
    #                   < X <             | \
    #                /|       |\          |  \
    #               / |       |M\         | R \
    #              /  |       ----        |    \
    #             / L |                   -------
    #            /    |
    #           -------
    # right rotate
    #                   < X < 
    #                /|            < Y <
    #               / |          /|       |\
    #              /  |         /M|       | \
    #             / L |        ----       |  \
    #            /    |                   | R \
    #           -------                   |    \
    #                                     -------

    middle = x.right

    # swap
    x.swap(y)
    x,y = y,x

    # fixup y
    y.left = middle
    if(middle is not None):
        middle.parent = y
    y.height -= 1
    
    # fixup x
    x.right = y
    y.parent = x

    # fix height
    y.height -= 1
    y.fix_height()
    
    # fix subtree-size
    y.fix_subtree_size()
    x.fix_subtree_size()

def upgrade_x_right(x,y):
    #print("Doing upgrade_x_right")
    assert(y.right == x)
    # right heavy
    #                   < Y <
    #                /|          < X <    
    #               / |        /|      |\
    #              /  |       / |      | \
    #             / L |      /  |      |  \
    #            ------     / M |      | R \
    #                      ------      |    \
    #                                  -------
    # left rotate
    #                            < X <
    #                   < Y <          |\ 
    #                /|      |\        | \
    #               / |      | \       |  \
    #              /  |      |  \      |   \
    #             / L |      | M \     | R  \
    #            ------      ------    -------
    #

    middle = x.left

    # swap
    x.swap(y)
    x,y = y,x

    # fixup y
    y.right = middle
    if(middle is not None):
        middle.parent = y
    
    # fixup x
    x.left = y
    y.parent = x

    # fix height
    y.height -= 1
    y.fix_height()
    
    # fix subtree-size
    y.fix_subtree_size()
    x.fix_subtree_size()

def upgrade_z_left(x,y,z):
    assert(x.right == z)
    assert(y.left == x)
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
    middle_left = z.left
    middle_right = z.right
    right = y.right

    # swap
    z.swap(y)
    z,y = y,z

    # fix z
    z.left = x
    x.parent = z
    z.right = y
    y.parent = z

    # fix x
    x.right = middle_left
    if middle_left is not None:
        middle_left.parent = x

    # fix y
    y.left = middle_right
    if middle_right is not None:
        middle_right.parent = y

    # fix height
    x.height -= 1
    y.height -= 1
    y.fix_height()
    
    # fix subtree-size
    x.fix_subtree_size()
    y.fix_subtree_size()
    z.fix_subtree_size()

def upgrade_z_right(x,y,z):
    assert(x.left == z)
    assert(y.right == x)
    # middle heavy
    #                   < Y <                         
    #                                           < X < 
    #                /|              < z <            |\
    #               /L|           /|      |\          |R\
    #              ----          / |      | \         ----
    #                           /  |      |  \
    #                          /ML |      | MR\
    #                         ------      ------
    #                                
    # rotate left and then right, swap Z and Y
    #                                 
    #                                < Z <
    #                   < Y <                    < X <  
    #                /|       |\             /|       |\
    #               /L|       | \           / |       | \
    #              ----       |  \         /  |       |  \
    #                         |ML \       / MR|       | R \ 
    #                         ------     ------       ------
    middle_left = z.left
    middle_right = z.right
    right = y.right

    # swap
    z.swap(y)
    y,z = z,y

    # fix z
    z.left = y
    y.parent = z
    z.right = x
    x.parent = z

    # fix x
    x.left = middle_right
    if middle_right is not None:
        middle_right.parent = x

    # fix y
    y.right = middle_left
    if middle_left is not None:
        middle_left.parent = y

    # fix height
    x.height -= 1
    y.height -= 1
    y.fix_height()
    
    # fix subtree-size
    x.fix_subtree_size()
    y.fix_subtree_size()
    z.fix_subtree_size()


class avl_tree(algo_tree.algo_tree):
    '''
    AVL tree is self balancing binary tree
    '''
    def __init__(self,x=None,parent=None):
        algo_tree.algo_tree.__init__(self,x,parent)


    @classmethod
    def from_sorted_unique_array(cls,parent,sorted_array,start,end):
        '''
        build avl tree from sorted data.
        NOTE it can not handle duplicate data

        Parameters:
            start   start index of the sorted array
            end     end index(not included) of the sorted array
        '''
        mid = (start+end)>>1
        x = sorted_array[mid]
        self = avl_tree(x,parent)
        left_height = 0
        right_height = 0
        if start != mid:
            self.left = avl_tree.from_sorted_unique_array(self,sorted_array,start,mid)
            self.subtree_size += self.left.subtree_size
            left_height = self.left.height
        if (mid+1) != end:
            self.right = avl_tree.from_sorted_unique_array(self,sorted_array,mid+1,end)
            self.subtree_size += self.right.subtree_size
            right_height = self.right.height
        self.height = max(left_height,right_height)
        return self
 

    def balancing_factor(self):
        bfactor = 0
        if self.left is None:
            bfactor = -1
        else:
            bfactor = self.left.height
        if self.right is None:
            bfactor += 1
        else:
            bfactor -= self.right.height
        return bfactor
        
    def avl_balance(self, added_node):
        '''
        Parameters:
            added_node The node containing the new value, it may not be the real
                       added-node. It can be some other swapped node
            return The node containing the added value.
        '''


        data = None
        if added_node is not None:
            data = added_node.root

        if self.parent is None:
            #print("No parent:" + repr(self))
            # No balancing for root node
            return added_node

        # calculate the balance factor
        bfactor = self.parent.balancing_factor()
        #print("balancing factor of parent {parent} is {bf}".format(parent=repr(self.parent),bf=bfactor))

        if self == self.parent.left and bfactor > 1:
            # When insertion
            # left heavy
            #                 X < Y <
            #                /|       |\
            #               / |       |R\
            #              /  |       ----
            #             / L |
            #            /    |
            #           -------

            left_bfactor = self.balancing_factor()
            if left_bfactor > 0:
                # left heavy
                #                              < Y <
                #
                #                                     |\
                #                   < X <             | \
                #                /|       |\          |  \
                #               / |       |M\         | R \
                #              /  |       ----        |    \
                #             / L |                   -------
                #            /    |
                #           -------
                # right rotate
                #                   < X < 
                #                /|            < Y <
                #               / |          /|       |\
                #              /  |         /M|       | \
                #             / L |        ----       |  \
                #            /    |                   | R \
                #           -------                   |    \
                #                                     -------
                if added_node == self:
                    added_node = self.parent # it swaps the value with parent

                upgrade_x_left(self,self.parent)
                assert(added_node.root == data)

            elif left_bfactor < 0:
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
                if added_node == self.right:
                    added_node = self.parent # it swaps the value with parent

                upgrade_z_left(self,self.parent,self.right)
                assert(added_node.root == data)


        elif self == self.parent.right and bfactor < -1:
            # when insertion
            # right heavy
            #                   < Y < X
            #                /|       |\
            #               /L|       | \
            #              ----       |  \ 
            #                         | R \
            #                         |    \
            #                         -------
            right_bfactor = self.balancing_factor()
            if right_bfactor < 0:
                # right heavy
                # (Y.bfactor < -1)   < Y < 
                #                /|            < X < (X.bfactor < 0)
                #               / |          /|       |\
                #              /  |         /M|       | \
                #             / L |        ----       |  \
                #            ------                   | R \
                #                                     |    \
                #                                     -------
                # left rotate (upgrade right)
                #                              < X <
                #                   < Y <             |\
                #                /|       |\          | \
                #               / |       |M\         |  \
                #              /  |       ----        |   \
                #             / L |                   |  R \
                #            /    |                   |     \
                #           -------                   --------
                if added_node == self:
                    added_node = self.parent # it swaps the value with parent

                upgrade_x_right(self,self.parent)
                assert(added_node.root == data)
            elif right_bfactor > 0:
                # middle heavy
                # TODO diagram
                if added_node == self.left:
                    added_node = self.parent # it swaps the value with parent

                upgrade_z_right(self,self.parent,self.left)
                assert(added_node.root == data)

        elif self == self.parent.left and bfactor < -1:
            # when deletion
            # right heavy
            #                 X < Y <
            #                /|       |\
            #               /L|       | \
            #              ----       |  \ 
            #                         | R \
            #                         |    \
            #                         -------
            # TODO implement
            pass

        elif self == self.parent.right and bfactor > 1:
            # when deletion
            # left heavy
            #                   < Y < X
            #                /|       |\
            #               / |       |R\
            #              /  |       ----
            #             / L |
            #            /    |
            #           -------
            # TODO implement
            pass
        return added_node

    def insert_recursive(self,x,maintain_dup_list=True,new_avl_tree = None):

        #print("Inserting {x} in avl-tree".format(x=str(x)))
        if(new_avl_tree is None):
            new_avl_tree = avl_tree(x)

        # insert
        result_node,is_duplicate = algo_tree.algo_tree.insert_recursive(self,x,maintain_dup_list,new_avl_tree)
        if result_node is None:
            # when the insertion fails
            return result_node,is_duplicate

        #print("Inserted {x} in avl-tree --- backtracking at {y}".format(x=repr(result_node),y=repr(self)))
        if not is_duplicate:
            #print("balancing avl-tree for {node}".format(node=repr(self)))
            # We really added a new node
            result_node = self.avl_balance(result_node)
            assert(result_node.root == x)

        return result_node,is_duplicate

    def _insert_non_recursive(self,x,maintain_dup_list=True,new_node=None):
        if new_node is None:
            new_node = avl_tree(x)
        
        return algo_tree.algo_tree._insert_non_recursive(self,x,maintain_dup_list,new_node)
        
    def insert_non_recursive_after(self, added_node):
        self.fix_height() # this is recursive
        added_node = self.avl_balance(added_node)
        return algo_tree.algo_tree.insert_non_recursive_after(self,added_node)





if __name__ == "__main__":
    tree = avl_tree()
    tree.insert_non_recursive(5)
    tree.insert_non_recursive(3)
    tree.insert_non_recursive(6)
    print(str(tree))
    print("==========================")
    for i in range(10):
        tree.insert_non_recursive(i)

    print(str(tree))
    print("==========================")
    # try wikipedia example
    tree = avl_tree()
    tree.insert_non_recursive('M')
    tree.insert_non_recursive('N')
    print(str(tree))
    print("==========================")
    tree.insert_non_recursive('O')
    print(str(tree))
    print("==========================")
    tree.insert_non_recursive('L')
    print(str(tree))
    print("==========================")
    tree.insert_non_recursive('K')
    print(str(tree))
    print("==========================")
    tree.insert_non_recursive('Q')
    print(str(tree))
    print("==========================")
    tree.insert_non_recursive('P')
    print(str(tree))
    print("==========================")
    tree.insert_non_recursive('H')
    print(str(tree))
    print("==========================")
    tree.insert_non_recursive('I')
    print(str(tree))
    print("==========================")
    tree.insert_non_recursive('A')
    print(str(tree))
    print("==========================")

