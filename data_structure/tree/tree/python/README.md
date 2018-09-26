
Tree implementation in python.

Features
===========

#### Iterative insert

```python
    def _insert_non_recursive(self,x,maintain_dup_list=True,new_node=None):
        node = self
        if new_node is None:
            new_node = algo_tree(x)
            
        while True:
            if node.root is None:
                node.root = x
                return node,False

            if x == node.root:
                if maintain_dup_list:
                    node.dup_list.append(x)
                    return node,True
                return node,True
            
            if x < node.root:
                if node.left is None:
                    node.left = new_node
                    new_node.parent = node
                    break # done inserting
                else:
                    node = node.left
            else: # x > node.root
                if node.right is None:
                    # set as right node
                    node.right = new_node
                    new_node.parent = node
                    break # done inserting
                else:
                    node = node.right
        
        added_node = new_node
        node = new_node
        while node is not None:
            added_node = node.insert_non_recursive_after(added_node)
            node = node.parent
        return added_node,False
```

#### Recursive Insert

It is implemented under `insert_recursive`.

#### Iterative Insert from Neighbor node

It is useful to reduce insertion time using square-root decomposition.

```python
    def insert_neighbor_non_recursive(self,x,maintain_dup_list=True,new_node=None):
        node = self
        while True:
            if node.parent is None:
                return node._insert_non_recursive(x,maintain_dup_list,new_node)
            else:
                if node.root == x:
                    return node._insert_non_recursive(x, maintain_dup_list,new_node)
                elif node.root < x:
                    # we should add x to the right
                    # check if we are left subtree
                    if node == node.parent.left:
                        if x < node.parent.root:
                            # node.root < x < node.parent.left
                            # the insertion have to be in the right-subtree
                            return node._insert_non_recursive(x, maintain_dup_list,new_node)
                        else:
                            node = node.parent
                            continue
                    else: # when we are right subtree
                        # node.parent.left < node.right < x
                        # return node._insert_non_recursive(x, maintain_dup_list,new_node)
                        node = node.parent
                        continue
                elif x < node.root:
                    # we should add x to the left
                    if node == node.parent.right:
                        # we are right child of parent
                        # that means we are greater than parent
                        if node.parent.root < x:
                            # node.parent.root < x < node.root
                            return node._insert_non_recursive(x, maintain_dup_list,new_node)
                        else:
                            node = node.parent
                            continue
                    else:
                        # we are left child of parent
                        # x < node.root < node.parent.root
                        # return node._insert_non_recursive(x, maintain_dup_list,new_node)
                        node = node.parent
```


#### Make tree from sorted data


#### Assert bst invariant

```
    def assert_invariant(self):
        last = None
        for x in self.traverse():
            if last is not None:
                assert(x >= last)
            last = x
```

Input commands
===============

```
if __name__ == "__main__":
    tree = algo_tree()
    tree.insert_recursive(4)
    tree.assert_invariant()
    tree.insert_recursive(3)
    tree.assert_invariant()
    tree.insert_non_recursive(5)
    tree.assert_invariant()
    tree.insert_recursive(6)
    tree.assert_invariant()
    print(str(tree))
    print("==================================")
    print("Deleting right-heavy node 4(root)")
    tree.delete(4)
    tree.assert_invariant()
    print(str(tree))
    print("==================================")
    tree.insert_recursive(10)
    tree.assert_invariant()
    print(str(tree))
    print("==================================")
    print("Deleting missing node 11")
    tree.delete(11)
    print(str(tree))
    print("==================================")
    tree.assert_invariant()
    tree.insert_non_recursive(9)
    tree.assert_invariant()
    tree.insert_recursive(7)
    tree.insert_non_recursive(4)
    tree.assert_invariant()
    print(str(tree))
    print("==================================")
    print("Deleting left-heavy node 9(when right is empty)")
    tree.delete(9)
    print(str(tree))
    print("==================================")
    print("Deleting right-heavy node 3(when left is empty)")
    tree.delete(3)
    print(str(tree))
    print("==================================")
    tree.insert_non_recursive(1)
    tree.insert_recursive(2)
    tree.insert_recursive(3)
    tree.insert_recursive(4)
    print(str(tree))
    print("==================================")
    print("Deleting left-heavy node 5(root) balances the tree")
    tree.delete(5)
    tree.assert_invariant()
    print(str(tree))
    

```

Output tree
============

```
python algo_tree.py
			None
		0,3,1
			None
	2,4,4
			None
		1,5,2
				None
			0,6,1
				None

==================================
Deleting right-heavy node 4(root)
			None
		0,3,1
			None
	1,5,3
			None
		0,6,1
			None

==================================
			None
		0,3,1
			None
	2,5,4
			None
		1,6,2
				None
			0,10,1
				None

==================================
Deleting missing node 11
			None
		0,3,1
			None
	2,5,4
			None
		1,6,2
				None
			0,10,1
				None

==================================
			None
		1,3,2
				None
			0,4,1
				None
	4,5,7
			None
		3,6,4
						None
					0,7,1
						None
				1,9,2
					None
			2,10,3
				None

==================================
Deleting left-heavy node 9(when right is empty)
			None
		1,3,2
				None
			0,4,1
				None
	3,5,6
			None
		2,6,3
					None
				0,7,1
					None
			1,10,2
				None

==================================
Deleting right-heavy node 3(when left is empty)
			None
		0,4,1
			None
	3,5,5
			None
		2,6,3
					None
				0,7,1
					None
			1,10,2
				None

==================================
				None
			2,1,3
					None
				1,2,2
						None
					0,3,1
						None
		3,4,4
			None
	4,5,8
			None
		2,6,3
					None
				0,7,1
					None
			1,10,2
				None

==================================
Deleting left-heavy node 5(root) balances the tree
			None
		2,1,3
				None
			1,2,2
					None
				0,3,1
					None
	3,4,7
			None
		2,6,3
					None
				0,7,1
					None
			1,10,2
				None
==================================
```


