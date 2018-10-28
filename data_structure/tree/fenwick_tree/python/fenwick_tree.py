#!/bin/python3
# vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

'''
fenwick_tree.py file is part of Algosnippet.
Algosnippet is a collection of practice data-structures and algorithms
Copyright (C) 2018  Kamanashis Roy
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



class fenwick_tree:
    '''
    Fenwick tree is implicit data-structure that operates(update,query) in O(log(n)) time and O(n) space.

    It is comparable with prefix-array. While the prefix-array can be queried in O(1) time, it needs O(n) update time. 

    Fenwick tree can additionally be used for range-minimum query. It is comparable to square-root decomposition. While square-root decomposition takes O(sqrt(n)) space, it needs O(1) update time. The query time is O(sqrt(n)) which is bigger than Fenwick tree.
    '''
    __slots__ = ["binary_indexed_array", "base_array"]
    def __init__(self,max_size,defaultval=0):
        self.binary_indexed_array = [defaultval]*max_size

        # Note that base array is not needed in sum query and can be skipped
        self.base_array = [defaultval]*max_size

    def update_min(self, idx, xval):
        '''
        [ 1   2   3   4   5   6   7   8 ] = 1 based index
         -------------------------------
          1*  0   1*  0   1*  0   1*  0 | Binary representation of 1 based(Pascal) index
              1*  1   0   0   1*  1   0 |
                      1*  1   1   1   0 | The * represents the summary level
                                      1*|
         -------------------------------
        [ 1   3   4   8   6   1   4   2 ] = user array
        [ 1   1   4   1   6   1   4   1 ] = Fenwick tree or binary indexed tree for range-min
          ^   ^   ^   ^   ^   ^   ^   ^
        ---   | ---   | ---   | ---   |
        -------       | -------       |
        ---------------               |
        -------------------------------
        '''
        self.base_array[idx] = xval # update base array
        k = idx+1 # convert to pascal index
        while k<=len(self.binary_indexed_array):
            # get least significant bit
            if self.binary_indexed_array[k-1] <= xval:
                break # heap property holds
            self.binary_indexed_array[k-1] = xval
            k += (k & -k)

    def query_min(self, start_idx, end_idx):
        '''
        Suppose we query minimum of 5 to 7
        [ 1   2   3   4   5   6   7   8 ] = 1 based index
         -------------------------------
          1*  0   1*  0   1*  0   1*  0 | Binary representation of 1 based(Pascal) index
              1*  1   0   0   1*  1   0 |
                      1*  1   1   1   0 | The * represents the summary level
                                      1*|
         -------------------------------
        [ 1   3   4   8   6   1   4   2 ] = user array
        [ 1   1   4   1   6   1   4   1 ] = Fenwick tree or binary indexed tree
          ^   ^   ^   ^   ^   ^   ^   ^
        ---   | ---   | ---   | ***   |  Suppose we are quering min of 4(pascal index 5) to 6(pascal index 7),
        -------       | *******       |  we use the stared path
        ---------------               |
        -------------------------------

        Another query
          ^   ^   ^   ^   ^   ^   ^   ^
        ---   | ***   | ***   | ---   |  Suppose we are quering min of 2(pascal index 3) to 4(pascal index 5),
        -------       | -------       |  we use the starred path, something that is not starred, is collected from base_array
        ---------------               |
        -------------------------------
        '''
        assert start_idx < end_idx
        assert end_idx < len(self.base_array)

        # very tricky

        dist = end_idx-start_idx+1
        k = end_idx+1 # convert to pascal index
        result = self.base_array[end_idx]
        while k>=(start_idx+1):

            # when the memo covers the start_idx , we cannot use it
            if dist < (k & -k):
                # use base_array
                result = min(result, self.base_array[k-1])
                dist -= 1
                k -= 1 # try to get next memo
            else:
                # use memo
                result = min(result,self.binary_indexed_array[k-1])
                dist -= (k & -k)
                k -= (k & -k)
        return result
                
                

    def update_sum(self, idx, xval):
        '''
        [ 1   2   3   4   5   6   7   8 ] = 1 based(Pascal) index
         -------------------------------
          1*  0   1*  0   1*  0   1*  0 | Binary representation of 1 based(Pascal) index
              1*  1   0   0   1*  1   0 |
                      1*  1   1   1   0 | The * represents the summary level
                                      1*|
         -------------------------------
        [ 1   3   4   8   6   1   4   2 ] = user array
        [ 1   4   4  16   6   7   4  29 ] = Fenwick tree or binary indexed tree
          ^   ^   ^   ^   ^   ^   ^   ^
        ---   | ---   | ---   | ---   |
        -------       | -------       |
        ---------------               |
        -------------------------------
        '''
        k = idx+1 # convert to pascal index
        while k<=len(self.binary_indexed_array):
            # get least significant bit
            self.binary_indexed_array[k-1] += xval
            k += (k & -k)

    def query_sum(self, idx):
        k = idx+1 # convert to pascal index
        result = 0
        while k:
            result += self.binary_indexed_array[k-1]
            k -= (k & -k)
        return result
            
    def __repr__(self):
        return "[Fenwick-tree(" + str(self.binary_indexed_array) + ")]"

    def __str__(self):
        return "[Fenwick-tree(" + str(self.binary_indexed_array) + ")]"

if __name__ == "__main__":
    data = [1,3,4,8,6,1,4,2]
    print("Making fenwick-sum tree for", data)
    ftree = fenwick_tree(len(data),0)
    for i,x in enumerate(data):
        ftree.update_sum(i,x)
        print(ftree)

    assert(ftree.query_sum(0) == 1)
    assert(ftree.query_sum(1) == 4)
    assert(ftree.query_sum(2) == 8)
    assert(ftree.query_sum(3) == 16)
    assert(ftree.query_sum(4) == 22)
    assert(ftree.query_sum(5) == 23)
    assert(ftree.query_sum(6) == 27)
    assert(ftree.query_sum(7) == 29)

    print("Making fenwick-min tree for", data)
    ftree = fenwick_tree(len(data),max(data)+1)
    for i,x in enumerate(data):
        ftree.update_min(i,x)
        print(ftree)

    assert(ftree.query_min(4,6) == 1)
    assert(ftree.query_min(2,4) == 4)
    assert(ftree.query_min(3,4) == 6)
 
    print("successful")
