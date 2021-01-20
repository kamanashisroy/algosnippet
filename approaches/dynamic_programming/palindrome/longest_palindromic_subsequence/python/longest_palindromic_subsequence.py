#!python

from collections import namedtuple
PMEMO = namedtuple('PMEMO','sz,lo,hi,s')
class Solution:
    def longestPalindromeSubseq(self, s: str) -> int:
        N,memo = len(s),[]
        
        # odd palindrome base
        memo.append([PMEMO(lo=i,hi=i,sz=1,s=s[i:i+1]) for i in range(N)])
        
        # even palindrome base
        even_memo = memo[-1][:]
        memo.append(even_memo)
        for i in range(N-1):
            if s[i] == s[i+1]:
                even_memo[i] = PMEMO(lo=i,hi=i+1,sz=2,s=s[i:i+2])

        for k in range(2,N):
            enclosed_memo,next_memo = memo[-2],memo[-1][:]
            memo.append(next_memo)
            for lo in range(N-1):
                curr = next_memo[lo] = max(next_memo[lo],next_memo[lo+1])
                if (lo+k) < N:
                    hi = lo+k
                    if s[lo] == s[hi]:
                        prev = enclosed_memo[lo+1]
                        next_memo[lo] = max(curr, PMEMO(lo=lo,hi=hi,sz=prev.sz+2,s=s[lo]+prev.s+s[hi]))
        print('size | ', ' | '.join([str((i,x)) for i,x in enumerate(s)]))
        print('---  | ', ' | '.join(['---']*N))
        for k,m in enumerate(memo):
            print(k, ' | ', ' | '.join(map(str,m)))
        return max(memo[-1]).sz
