
Dynamic programming is traversal in the subproblem graph(DAG) while doing counting/optimization etc.

Note that unlike Greedy, where each subproblem comes from one parent(like a tree node), in Dynamic programming, each subproblem can come from multiple parent(like in Directed Acyclic Graph).

 .                    | Dynamic programming     | Greedy  | Divide and conquor
 ---                  | ---                     | ---     | ---
 Overlapping subproblem | Allowed               | Not calculated | Not allowed
 subproblem graph     | Directed acyclic graph  | Straight line tree    | Tree

Dynamic programming close comparison table
============================================

 Problem                      | Subproblems    | Cost at each subproblem        | Cost
 ---                          | ---            | ---                            | ---
 Fibonacci Numbers            | `O(n)`         | `O(1)`                         | `O(n)`    
 Binomial  Numbers            | `todo`         | `todo`                         | `O(n*n)`
 Bellman-Ford algorithm       | `O(V)`         | `O(E)`                         | `O(V*E)` , best case `O(E)`
 Subset sum                   | `O(2^n)`       | `O(1)`                         | `O(2^n)`
 Repeat sum (coin change)     | `O(amount)`    | `O(num_coins)`                 | `O(num_coins*amount)`
 Knapsack                     | `O(2^n)`       | `O(1)`                         | `O(2^n)`
 Longest common subsequence   | `O(m*n)`       | `O(1)`                         | `O(m*n)`
 Brick game                   | `O(n)`         | `O(1)`                         | `O(n)`
  

Comparison
===========

#### Fibonacci number

Approach: Forward in-edge relaxation, prefix-subproblem-memoization

```
// fill me
```

#### Binomial number

Approach: Forward in-edge relaxation, prefix-subproblem-memoization

```
// fill me
```

#### Bellman-Ford algorithm

Approach: Random edge relaxation

```python
def bellman_ford(self, n: int, edges: List[List[int]], src: int, dst: int) -> int:
    if 0 >= n or src == dst:
        return 0
    
    cost = [-1]*n
    cost[src] = 0                      # root
    relaxed = True
    
    while relaxed:
        relaxed = False
        for edge in edges:             # expand edges
            x,y,money = edge
            if -1 != cost[x] and (-1 == cost[y] or cost[y] > (cost[x]+money)): # relaxation
                cost[y] = cost[x]+money
                relaxed = True
        
    return cost[dst]
```

#### Subset sum

Approach: Forward BFS(out-edge), prefix-subproblem-memoization

```python
class Solution:
    def subset_sum(self, nums, target):
        memo = dict()
        memo[0] = 1                    # root
        N = len(nums)
        
        for x in nums:                 # expand(out-edge) subproblems through x (induction step)
            memo_next = dict()
            for k in memo.keys():
                memo_next[k] = 1
                memo_next[k+x] = 1
            memo = memo_next
            if target in memo:
                return True
            
        return False                   # no relaxation in decision problem
```

#### Knapsack

Approach: Forward BFS(out-edge) + relaxation, prefix-subproblem-memoization

```python
def solve_knapsack(objs, limit):
    memo = dict()
    memo[0] = 0                        # root
    
    result = 0
    for w,v in objs:                   # expand(out-edge) subproblems through object of weight,w and value,v (induction step)
        memo_next = dict()
        for x in memo.keys():
            if x not in memo_next or memo_next[x] < memo[x]:
                memo_next[x] = memo[x]
            calc_value = memo[x]+v
            if (x+w) < limit and ((x+w) not in memo_next or memo_next[x+w] < calc_value):
                memo_next[x+w] = calc_value
                result = max(result,calc_value)     # relaxation step
        memo = memo_next
    return result
```

#### Repeat-sum(Coin-change) algorithm

Approach: Forward in-edge relaxation, prefix-subproblem-memoization

```python
def coinChangeMin(self, coins: List[int], amount: int) -> int:
    N = len(coins)
    memo = [-1]*(amount+1)
    memo[0] = 0                        # root
    for i in range(1,amount+1):
        for c in coins:                # expand(in-edge) edges
            if i >= c and -1 != memo[i-c] and (-1 == memo[i] or memo[i] > (memo[i-c]+1)): # relaxation
                memo[i] = memo[i-c]+1
    return memo[amount]
```

Counting number of unique ways has exponential time and space cost. O(X^C) where coin can appear X number of times.

```python
def coinChangeCountWays(n, c):
    # Write your code here
    memo = [None]*(n+1)
    memo[0] = {0:1}                    # root
    for i in range(1,n+1):
        next_memo = defaultdict(int)
        for ci,x in enumerate(c):      # expand(in-edge) edges
            if i >= x:
                for comb,count in memo[i-x].items():
                    mycomb = comb + (1<<(16*ci))
                    if mycomb not in next_memo:
                        next_memo[mycomb] = count
        memo[i] = next_memo
    return sum(memo[n].values())
```

#### Longest common subsequence

Approach: Forward in-edge relaxation, prefix-subproblem-memoization

```python
def longestCommonSubsequence(self, text1: str, text2: str) -> int:

    LEN1 = len(text1)
    LEN2 = len(text2)

    memo = [[0]*(LEN2+1) for i in range(LEN1+1)]

    for i,x in enumerate(text1):
        for j,y in enumerate(text2):                            # expand(in-edge) 3 ways
            if x == y:                                          # expand from top-left corner
                memo[i+1][j+1] = memo[i][j] + 1
            else:                                               # expand from left or from top
                memo[i+1][j+1] = max(memo[i][j+1],memo[i+1][j]) # relaxation

    return memo[LEN1][LEN2]
```

#### Bricks Game

Similar to blackjack game playing.

Approach: Backward in-edge relaxation, suffix-subproblem-memoization

```
def bricksGame(arr):
    N = len(arr)
    memo = [MSCORE(0,0) for i in range(N+1)]                    # root = memo[N] = MSCORE(0,0)
    
    for i in reversed(range(N)):
        # when in pos i
        cum_score = arr[i]
        result = MSCORE(my=memo[i+1].his+cum_score,his=memo[i+1].my)
        for j in range(i+1,min(i+3,N)):                         # expand(in-edge) 3 ways
            cum_score += arr[j]
            rest = memo[j+1]
            combined = MSCORE(my=rest.his+cum_score, his=rest.my)
            if combined.my > result.my:
                result = combined                               # relaxation
        memo[i] = result
    return memo[0].my
```

[Bricks game](https://www.hackerrank.com/challenges/play-game)

#### Cutting stick

Approach: Forward BFS, substring-subproblem-memoization

```
    def stick_cutting_bottomup(self, cuts:List[int]):
        N = len(cuts)
        memo = [[-1]*(N-sz) for sz in range(N)]
        
        # setup smaller base cases                              # Many roots
        for k in range(3):
            for begin in range(N-k):
                if 2 == k:
                    memo[begin][k] = cuts[begin+k]-cuts[begin] # base case 2 , 1 cut is needed
                else:
                    memo[begin][k] = 0 # base case, no cuts required
                
        for k in range(3,N):
            for begin in range(N-k):
                end = begin+k
                setup_cost = cuts[end]-cuts[begin]
                cost = -1
                for i in range(begin+1,end):                     # expand to substrings
                    costa = memo[begin][i-begin]
                    costb = memo[i][end-i]
                    if -1 == cost or cost > (costa+costb+setup_cost):
                        cost = costa+costb+setup_cost            # relaxation
                memo[begin][k] = cost
        return memo[0][N-1]
```

[Cutting stick](https://leetcode.com/problems/minimum-cost-to-cut-a-stick/)

Lectures
=========

- [Dynamic programming](https://web.stanford.edu/class/archive/cs/cs161/cs161.1168/lecture12.pdf)
- [Full video course](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/)
    - [Fibonacci and shortest paths](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-19-dynamic-programming-i-fibonacci-shortest-paths)
    - [Text justification and blackjack](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-20-dynamic-programming-ii-text-justification-blackjack)
    - [Parenthesization, Edit distance and knapsack](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-21-dp-iii-parenthesization-edit-distance-knapsack)
    - [Guiter fingering, Tetris and Super Mario Bros](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-22-dp-iv-guitar-fingering-tetris-super-mario-bros)


