

class RollingHash:
    '''
    rk_best.py file is part of Algosnippet.
    Algosnippet is a collection of practice data-structures and algorithms
    Copyright (C) 2025  Kamanashis Roy
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

    def __init__(self, q):
        QN = len(q)
        suffixMemo = [0]*(QN+1)
        mul = [1]

        BIG,SMALL = 1000000007,31
        hcode = 0
        xmul = 1
        for i in range(QN-1,-1,-1):
            hcode *= SMALL
            hcode += (q[i]+1)
            hcode %= BIG
            suffixMemo[i] = hcode
            xmul *= SMALL
            xmul %= BIG
            mul.append(xmul)
        self.suffixMemo = suffixMemo
        self.mul = mul
        self.QN = QN
        self.BIG = BIG
        self.SMALL = SMALL
    
    def substr(self, beg, end ):
        if end <= beg:
            return 0
        if end >= self.QN:
            return self.suffixMemo[beg]

        begPart = self.suffixMemo[beg]
        endPart = self.suffixMemo[end]

        endPart *= self.mul[end-beg]
        endPart %= self.BIG
        
        if begPart < endPart:
            begPart += self.BIG
        return begPart - endPart


