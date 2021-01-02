
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
        right_most = x & (-x) # keep only the rightmost bit set
        return self.log2(right_most)

if __name__ == '__main__':
    tw = bit_twiddling()

    for i in range(16):
        print(bin(i),tw.myctz(i))
