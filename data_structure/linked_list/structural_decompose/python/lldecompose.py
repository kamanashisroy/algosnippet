#!python

from typing import TypeVar, Generic

HT = TypeVar('HT')

class LLDicompose(Generic[HT]):
    __slots__ = ['N', 'M', 'MBITS', 'buckets']
    def __init__(self, head:HT, M:int = 0b1111):
        self.M:int = M
        self.MBITS:int = 0
        while M:
            self.MBITS += 1
            M >>= 1
        ll,i = head,0
        self.buckets:List[HT] = []
        while ll:
            if (i&self.M) == 0:
                #print(i,'memo:',len(self.buckets),ll.val)
                self.buckets.append(ll)
            ll = ll.next
            i += 1
        self.N:int = i
        
    def __len__(self) -> int:
        return self.N
    
    def __getitem__(self, idx:int) -> HT:
        if idx < 0: # handle negative index
            idx = self.N+idx
        if idx > self.N:
            return None # handle out of bound
        i,ll = 0,self.buckets[0]
        
        bidx:int = idx >> self.MBITS
        if len(self.buckets) > bidx:
            i,ll = (bidx<<self.MBITS),self.buckets[bidx]
            
        #print(idx,'getitem:',bidx,i,ll.val)
        while ll:
            if i == idx:
                #print(idx,'item:',ll.val)
                return ll
            ll = ll.next
            i += 1
            
        return None


