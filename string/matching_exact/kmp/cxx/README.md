
Knuth Morris Pratt Algorithm
================================
This algorithm uses a precalcualted table to decide the state of the searching. The table creation takes Theta(|substring|) asymbtotic time and the searching takes Theta(|string|).

Longest Common Prefix table
============================

The longest common prefix table allow restart matching from partial LCP match.

```
            //! \brief calculate lcp table for given pattern
            void make_lcp_table() {
                // sanity check
                if(pat.size() == 0) {
                    return;
                }
                // Suppose the pattern               = XXXXYXXZZZ
                // Now a proper prefix               = XXXXYXX
                // LCP of the suffixes of prefix     =      XX
                // length                            =       2

                // If we convert the string of alphabet A, to a graph, then LCP length is the length of the longest cycle.

                lcp_len.resize(pat.size(),0);
                for(unsigned int i = 1; i < pat.size(); i++) {
                    if(pat[i] == pat[lcp_len[i-1]]) {
                        // increase the pattern length by adding from previous
                        lcp_len[i] = lcp_len[i-1]+1;
                    } else {
                        lcp_len[i] = (pat[i] == pat[0])?1:0;
                    }
                    assert(lcp_len[i] >= 0 && lcp_len[i] < (int)(pat.size()));
                }
            }
```

Links
======

- [KMP-LCP Problem](https://www.hackerrank.com/challenges/kmp-problem/problem)

