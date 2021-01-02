
Counting trailing zero
========================

GCC implementation `__builtin_ctz()`.

C++ implementation `std::ffs()-1`

The following python code is based on [lsb](../lsb) calculation.

```python
from bisect import bisect_left

class bit_twiddling:
    '''
    __slots__ = [_log_table]
    '''

    def __init__(self):
        self.log_table = [1<<i for i in range(128)]

    def log2(self, x):
        return bisect_left(self.log_table,x)

    def myctz(self, x):
        lsb = x & (-x) # keep only the rightmost bit set
        return self.log2(lsb)

if __name__ == '__main__':
    tw = bit_twiddling()

    for i in range(16):
        print(bin(i),tw.myctz(i))
```

Output

```
$ python python/ctz.py
0b0 0
0b1 0
0b10 1
0b11 0
0b100 2
0b101 0
0b110 1
0b111 0
0b1000 3
0b1001 0
0b1010 1
0b1011 0
0b1100 2
0b1101 0
0b1110 1
0b1111 0
```

Links
======

- [FFS](https://en.wikipedia.org/wiki/Find_first_set)

