
Fenwick tree is implicit data-structure that operates(update,query) in O(log(n)) time and O(n) space.

#### Example of Fenwick tree

```
        [ 1   2   3   4   5   6   7   8 ] = 1 based(Pascal) index
         -------------------------------
          1*  0   1*  0   1*  0   1*  0 | Binary representation of 1 based(Pascal) index
              1*  1   0   0   1*  1   0 |
                      1*  1   1   1   0 | The * represents the summary level
                                      1*|
         -------------------------------
        [ 1   3   4   8   6   1   4   2 ] = user array
        [ 1   4   4  16   6   7   4  29 ] = Fenwick tree or binary indexed tree
          ^   ^   ^   ^   ^   ^   ^   ^
        ---   | ---   | ---   | ---   |
        -------       | -------       |
        ---------------               |
        -------------------------------
```

Here is the output of the test-app,

```
('Making fenwick tree for', [1, 3, 4, 8, 6, 1, 4, 2])
[Fenwick-tree([1, 1, 0, 1, 0, 0, 0, 1])]
[Fenwick-tree([1, 4, 0, 4, 0, 0, 0, 4])]
[Fenwick-tree([1, 4, 4, 8, 0, 0, 0, 8])]
[Fenwick-tree([1, 4, 4, 16, 0, 0, 0, 16])]
[Fenwick-tree([1, 4, 4, 16, 6, 6, 0, 22])]
[Fenwick-tree([1, 4, 4, 16, 6, 7, 0, 23])]
[Fenwick-tree([1, 4, 4, 16, 6, 7, 4, 27])]
[Fenwick-tree([1, 4, 4, 16, 6, 7, 4, 29])]
successful
```


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
- [Hackerrank Neighborhood queries](https://www.hackerrank.com/contests/w38/challenges/neighborhood-queries)
 
