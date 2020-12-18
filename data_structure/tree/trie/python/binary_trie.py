#!/bin/python3
# vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

'''
binary_trie.py file is part of Algosnippet.

Algosnippet is a collection of practice data-structures and algorithms
Copyright (C) 2020  Kamanashis Roy

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


def iter_bits(given):
    while given:
        old = given
        given = given >> 1
        yield (old-(given<<1))
        
        

# Binary trie
class binary_trie:
    '''
    Algosnippet is a collection of practice data-structures and algorithms
    Copyright (C) 2020  Kamanashis Roy

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
    __slots__ = ["direction", "left", "right", "compstr", "data"]
    def __init__(self,direction):
        self.direction = direction
        self.left = None
        self.right = None
        self.compstr = str(direction)
        self.data = []
    
    def append(self, given_iter,data):
        x = next(given_iter,None)
        if x is None:
            self.data.append(data)
        elif x == 0:
            if self.left is None:
                self.left = binary_trie(0)
            self.left.append(given_iter,data)
        else:
            if self.right is None:
                self.right = binary_trie(1)
            self.right.append(given_iter,data)
            
    def lookup(self, given_iter):
        x = next(given_iter,None)
        if x is None:
            return self.data
        elif x == 0:
            if self.left is None:
                return None
            else:
                return self.left.lookup(given_iter)
        else:
            if self.right is None:
                return None
            else:
                return self.right.lookup(given_iter)
        
    def __compress_helper2(self,xcomp,xstr):
        x = self
        while x:
            if x.data:
                xstr.append(str(x.direction))
                return x # it has valid data
            if x.left is None:
                if x.right is None:
                    xstr.append(str(x.direction))
                    return x # both are invalid
                else:
                    # x can be compressed with right
                    xcomp.append(x)
                    xstr.append(str(x.direction))
                    x = x.right
            else:
                if x.right is None:
                    xcomp.append(x)
                    xstr.append(str(x.direction))
                    x = x.left
                else:
                    xstr.append(str(x.direction))
                    return x # both left and right is valid
    
    def __compress_helper(self):
        xcomp = []
        xstr = []
        last_node = self.__compress_helper2(xcomp,xstr)
        if(xcomp):
            # we have a scope to compress
            #self.compstr = '-'.join(xstr)
            last_node.compstr = '-'.join(xstr)
            #if last_node is None:
            #    self.left = None # compressed
            #    self.right = None # compressed
            #elif 0 == last_node.direction:
            #    self.left = last_node
            #    self.right = None # compressed
            #    self.left.compress()
            #else: # when direction == 1
            #    self.right = last_node
            #    self.left = None # compressed
            #    self.right.compress()   
            last_node.compress()
            return last_node
        else:
            self.compress()
        return self
                    
    def compress(self):
        if self.left:
            self.left = self.left.__compress_helper()
        if self.right:
            self.right = self.right.__compress_helper()
            
    def __str__(self,depth=0):
        ret = ""
        if(self.left is not None):
            ret += self.left.__str__(depth+1)
        ret += "\t"*(depth)+"dir={direction},\"{compressed_str}\",{data}\n".format(direction=self.direction,compressed_str=str(self.compstr),data=str(self.data))
        if(self.right is not None):
            ret += self.right.__str__(depth+1)
        return ret


if __name__ == "__main__":
    print("We made a binary trie")
    table = binary_trie(-1)
    print("inserting 4")
    table.append(iter_bits(4),4) # 0b100
    print("trie -----------------------")
    print(str(table))
    print("inserting 5")
    table.append(iter_bits(5),5) # 0b101
    print("trie -----------------------")
    print(str(table))
    print("inserting 8")
    table.append(iter_bits(8),8) # 0b1000
    print("trie -----------------------")
    print(str(table))
    print("patricia tree --------------")
    table.compress()
    print(str(table))
    
