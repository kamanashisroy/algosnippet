#!/bin/python3


class disjoint_set:
    def __init__(self,sz):
        self.parent = list(range(0,sz))
        self.rank = [0]*sz

    #def make_set(self,x):
    #    self.parent[x] = x
        
    def join(self,x,y):
        px = self.find(x)
        py = self.find(y)
        if px != py: # join when not equal
            rx = self.rank[px]
            ry = self.rank[py]
            if rx > ry:
                self.parent[px] = py
            elif rx < ry:
                self.parent[py] = px
            else:# when rankings are equal
                self.rank[py] += 1 # rank is increased
                self.parent[py] = px
        
    def find(self,x):
        while self.parent[x] != x:
            grandpa = self.parent[self.parent[x]]
            self.parent[x] = grandpa # path halving
            x = grandpa
        return x

