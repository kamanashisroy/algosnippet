
Manber Myer algorithm for Suffix-array
===========================================

Here is the [reference](https://www.hackerrank.com/challenges/string-similarity/topics).

The sorting could be made faster by 3 way quick sort by not disrupting the already sorted parts.

LCP Array calculation
================

LCP array is an array containing the *longest common prefix* of the sorted suffix that matches with the previous/next suffix. Note that when calculated in decreasing length of suffix, the lcp length is at least the `previous lcp length - 1`.

```
            //! \NOTE this should be followed by after sort_suffix()
            void calculate_lcp() {
                for(unsigned int i = 0; i < content.size(); ++i) {
                    if(0 == lookup_sfx[i].suffix_rank) {
                        continue; // we are the first of the suffix array so lcp = 0
                    }
                    if(i && lookup_sfx[i-1].lcp > 1) {
                        lookup_sfx[i].lcp = lookup_sfx[i-1].lcp-1;
                    }
                    for(unsigned int j = i+lookup_sfx[i].lcp, k = ordered_sfx[lookup_sfx[i].suffix_rank-1].get().idx+lookup_sfx[i].lcp; j < content.size() && k < content.size(); j++,k++) {
                        if(content[j] == content[k]) {
                            lookup_sfx[i].lcp++;
                        } else {
                            break;
                        }
                    }
                }
```

Program output,

```
Suffix array of mississippi
10:i,lcp:0
7:ippi,lcp:1
4:issippi,lcp:1
1:ississippi,lcp:4
0:mississippi,lcp:0
9:pi,lcp:0
8:ppi,lcp:1
6:sippi,lcp:0
3:sissippi,lcp:2
5:ssippi,lcp:1
2:ssissippi,lcp:3

Suffix array of banana
5:a,lcp:0
3:ana,lcp:1
1:anana,lcp:3
0:banana,lcp:0
4:na,lcp:0
2:nana,lcp:2

successful 
```

