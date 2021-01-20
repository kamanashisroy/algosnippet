
The bottom-up solution has `O(N*N)` time-complexity.

Here is the table for "abcab".

size |  (0, 'a') | (1, 'b') | (2, 'c') | (3, 'a') | (4, 'b')
---  |  --- | --- | --- | --- | ---
0  |  PMEMO(sz=1, lo=0, hi=0, s='a') | PMEMO(sz=1, lo=1, hi=1, s='b') | PMEMO(sz=1, lo=2, hi=2, s='c') | PMEMO(sz=1, lo=3, hi=3, s='a') | PMEMO(sz=1, lo=4, hi=4, s='b')
1  |  None | None | None | None | None
2  |  None | None | None | None | None
3  |  None | None | None | None | None
4  |  None | None | None | None | None


It is possible to accelerate via Dijkstra algorithm.

// TODO

- [Longest Palindromic Substring](https://leetcode.com/problems/longest-palindromic-substring)
