

class LazySuffixTrie:
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

    def __init__(self, cur):
        self.cur = cur
        self.children = [None]*26
        self.indices = set()
        self.memo = 0

    def __init__(self, cur):
        self.cur = cur
        self.children = [None]*26
        self.indices = set()

    def pushAt(self, beg):
        self.indices.add(beg)

    def expand(self, content, callback = None):
        for curpos in self.indices:
            cur = self
            if callback:
                cur.memo = callback(cur.memo, curpos)
            x = content[curpos]
            if cur.children[x] is None:
                cur.children[x] = LazySuffixTrie(x)
            if (curpos+1) < len(content):
                cur.children[x].pushAt(curpos+1)
        self.indices.clear()

    @staticmethod
    def makeTrie(given):
        tr = LazySuffixTrie(None)
        for i in range(len(given)):
            tr.pushAt(i)
        return tr


if __name__ == "__main__":

    first,second = 'feelsgood','feelssupercool'
    first,second = [ord(x)-ord('a') for x in first],[ord(x)-ord('a') for x in second]

    def calc(a,b,depth=0):
        a.expand(first)
        b.expand(second)
        ret = depth
        for x,y in zip(a.children,b.children):
            if x is not None and y is not None:
                ret = max(ret, calc(x,y,depth+1))
        return ret

    print('Longest common substring', calc(LazySuffixTrie.makeTrie(first), LazySuffixTrie.makeTrie(second)))

