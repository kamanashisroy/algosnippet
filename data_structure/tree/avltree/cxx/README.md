
This is AVL tree implementation.

AVL tree is faster than Red-Black tree when the search is more than insertion/deletion.

#### height augmentation

The AVL tree keeps an height property of the node.

- Height is defined as the longest path to the leaf. So the height of a leaf is 0.
- Height of an internal node is max(height of children)

```C++
    void fixHeight(AVLHEAP &heap) {
        height = 0;
        if(-1 != right && (heap[right].height > (height-1))) {
            height = heap[right].height+1;
        }
        if(-1 != left && (heap[left].height > (height-1))) {
            height = heap[left].height+1;
        }
        //cout << " height of " << key << " is " << height << endl;
    }
```


#### Rotation

The rotation always changes the height of the sub-tree except in zig-zag condition. In zig-zag we need to straighted up the right/left child before rotation.

Here is a right rotation example.

```C++
    int rotateRight(AVLHEAP&heap) {
        //std::cout << "idx=" << idx << ",rotateRight " << std::endl;
        assert(-1 != left);
        //cout << " rotating right " << key << endl;
        auto& head = heap[left];
        head.parent = parent;
        if(-1 != parent) { // fixup parent
            auto& head_parent = heap[parent];
            if(head_parent.right == idx)
                head_parent.right = head.idx;
            else
                head_parent.left = head.idx;
        }

        // transplant left
        left = head.right;
        if(-1 != left)
            heap[left].parent = idx;

        // transplant right
        head.right = idx;
        parent = head.idx;

        // augment
        augment(heap);
        head.augment(heap);
        return head.idx;
    }
```

Note that after rotation the head is changed.

#### Handling zigzag.

To balance the height of AVL-tree we need to take care of zig-zag and make the tangle straight.

```C++
    if(diff > 0) { /* left-heavy */
        assert(-1 != left);
        auto& xleft = heap[left];
        if(xleft.balanceFactor(heap) < 0) { // zigzag case, where it is middle heavy

#ifdef DEBUG_FIX_AVL
            std::cout << "Double rotate left(middle)-heavy zigzag at " << left << std::endl;
#endif
            xleft.rotateLeft(heap);
        }
        // Now there must be a left child of left child
        return rotateRight(heap); // rotate it right to lower the left height
	}
```

So the AVL-tree fixing is the following.

```C++
    int fixAVLProperty(AVLHEAP&heap) {
        int diff = balanceFactor(heap);

#ifdef DEBUG_FIX_AVL
        std::cout << idx << " checking avl property for " << key.avl_key() << " the diff is " << diff << std::endl;
#endif
        /* check AVL condition */
        if(diff == 1 || diff == -1 || diff == 0) {
            augment(heap);
            return idx; // no worry
        }

        if(diff > 0) { /* left-heavy */
            assert(-1 != left);
            auto& xleft = heap[left];
            if(xleft.balanceFactor(heap) < 0) { // zigzag case, where it is middle heavy

#ifdef DEBUG_FIX_AVL
                std::cout << "Double rotate left(middle)-heavy zigzag at " << left << std::endl;
#endif
                xleft.rotateLeft(heap);
            }
            // Now there must be a left child of left child
            return rotateRight(heap); // rotate it right to lower the left height
        } else { /* right tree is too deep */
            auto& xright = heap[right];
            if(xright.balanceFactor(heap) > 0) { // middle-heavy, zigzag case
                /* middle heavy
                 *                   < Y <                         
                 *                                           < X < 
                 *                /|              < z <            |\
                 *               /L|           /|      |\          |R\
                 *              ----          / |      | \         ----
                 *                           /  |      |  \
                 *                          /ML |      | MR\
                 *                         ------      ------
                 *                                
                 * rotate right and then left, swap Z and Y
                 *                                 
                 *                                < Z <
                 *                   < Y <                    < X <  
                 *                /|       |\             /|       |\
                 *               /L|       | \           / |       | \
                 *              ----       |  \         /  |       |  \
                 *                         |ML \       / MR|       | R \
                 *                         ------     ------       ------
                 **/
#ifdef DEBUG_FIX_AVL
                std::cout << "Double rotate right(middle)-heavy zigzag at " << right << std::endl;
#endif
                xright.rotateRight(heap);
            }
            return rotateLeft(heap); // now rotate left to lower the right height
        }
    }
```

#### Insertion

Insertion is same as binary search tree except it needs additional steps of updating the hegiht property and tree balancing.

#### Deletion

Delete is done by removing successor or predecessor.

Finding the successor,

```C++
    int successor = -1;
    int root = idx;
    if(-1 != right) {
        // successor should be in the right
        successor = heap[right].idx;
        // now successor should be in the left
        while(-1 != heap[successor].left) {
            successor = heap[successor].left;
        }
    }
```

Finding the predecessor,

```C++
    int predecessor = -1;
    if(-1 != left) {
        predecessor = left;
        while(-1 != heap[predecessor].right) {
            predecessor = heap[predecessor].right;
        }
    }
```

Augmentation
=============

#### Interval tree

The tree can be augmented to keep the largest value from the left subtree. 

```
struct test_interval {
    int val             = 1;
    int end             = 1;
    int max_end         = 1;
    int max_left_end    = 1;

    explicit test_interval(int val, int end):val(val),end(end),max_end(end),max_left_end(val)
    {}

    int avl_key() const {
        return val;
    }

    int avl_key_end() const {
        return end;
    }

    int avl_aug_val() const {
        return max_end;
    }

    int avl_left_aug_val() const {
        return max_left_end;
    }

    void augment_left(const test_interval& other) {
        max_end = std::max(other.avl_aug_val(),end);
        max_left_end = other.avl_aug_val();
    }

    void augment_right(const test_interval& other) {
        max_end = std::max(other.avl_aug_val(),end);
    }

    void inc() {
        val++;
        if(val == end) {
            end += 3;
            max_end = end;
            max_left_end = val;
        }
    }
};
```

#### Searching interval tree

Searching an interval inside the interval tree needs extra work on left tree node.

The searching needs to be done on left subtree in case `target.avl_key() < pivot.avl_aug_end()`.

```C++
    template <typename K>
    struct avl_search_go_left {
        constexpr bool operator()(const K &target, const K &pivot) const {
            if(target.avl_key() < pivot.avl_key()               // obviously, according to binary tree invariant
                || target.avl_key() < pivot.avl_left_aug_val()  // interval-tree invariant target_key < maximum_end_interval_at_left
                    ) {
                return true;
            }
            return false;
        }
    };
```

Also we need to check interval overlap,

```
template <typename K>
struct avl_search_overlaps {
    constexpr bool operator()(const K &lhs, const K &pivot) const {
        if(lhs.avl_key() >= pivot.avl_key() && lhs.avl_key() < pivot.avl_key_end()) {
            return true;
        }
        if(pivot.avl_key() >= lhs.avl_key() && pivot.avl_key() < lhs.avl_key_end()) {
            return true;
        }
        return false;
    }
};
```

#### subtree size augmentation

```
template <typename TCONTENT=long>
struct test_number {
    TCONTENT val        = 0;
    size_t subtree_size = 1;

    explicit test_number(int val):val(val)
    {}

    TCONTENT avl_key() const {
        return val;
    }

    size_t avl_aug_val() const {
        return subtree_size;
    }

    void augment_reset() {
        subtree_size = 1;
    }

    void augment_left(const test_number& other) {
        subtree_size += other.subtree_size;
    }

    void augment_right(const test_number& other) {
        subtree_size += other.subtree_size;
    }
    void inc() {
        val++;
        subtree_size = 1;
    }
};
```

#### Finding the rank

```
        // calculate rank
        size_t rank = 0;
        bool is_right_child = true;
        while(-1 != idx) {
            const auto&top = heap[idx];
            if(is_right_child) {
                rank += 1;          // for this node
                if(-1 != top.left) {
                    rank += heap[top.left].key.avl_aug_val();
                }
#ifdef DEBUG_ON
                cout << " calc rank(right) at " << top.key.avl_key() << " rank=" << rank << endl;
#endif
            }
            
            if( -1 == top.parent) {
                break; // reached root
            }
            
            if(heap[top.parent].left == idx) {
                is_right_child = false;
            } else {
                is_right_child = true;
#ifdef DEBUG_ON
                cout << " is right child " << endl;
#endif
            }
            idx = top.parent;
        }

```
