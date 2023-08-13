
The Longest common proper-prefix building has elements of string searching algorithm.

```
def calcLongestProperSuffixArray(given: str) -> List[int]:
    '''
    LPS is used in Knuth Morris Pratt aglorithm
    
    If we convert the string of alphabet A, to a graph, then LCP length is the length of the longest cycle.

    
    Test case "aabaa" [0,1,0,1,2]
    Test case "aabaaac" [0, 1, 0, 1, 2, 1, 0]
    '''
    M = len(given)
    output = [0]*M
    
    for i in range(1,M):
        x = given[i]
        mlen = output[i-1]
        assert(mlen < M)
        y = given[mlen]
        #print(i, 'compare', x, y)
        if x == y:
            # increase lps length by one
            output[i] = output[i-1]+1
            #print(output)
        else:# mismatch
            # reset mlen
            #if x == given[0]:
            #    output[i] = 1
            while mlen > 0:
                mlen = output[mlen-1]
                #print(mlen,x,given[mlen])
                if x == given[mlen]:
                    mlen += 1
                    break
            output[i] = mlen
                
    return output

def strStr(haystack: str, needle: str) -> int:
    '''
    Knuth Morris Pratt aglorithm

    Needle     "aabaa"
    LPS array  [0,1,0,1,2]
    
    haystack   "aaaaaaaabaa"
    '''
    if 0 == len(needle): # sanity check
        return 0
    lps_array = calcLongestProperSuffixArray(needle)
    #print(needle,lps_array)
    
    mlen = 0
    for i,x in enumerate(haystack):
        if x == needle[mlen]:
            mlen += 1
        else: # mismatch case
            #print('mismatch case,lookup lps_array',mlen)
            while mlen > 0:
                mlen = lps_array[mlen-1]
                #print(mlen,x,needle[mlen])
                if x == needle[mlen]:
                    mlen += 1
                    break
        #print(x,mlen)
        if mlen == len(needle):
            return i-mlen+1
    return -1
```
