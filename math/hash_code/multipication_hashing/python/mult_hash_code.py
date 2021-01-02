#!python

from random import randint

class mult_hash_code:
    '''
    __slots__ = ['a','r','M']
    '''
    def __init__(self, M, SZ=32):
        self.a = randint(2**(SZ-1),2**(SZ))
        self.r = mult_hash_code.num_bits(M)
        self.M = M

    def num_bits(x):
        '''
        Calculate the size of(x) in log(x) time
        '''
        if 0 == x: # base case
            return 0

        hi = 128
        lo = 0

        while lo != hi:
            if (1+lo) == hi: # cannot divide
                if (-(1<<lo)) & x:
                    return hi
                else:
                    return lo
                

            mid = (lo+hi) >> 1

            if (-(1<<mid)) & x:
                lo = mid+1
            else:
                hi = mid

        return lo

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

if __name__ == '__main__':


    M = 15
    N = 100
    count1 = [0]*M
    count2 = [0]*(1+M)

    mf = mult_hash_code(M)
    print(mf)

    for i in range(N):
        count1[mf.hash_code(i+1)] += 1
        count2[mf.hash_code_fast(i+1)] += 1

    print(count1)
    print(count2)
    '''
    output 
    [10, 8, 9, 9, 9, 10, 10, 12, 12, 11]
    [9, 11, 10, 11, 10, 10, 9, 10, 9, 11]
    [11, 10, 10, 10, 10, 10, 9, 10, 10, 10]
    '''



