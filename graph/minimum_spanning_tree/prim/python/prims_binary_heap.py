#!/bin/python3
# vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

'''
prims_binary_heap.py file is part of Algosnippet.
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

import math
import os
import random
import re
import sys
import collections
from heapq import heapify,heappop,heappush

WeightedEdge = collections.namedtuple("WeightedEdge", "weight,src,dest,idx")

class y_heap(list):
    '''
    y_heap is simply a list. It extends the comparison of list to compare the first element only.
    '''
    def __lt__(self,other):
        return self[0] < other[0]
    
def prims(n, edges, start):
    '''
    Complexity |E| + |V| + (2*|E|)log(|V|)
    '''
    
    # complexity 2*|E| 
    # heapify all the edge lists
    # Each of these heaps will be part of 2-dimensional heap
    for y_hp in edges:
        heapify(y_hp)
    
    explored_edges = [False]*m
    explored_nodes = [False]*n
    
    # setup start node
    x_hp = [edges[start]] # x_hp is two dimensional heap initially containing the edges containing the starting ndoe
    n_explored = 1
    explored_nodes[start] = True # mark as explored
    mst_weight = 0 # the sum of selected edges of mst
    
    # Heap has total log(|V|) depth
    # And we push/pop at most 2*|E| times
    while n_explored < n:
        x = heappop(x_hp)
        assert(x) # our assumption is it is connected graph
        
        if explored_edges[x[0].idx] or explored_nodes[x[0].dest]: # the edges/dest node is already explored
            while explored_edges[x[0].idx] or explored_nodes[x[0].dest]: # skip the edges/dest-nodes already explored
                heappop(x)
                if not x:
                    break
                    
            if x:
                heappush(x_hp,x) # we shall come back later
            continue
        
        # now we have an unexplored destination/edge
        n_explored += 1
        xy_edge = heappop(x)
        heappush(x_hp, edges[xy_edge.dest])
        explored_edges[xy_edge.idx] = True        
        explored_nodes[xy_edge.dest] = True
        mst_weight += xy_edge.weight
        
        # pop the explored node
        if x:
            heappush(x_hp, x)
    
    return mst_weight

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    nm = input().split()

    n = int(nm[0])

    m = int(nm[1])

    edges = [y_heap() for i in range(n)]
    for i in range(m):
        x,y,w = tuple(map(int, input().rstrip().split()))
        # added edges in 0 based indexing
        edges[x-1].append(WeightedEdge(w,x-1,y-1,i))
        edges[y-1].append(WeightedEdge(w,y-1,x-1,i))

    start = int(input())

    result = prims(n, edges, start-1)

    fptr.write(str(result) + '\n')

    fptr.close()
