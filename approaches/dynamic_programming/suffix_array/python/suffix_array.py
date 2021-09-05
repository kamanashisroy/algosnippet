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
    level:int  = 0
    src:list   = None
        
    def __getitem__(self, idx, ABSCENT=None):
        idx += self.pos
        return self.src[idx] if idx < len(self.src) else ABSCENT
    
from collections import defaultdict
from itertools import accumulate

class suffix_array(Generic[XTSUFFIX_ARRAY]):
    def __init__(self, s:List[XTSUFFIX_ARRAY], ABSCENT=None):
        N = len(s)
        self.s = s
        self.LCP = [0]*N
        self.suffixes = [algo_suffix(pos=i,src=s) for i in range(N)]
        #self.alpha = [ABSCENT]
        self.alpha = []
        self.alpha.extend({x for x in s})
        self.alpha.sort()
        self.alpha.insert(0,ABSCENT)
        self.alpha_rank = {x:i for i,x in enumerate(self.alpha)}
        self.ABSCENT = ABSCENT

    def sortNSquare(self):
        '''
        Count sort the suffixes using ranks
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
                count = defaultdict(int)
                for i in range(begin,end):
                    x = self.sorted_suffixes[i]
                    x.rank = 0
                    count[x[k]] += 1

                #print(count)
                # now assign rank
                suffix_by_rank = dict()
                #cumsum = list(accumulate(map(operator.itemgetter,self.alpha,count)))
                cumsum = list(accumulate([count[x] for x in self.alpha],initial=0))
                for i in range(begin,end):
                    x = self.sorted_suffixes[i]
                    y = x[k]
                    arank = self.alpha_rank[y]
                    x.rank = cumsum[arank]
                    suffix_by_rank[x.rank+count[y]-1] = x
                    count[y] -= 1
                
                #print('cumsum=',cumsum)
                #print('suffix by rank=',suffix_by_rank)
                seg_begin,seg_rank = begin,0
                for i in range(begin,end):
                    rank = i - begin
                    x = suffix_by_rank[rank]
                    self.sorted_suffixes[i] = x
                    if seg_rank != x.rank:
                        if (seg_rank+1) != i:
                            next_segments.append((seg_begin,i))
                        seg_begin = i
                        seg_rank = x.rank
                if (seg_begin+1) != end:
                    next_segments.append((seg_begin,end))
                #print('next-segments=', next_segments)
                #self.dump()
                    
            segments = next_segments
        
    def sortNLogN(self):
        '''
        Count sort the suffixes using ranks

        Note that it takes O(N*Log N) time
        '''
        self.sorted_suffixes = self.suffixes[:]
        N =  len(self.suffixes)
        segments = [(0,N)]

        step,k = 0,0
        while k < N and segments:
            '''
            Calculate rank at kth position
            '''
            #print('step=',step)
            next_segments = []
            for begin,end in segments:

                #print('sorting', begin, end, end-begin)
                # try count sort
                count = defaultdict(int)
                for i in range(begin,end):
                    x = self.sorted_suffixes[i]
                    count[x[k]] += 1

                #print(count)
                # scatter suffixes by rank
                map_suffix_by_rank = dict()
                #cumsum = list(accumulate(map(operator.itemgetter,self.alpha,count)))
                cumsum = list(accumulate([count[x] for x in self.alpha],initial=0))
                #print('cumsum=',cumsum)
                for i in range(begin,end):
                    x = self.sorted_suffixes[i]
                    y = x[k]
                    arank = self.alpha_rank[y]
                    x.rank = cumsum[arank]
                    #print(x.pos,x.rank, 'setting rank', x.rank+count[y]-1, ' for ', y)
                    map_suffix_by_rank[x.rank+count[y]-1] = x
                    count[y] -= 1
                
                # gather/reduce by rank
                #print('suffix by rank=',map_suffix_by_rank)
                seg_begin,seg_rank = begin,0
                for i in range(begin,end):
                    rank = i - begin
                    x = map_suffix_by_rank[rank]
                    self.sorted_suffixes[i] = x
                    if seg_rank != x.rank:
                        if (seg_rank+1) != i:
                            next_segments.append((seg_begin,i))
                        seg_begin = i
                        seg_rank = x.rank
                if (seg_begin+1) != end:
                    next_segments.append((seg_begin,end))
                #print('next-segments=', next_segments)
                #self.dump()
                    
            segments = next_segments
            k = 1<<step # k*2
            step += 1
        
    def dump(self):
        print([(self.s[x.pos:],x.pos,x.rank) for x in self.sorted_suffixes])

    sort = sortNLogN
            
if __name__ == '__main__':
    s = 'aaabababab'
    a = suffix_array(s)
    a.sort()
    a.dump()
    
