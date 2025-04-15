
class TrieDict:
    '''
    Algosnippet is a collection of practice data-structures and algorithms
    Copyright (C) 2025  Kamanashis Roy

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
    def __init__(self, val=None, depth=0):
        self.val = val
        self.children = [None]*26
        self.leaves = set()
        self.depth = depth
        self.numInserted = 0
    
    def __setitem__(self, strval, assoc):
        cur = self
        cur.numInserted += 1
        for x in strval:
            if cur.children[x] is None:
                cur.children[x] = TrieDict(x,cur.depth+1)
            cur = cur.children[x]
            cur.numInserted += 1
        cur.leaves.add(assoc)
        
    def iterNodes(self, itrstr):
        cur = self
        for x in itrstr:
            if cur.children[x] is None:
                return
            cur = cur.children[x]
            yield cur
    
    def values(self):
        stack = [self]
        while stack:
            cur = stack.pop()
            if cur.leaves:
                for assoc in cur.leaves:
                    yield assoc
            for x in cur.children:
                if x is not None:
                    stack.append(x)
    
    def __len__(self):
        return self.numInserted

if __name__ == '__main__':

    from functools import lru_cache
    from itertools import islice

    origWords = ['drama', 'king', 'dramaking', 'kingspike']

    ORDA = ord('a')
    def normalize(w):
        return [ord(x)-ORDA for x in w]

    words = [normalize(w) for w in origWords]


    lookup = TrieDict()
    for i,w in enumerate(words):
        lookup[w] = i
    
    #lookup.showWords(origWords)
    
    @lru_cache(maxsize=100)
    def calc(widx, pos):
        if widx > len(words):
            return False
        w = words[widx]
        if pos >= len(w):
            return True
        
        for node in lookup.iterNodes( islice(w,pos,None) ):
            if 0 == pos and 1 == len(node):
                break
            
            if 0 == node.depth or not node.leaves:
                continue
            for other in node.leaves:
                if other == widx:
                    continue
                if calc(widx, pos+node.depth):
                    #print(widx,origWords[widx],'Found',pos+node.depth, )
                    return True
                break
        return False
    
    result = []
    for i,w in enumerate(origWords):
        calc.cache_clear()
        if calc(i,0):
            result.append(w)
    print(result)
