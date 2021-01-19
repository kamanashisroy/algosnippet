#!python

from collections import namedtuple

DIST = namedtuple('DIST','cost,op', defaults=(0,None))
class edit_distance:
    @staticmethod
    def expand(topleft, top, left, x, y):
        cost,op = topleft.cost+1,'r'   # replace character
        if x == y and cost > topleft.cost:
            cost,op = topleft.cost,'a' # accept character
        if cost > (left.cost+1):
            cost,op = left.cost+1,'i'  # insert character
        if cost > (top.cost+1):
            cost,op = top.cost+1,'d'   # drop character
        return DIST(cost=cost,op=op)

    @staticmethod
    def distance(src:str, dst:str) -> int:
        M,N = len(src),len(dst)
        if 0 == M: # when from word is empty
            return N

        print('None |', ' | '.join(dst))
        print(' | '.join(['---' for _ in range(N+1)]))
        memo = [DIST(cost=i,op='i' if i else ' ') for i in range(N+1)] # DAG roots
        print('root |', ' | '.join(map(str,iter(memo))))

        # Do BFS
        for i,x in enumerate(src,1):
            next_memo = [DIST(cost=i,op='d')] # initialize with cost of drop
            for j,y in enumerate(dst,1):
                next_memo.append(edit_distance.expand(memo[j-1], memo[j], next_memo[-1], x, y))
            memo = next_memo
            print(x, '|', ' | '.join(map(str,iter(memo))))

        return memo[-1].cost
