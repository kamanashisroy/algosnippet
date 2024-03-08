'''
suffix_array.py file is part of Algosnippet.
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



from dataclasses import dataclass
from typing import Generic,TypeVar,List
from collections.abc import Sequence

XTSUFFIX_ARRAY = TypeVar('XTSUFFIX_ARRAY')

@dataclass
class algo_suffix:
    pos:int    = 0
    rank:int   = 0
    lcp:int    = 0
    src:list   = None
        
    def __getitem__(self, idx, ABSCENT=None):
        idx += self.pos
        return self.src[idx] if idx < len(self.src) else ABSCENT

    def __repr__(self):
        return '<suf pos={pos},lcp={lcp}>'.format(pos=self.pos,lcp=self.lcp)
    
from collections import defaultdict
from itertools import accumulate,islice

class suffix_array(Generic[XTSUFFIX_ARRAY]):
    def __init__(self, s:List[XTSUFFIX_ARRAY], ABSCENT=None):
        N = len(s)
        self.s = s
        self.LCP = [0]*N
        self.suffixes = [algo_suffix(pos=i,src=s) for i in range(N)]
        self.alpha = [ABSCENT]
        self.alpha.extend(sorted(set(s)))
        self.alpha2rank = {x:i for i,x in enumerate(self.alpha)}
        self.ABSCENT = ABSCENT

    def sortNSquareA(self):
        '''
        Count sort the suffixes using ranks
        cost = O(N*N)*O(ALPHA)
        '''
        self.sorted_suffixes = self.suffixes[:]
        N =  len(self.suffixes)
        segments = [(0,N)]
        for k in range(N):
            '''
            Calculate rank at kth position
            '''
            if not segments:
                break
                
            next_segments = []
            for begin,end in segments:

                #print('sorting', begin, end)
                # try count sort
                count = [0]*len(self.alpha)
                for i,x in enumerate(islice(self.sorted_suffixes,begin,end),begin):
                    arank = self.alpha2rank[x[k]]
                    count[arank] += 1

                #print(count)
                cumsum = list(accumulate(count,initial=0))
                idx2suffix = [None]*cumsum[-1]
                for i,x in enumerate(islice(self.sorted_suffixes,begin,end),begin):
                    arank = self.alpha2rank[x[k]]
                    x.rank = cumsum[arank]
                    idx2suffix[x.rank+count[arank]-1] = x
                    count[arank] -= 1
                
                #print('cumsum=',cumsum)
                #print('suffix by index=',idx2suffix)
                seg_begin,seg_rank = begin,0
                for idx,x in enumerate(idx2suffix):
                    i = begin+idx
                    self.sorted_suffixes[i] = x
                    if seg_rank != x.rank:
                        if (seg_begin+1) < i:
                            next_segments.append((seg_begin,i))
                        seg_begin = i
                        seg_rank = x.rank
                        if idx > 0:
                            x.lcp = k
                            print('no match', self.s[idx2suffix[idx-1].pos:],idx2suffix[idx-1],self.s[x.pos:], x, k)
                    elif idx > 0:
                        x.lcp = idx2suffix[idx-1].lcp
                        print(self.s[idx2suffix[idx-1].pos:],idx2suffix[idx-1],self.s[x.pos:], x, k)
                if (seg_begin+1) < end:
                    next_segments.append((seg_begin,end))
                #print('next-segments=', next_segments)
                #self.dump()
                    
            segments = next_segments
        
    def sortNLogSorted(self):
        '''
        Count sort the suffixes using ranks
        cost = O(N*Log N)*O(N)
        '''
        self.sorted_suffixes = self.suffixes[:]
        N =  len(self.suffixes)
        reference_rank = [self.alpha2rank[x[0]] for x in self.suffixes]

        step,k = 0,0
        while k < N:            # Iterate Log N times
            '''
            Calculate rank at kth position
            '''

            hp = [(reference_rank[x.pos],reference_rank[x.pos+k] if (x.pos+k) < N else -1,i,x) for i,x in enumerate(self.sorted_suffixes)]
            i = 0
            seg_begin,seg_rank = 0,None
            level = 0
            for rank1,rank2,unused3,x in sorted(hp):
                x.rank = (rank1,rank2)
                self.sorted_suffixes[i] = x
                if seg_rank is not None:
                    if seg_rank != x.rank:
                        level += 1
                seg_rank = x.rank
                reference_rank[x.pos] = level
                i += 1

            #self.dump()
            k = 1<<step # k*2
            step += 1
            #print(k,reference_rank)

    def sortNLogSegmented(self):
        '''
        Count sort the suffixes using ranks
        cost = O(N*Log N)*O(N)
        '''
        self.sorted_suffixes = self.suffixes[:]
        N =  len(self.suffixes)
        reference_rank = [self.alpha2rank[x[0]] for x in self.suffixes]

        segments = [(0,N)]
        step,k = 0,0
        while k < N and segments:
            '''
            Calculate rank at kth position
            '''

            for x in self.sorted_suffixes:
                x.rank = (reference_rank[x.pos],reference_rank[x.pos+k] if (x.pos+k) < N else -1)

            for begin,end in segments:
                hp = [ (x.rank,i,x) for i,x in enumerate(islice(self.sorted_suffixes,begin,end),begin)]
                i = 0
                for unused,unused,x in sorted(hp):
                    self.sorted_suffixes[i] = x
                    i += 1

            segments,seg_begin = [],0
            level,prev_rank = 0,self.sorted_suffixes[0].rank
            reference_rank[self.sorted_suffixes[0].pos] = level
            for i,x in enumerate(islice(self.sorted_suffixes,1),1):
                if prev_rank != x.rank:
                    level += 1
                    prev_rank = x.rank
                    if seg_begin+1 < i:
                        segments.append(seg_begin,i)
                    seg_begin = i
                reference_rank[x.pos] = level
            if seg_begin+1 < N:
                segments.append((seg_begin,N))
                
            print(segments)
            print([(self.s[x.pos:],x.pos,reference_rank[x.pos]) for x in self.sorted_suffixes])
            k = 1<<step # k*2
            step += 1
            print(k,reference_rank)
 

        
    def dump(self):
        #print([(self.s[x.pos:],x) for x in self.sorted_suffixes])
        print([(self.s[x.pos:],x.pos,x.lcp) for x in self.sorted_suffixes])

    sort = sortNLogSorted
            
if __name__ == '__main__':
    s = 'aaabababab'
    a = suffix_array(s)
    a.sortNSquareA()
    a.dump()
    a.sortNLogSorted()
    a.dump()
    a.sortNLogSegmented()
    a.dump()
    
