
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
