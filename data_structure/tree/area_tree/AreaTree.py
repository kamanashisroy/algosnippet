
nodelimit = [0,200000000]

PRM = 1000000007

class AreaTree:
    def __init__(self, dim, cover, MDIM=2):
        self.dim = dim
        self.cover = self.copy(cover)
        self.bottom = None
        self.top = None
        lo,hi = self.cover[self.dim]
        self.mid = (lo+hi)>>1
        self.MDIM = MDIM
        self.leaf = None
        self.areaMemo = None
        self.coverArea = self.computeArea(self.cover)
        nodelimit[0] += 1

    def copy(self, given):
        return [dimval[:] for dimval in given]
        
    def addTop(self, area):
        lo,hi = area[self.dim]
        assert(lo<=hi)
        if hi <= self.mid:
            return
        if self.top is None:
            if nodelimit[0] > nodelimit[1]:
                return
            topcover = self.copy(self.cover)
            topcover[self.dim][0] = self.mid
            #print(self.cover, 'Splitting to top', topcover)
            self.top = AreaTree( (self.dim+1)%self.MDIM, topcover, self.MDIM)
        toparea = self.copy(area)
        toparea[self.dim][0] = max(self.mid,lo)
        #print('Inserting toparea', toparea)
        self.top.insert(toparea)

    def addBottom(self, area):
        lo,hi = area[self.dim]
        assert(lo<=hi)
        if lo >= self.mid:
            return
        if self.bottom is None:
            if nodelimit[0] > nodelimit[1]:
                return
            bottomcover = self.copy(self.cover)
            bottomcover[self.dim][1] = self.mid
            #print(self.cover, 'Splitting to bottom', bottomcover)
            self.bottom = AreaTree( (self.dim+1)%self.MDIM, bottomcover, self.MDIM)
        bottomarea = self.copy(area)
        bottomarea[self.dim][1] = min(self.mid,hi)
        #print('Inserting bottomarea', bottomarea)
        self.bottom.insert(bottomarea)

    def equals(self,a,b):
        for dim in range(self.MDIM):
            if a[dim][0] != b[dim][0] or a[dim][1] != b[dim][1]:
                return False
        return True
        
    def contains(self,a,b):
        for dim in range(self.MDIM):
            if a[dim][0] > b[dim][0] or a[dim][1] < b[dim][1]:
                return False
        return True

    def combine(self, a, b):
        ret = self.copy(a)
        for dim in range(self.MDIM):
            ret[dim][0] = min(ret[dim][0], b[dim][0])
            ret[dim][1] = max(ret[dim][1], b[dim][1])
        return ret
        

    def computeArea(self,area):
        ret = 1 
        for dim in range(self.MDIM):
            ret *= area[dim][1]-area[dim][0]
        return ret

    def computeArea2(self, a, b):
        '''
        This implementation is 2d 
        '''
        aArea = self.computeArea(a)
        bArea = self.computeArea(b)
        # now subtract overlapping area
        overlap = 1 
        for dim in range(self.MDIM):
            alo,ahi = a[dim]
            blo,bhi = b[dim]
            # suppose , alo < blo < ahi 
            if alo <= blo and blo <= ahi:
                overlap *= min(bhi,ahi)-blo
            elif blo < alo and alo < bhi: # suppose blo < alo < bhi
                overlap *= min(bhi,ahi)-alo
            else:
                overlap = 0
                break # no overlap
        return aArea+bArea-overlap

    def optimize(self):
        if self.getArea() == self.coverArea:
            # fully covered
            if self.top:
                #print('Optimized top', self.top.cover)
                self.top = None
            if self.bottom:
                #print('Optimized bottom', self.bottom.cover)
                self.bottom = None
            self.leaf = self.cover
            return # no need to add

    def insert(self, area):
        assert(self.contains(self.cover,area))
        if self.getArea() == self.coverArea:
            return # no need to insert, it is full
        self.areaMemo = None
        #print(self.cover,'inserting ', area)
        if self.leaf is None and self.top is None and self.bottom is None:
            self.leaf = self.copy(area)
        else:
            if self.leaf is not None:
                if self.contains(self.leaf, area):
                    #print(self.leaf, 'No need to insert', area)
                    return # no need to insert duplicate
                elif self.contains(area,self.leaf):
                    self.leaf = self.copy(area)
                    self.optimize()
                    return
                else:
                    comb = self.combine(area,self.leaf)
                    if self.computeArea(comb) == self.computeArea2(area, self.leaf):
                        self.leaf = comb
                        self.optimize()
                        return
                self.addTop(self.leaf)
                self.addBottom(self.leaf)
                self.leaf = None
            self.addTop(area)
            self.addBottom(area)
        self.optimize()
    
    def fill(self, areaList):
        for area in areaList:
            self.insert(area)

    def getArea(self):
        if self.areaMemo is not None:
            return self.areaMemo
        ret = 0
        if self.leaf is not None:
            ret += self.computeArea(self.leaf)

        if self.top is not None:
            ret += self.top.getArea()
            
        if self.bottom is not None:
            ret += self.bottom.getArea()
        ret %= PRM
        self.areaMemo = ret
        return ret

    def getAreaDiv(self, mid,midDim):
        coverLo,coverHi = self.cover[midDim]
        if coverLo >= mid:
            return [self.getArea(),0]
        elif coverHi <= mid:
            return [0,self.getArea()]
        if self.leaf is not None:
            lo,hi = self.leaf[midDim]
            if lo >= mid:
                return [self.computeArea(self.leaf),0]
            elif hi <= mid:
                return [0,self.computeArea(self.leaf)]
            else:
                top = self.copy(self.leaf)
                top[midDim][0] = max(mid,lo)
                bottom = self.copy(self.leaf)
                bottom[midDim][1] = min(mid,hi)
                return [self.computeArea(top),self.computeArea(bottom)]
        ret = [0,0]
        if self.top is not None:
            ret = self.top.getAreaDiv(mid,midDim)
        if self.bottom is not None:
            ret2 = self.bottom.getAreaDiv(mid,midDim)
            ret[0] += ret2[0]
            ret[1] += ret2[1]
        return ret

    def prettyPrint(self, depth=0):
        if self.top:
            self.top.prettyPrint(depth+1)
        prefix = '  '*depth
        print(prefix,'-',self.cover,self.leaf)
        if self.bottom:
            self.bottom.prettyPrint(depth+1)


    def svgPrint(self, depth=0):
        if self.top:
            self.top.svgPrint(depth+1)
        if self.leaf:
            xlo,xhi = self.leaf[0]
            ylo,yhi = self.leaf[1]
            print('<rect x="%f" y="%f" width="%f" height="%f" fill="yellow"/>' % (xlo,ylo,xhi-xlo,yhi-ylo))
        if self.bottom:
            self.bottom.svgPrint(depth+1)
       

