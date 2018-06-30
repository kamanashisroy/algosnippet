
Tree implementation in python.

Input commands
===============

```
if __name__ == "__main__":
    tree = algo_tree()
    tree.insert(4)
    tree.insert(3)
    tree.insert(5)
    tree.insert(6)
    print(str(tree))
    print("==================================")
    tree.delete(4)
    print(str(tree))
    print("==================================")
    tree.insert(10)
    tree.delete(11)
    tree.insert(9)
    tree.insert(7)
    tree.insert(4)
    print(str(tree))
    print("==================================")
```

Output tree
============

```
python algo_tree.py
			None
		3
			None
	4
			None
		5
				None
			6
				None

==================================
			None
		3
			None
	5
			None
		6
			None

==================================
			None
		3
				None
			4
				None
	5
			None
		6
						None
					7
						None
				9
					None
			10
				None

==================================
```


