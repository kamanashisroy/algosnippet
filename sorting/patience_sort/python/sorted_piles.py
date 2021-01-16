#!python

from typing import TypeVar,Generic

SPXT = TypeVar('SPXT')

class sorted_piles(Generic[SPXT]):
    __slots__ = ['piles']
    def __init__(self):
        self.piles = []

    def bisect_right(self,elem:SPXT) -> int:
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
    
    def insort(self, elem:SPXT) -> None:
        '''
        Insert a new element in the sorted piles
        '''
        idx:int = self.bisect_right(elem)
        if -1 != idx and self.piles[idx][-1] <= elem:
            self.piles[idx].append(elem)
        else:
            self.piles.insert(idx+1,[elem])

    def calc_rank(self, elem:SPXT) -> int:
        '''
        Calculate the number of smaller elements in the pile
        '''
        rank = 0
        for pile in self.piles:
            idx = bisect.bisect_left(pile,elem)
            if -1 != idx:
                rank += idx
        
        return rank
