
Longest-common-subsequence is a special case of edit-distance problem.

Here is the visualization for `edit_distance.distance('tea', 'tree')`.

None |  root |  t | r | e | e
--- | --- | --- | --- | --- | ---
root | DIST(cost=0, op=' ') | DIST(cost=1, op='i') | DIST(cost=2, op='i') | DIST(cost=3, op='i') | DIST(cost=4, op='i')
t | DIST(cost=1, op='d') | DIST(cost=0, op='a') | DIST(cost=1, op='i') | DIST(cost=2, op='i') | DIST(cost=3, op='i')
e | DIST(cost=2, op='d') | DIST(cost=1, op='d') | DIST(cost=1, op='r') | DIST(cost=1, op='a') | DIST(cost=2, op='a')
a | DIST(cost=3, op='d') | DIST(cost=2, op='d') | DIST(cost=2, op='r') | DIST(cost=2, op='r') | DIST(cost=2, op='r')

More DP visualization [here](https://easyhard.github.io/dpv/).

Links
======

- [Edit distance](https://leetcode.com/problems/edit-distance/)
- [Hackerrank abbreviation](https://www.hackerrank.com/challenges/abbr/problem)
- [Minimum Adjacent Swaps for K Consecutive Ones](https://leetcode.com/contest/biweekly-contest-42/problems/minimum-adjacent-swaps-for-k-consecutive-ones/)
- [Minimize Hamming Distance After Swap Operations](https://leetcode.com/problems/minimize-hamming-distance-after-swap-operations/)

