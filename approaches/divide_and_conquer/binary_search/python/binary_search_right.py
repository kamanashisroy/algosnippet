#!/usr/bin/env python

'''
bin_search_right.py file is part of Algosnippet.
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

def bin_search_right(content, pvt, begin=0, end=None):
    '''
    Algorithm searches in the range [begin,end) .

    Returns the first index of x where pvt < content[x]
            , otherwise returns end when all elements are smaller or equal.
    '''
    # avoid overflow
    end = len(content) if end is None else min(end,len(content))

    while (begin+1) < end:
        # divide
        mid = (begin+end) >> 1

        if content[mid] <= pvt:
            # skip left content
            begin = mid
        else: # when pvt < content[mid]:
            # skip right contents
            end = mid
 
    return begin if pvt < content[begin] else (begin+1)
    

if __name__ == "__main__":
    assert bin_search_right([1,2,3,4,5], 6) == 5, "Failed"
    assert bin_search_right([1,2,3,4,5], 5) == 5, "Failed"
    assert bin_search_right([1,2,3,4,5], 4) == 4, "Failed"
    assert bin_search_right([1,2,3,4,5], 3) == 3, "Failed"
    assert bin_search_right([1,2,3,4,5], 2) == 2, "Failed"
    assert bin_search_right([1,2,3,4,5], 1) == 1, "Failed"
    assert bin_search_right([1,2,3,4,5], 0) == 0, "Failed"
    print("Successful")
    
