#!python3


class disjoint_set:
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
