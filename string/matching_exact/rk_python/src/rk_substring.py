
PRIME1 = 31
PRIME2 = 1000000007
class RKHash:
    '''
    rk.py file is part of Algosnippet.
    Algosnippet is a collection of practice data-structures and algorithms
    Copyright (C) 2021  Kamanashis Roy
    Algosnippet is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    Algosnippet is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with Algosnippet.  If not, see <https://www.gnu.org/licenses/>.
    '''

    def __init__(self):
        self.val = 0
        self.sz  = 0
        self.mul = 1
    
    def append(self, intval):
        self.val *= PRIME1
        self.val += intval+1
        self.val %= PRIME2
        self.sz  += 1
        self.mul *= PRIME1
        self.mul %= PRIME2
    
    def prepend(self, intval):
        self.val += (intval+1)*self.mul
        self.val %= PRIME2
        self.sz  += 1
        self.mul *= PRIME1
        self.mul %= PRIME2
    
    def __hash__(self):
        return (self.val,self.sz)
    
    def key(self):
        return (self.val,self.sz)

    def copy(self):
        ret = RKHash()
        ret.val = self.val
        ret.sz  = self.sz
        ret.mul = self.mul
        return ret
    
    def test(self):
        sample = [1,2,3,4,5]
        rk1,rk2 = RKHash(),RKHash()
        for x in sample:
            rk1.append(x)
        for x in reversed(sample):
            rk2.prepend(x)
        assert(rk1.val == rk2.val)
        assert(rk1.sz == rk2.sz)

class RKSubstringHash:
    '''
    Allow lookup hash of a substring.
    With substring we can binary search for longest match.
    Example here https://leetcode.com/problems/minimum-number-of-valid-strings-to-form-target-ii/submissions/
    '''
    def __init__(self, given):
        self.N = len(given)    
        self.rkprefix = [0]*self.N
        self.rkmul    = [0]*self.N
        rk = RKHash()
        for i,x in enumerate(given):
            rk.append(x)
            self.rkprefix[i] = rk.key()
            self.rkmul[i] = rk.mul

        self.rksuffix = [0]*self.N
        rk = RKHash()
        for i in range(self.N-1,-1,-1):
            rk.prepend(given[i])
            self.rksuffix[i] = rk.key()
    
    def test_substring(self, given, beg:int,end:int):
        assert(beg<end)
        rk = RKHash()
        for i in range(beg,end):
            rk.append(given[i])
        #print(self.rksuffix)
        subkey = self.substring(beg,end)
        print(beg,end,'test_substring', given[beg:end] , rk.key(), subkey)
        assert(rk.key() == subkey)
        
    def substring(self, beg:int,end:int):
        assert(beg<end)
        if end >= self.N:
            #print('substring returning suffix', self.rksuffix)
            return self.rksuffix[beg]
        if 0 == beg:
            return self.rkprefix[end-1]
        
        eprefix = self.rkprefix[end-1][0]
        bprefix = self.rkprefix[beg-1][0]
        bprefix *= self.rkmul[end-beg-1]
        bprefix %= PRIME2
        rval = (eprefix-bprefix)%PRIME2
        return (rval,end-beg)


