#!python3


class disjoint_set:
    '''
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


    __slots__ = ['rank','parent']
    def __init__(self, N:int):
        self.rank = [1]*N
        self.parent = list(range(N))

    def __setitem__(self, i:int,j:int) -> None:
        i = self.find(i)
        j = self.find(j)
        if i != j:
            ri = self.rank[i]
            rj = self.rank[j]
            if ri > rj:
                self.parent[j] = i
            elif ri == rj:
                self.parent[j] = i
                self.rank[i] += 1
            else:
                self.parent[i] = j

    def __getitem__(self, i:int) -> int:
        pt:int = self.parent[i]
        while pt != i:
            self.parent[i] = self.parent[pt] # path halving
            i = pt
            pt = self.parent[pt]
        return pt

    join = __setitem__
    find = __getitem__

class disjoint_set2:
    '''
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


    __slots__ = ['nodes']
    def __init__(self, N):
        self.nodes = [(i,1) for i in range(N)]

    def __setitem__(self, i:int,j:int) -> None:
        i = self.find(i)
        j = self.find(j)
        if i != j:
            ri = self.nodes[i][1]
            rj = self.nodes[j][1]
            if ri > rj:
                self.nodes[j] = (i,-1)
            elif ri == rj:
                self.nodes[j] = (i,-1)
                self.nodes[i] = (i,ri+1)
            else:
                self.nodes[i] = (j,-1)

    def __getitem__(self, i:int) -> int:
        pt:int = self.nodes[i][0]
        while pt != i:
            grandpa:int = self.nodes[pt][0]
            self.nodes[i] = (grandpa,-1) # path halving
            i,pt = pt,grandpa
        return pt

    join = __setitem__
    find = __getitem__
