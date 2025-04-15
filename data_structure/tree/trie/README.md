
`Trie` and `Prefix-tree` are the same thing. `Patricia tree` or `radix tree` is the `compact trie`. When inserted all suffixes of string, it(`Patricia tree`) is called `suffix tree`.

String prefix search
=====================

A trie can work as a dictionary. On top of that we can search for prefix matches.


```
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
                    print(origWords[assoc])
            for x in cur.children:
                if x is not None:
                    yield x
    
    def __len__(self):
        return self.numInserted

```


Suffix Trie sub-string search
==============================

Normally the cost of creating a suffix-trie is `O(N*N)`. This is because we need to insert all the suffixes in the trie.

But, probably we do not need all the branches in the Trie, we only need the nodes that matches our query.

So better use a lazy-suffix-trie.

```
class LazyPrefixTrie:
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

    def pushPrefixAt(self, beg):
        self.indices.add(beg)

    def expand(self, content):
        for curpos in self.indices:
            cur = self
            x = content[curpos]
            if cur.children[x] is None:
                cur.children[x] = LazyPrefixTrie(x)
            if (curpos+1) < len(content):
                cur.children[x].pushPrefixAt(curpos+1)
        self.indices.clear()

    @staticmethod
    def makeTrie(given):
        tr = LazyPrefixTrie(None)
        for i in range(len(given)):
            tr.pushPrefixAt(i)
        return tr


```

So when searched a given string, we can just `expand` a node only if it is needed to.


Using two suffix-trie to find longest common sub-string
=======================================================

We can use the `LazyPrefixTrie` built from the two given string and then traverse them to find the longest common substring.

```
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

print('Longest common substring', calc(LazyPrefixTrie.makeTrie(first), LazyPrefixTrie.makeTrie(second)))
```


Python Notes
=============

#### Binary-trie or fusion tree

```
We made a binary trie
inserting 4
trie -----------------------
		dir=0,"0",[]
			dir=1,"1",[4]
	dir=0,"0",[]
dir=-1,"-1",[]

inserting 5
trie -----------------------
		dir=0,"0",[]
			dir=1,"1",[4]
	dir=0,"0",[]
dir=-1,"-1",[]
		dir=0,"0",[]
			dir=1,"1",[5]
	dir=1,"1",[]

inserting 8
trie -----------------------
			dir=0,"0",[]
				dir=1,"1",[8]
		dir=0,"0",[]
			dir=1,"1",[4]
	dir=0,"0",[]
dir=-1,"-1",[]
		dir=0,"0",[]
			dir=1,"1",[5]
	dir=1,"1",[]
```

#### Patricia tree/Radix tree

```
patricia tree --------------
		dir=1,"0-1",[8]
	dir=0,"0-0",[]
		dir=1,"1",[4]
dir=-1,"-1",[]
	dir=1,"1-0-1",[5]
```

C++ Notes
===========

This is radix-tree/trie/prefix tree implemented over tree for strings.

Trie related problems
=======================

- [z-function](https://www.hackerrank.com/contests/w37/challenges/z-function)
- [Maximum Genetic Difference(XOR) Query](https://leetcode.com/problems/maximum-genetic-difference-query/)
- [Maximum XOR With an Element From Array](https://leetcode.com/problems/maximum-xor-with-an-element-from-array/)

#### Palindrome related
- [3504. Longest Palindrome After Substring Concatenation II](https://leetcode.com/problems/longest-palindrome-after-substring-concatenation-ii/)




