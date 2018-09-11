#!/bin/python3
# vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

'''
kary_heap_lazy.py file is part of Algosnippet.

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


import math
import os
import random
import re
import sys
import collections
from heapq import heapify,heappush,heappop

class kary_heap_lazy(kary_heap):
    __slots__ = "cache"
    def __init__(self,order):
        kary_heap.__init__(self,order)
        self.cache = []

    def __len__(self):
        return len(self.heap)+len(self.cache)

    def __bool__(self):
        return bool(self.heap) and bool(self.cache)

    def __insert_cache(self):
        if self.cache:
            # O(n)
            heapify(self.cache)
            kary_heap.append(self.cache);
            self.cache = []
    
    def peek(self):
        self.__insert_cache()
        return self.heap[0][0] if self.heap else None
    
    def append(self,x):
        # sanity check
        if x is None:
            return False

        self.cache.append(x)
        return True

    def popleft(self):
        output = self.peek()
        if self.heap:
            heappop(self.heap[0]) # pop the top
            if self.heap[0]:
                self.__down_heap(0)
            else:
                kary_heap.popleft(self)
        return output


