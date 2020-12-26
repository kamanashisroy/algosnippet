def coinChange(self, coins: List[int], amount: int) -> int:
    N = len(coins)
    memo = [-1]*(amount+1)
    memo[0] = 0
    for i in range(1,amount+1):
        for c in coins:
            if i >= c and -1 != memo[i-c] and (-1 == memo[i] or memo[i] > (memo[i-c]+1)):
                memo[i] = memo[i-c]+1
    return memo[amount]
