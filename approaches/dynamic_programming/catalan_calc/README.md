
Catalan number
==============

```python
class catalan:
    def __init__(self, n):
        '''
        Cost is O(n*n)
        '''
        self.memo = [0]*n

        self.memo[0] = 1 # base case catalan number for 0
        self.memo[1] = 1 # catalan number for 1
        for i in range(2,n):
            for j in range(i):
                self.memo[i] += self.memo[j]*self.memo[i-j-1]

    def get(n):
        '''
        Get memo on O(1) time
        '''
        return self.memo[n]
```

First 10 catalan numbers,

```
[1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862]
```

For example 4 character string can be paranthesized in 5 different ways,

```
((ab)c)d     (a(bc))d     (ab)(cd)     a((bc)d)     a(b(cd))
```
