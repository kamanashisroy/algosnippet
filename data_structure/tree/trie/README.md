
`Trie` and `Prefix-tree` are the same thing. `Patricia tree` or `radix tree` is the `compact trie`. When inserted all suffixes of string, it(`Patricia tree`) is called `suffix tree`.

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




