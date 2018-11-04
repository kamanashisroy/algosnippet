#!/usr/bin/env python

'''
bin_search_equal.py file is part of Algosnippet.
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

def bin_search_equal(content, pvt, begin=0, end=None):
    '''
    It searches for the exact match in sorted content.
    Returns the index of exact match, None otherwise
    '''
    end = len(content) if end is None else min(end,len(content))

    while (begin+1) < end:
        mid = (begin+end)>>1

        if content[mid] == pvt:
            return mid
        elif content[mid] < pvt:
            # skip left
            begin = mid
        else: # when pvt < content[mid]
            end = mid
    
    return begin if content[begin] == pvt else None

if __name__ == "__main__":
    assert bin_search_equal([1,2,3,4,5], 6) is None, "Failed"
    assert bin_search_equal([1,2,3,4,5], 5) == 4, "Failed"
    assert bin_search_equal([1,2,3,4,5], 4) == 3, "Failed"
    assert bin_search_equal([1,2,3,4,5], 3) == 2, "Failed"
    assert bin_search_equal([1,2,3,4,5], 2) == 1, "Failed"
    assert bin_search_equal([1,2,3,4,5], 1) == 0, "Failed"
    assert bin_search_equal([1,2,3,4,5], 0) is None, "Failed"

    content = [1,2,2,5,5]
    assert content[bin_search_equal(content, 5)] == 5, "Failed"
    assert content[bin_search_equal(content, 2)] == 2, "Failed"
    print("Successful")
    
