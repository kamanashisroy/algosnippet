
Segment tree can be implicit when the Universe is static. That is it can be built into an array. In that case the child/parent can be accessed like binary-heap.


Comparison of different range structures
===========================================

 Operation            | Fenwick tree                  | sqrt decomposition (bucketing)| Prefix-array                 | Segment tree                   | Lazy Propagation Seg. tree  | Quick Select             | Heap (binary)
 ---                  | ---                           | ---                           | ---                          | ---                            | ---                         | ---                      | ---
 Space                | O(n) (implicit)               | O(sqrt(n)) (implicit)         | O(n) (implicit)              | O(n) (implicit/explicit)       | O(n) (implicit/explicit)    | O(n) (implicit)          | O(n) (implicit)
 Update               | O(log(n))                     | O(1)                          | O(n)                         | O(log(n))                      | O(1)                        | 1                        | O(log(n))
 Query sum            | O(log(n))                     | O(sqrt(n))                    | O(1)                         | O(log(n))                      | O(log(n))                   | NA                       | NA
 Query min/max        | O(log(n)) (Complex)           | O(sqrt(n))                    | NA                           | O(log(n))                      | O(log(n))                   | O(n)                     | O(1) (not ranged)
 Query k-th(using sum)| O(log(n))                     | O(sqrt(n))                    | O(log(n)) binary search      | O(log(n))                      | O(log(n))                   | O(k)                     | O(k log n) (pop k elements), or `3*k` refer to Skiena book

Links
======

- [Hackerrank Cyclical queries](https://www.hackerrank.com/contests/w38/challenges/cyclical-queries/problem)
- [Neighborhood queries](https://www.hackerrank.com/contests/w38/challenges/neighborhood-queries)
- Hard [Count Good Triplets in an Array](https://leetcode.com/problems/count-good-triplets-in-an-array/)
- Hard [Count Integers in Intervals](https://leetcode.com/problems/count-integers-in-intervals/)
