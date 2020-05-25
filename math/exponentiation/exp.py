#!python

class kernel:
    def __init__(self, x):
        '''
        Here we create a table in constant time
        '''
        self.table = [1]*(33) # calculate power for 32 bit number
        self.table[1] = x

        for xpow in range(2,33):
            self.table[xpow] = (self.table[xpow-1]*self.table[xpow-1])%1000000007

    def calc_fast_pow(self, exp):
        '''
        This step takes O(log exp) operations
        '''
        result = 1
        for i in range(0,11):
            if (1<<i) & exp:
                result = (result*self.table[i+1])%1000000007
        return result


if __name__ == "__main__":
    krn = kernel(3)
    print(krn.table)
    print(krn.calc_fast_pow(7))
