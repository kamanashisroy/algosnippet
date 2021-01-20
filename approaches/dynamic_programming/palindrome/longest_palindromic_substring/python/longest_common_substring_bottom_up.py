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
