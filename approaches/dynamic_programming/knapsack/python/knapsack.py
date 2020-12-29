#!python

def solve_knapsack(objs, limit):
    memo = dict()
    memo[0] = 0
    
    result = 0
    for w,v in objs:
        memo_next = dict()
        for x in memo.keys():
            if x not in memo_next or memo_next[x] < memo[x]:
                memo_next[x] = memo[x]
            calc_value = memo[x]+v
            if (x+w) < limit and ((x+w) not in memo_next or memo_next[x+w] < calc_value):
                memo_next[x+w] = calc_value
                result = max(result,calc_value)
        memo = memo_next
    return result

if __name__ == "__main__":
    num_queries = int(input())
    for _ in range(num_queries):
        limit,num_items = [int(x) for x in input().strip().split()]
        objs = [None]*num_items
        value = [0]*num_items
        for i in range(num_items):
            objs[i] = [int(x) for x in input().strip().split()]
        print(solve_knapsack(objs,limit))
        
