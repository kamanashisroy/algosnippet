#!/bin/python3
# vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

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
    tmp = x
    x = y
    y = tmp

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
    tmp = x
    x = y
    y = tmp

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
    tmp = z
    z = y
    y = tmp

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
    tmp = z
    z = y
    y = tmp

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


class avl_tree(algo_tree.algo_tree):
    '''
    AVL tree is self balancing binary tree
    '''
    def __init__(self,x=None,parent=None):
        algo_tree.algo_tree.__init__(self,x,parent)

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
        
    def avl_balance(self):

        if(self.parent is None):
            #print("No parent:" + repr(self))
            # No balancing for root node
            return

        self.needs_balancing = False
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
                upgrade_x_left(self,self.parent)

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
                upgrade_z_left(self,self.parent,self.right)


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
                # TODO diagram
                upgrade_x_right(self,self.parent)
            elif right_bfactor > 0:
                # middle heavy
                # TODO diagram
                upgrade_z_right(self,self.parent,self.left)

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

    def insert(self,x,duplicate=True,new_avl_tree = None):

        #print("Inserting {x} in avl-tree".format(x=str(x)))
        if(new_avl_tree is None):
            new_avl_tree = avl_tree(x)

        # insert
        result_node = algo_tree.algo_tree.insert(self,x,duplicate,new_avl_tree)
        if result_node is None:
            # when the insertion fails
            return result_node

        #print("Inserted {x} in avl-tree --- backtracking at {y}".format(x=repr(result_node),y=repr(self)))
        if(result_node == new_avl_tree):
            #print("balancing avl-tree for {node}".format(node=repr(self)))
            # We really added a new node
            self.avl_balance()

        return result_node


if __name__ == "__main__":
    tree = avl_tree()
    tree.insert(5)
    tree.insert(3)
    tree.insert(6)
    print(str(tree))
    print("==========================")
    for i in range(10):
        tree.insert(i)

    print(str(tree))
    print("==========================")
    # try wikipedia example
    tree = avl_tree()
    tree.insert('M')
    tree.insert('N')
    print(str(tree))
    print("==========================")
    tree.insert('O')
    print(str(tree))
    print("==========================")
    tree.insert('L')
    print(str(tree))
    print("==========================")
    tree.insert('K')
    print(str(tree))
    print("==========================")
    tree.insert('Q')
    print(str(tree))
    print("==========================")
    tree.insert('P')
    print(str(tree))
    print("==========================")
    tree.insert('H')
    print(str(tree))
    print("==========================")
    tree.insert('I')
    print(str(tree))
    print("==========================")
    tree.insert('A')
    print(str(tree))
    print("==========================")

