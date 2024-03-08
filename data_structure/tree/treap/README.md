
Treap
======

#### Insert

```Python
    def append_node(self,given_treap_node):
        '''
        return new root after adding the treap-node
        '''

        #############################################
        # check the HEAP PROPERTY
        if given_treap_node.heap_key < self.heap_key:
            # self goes under given_treap_node
            given_treap_node.append_node(self)
            return given_treap_node # new root
        # HEAP PROPERTY
        #############################################

        self.num_nodes += given_treap_node.num_nodes
        #############################################
        # check the BINARY SEARCH TREE PROPERTY
        #############################################
        if given_treap_node.key <= self.key:
            # keep the new node at left
            if self.left is None:
                self.left = given_treap_node
            else:
                self.left = self.left.append_node(given_treap_node)
            self.left.parent = self
        else: # when given_treap_node is BIGGER
            if self.right is None:
                self.right = given_treap_node
            else:
                self.right = self.right.append_node(given_treap_node)
            self.right.parent = self
        return self
```

TODO implement stack based construction approach, see the lecture below.

Treap example output
=====================

Note that in the treap below, the first data-field in the tuple is sorted from top(0,32,0) to bottom(16,94,16).
```
python treap.py
					None
				(0, 32, 0)
					None
			(1, 14, 1)
				None
		(2, 12, 2)
					None
				(3, 523, 3)
					None
			(4, 13, 4)
				None
	(5, 1, 5)
				None
			(6, 7, 6)
						None
					(7, 23, 7)
						None
				(8, 7, 8)
					None
		(9, 2, 9)
						None
					(10, 7, 10)
						None
				(11, 4, 11)
							None
						(12, 89, 12)
							None
					(13, 8, 13)
						None
			(14, 3, 14)
					None
				(15, 26, 15)
						None
					(16, 94, 16)
						None
```

While the data is sorted when traversed in-order, there is heap property which places the tuples with higher middle value to right.

Now when we query all the elements at depth 10 we get the following in sorted order.

```
[(5, 1, 5), (6, 7, 6), (8, 7, 8), (9, 2, 9), (10, 7, 10), (11, 4, 11), (13, 8, 13), (14, 3, 14)]
```

Treap related problem
=======================

Augmented-Treap can be used as order-statistics-tree to solve problems of tree-distance calculations.

```
https://www.hackerrank.com/contests/w38/challenges/neighborhood-queries/submissions/code/1310160145
```

- [Number of visible people in a queue](https://leetcode.com/problems/number-of-visible-people-in-a-queue/)

Lectures
========

- [Stanford lecture slide for RMQ and treap](http://web.stanford.edu/class/cs166/lectures/01/Slides01.pdf)


