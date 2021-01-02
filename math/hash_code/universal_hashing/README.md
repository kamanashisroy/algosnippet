

Universal hash function gives points on a straight line `y=ax+b`.

```python
#!python

from random import randint

class universal_hash_function:
    '''
    a and b are random number in range 1 < a,b < big_prime

    __slots__ = ['a','b','big_prime']
    '''
    def __init__(self, big_prime=1000000007):
        self.a = randint(1,big_prime-1)
        self.b = randint(1,big_prime-1)
        self.big_prime = big_prime

    def hash_code(self, k):
        return (self.a*k+self.b)%self.big_prime

    def distribute(self, k,m):
        '''
        In worst case, probability of collision is 1/m
        '''
        return self.hash_code(k)%m

if __name__ == '__main__':

    hf = universal_hash_function()

    M = 10
    N = 100
    count = [0]*M

    for i in range(N):
        count[hf.distribute(i+1,M)] += 1

    print(count)
    '''
    output 
    [10, 8, 9, 9, 9, 10, 10, 12, 12, 11]
    [9, 11, 10, 11, 10, 10, 9, 10, 9, 11]
    [11, 10, 10, 10, 10, 10, 9, 10, 10, 10]
    '''

```

Notice that in each bucket, there are almost `N/M` elements, where `load factor = N/M`.

#### Probability of collision

Probability of collision is equals to `1/m`

```
Pr(a,b){h(k1) == h(k2)} = 1/m
```



