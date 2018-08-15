#!/bin/python3
# vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

import avl_tree

class interval:
    '''
    Intervals have rich comparison

    '''
    def __init__(self,start,end):
        self.start = start
        self.end = end

    def __lt__(self,other):
        return self.start < other.start

    def __le__(self,other):
        return self.start <= other.start

    def __gt__(self,other):
        if self.start > other.start:
            return True
        elif self.start == other.start and self.end > other.end:
            return True
        return False

    def __ge__(self,other):
        if self.start > other.start:
            return True
        elif self.start == other.start and self.end >= other.end:
            return True
        return False

    def __eq__(self,other):
        return self.start == other.start and self.end == other.end

    def __ne__(self,other):
        return self.start != other.start or self.end != other.end

    def __repr__(self):
        return "({start},{end})".format(start=self.start,end=self.end)

class interval_tree(avl_tree.avl_tree):
    def __init__(self,x=None,parent=None):
        avl_tree.avl_tree.__init__(self,x,parent)
        self.right_max = None
        if(x is not None):
            self.right_max = x.end

    def __repr__(self):
        output = avl_tree.avl_tree.__repr__(self)
        output += ',' + str(self.right_max)
        return output
        
    def __str__(self,depth=0):
        ret = ""
        if(self.left is None):
            ret += "\t"*(depth+2)+"None\n"
        else:
            ret += self.left.__str__(depth+1)
        ret += "\t"*(depth+1)+str(self.height)+','+str(self.root)+','+str(self.right_max)+"\n"
        if(self.right is None):
            ret += "\t"*(depth+2)+"None\n"
        else:
            ret += self.right.__str__(depth+1)
        return ret

    def insert(self,x,duplicate=True,new_interval_tree = None):
        if(new_interval_tree is None):
            new_interval_tree = interval_tree(x)

        return avl_tree.avl_tree.insert(self,x,duplicate,new_interval_tree)

if __name__ == "__main__":
    tree = interval_tree()
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
    

