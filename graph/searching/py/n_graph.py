#!python3

class n_graph_adj:
    def connect(self, i, j, w):
        pass

    def biconnect(self, i, j, w=1):
        self.connect(i, j, w)
        self.connect(j, i, w)
    
    def iter_connected(self, i):
        pass

class n_graph_adj_matrix(n_graph_adj):
    '''
    Adjucency matrix based on full matrix
    '''
    def __init__(self, sz):
        self.adj = [[0]*sz for i in range(sz)]
    
    def connect(self, i, j, w):
        self.adj[i][j] += w

    def iter_connected(self, i):
        for j,w in enumerate(self.adj[i]):
            if w > 0:
                yield j,w

class n_graph_adj_trimatrix(n_graph_adj):
    '''
    Adjucency matrix based on triangle matrix
    '''
    def __init__(self, sz):
        self.adj = [[0]*(sz-i) for i in range(sz)]
    
    def connect(self, i, j, w):
        if i < j:
            self.adj[i][j-i] += w
        else:
            self.adj[j][i-j] += w

    def iter_connected(self, i):
        for j,w in enumerate(self.adj[i]):
            if w > 0:
                yield i+j,w
        for j in range(i):
            w = self.adj[j][i-j]
            if w:
                yield j,w
    
    def biconnect(self, i, j, w=1):
        self.connect(i, j, w)
        
class n_graph_adj_list(n_graph_adj):
    '''
    Adjucency list, it takes O(edge) size 
    '''
    def __init__(self, sz):
        self.adj = [[] for i in range(sz)]
    
    def connect(self, i, j, w=1):
        self.adj[i].append((j,w))

    def iter_connected(self, i):
        for j,w in self.adj[i]:
            yield j,w

class n_graph_alg(n_graph_adj):
    '''
    This a graph of N nodes

    Note that triangle-adjucency matrix only works on undirected graph

    Node index is 0 based.
    '''
    def __init__(self, sz, adj_type=n_graph_adj_list):
        self.n = sz
        self.visited = [False]*sz
        self.expanded = [False]*sz
        self.processed = [False]*sz
        self.components = []
        self.adj = adj_type(sz)

    def connect(self,i,j,w):
        '''
        Decorator pattern
        '''
        self.adj.connect(i,j,w)
    
    def biconnect(self,i,j,w=1):
        '''
        Decorator pattern
        '''
        self.adj.biconnect(i,j,w)
 
    
    def iter_connected(self, i):
        '''
        Decorator pattern
        '''
        self.adj.iter_connected(i)
    
    def iter_dfs(self, root=0):
        visited = [False]*self.n
        expanded = [False]*self.n
        processed = [False]*self.n
        stack = [root]
        visited[root] = True
        while stack:
            x = stack[-1]
            assert visited[x]
            if expanded[x]:
                assert not processed[x]
                yield x,processed
                processed[x] = True
                stack.pop() # get rid of x
                continue

            for j,w in self.adj.iter_connected(x):
                if expanded[j]:
                    # has back-edge
                    # possibly it is the parent
                    continue
                if visited[j]:
                    # connection to sibling
                    continue
                visited[j] = True
                stack.append(j)
            
            expanded[x] = True


if __name__ == "__main__":
    ng = n_graph_alg(4, adj_type=n_graph_adj_list)
    
    # 0 - 1 - 2 - 3
    ng.biconnect(0,1)
    ng.biconnect(1,2)
    ng.biconnect(2,3)

    print("Running dfs from root=0")
    for j,processed in ng.iter_dfs(0):
        print(j)

    print("Running dfs from root=1")
    for j,processed in ng.iter_dfs(1):
        print(j)

    def sum_two(x, edge, processed=[], values=[]):
        y,w = edge
        return x+values[y] if processed[y] else x

    def mul_two(x, edge, processed=[], values=[]):
        y,w = edge
        return x*values[y] if processed[y] else x

    init_val = {}
    init_val[sum_two] = 0
    init_val[mul_two] = 1

    # evaluate a postfix notation 1+2*4
    symbols = [1,sum_two,2,mul_two,4]
    ng = n_graph_alg(5, adj_type=n_graph_adj_list)

    # 2*4
    ng.connect(3,4,1)
    ng.connect(3,2,1)
    
    # 1+(2*4)
    ng.connect(1,0,1)
    ng.connect(1,3,1)

    print("Expression:", symbols)

    values = symbols[:]
    from functools import reduce
    from functools import partial
    # eval from 1st node
    for j,processed in ng.iter_dfs(1):
        if isinstance(values[j],int):
            continue # already evaluated

        action = partial(values[j],processed=processed,values=values)
        # reduce here
        values[j] = reduce(action, ng.adj.iter_connected(j), init_val[values[j]])
        print(j, "evaluating ", action, processed, values[j])
        print(list(ng.adj.iter_connected(j)))

    print(values)
    print("Result=",values[1])

