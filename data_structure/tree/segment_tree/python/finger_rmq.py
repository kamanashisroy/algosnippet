class fingerRMQ:
    '''
    fingerRMQ.py file is part of Algosnippet.
    Algosnippet is a collection of practice data-structures and algorithms
    Copyright (C) 2021  Kamanashis Roy
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


    def __init__(self, aN, defaultVal=-1):
        self.N = aN
        depth = 1
        while (1<<depth) < self.N:
            depth += 1
        
        self.INFLO = (defaultVal, -1)
        self.N = 1<<depth
        self.nodes = [self.INFLO]*((self.N+1)<<1)
    
    def fill(self,aNums):
        for i,x in enumerate(aNums):
            self.nodes[i+self.N] = (x,i)
        
        for i in range(self.N-1,0,-1):
            self.nodes[i] = max(self.nodes[i<<1],self.nodes[(i<<1)+1])

    def __getitem__(self, i:int):
        cur = self.N+i
        return self.nodes[cur]

    def __setitem__(self, i:int, val:int):
        cur = self.N+i
        if val == self.nodes[cur][0]:
            return
        self.nodes[cur] = (val,i)
        while cur > 1:
            parent = cur>>1
            if self.nodes[parent] >= (val,i):
                break
            self.nodes[parent] = max(self.nodes[parent], (val,i))
            cur = parent

    def rmq(self, beg, size):
        if size <= 0:
            return self.INFLO

        if size < 8:
            ret = self.INFLO
            for i in range(beg,beg+size):
                ret = max(ret,self.nodes[self.N+i])
            return ret

        left = self.N+beg
        right = left+size-1
        cur = right
        ret = self.nodes[cur]
        covered_left = cur

        depth = 0
        while cur > 1:
            parent = cur>>1
            if cur&1: # if right child
                # we are good
                subtree_beg = covered_left - (1<<depth)
                if subtree_beg >= left:
                    # go ahead
                    ret = max(ret,self.nodes[parent])
                    covered_left = subtree_beg
                    if left == subtree_beg:
                        return ret
                else:
                    return max(ret,self.rmq(beg, covered_left-left))
            else: # if left child
                return max(ret,self.rmq(beg, covered_left-left))
            cur = parent
            depth+=1
