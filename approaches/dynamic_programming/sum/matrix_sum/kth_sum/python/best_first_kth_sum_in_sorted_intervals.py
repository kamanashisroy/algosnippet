
from collections import namedtuple
from typing import TypeVar, Generic
from typing import List


DBLXT = TypeVar('DBLXT')
class DBL(Generic[DBLXT]):
    __slots__ = ['x','fr','to']
    def __init__(self,x:DBLXT,fr:'DBL[DBLXT]' = None,to:'DBL[DBLXT]' = None):
        self.x:DBLXT = x
        self.to = to
        self.fr = fr

    def appendafter(self,y:DBLXT) -> None:
        to = self.to
        self.to = DBL(y, self, self.to)
        if to is not None:
            to.fr = self.to

    def appendright(self,y:DBLXT) -> 'DBL[DBLXT]':
        assert(self.to is None)
        self.to = DBL(y,self)
        return self.to

    def extendafter(self, other:List[DBLXT]) -> None:
        for x in other:
            self.appendafter(x)

    def join(self,y:'DBL[DBLXT]') -> None:
        if y:
            self.to = y
            y.fr = self
        else:
            self.to = None

    def drop(self) -> None:
        if self.to:
            self.to.fr = self.fr
        if self.fr:
            self.fr.to = self.to

    def __iter__(self) -> None:
        head = self
        while head:
            yield head.x
            head = head.to

    def linkeditems(self, skip_head:bool = True) -> None:
        head = self
        if head and skip_head:
            head = head.to
        while head:
            yield head,head.x
            head = head.to



SIVAL = TypeVar('SIVAL')
class sortedival(Generic[SIVAL]):
    __slots__ = ['content','future_content']
    def __init__(self):
        self.content = DBL(None)
        self.future_content = []
    
    def insert_future(self, x:SIVAL) -> None:
        self.future_content.append((x.lo,x.hi,'l',x))
        self.future_content.append((x.hi,x.lo,'r',x))
    
    def sort(self, head = None) -> None:
        self.future_content.sort()
        if head is None:
            head = self.content
        for x in self.future_content:
            #print('appending ', x)
            # append right
            while head and head.to:
                if x >= head.to.x:
                    head = head.to
                else:
                    break
            head.appendafter(x)
            #print('after ', head,x)

        self.future_content.clear()
    
    def __iter__(self) -> None:
        for ll,(bound1,bound2,c,y) in self.content.linkeditems():
            yield ll,bound1,c,y
    
    def __repr__(self) -> str:
        output = ['<sival:']
        for x in self.content:
            if x:
                output.append(str(x[2]))
        output.append('>')
        return ','.join(output)
    
class subproblem:
    __slots__ = ['lo','hi','row','curr_sum','curr_count','optimized','expanded']
    def __init__(self,lo:int,hi:int,row:int,curr_sum:int,curr_count:int):
        self.lo = lo
        self.hi = hi
        self.row = row
        self.curr_sum = curr_sum
        self.curr_count = curr_count
        self.optimized = False
        self.expanded = False
    
    def __repr__(self) -> str:
        return '<sub:lo={lo},hi={hi},row={row},curr_sum={curr_sum},ct={ct},exp={exp},opt={opt}>'.format(lo=self.lo,hi=self.hi,row=self.row,curr_sum=self.curr_sum,ct=self.curr_count,exp=self.expanded,opt=self.optimized)
        
    def __lt__(self, other) -> bool:
        return self.hi < other.hi
    
    def __le__(self, other) -> bool:
        return self.hi <= other.hi
    
    def __gt__(self, other) -> bool:
        return self.hi > other.hi
    
    def __ge__(self, other) -> bool:
        return self.hi >= other.hi
    
WIN = namedtuple('WIN','lo,hi',defaults=(0,0))
class Solution:
    def kthSmallest(self, mat: List[List[int]], k: int) -> int:
        N = len(mat)
        M = len(mat[0])
        
        count = 1
        result = 0
        for row in mat:
            result += row[0]
            
        if 1 == M or 1 == k:
            return result
        
        
        # put the highest distant rows at the top
        gaps = [(row[0]-row[-1],row) for row in mat]
        gaps.sort()
        
        mat = [row for unused,row in gaps]
        #print(mat)

        window = [WIN(0,0)]
        TOTAL = [1]
        future_count = 1
        for row in reversed(mat):
            lo,hi = window[-1]
            lo += row[0]
            hi += row[-1]
            window.append(WIN(lo,hi))
            future_count *= M
            TOTAL.append(future_count)
        
        window = list(reversed(window))
        
        #print(M**N,TOTAL[-1])
        GRANDTOTAL = TOTAL[-1]
        ivals = sortedival()
        root = subproblem(window[0].lo,window[0].hi,-1,0,1)
        ivals.insert_future(root)
        optimized_left = []
        optimized_left_count = 0
        optimized_right_subproblem_count = 0
        num_expanded = 0
        #optimized_right_count = 0
        
        #TOTAL.pop()
        TOTAL = list(reversed(TOTAL))
        #print(TOTAL)

        ivals.sort()
        relaxed = True
        while relaxed:
            relaxed = False
            
            rcount:int = 0
            lcount:int = 0
            
            for ll,boundary,flag,sub in ivals:
                if sub.expanded or sub.optimized:
                    ll.drop()
                    continue
                if 'r' == flag:
                    ct:int = sub.curr_count*TOTAL[sub.row+1]
                    lcount -= ct
                    #print(lcount+rcount,sub,k)
                    if (optimized_left_count + lcount + rcount + ct) < k:
                        sub.optimized = True
                        optimized_left.append(sub)
                        ll.drop()
                        optimized_left_count += ct
                    else:
                        rcount += ct
                    
                elif 'l' == flag:
                    if (optimized_left_count + rcount) > k:
                        sub.optimized = True
                        #optimized_right_count += sub.curr_count*sub.future_count
                        optimized_right_subproblem_count += 1
                        ll.drop()
                    else:
                        lcount += sub.curr_count*TOTAL[sub.row+1]
                        
            #print(ivals)
            #print('--------')
            for ll,boundary,flag,sub in ivals:
                if sub.expanded or sub.optimized:
                    ll.drop()
                    continue
                #if sub.row != (ridx-1):
                #    continue
                if sub.hi == sub.lo:
                    continue
                sub.expanded = True
                
                relaxed = True
                ridx = sub.row+1
                window_lo,window_hi = window[ridx+1]
                #print('expanding', sub)
                expanded_fringe = dict()
                for x in mat[ridx]:
                    y = sub.curr_sum + x
                    count = sub.curr_count

                    if y not in expanded_fringe:
                        expanded_fringe[y] = subproblem(window_lo+y, window_hi+y,ridx,y,count)
                    else:
                        expanded_fringe[y].curr_count += count
                #print(expanded_fringe)
                for x in expanded_fringe.values():
                    num_expanded += 1
                    ivals.insert_future(x)
                ivals.sort(ll)
                ll.drop()
                break # do not expand anymore

                
        #ivals.sort()
        #print(ivals)
        #usubs = [sub for boundary,flag,sub in ivals.content if not sub.expanded and 'l' != flag]
            
        #print('optimized left', optimized_left_count)
        #print('optimized right', optimized_right_count)
        #print('optimized right subproblems', optimized_right_subproblem_count)
        #print('optimized left', optimized_left)
        #print('final subs', len(usubs))
        #print('expanded subs', num_expanded)
        #print(usubs)
        count = optimized_left_count
        #for m in sorted(usubs):
        for ll,boundary,flag,m in ivals:
            if m.expanded or 'l' == flag:
                continue
            ct = m.curr_count*TOTAL[m.row+1]
            #print('**', count+ct, m)
            if (count+ct) >= k:
                return m.hi
            count += ct
        #print(count)
        return None

if __name__ == '__main__':
    sln = Solution()

    #print(sln.kthSmallest([[49,59,210,256,369,385,533,751,789,795,1004,1033,1199,1411,1514,1617,1684,1737,1817,1932,2056,2086,2320,2409,2580,2917,3125,3374,3380,3557,3582,3715,3736,3837],[23,161,363,443,600,875,908,1078,1122,1159,1279,1343,1534,1651,1660,1716,1954,1989,2022,2039,2262,2267,2473,2593,2842,3046,3135,3187,3245,3299,3377,3605,3737,3956],[336,355,880,919,953,1127,1229,1248,1291,1552,1623,1677,1761,1937,1938,1975,2211,2218,2243,2585,2610,2698,2796,2868,2982,3022,3213,3413,3475,3546,3563,3594,3635,3978],[3,113,153,377,409,474,610,799,983,1190,1417,1438,1810,1998,2100,2131,2137,2171,2256,2354,2364,2612,2746,2843,3028,3031,3051,3178,3188,3221,3651,3651,3715,3971],[22,261,689,765,798,899,904,1043,1182,1187,1278,1305,1460,1481,1589,1657,1683,1684,1957,1961,2301,2327,2761,2773,2926,3196,3201,3317,3360,3380,3661,3738,3861,3943],[21,104,197,310,370,450,777,782,997,1001,1057,1126,1159,1238,1324,1440,1533,1761,1879,1953,2041,2321,2424,2466,2589,2616,2697,2909,3013,3107,3564,3579,3792,3870],[113,201,259,279,492,540,554,634,696,800,999,1072,1202,1437,1626,1641,1866,2073,2146,2148,2187,2290,2392,2431,2619,3104,3296,3318,3456,3479,3809,3856,3873,3919],[132,203,243,280,349,422,459,877,918,919,1181,1181,1239,1393,1480,1548,1697,1744,1870,1969,2000,2058,2267,2367,2433,2438,2626,2877,3157,3272,3446,3645,3824,3964],[251,406,469,544,611,1058,1105,1189,1222,1600,1843,2028,2423,2436,2459,2463,2486,2619,3008,3107,3131,3207,3250,3336,3353,3684,3691,3740,3776,3794,3795,3813,3848,3996],[35,128,219,263,279,492,892,940,1268,1416,1426,1634,1645,1742,1793,1852,2018,2040,2040,2163,2272,2354,2594,2601,2774,2820,2891,3229,3385,3417,3446,3671,3899,3909],[4,41,292,418,460,628,687,814,1083,1526,1632,1850,1868,1997,2119,2195,2352,2519,2544,2629,2725,2787,2829,2875,2898,2907,3180,3209,3217,3305,3375,3390,3787,3904],[94,279,455,872,982,1006,1104,1139,1196,1396,1426,1518,1529,1582,1811,1918,1969,2001,2079,2405,2517,2668,2668,2745,2819,2932,3160,3199,3415,3600,3673,3810,3893,3997],[84,100,117,432,587,689,716,728,774,816,915,935,1057,1137,1178,1309,1360,1420,1529,1550,1570,1603,1998,2282,2439,2657,2679,3025,3071,3297,3321,3419,3794,3860],[65,76,215,352,438,540,597,605,762,1131,1456,1481,1601,1836,1880,1930,2004,2203,2263,2539,2542,2634,2647,2722,3165,3283,3332,3413,3524,3641,3772,3775,3835,3932],[141,216,364,488,512,523,534,557,801,848,932,933,953,1197,1286,1305,1327,1444,1452,1480,1790,2029,2389,2481,2568,2645,2663,2849,2855,3068,3321,3568,3773,3981],[199,352,392,471,518,564,668,797,1067,1131,1137,1207,1423,1427,1523,1532,1590,1831,1904,2182,2254,2367,2428,3004,3019,3135,3214,3264,3415,3487,3632,3733,3798,3912],[42,57,137,483,534,654,660,748,857,929,946,1281,1298,1306,1586,2079,2088,2284,2529,2551,2779,2835,2844,2958,3067,3125,3137,3412,3501,3641,3703,3935,3986,3998],[13,111,360,554,653,697,705,911,977,1339,1598,1609,1694,1707,1822,1832,1885,1952,2002,2053,2096,2140,2180,2455,2633,2707,2724,2865,2989,3124,3292,3360,3562,3986],[373,499,607,763,769,912,1083,1222,1515,1558,1582,1639,1876,2018,2089,2302,2321,2459,2547,2633,2711,2747,2929,3199,3215,3387,3413,3438,3508,3626,3630,3846,3877,3887]],3000))
    print(sln.kthSmallest([[5,40],[2,27],[18,45],[23,24],[24,39],[18,31],[5,35]],20))
