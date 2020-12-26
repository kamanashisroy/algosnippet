def bellman_ford(self, n: int, edges: List[List[int]], src: int, dst: int) -> int:
    if 0 >= n or src == dst:
        return 0
    
    cost = [-1]*n
    cost[src] = 0
    relaxed = True
    
    while relaxed:
        relaxed = False
        for edge in edges:
            x,y,money = edge
            if -1 != cost[x] and (-1 == cost[y] or cost[y] > (cost[x]+money)):
                cost[y] = cost[x]+money
                relaxed = True
        
    return cost[dst]
