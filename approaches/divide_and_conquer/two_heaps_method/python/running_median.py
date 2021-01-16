#!python

from heapq import heappush
from heapq import heappop

def runningMedian(a):
    heapa = []
    heapb = []
    result = []
    for count,x in enumerate(a):
        m = (count+1)&1
        if not heapa or (-heapa[0]) >= x:
            heappush(heapa,-x)
            while len(heapa) > (len(heapb)+m):
                y = -heappop(heapa)
                heappush(heapb,y)
            odd_midval = -heapa[0]
        else:
            heappush(heapb,x)
            while len(heapb) > (len(heapa)+m):
                y = heappop(heapb)
                heappush(heapa,-y)
            odd_midval = heapb[0]
        if 1 == m:
            result.append('%.1f' % odd_midval)
        else:
            result.append('%.1f' % round((-heapa[0]+heapb[0])/2,1))
                
    return result
