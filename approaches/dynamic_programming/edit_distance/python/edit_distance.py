#!python

from collections import namedtuple

DIST = namedtuple('DIST','cost,op', defaults=(0,None))
class edit_distance:
    @staticmethod
    def expand(topleft, top, left, x, y):
        yield DIST(topleft.cost+1,'r')   # replace character
        if x == y:
            yield DIST(topleft.cost,'a') # accept character
        yield DIST(left.cost+1,'i')      # insert character
        yield DIST(top.cost+1,'d')       # drop character
    
    @staticmethod
    def distance(src:str, dst:str) -> int:
        M,N = len(src),len(dst)
        if 0 == M: # when from word is empty
            return N
        
        print('None |', ' root | ', ' | '.join(dst))
        print(' | '.join(['---' for _ in range(N+2)]))
        memo = [DIST(cost=i,op='i' if i else ' ') for i in range(N+1)] # DAG roots
        print('root |', ' | '.join(map(str,iter(memo))))
        
        # Do BFS
        for i,x in enumerate(src,1):
            next_memo = [DIST(cost=i,op='d')] # initialize with cost of drop
            for j,y in enumerate(dst,1):
                next_memo.append(min(edit_distance.expand(memo[j-1], memo[j], next_memo[-1], x, y)))
            memo = next_memo
            print(x, '|', ' | '.join(map(str,iter(memo))))
            
        return memo[-1].cost
