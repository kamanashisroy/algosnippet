#!/bin/python3
# vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4


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
        duplicate   The elements that are compared equal to root
        height      Height of the tree
        
    '''
    def __init__(self,x=None,parent=None):
        self.root = x
        self.left = None
        self.right = None
        self.parent = parent
        self.duplicate = []
        self.height = 0

    def insert(self,x,duplicate=True,new_node = None):
        '''
            Insert an element in the binary-tree

            Params:
                x (obj): The value to insert
                duplicate (bool): Indicate if we should insert duplicate value

            Return:
                tuple(int,node): the depth of the inserted element, -1 when failed
        '''

        if(self.root is None):
            # when root is empty, set the root as x
            self.root = x
            return self

        if(x == self.root):
            if(duplicate):
                self.duplicate.append(x)
                return self
            return None
            
        elif(x < self.root):
            if(self.left is None):
                # when the left is empty, set it as x
                if new_node is None:
                    new_node = algo_tree(x,self)
                else:
                    new_node.parent = self
                self.left = new_node
                if 1 > self.height:
                    self.height = 1
                return self.left
            else:
                # cascade left
                result_node = self.left.insert(x,duplicate,new_node)
                if self.left.height >= self.height:
                    self.height = self.left.height+1
                return result_node
        elif(x > self.root):

            if(self.right is None):
                # when the right is empty set it as x
                if new_node is None:
                    new_node = algo_tree(x,self)
                else:
                    new_node.parent = self
                self.right = new_node
                if 1 > self.height:
                    self.height = 1
                return self.right
            else:
                # cascade right
                result_node = self.right.insert(x,duplicate,new_node)
                if self.right.height >= self.height:
                    self.height = self.right.height+1
                return result_node

        raise AssertionError("Unreachable code:" + repr(x) + "<>" + repr(self.root))

    def swap(self,other):
        '''
        every value is swapped except the parent
        '''
        root = self.root
        left = self.left
        right = self.right
        duplicate = self.duplicate
        height = self.height
        self.root = other.root
        self.left = other.left
        self.right = other.right
        self.duplicate = other.duplicate
        self.height = other.height
        other.root = root
        other.left = left
        other.right = right
        other.duplicate = duplicate
        other.height = height
        

    def fix_height(self):
        left_height = 0 if self.left is None else (self.left.height + 1)
        right_height = 0 if self.right is None else (self.right.height + 1)
        height = max(left_height,right_height)
        if(self.height != height):
            self.height = height
        if(self.parent is not None):
            self.parent.fix_height()

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
        if parent is not None:
            parent.fix_height()

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
        elif len(node.duplicate) > 0:
            # The node does not need to be deleted, it can be popped
            return (node.duplicate.pop(),node)
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
                predecessor.unlink()
                node.swap(predecessor)
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
            successor.unlink()
            node.swap(successor)
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
                node.swap(predecessor)
                node.right = predecessor.right
                predecessor.right = None
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
                node.swap(successor)
                node.left = successor.left
                successor.left = None
                return (x,successor)
        raise AssertionError("Unreachable code")


    def max(self):
        result = self
        if self.root is None:
            return result
        elif self.right is None:
            return result
        else:
            return self.right.max()
        

    def min(self):
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
                # cascade left
                return self.left.find(x)
        else:
            # when the element is in right subtree
            if(self.right is None):
                # not found
                return None
            else:
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
                self.left.traverse(order)

        if 2 != order:
            # when NOT postorder
            yield self


        if 1 != order:
            # when preorder
            if self.left is not None:
                self.left.traverse(order)

        if self.right is not None:
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
            for x in node.duplicate:
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
        ret += "\t"*(depth+1)+str(self.height)+','+str(self.root)+"\n"
        if(self.right is None):
            ret += "\t"*(depth+2)+"None\n"
        else:
            ret += self.right.__str__(depth+1)
        return ret

    def __repr__(self):
        return '<algo_tree:root={root},left={left},right={right},parent={parent}>'.format(root=str(self.root),left=id(self.left),right=id(self.right),parent=id(self.parent))

if __name__ == "__main__":
    tree = algo_tree()
    tree.insert(4)
    tree.insert(3)
    tree.insert(5)
    tree.insert(6)
    print(str(tree))
    print("==================================")
    tree.delete(4)
    print(str(tree))
    print("==================================")
    tree.insert(10)
    tree.delete(11)
    tree.insert(9)
    tree.insert(7)
    tree.insert(4)
    print(str(tree))
    print("==================================")
    

