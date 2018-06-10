#!/bin/python3
# vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

import avl_tree

class interval:
    def __init__(self,start,end):
        self.start = start
        self.end = end

    def __lt__(self,other):
        return other.end < self.end

    def __gt__(self,other):
        return other.start > self.start

    def __eq__(self,other):
        return self.start == other.start and self.end == other.end

    def __repr__(self):
        return "({start},{end})".format(start=self.start,end=self.end)

if __name__ == "__main__":
    tree = avl_tree.avl_tree()
    tree.insert(interval(5,6))
    tree.insert(interval(4,7))
    tree.insert(interval(3,5))
    tree.insert(interval(7,8))
    tree.insert(interval(1,2))
    tree.insert(interval(2,5))
    tree.insert(interval(5,8))
    tree.insert(interval(8,9))
    print(str(tree))
    print("==================================")
    

