
While multiplication the mixing of the bits happen in the middle of multiplication output.


```
        0b0101010101    = k
             * 0b101    = a (a is some constant)
-----------------------------------------------
        0b0101010101
       0b0000000000
    + 0b0101010101
-----------------------------------------------
          [mixing]
```

```python

class mult_hash_code:
    '''
    __slots__ = ['a','r','M']
    '''
    def __init__(self, M, SZ=32):
        self.a = randint(2**(SZ-1),2**(SZ))
        self.r = mult_hash_code.num_bits(M)
        self.M = M

    def hash_code_fast(self, k):
        '''
        Fast implementation works only when M is (power of 2)
        '''
        w = mult_hash_code.num_bits(k)
        #print(bin(k),w,self.r,bin(~(-(1<<w))))
        result = ((k*self.a) & ~(-(1<<w))) >> max(0,w-self.r)
        #print(bin(result))
        return result

    def hash_code(self, k):
        w = mult_hash_code.num_bits(k)
        return ((k*self.a) %(1<<w)) % self.M

    def __repr__(self):
        return '<mult_hash_code M=%s,a=%d,r=%d>' %(bin(self.M),self.a,self.r)

'''
python python/mult_hash_code.py
<mult_hash_code M=0b1111,a=2811226237,r=4>
[10, 9, 5, 13, 7, 3, 11, 5, 3, 10, 5, 2, 10, 5, 2]
[6, 7, 9, 11, 6, 8, 10, 5, 5, 4, 4, 3, 7, 5, 3, 7]
'''
```



Links
======

- [Why multiplication](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-8-hashing-with-chaining/)
