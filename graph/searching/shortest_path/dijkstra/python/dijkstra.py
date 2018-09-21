#!/bin/python3
# vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

import math
import os
import random
import re
import sys
import collections
import kary_heap

# NOTE The given input junktions are counted from 1, while we use 0 based indexing here.

Edge = collections.namedtuple("Edge", "dest cost")
Path = collections.namedtuple("Path", "src dest")

debug = False

class Node:
    def __init__(self, identifier,maxnodes):
        self.identifier = identifier
        self.edges = dict()
        self.path_cost = None
        
    def add_edge(self, dest, cost):
        if dest.identifier in self.edges and self.edges[dest.identifier].cost <= cost:
            # existing edge is better be kept while given edge is avoided
            return

        edge = Edge(dest,cost)
        self.edges[dest.identifier] = edge


    def __hash__(self):
        return self.identifier
        
    def __repr__(self):
        return "<{identifier}:{path_cost}> -> {edges}".format(identifier=self.identifier,path_cost=self.path_cost,edges=','.join([str(tuple((dest.identifier,cost))) for dest,cost in self.edges.values()]))
    
    def __lt__(self,other):
        if self.path_cost == other.path_cost:
            # when both None or the same
            return (self.identifier < other.identifier)

        if self.path_cost is None and other.path_cost is None:
            return (self.identifier < other.identifier)

        if other.path_cost is None:
            return True

        if self.path_cost is None:
            return False
            
        return self.path_cost < other.path_cost
    
    def __gt__(self,other):
        if self.path_cost == other.path_cost:
            # when both None or the same
            return (self.identifier > other.identifier)

        if self.path_cost is None and other.path_cost is None:
            return (self.identifier > other.identifier)

        if other.path_cost is None:
            return False

        if self.path_cost is None:
            return True
            
        return self.path_cost > other.path_cost
    
    def __eq__(self,other):
        return self.identifier == other.identifier
    
    def __ne__(self,other):
        return self.identifier != other.identifier
    
    def __le__(self,other):
        return self.__eq__(other) or self.__lt__(other)

    def __ge__(self,other):
        return self.__eq__(other) or self.__gt__(other)

class ShortestPath:
    def __init__(self, nodes):
        self.nodes = nodes
        self.n = len(nodes)
        self.last_node = self.n-1
    
    def find_path(self):
        
        explored = [False]*self.n
        expanded = [False]*self.n
        self.nodes[0].path_cost = 0
        expanded[0] = True
        explored[0] = True
        
        #fringe = Fringe()
        #fringe = kary_heap(1,self.n)
        fringe = kary_heap.kary_heap(4)
        fringe.append(self.nodes[0]) # start journey from 0
        while not fringe.empty():
            node = fringe.popleft()
            expanded[node.identifier] = True
            if debug:
                print("Expanding node ", node.identifier)
            if node.identifier == (self.last_node):
                # destination is reached
                if debug:
                    print("found")
                return node.path_cost
            for edge in node.edges.values():
                if expanded[edge.dest.identifier]: # avoid updating the ancesters
                    continue
                
                route_cost = node.path_cost + edge.cost
                
                if debug:
                    print("Exploring node ", edge.dest.identifier, edge.dest.path_cost, route_cost)
                if edge.dest.path_cost is None or edge.dest.path_cost > route_cost: 
                    
                    # relaxation
                    if debug:
                        print("Relaxing node ", edge.dest.identifier, route_cost)
                    edge.dest.path_cost = route_cost
                    if not explored[edge.dest.identifier]: # avoid already enfringed nodes
                        if debug:
                            print("Pushing node ", edge.dest.identifier, route_cost)
                        fringe.append(edge.dest)
                        explored[edge.dest.identifier] = True
                    elif not expanded[edge.dest.identifier]: # the node is already in the fringe
                        fringe.fix_node_when_reduced(edge.dest)
        return -1
                

# Complete the leastTimeToInterview function below.
def leastTimeToInterview(n, k, m):
    # Return the least amount of time needed to reach the interview location in seconds.
    
    # make a list of nodes
    nodes = [Node(i,n) for i in range(n)]
    
    # read all the edges
    for _ in range(m):
        i,j,t = map(int,input().strip().split())
        if i == j:
            continue
        if debug:
            print("adding edge",i-1,j-1)
        nodes[i-1].add_edge(nodes[j-1],t)
        nodes[j-1].add_edge(nodes[i-1],t)
    
    #for node in nodes:
    #    print(node)
    prob = ShortestPath(nodes)
    return prob.find_path()

if __name__ == '__main__':
    n = int(input())

    k = int(input())

    m = int(input())

    result = leastTimeToInterview(n, k, m)

    print(str(result))

