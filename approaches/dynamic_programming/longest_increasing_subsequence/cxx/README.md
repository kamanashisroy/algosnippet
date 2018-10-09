
Longest common subsequence
============================

Dynamic programming takes `O(n*n)` time.

```
for(int i = 1; i < n; i++) {
    for(int j = 0; j < i; j++) {
        if(arr[i] > arr[j]) { // build-up on previous optimization
            if(memo_len[i] < (memo_len[j]+1)) {
                // relaxation
                memo_len[i] = memo_len[j]+1;
                result = std::max(result,memo_len[i]);
            }
        }
    }
}
```
It also contains a binary search based solution that runs in `O(n log n)` time.

[Hackerank problem link](https://www.hackerrank.com/challenges/longest-increasing-subsequent/problem)




