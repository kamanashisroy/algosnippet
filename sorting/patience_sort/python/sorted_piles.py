#!python

from typing import TypeVar,Generic
from collections import deque

SPXT = TypeVar('SPXT')

class sorted_piles(Generic[SPXT]):
    __slots__ = ['piles','count']
    def __init__(self):
        self.piles = []
        self.count = 0
    
    def __len__(self) -> int:
        return self.count

    def max(self) -> SPXT:
        if self.piles:
            return self.piles[-1][-1]
        return None
        
    def bisect_end(self,elem:SPXT) -> int:
        '''
        Finds the position where the element should be inserted
        '''
        if not self.piles:
            return -1
        # binary search insert position
        lo:int = 0
        hi:int = len(self.piles)
        
        while lo < hi:
            if (lo+1) == hi:
                break
            mid:int = (lo+hi) >> 1
            if self.piles[mid][-1] == elem:
                return mid
            elif self.piles[mid][-1] < elem:
                lo = mid
            else:
                hi = mid
        return lo
    
    def bisect_begin(self,elem:SPXT) -> int:
        '''
        Finds the position where the element could be inserted at the beginning
        '''
        if not self.piles:
            return -1
        # binary search insert position
        lo:int = 0
        hi:int = len(self.piles)
        
        while lo < hi:
            if (lo+1) == hi:
                break
            mid:int = (lo+hi) >> 1
            if self.piles[mid][0] == elem:
                return mid
            elif self.piles[mid][0] > elem:
                lo = mid
            else:
                hi = mid
        return lo

    def insort_end(self, elem:SPXT) -> None:
        '''
        Insert a new element in the sorted piles
        '''
        idx:int = self.bisect_end(elem)
        if -1 != idx and self.piles[idx][-1] <= elem:
            self.piles[idx].append(elem)
        else:
            pile = deque()
            pile.append(elem)
            self.piles.insert(idx+1,pile)
        
    def insort_begin(self, elem:SPXT) -> None:
        '''
        Insert a new element in the sorted piles using appendleft
        '''
        idx:int = self.bisect_begin(elem)
        if -1 != idx and self.piles[idx][0] >= elem:
            self.piles[idx].appendleft(elem)
        else:
            pile = deque()
            pile.append(elem)
            self.piles.insert(idx+1,pile)
        
        self.count += 1

    def insort(self, elem:SPXT) -> None:
        idx:int = self.bisect_end(elem)
        if -1 != idx and self.piles[idx][-1] <= elem:
            self.piles[idx].append(elem)
        else:
            idx:int = self.bisect_begin(elem)
            if -1!= idx and self.piles[idx][0] >= elem:
                self.piles[idx].appendleft(elem)
            else:
                pile = deque()
                pile.append(elem)
                self.piles.insert(idx+1,pile)
        
    def count_smaller(self, elem:SPXT) -> int:
        '''
        Calculate the number of smaller elements in the pile
        '''
        rank = 0
        for pile in self.piles:
            idx = bisect.bisect_left(pile,elem)
            if -1 != idx:
                rank += idx
        
        return rank

