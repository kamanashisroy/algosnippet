
def longestCommonSubsequence(self, text1: str, text2: str) -> int:

    LEN1 = len(text1)
    LEN2 = len(text2)

    memo = [[0]*(LEN2+1) for i in range(LEN1+1)]

    for i,x in enumerate(text1):
        for j,y in enumerate(text2):
            if x == y:
                memo[i+1][j+1] = memo[i][j] + 1
            else:
                memo[i+1][j+1] = max(memo[i][j+1],memo[i+1][j])

    return memo[LEN1][LEN2]
