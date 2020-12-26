
Dynamic programming is traversal in the subproblem graph(DAG) while doing counting/optimization etc.

Note that unlike Greedy, where each subproblem comes from one parent(like a tree node), in Dynamic programming, each subproblem can come from multiple parent(like in Directed Acyclic Graph).

 .                    | Dynamic programming     | Greedy  | Divide and conquor
 ---                  | ---                     | ---     | ---
 Overlapping subproblem | Allowed               | Not allowed | Not allowed
 subproblem graph     | Directed acyclic graph  | Tree    | Tree

Dynamic programming close comparison table
============================================

 Problem                      | Cost 
 ---                          | --- 
 Fibonacci Numbers            | `O(n)`
 Binomial  Numbers            | `O(n*n)`
 Bellman-Ford algorithm       | `O(V*E)`
 Longest common subsequence   | `O(m*n)`
 Subset sum                   | `O(2^n)`
  

Comparison
===========

#### Fibonacci number

```
// fill me
```

#### Binomial number

```
// fill me
```

#### Bellman-Ford algorithm

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

```python
class Solution:
    def subset_sum(self, nums, target):
        memo = dict()
        memo[0] = 1                    # root
        N = len(nums)
        
        for x in nums:                 # expand edges through x (induction step)
            memo_next = dict()
            for k in memo.keys():
                memo_next[k] = 1
                memo_next[k+x] = 1
            memo = memo_next
            if target in memo:
                return True
            
        return False                   # no relaxation in decision problem
```

#### Coin-change algorithm

```python
def coinChange(self, coins: List[int], amount: int) -> int:
    N = len(coins)
    memo = [-1]*(amount+1)
    memo[0] = 0                        # root
    for i in range(1,amount+1):
        for c in coins:                # expand edges
            if i >= c and -1 != memo[i-c] and (-1 == memo[i] or memo[i] > (memo[i-c]+1)): # relaxation
                memo[i] = memo[i-c]+1
    return memo[amount]
```

#### Longest common subsequence

```python
def longestCommonSubsequence(self, text1: str, text2: str) -> int:

    LEN1 = len(text1)
    LEN2 = len(text2)

    memo = [[0]*(LEN2+1) for i in range(LEN1+1)]

    for i,x in enumerate(text1):
        for j,y in enumerate(text2):                            # expand 3 ways
            if x == y:                                          # expand from top-left corner
                memo[i+1][j+1] = memo[i][j] + 1
            else:                                               # expand from left or from top
                memo[i+1][j+1] = max(memo[i][j+1],memo[i+1][j]) # relaxation

    return memo[LEN1][LEN2]
```

Lectures
=========

- [Dynamic programming](https://web.stanford.edu/class/archive/cs/cs161/cs161.1168/lecture12.pdf)
- [Full video course](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/)
    - [Fibonacci and shortest paths](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-19-dynamic-programming-i-fibonacci-shortest-paths)
    - [Text justification and blackjack](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-20-dynamic-programming-ii-text-justification-blackjack)
    - [Parenthesization, Edit distance and knapsack](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-21-dp-iii-parenthesization-edit-distance-knapsack)
    - [Guiter fingering, Tetris and Super Mario Bros](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-22-dp-iv-guitar-fingering-tetris-super-mario-bros)


