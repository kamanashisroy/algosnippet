
This interval tree is based on the book *Introduction to Algorithms*.


```

                < a [a ... b] a <= 
             /|                   |\
            / |                   | \
           /  |                   |  \
          / L |                   | R \
         /    |                   |    \
        -------                   -------
```

The interval tree above has a root that has an interval from `a` to `b`. And the left and right subtree is created such that,

- intervals in *left* subtree starts before `b`
- intervals in *right* subtree starts after `a`


The interval tree implemented here is a balanced-avl-tree. It has augmented value called right-max.

```
				None
			0,(1,2),2
				None
		1,(2,5),5
				None
			0,(3,5),5
				None
	3,(4,7),None
				None
			0,(5,6),8
				None
		2,(5,8),7
				None
			1,(7,8),8
					None
				0,(8,9),9
					None

```

TODO fix the augmented-right.


