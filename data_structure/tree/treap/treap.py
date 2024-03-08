#!/bin/python3
# vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

import os
import collections

class Treap:
    def __init__(self,compare_key,heap_key,identifier,given_data):
        self.key = compare_key
        self.heap_key = heap_key
        self.data = given_data
        self.identifier = identifier
        self.left = None
        self.right = None
        self.parent = None
        self.num_nodes = 1 # number of nodes in the subtree

    def append_node(self,given_treap_node):
        '''
        return new root after adding the treap-node
        '''

        #############################################
        # check the HEAP PROPERTY
        if given_treap_node.heap_key < self.heap_key:
            # self goes under given_treap_node
            given_treap_node.append_node(self)
            return given_treap_node # new root
        # HEAP PROPERTY
        #############################################

        self.num_nodes += given_treap_node.num_nodes
        #############################################
        # check the BINARY SEARCH TREE PROPERTY
        #############################################
        if given_treap_node.key <= self.key:
            # keep the new node at left
            if self.left is None:
                self.left = given_treap_node
            else:
                self.left = self.left.append_node(given_treap_node)
            self.left.parent = self
        else: # when given_treap_node is BIGGER
            if self.right is None:
                self.right = given_treap_node
            else:
                self.right = self.right.append_node(given_treap_node)
            self.right.parent = self
        return self

    def __repr__(self):
        return str((self.key,self.heap_key,self.identifier))

    def __str__(self,heap_key=0):
        ret = ""
        if(self.left is None):
            ret += "\t"*(heap_key+2)+"None\n"
        else:
            ret += self.left.__str__(heap_key+1)
        ret += "\t"*(heap_key+1)+str((self.key,self.heap_key,self.identifier))+"\n"
        if(self.right is None):
            ret += "\t"*(heap_key+2)+"None\n"
        else:
            ret += self.right.__str__(heap_key+1)
        return ret

    def query(self,heap_key_limit,k=None):

        # Do inorder traversal
        result = []
        expanded = [False]*(self.num_nodes+1)
        stack = []
        current = self
        count = 0
        while current is not None:

            if current.left is None or (current.left.heap_key > heap_key_limit or expanded[current.left.identifier]):

                #print("expanding ", current.identifier, count, current.key)
                # expand current
                #################################
                count += 1
                result.append(current)
                if k is not None and k == count:
                    return result
                expanded[current.identifier] = True

                if current.right is not None and current.right.heap_key <= heap_key_limit:
                    #print("going right ", current.identifier, count)
                    current = current.right
                else:
                    current = None if len(stack) == 0 else stack.pop()
            else:
                stack.append(current)
                #print("going left ", current.identifier, count)
                current = current.left

        return result
       
if __name__ == '__main__':
    heap_key = [32,14,12,523,13,1,7,23,7,2,7,4,89,8,3,26,94]
    n = len(heap_key)

    root = Treap(0,heap_key[0],0,0)
    for i in range(1,n):
        root = root.append_node(Treap(i,heap_key[i],i,i))
        root.parent = None

    print(str(root))
    print(root.query(10))
