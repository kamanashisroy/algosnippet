
Repeat-sum solution
===================

This is also called the coin change problem.

```
    def coinChange(self, coins: List[int], amount: int) -> int:
        N = len(coins)
        memo = [-1]*(amount+1)
        memo[0] = 0
        for i in range(1,amount+1):
            for c in coins:
                if i >= c and -1 != memo[i-c] and (-1 == memo[i] or memo[i] > (memo[i-c]+1)):
                    memo[i] = memo[i-c]+1
        return memo[amount]
```

It is very similar to Bellman Ford algorithm.

This problem is not greedy.

Links
===========

- [Number of dice rolls with target sum](https://leetcode.com/problems/number-of-dice-rolls-with-target-sum/)
- [Coin change](https://leetcode.com/problems/coin-change/)
- [Jump Game VI](https://leetcode.com/problems/jump-game-vi/)
- [Number of Dice Rolls With Target Sum](https://leetcode.com/problems/number-of-dice-rolls-with-target-sum/)

