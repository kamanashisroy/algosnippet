
Dynamic programming is traversal in the subproblem graph(DAG) while doing counting/optimization etc.

Note that unlike Greedy, where each subproblem comes from one parent(like a tree node), in Dynamic programming, each subproblem can come from multiple parent(like in Directed Acyclic Graph).

 .                    | Dynamic programming     | Greedy  | Divide and conquor
 ---                  | ---                     | ---     | ---
 Overlapping subproblem | Allowed               | Not calculated | Not allowed
 subproblem graph     | Directed acyclic graph  | Straight line tree    | Tree
 Proof                | Strong induction        | Induction             | Strong Induction

Dynamic programming close comparison table
============================================

 Problem                      | Subproblems    | Cost at each subproblem        | Cost
 ---                          | ---            | ---                            | ---
 Fibonacci Numbers            | `O(n)`         | `O(1)`                         | `O(n)`    
 Binomial  Numbers            | `O(n)`         | `O(1)`                         | `O(n)`
 Catalan   Numbers            | `O(n)`         | `O(n)`                         | `O(n*n)`
 Bellman-Ford algorithm       | `O(V)`         | `O(E)`                         | `O(V*E)` , best case `O(E)`
 Subarray sum                 | `O(n)`         | `O(1)`                         | `O(n)`
 Subset sum                   | `O(2^n)`       | `O(1)`                         | `O(2^n)` , pseudo-polynomial
 Repeat sum (coin change)     | `O(amount)`    | `O(num_coins)`                 | `O(num_coins*amount)`
 Knapsack                     | `O(2^n)`       | `O(1)`                         | `O(2^n)` , pseudo-polynomial
 Longest common subsequence   | `O(m*n)`       | `O(1)`                         | `O(m*n)`
 Longest increasing subsequence | `O(n)`       | `O(log n)`                     | `O(n*log n)`
 Longest palindromic subsequence | `O(n*n)`    | `O(1)`                         | `O(n*n)`
 Brick game                   | `O(n)`         | `O(1)`                         | `O(n)`
 Stick cutting                | `O(?)`         | `O(?)`                         | `O(?)`
  

Comparison
===========

#### Fibonacci number

Approach: Forward in-edge relaxation, prefix-subproblem-memoization

```
// fill me
```

#### Binomial number

Approach: Forward in-edge relaxation, 2D-prefix-subproblem-memoization

```C++
/*
  Pascals_Triangle
  1
  1  1
  1  2  1
  1  3  3  1
  1  4  6  4  1
  1  5  10 10 5 1

  ...
  ...
  tri[i][j] = tri[i-1][j] + tri[i-1][j-1]

 */
std::size_t binomial_calc(const std::size_t xn, const std::size_t xk) {
    std::size_t tri[xn+1][xn+1];

    // initialize the vertial 1 and ending 1
    for(std::size_t row = 0; row <= xn; row++) {
        tri[row][0] = 1;
        tri[row][row] = 1;
    }

    // calculate pascal triangle
    for(std::size_t row = 2; row <= xn; row++) {
        for(std::size_t col = 1; col < row; col++) {
            tri[row][col] = tri[row-1][col] + tri[row-1][col-1];
        }
    }
    
    return tri[xn][xk];
}
```

#### Catalan number

Approach: Forward in-edge relaxation, substring-subproblem-memoization

```python
class catalan:
    def __init__(self, n):
        '''
        Cost is O(n*n)
        '''
        self.memo = [0]*n

        self.memo[0] = 1 # base case catalan number for 0
        self.memo[1] = 1 # catalan number for 1
        for i in range(2,n):
            for j in range(i):
                self.memo[i] += self.memo[j]*self.memo[i-j-1]

    def get(n):
        '''
        Get memo on O(1) time
        '''
        return self.memo[n]
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

#### Subarray sum

Approach: Backward in-edge relaxation, cumulative sum was counted in forward direction

```
def subarraySum(self, nums: List[int], k: int) -> int:
    nums = [0] + nums
    cumsum = [(x,i) for i,x in enumerate(itertools.accumulate(nums))]
    
    result = 0
    appear = defaultdict(int)
    for x,i in reversed(cumsum):
        if k+x in appear:
            ap = appear[k+x]
            result += ap
        appear[x] += 1

    return result
```

- [Subarray sum](https://leetcode.com/problems/subarray-sum-equals-k/)
- [Product of Array Except Self](https://leetcode.com/problems/product-of-array-except-self/)

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

It is possible to get the kth smallest or largest sum by best first subproblem expansion.
It can be done with heapq(like Dijkstra's shortest path algorithm), or by using a sorted interval.

- [Kth smallest sum](https://leetcode.com/problems/find-the-kth-smallest-sum-of-a-matrix-with-sorted-rows/)

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

Just like `Fibonacci number` calculation above.

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

Again, calculating the maximum amount possible, for `K` number of coins is greedy problem(`biggest_coin*K`). 

#### Edit distance

Approach: Forward in-edge relaxation, BFS from multiple DAG root

Just like `Binomial number` calculation above.

```python
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
```

Here is the visualization for `edit_distance.distance('tea', 'tree')`.

None |  root |  t | r | e | e
--- | --- | --- | --- | --- | ---
root | DIST(cost=0, op=' ') | DIST(cost=1, op='i') | DIST(cost=2, op='i') | DIST(cost=3, op='i') | DIST(cost=4, op='i')
t | DIST(cost=1, op='d') | DIST(cost=0, op='a') | DIST(cost=1, op='i') | DIST(cost=2, op='i') | DIST(cost=3, op='i')
e | DIST(cost=2, op='d') | DIST(cost=1, op='d') | DIST(cost=1, op='r') | DIST(cost=1, op='a') | DIST(cost=2, op='a')
a | DIST(cost=3, op='d') | DIST(cost=2, op='d') | DIST(cost=2, op='r') | DIST(cost=2, op='r') | DIST(cost=2, op='r')

#### Longest common subsequence

Approach: Forward in-edge relaxation, 2D-prefix-subproblem-memoization

Just like *Binomial number* calculation above.

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

Here is the visualization for `longestCommonSubsequence('tea', 'tree')`.

None |  root |  t | r | e | e
--- | --- | --- | --- | --- | ---
t    |    0,None   |   1,t   |   1,t   |   1,t   |   1,t
e    |    0,None   |   1,t   |   1,t   |   2,e   |   2,e
a    |    0,None   |   1,t   |   1,t   |   2,e   |   2,e

- [Longest common subsequence](https://www.hackerrank.com/challenges/dynamic-programming-classics-the-longest-common-subsequence/)

##### Reductions

- *Longest common subsequence* can be reduced to *Edit distance* by allowing only delete operation.
- Note that *Longest common subsequence* can also be reduced to *Longest Increasing Subsequence*, in case all the characters are unique.
- Again, *Longest palindromic subsequence* can be reduced to *Longest common subsequence*, by using reversed string as the second input.

#### Longest increasing subsequence


Approach: Forward in-edge relaxation, prefix-subproblem-memoization

*Longest-common-subsequence* with unique character can be converted to *Longest-increasing-subsequence* to give `O(n log n)` time.

[Reduction to Longest increasing subsequence](https://leetcode.com/problems/minimum-operations-to-make-a-subsequence/submissions/).


```python
def longest_increasing_subseq(arr : List[int]) -> int:
    memo = []
    memo.append(LONGEST_INCREASING_SUBSEQ(sz=1,top=arr[0]))     # Best result in first iteration
    
    # make prefix memo
    for i in range(1,M):
        
        x = arr[i]
        basesub = LONGEST_INCREASING_SUBSEQ(sz=1,top=x)
        lo = bisect_left(memo,basesub)
        if lo >= len(memo):
            lo = len(memo)-1

        prev_memo = memo[lo]
        subprob = LONGEST_INCREASING_SUBSEQ(sz=prev_memo.sz,top=x)
        if prev_memo.top == x:
            continue # avoid piling up
        elif prev_memo.top > x:
            memo[lo] = subprob                                  # Relax memo with best value
            #print('replace biggest', subprob)
        else:
            memo.append(LONGEST_INCREASING_SUBSEQ(sz=prev_memo.sz+1, top=x))    # pile up like patience-sort
            #print('pile up', subprob)
    result = 0
    for x in memo:
        result = max(result,x.sz)
    return result
```

- [Number of visible people in a queue](https://leetcode.com/problems/number-of-visible-people-in-a-queue/)

#### Longest palindromic substring

```python
from collections import namedtuple
P = namedtuple('P','sz,lo,hi,s')
class Solution:
    def longestPalindrome(self, s: str) -> int:
        N,memo = len(s),[]

        # odd palindrome base
        memo.append([P(lo=i,hi=i,sz=1,s=s[i:i+1]) for i in range(N)])

        # even palindrome base
        even_memo = [None]*N
        memo.append(even_memo)
        for i in range(N-1):
            if s[i] == s[i+1]:
                even_memo[i] = P(lo=i,hi=i+1,sz=2,s=s[i:i+2])

        for k in range(2,N):
            enclosed_memo,next_memo = memo[-2],[None]*N
            memo.append(next_memo)
            for lo in range(N-1):
                if (lo+k) < N:
                    hi = lo+k
                    if s[lo] == s[hi] and enclosed_memo[lo+1]:
                        prev = enclosed_memo[lo+1]
                        next_memo[lo] = P(lo=lo,hi=hi,sz=prev.sz+2,s=s[lo]+prev.s+s[hi])

        print('size | ', ' | '.join([str((i,x)) for i,x in enumerate(s)]))
        print('---  | ', ' | '.join(['---']*N))
        for k,m in enumerate(memo):
            print(k, ' | ', ' | '.join(map(str,m)))

        result = memo[0][0]
        for m in memo:
            result = reduce(lambda x,y: y if y and y > x else x,m,result)
        return result.s
```

Here is the table for "abcab".

size |  (0, 'a') | (1, 'b') | (2, 'c') | (3, 'a') | (4, 'b')
---  |  --- | --- | --- | --- | ---
0  |  P(sz=1, lo=0, hi=0, s='a') | P(sz=1, lo=1, hi=1, s='b') | P(sz=1, lo=2, hi=2, s='c') | P(sz=1, lo=3, hi=3, s='a') | P(sz=1, lo=4, hi=4, s='b')
1  |  None | None | None | None | None
2  |  None | None | None | None | None
3  |  None | None | None | None | None
4  |  None | None | None | None | None

- [Palindrome Partitioning IV](https://leetcode.com/problems/palindrome-partitioning-iv/)

#### Longest palindromic subsequence

Approach: Forward in-edge relaxation, substring-subproblem-memoization

Just like `Binomial number` calculation above.

```python
from collections import namedtuple
P = namedtuple('P','sz,lo,hi,s')
class Solution:
    def longestPalindromeSubseq(self, s: str) -> int:
        N,memo = len(s),[]

        # odd palindrome base
        memo.append([P(lo=i,hi=i,sz=1,s=s[i:i+1]) for i in range(N)])

        # even palindrome base
        even_memo = memo[-1][:]
        memo.append(even_memo)
        for i in range(N-1):
            if s[i] == s[i+1]:
                even_memo[i] = P(lo=i,hi=i+1,sz=2,s=s[i:i+2])

        for k in range(2,N):
            enclosed_memo,next_memo = memo[-2],memo[-1][:]
            memo.append(next_memo)
            for lo in range(N-1):
                curr = next_memo[lo] = max(next_memo[lo],next_memo[lo+1])
                if (lo+k) < N:
                    hi = lo+k
                    if s[lo] == s[hi]:
                        prev = enclosed_memo[lo+1]
                        next_memo[lo] = max(curr, P(lo=lo,hi=hi,sz=prev.sz+2,s=s[lo]+prev.s+s[hi]))
        print('size | ', ' | '.join([str((i,x)) for i,x in enumerate(s)]))
        print('---  | ', ' | '.join(['---']*N))
        for k,m in enumerate(memo):
            print(k, ' | ', ' | '.join(map(str,m)))
        return max(memo[-1]).sz
```

Here is the table for "abcab".

size |  (0, 'a') | (1, 'b') | (2, 'c') | (3, 'a') | (4, 'b')
---  |  --- | --- | --- | --- | ---
0  |  P(sz=1, lo=0, hi=0, s='a') | P(sz=1, lo=1, hi=1, s='b') | P(sz=1, lo=2, hi=2, s='c') | P(sz=1, lo=3, hi=3, s='a') | P(sz=1, lo=4, hi=4, s='b')
1  |  P(sz=1, lo=0, hi=0, s='a') | P(sz=1, lo=1, hi=1, s='b') | P(sz=1, lo=2, hi=2, s='c') | P(sz=1, lo=3, hi=3, s='a') | P(sz=1, lo=4, hi=4, s='b')
2  |  P(sz=1, lo=1, hi=1, s='b') | P(sz=1, lo=2, hi=2, s='c') | P(sz=1, lo=3, hi=3, s='a') | P(sz=1, lo=4, hi=4, s='b') | P(sz=1, lo=4, hi=4, s='b')
3  |  P(sz=3, lo=0, hi=3, s='aba') | P(sz=3, lo=1, hi=4, s='bcb') | P(sz=1, lo=4, hi=4, s='b') | P(sz=1, lo=4, hi=4, s='b') | P(sz=1, lo=4, hi=4, s='b')
4  |  P(sz=3, lo=1, hi=4, s='bcb') | P(sz=3, lo=1, hi=4, s='bcb') | P(sz=1, lo=4, hi=4, s='b') | P(sz=1, lo=4, hi=4, s='b') | P(sz=1, lo=4, hi=4, s='b')


#### Bricks Game

Similar to blackjack game playing.

Approach: Backward in-edge relaxation, suffix-subproblem-memoization

```python
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

#### Stick cutting

Approach: Forward BFS, substring-subproblem-memoization

Just like `catalan number` calculation above.

```python
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

#### Burst Balloons

**This problem is hard to formulate** in bottom-up way.

Just like `catalan number` calculation.

```
    @cache                                                                  # Memoize
    def maxScoreStr(nums:str, left:int = 1, right:int = 1) -> int:
        if len(nums) == 0:
            return 0

        if len(nums) == 1:
            return ord(nums[0])*left*right

        result = 0
        for i,x in enumerate(nums):
            x = ord(x)

            # we have two subproblems left and right
            lresult = Solution.maxScoreStr(nums[:i],left,x)
            rresult = Solution.maxScoreStr(nums[i+1:],x,right)
            gain = lresult+rresult+x*left*right
            if gain > result:
                result = gain                                                # relaxation
                #print('bursting ', i, 'subproblem(',lo,hi,left,right,')', gain)

        return result

    def maxScore(self, nums: List[int]) -> int:
        prob = ''.join([chr(x) for x in nums])
        return Solution.maxScoreStr(prob)
```

[Burst Balloons](https://leetcode.com/problems/burst-balloons/)

Bottom up solution below,

```python
    def maxScore(self, nums: List[int]) -> int:
        N = len(nums)
        if 0 == N:
            return 0
        
        if 1 == N:
            return nums[0]
        
        nums = [1] + nums + [1] # this trick is needed for bottom up solution
        N += 2
        
        memo = [None]*(N+1)
        
        # base case when there are only 1 left (nothing to blow)
        memo[1] = [0]*N
        # base case when there are only 2 left (nothing to blow)
        memo[2] = [0]*N
        # base case when there are only 3 left
        memo[3] = [nums[i]*nums[i+1]*nums[i+2] for i in range(N-2)]
        
        for k in range(4,N+1):
            # when there are k elements
            next_memo = [0]*(N+1)
            memo[k] = next_memo
            for lo in range(N-k+1):
                hi = lo+k-1
                base_score = nums[lo]*nums[hi]
                best_score = 0
                for mid in range(lo+1,hi):
                    best_score = max(memo[mid-lo+1][lo]+memo[hi-mid+1][mid]+base_score*nums[mid],best_score)
                next_memo[lo] = best_score
        return memo[N][0]
```

#### Bidirectional DP

- [Best time to buy and sell stock twice](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/)
- [Maximum sum of 3 non-overlapping subarrays](https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/)

#### Structural DP

- [Binary tree maximum path](https://leetcode.com/problems/binary-tree-maximum-path-sum/)

Decomposing a linked-list into buckets,

```python
from typing import TypeVar, Generic

HT = TypeVar('HT')

class LLDicompose(Generic[HT]):
    __slots__ = ['N', 'M', 'MBITS', 'buckets']
    def __init__(self, head:HT, M:int = 0b1111):
        self.M:int = M
        self.MBITS:int = 0
        while M:
            self.MBITS += 1
            M >>= 1
        ll,i = head,0
        self.buckets:List[HT] = []
        while ll:
            if (i&self.M) == 0:
                #print(i,'memo:',len(self.buckets),ll.val)
                self.buckets.append(ll)
            ll = ll.next
            i += 1
        self.N:int = i

    def __len__(self) -> int:
        return self.N

    def __getitem__(self, idx:int) -> HT:
        if idx < 0: # handle negative index
            idx = self.N+idx
        if idx > self.N:
            return None # handle out of bound
        i,ll = 0,self.buckets[0]

        bidx:int = idx >> self.MBITS
        if len(self.buckets) > bidx:
            i,ll = (bidx<<self.MBITS),self.buckets[bidx]

        #print(idx,'getitem:',bidx,i,ll.val)
        while ll:
            if i == idx:
                #print(idx,'item:',ll.val)
                return ll
            ll = ll.next
            i += 1

        return None
```

#### Interval DP

- [Largest Submatrix With Rearrangements](https://leetcode.com/problems/largest-submatrix-with-rearrangements/)

Lectures
=========

- [Dynamic programming](https://web.stanford.edu/class/archive/cs/cs161/cs161.1168/lecture12.pdf)
- [Full video course](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/)
    - [Fibonacci and shortest paths](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-19-dynamic-programming-i-fibonacci-shortest-paths)
    - [Text justification and blackjack](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-20-dynamic-programming-ii-text-justification-blackjack)
    - [Parenthesization, Edit distance and knapsack](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-21-dp-iii-parenthesization-edit-distance-knapsack)
    - [Guiter fingering, Tetris and Super Mario Bros](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-22-dp-iv-guitar-fingering-tetris-super-mario-bros)
    - [Coin change](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-046j-design-and-analysis-of-algorithms-spring-2015/recitation-videos/recitation-5-dynamic-programming-more-examples/)


