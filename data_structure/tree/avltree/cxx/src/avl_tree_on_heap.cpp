#include <vector>
#include <stack>
#include <iostream>
#include <cstdarg>
#include <cassert>
#include <tuple>
#include <algorithm>

//#define DEBUG_FIX_AVL
//#define DEBUG_TRANSPLANT

namespace avltree {

    template <typename K, typename TAVLPTR=int, TAVLPTR INVALID_AVLPTR_VAL=-1>
    struct AVLNode {
        /*************************************************************************
         *  avl_tree_on_heap.cpp file is part of Algosnippet.
         *  Algosnippet is a collection of practice data-structures and algorithms
         *  Copyright (C) 2020  Kamanashis Roy
         *  Algosnippet is free software: you can redistribute it and/or modify
         *  it under the terms of the GNU General Public License as published by
         *  the Free Software Foundation, either version 3 of the License, or
         *  (at your option) any later version.
         *  Algosnippet is distributed in the hope that it will be useful,
         *  but WITHOUT ANY WARRANTY; without even the implied warranty of
         *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
         *  GNU General Public License for more details.
         *  You should have received a copy of the GNU General Public License
         *  along with Algosnippet.  If not, see <https://www.gnu.org/licenses/>.
         **************************************************************************/

        using key_type                  = K;
        using idx_type                  = TAVLPTR;
        K key;
        int height                      = 0;
        TAVLPTR right                   = INVALID_AVLPTR_VAL;
        TAVLPTR left                    = INVALID_AVLPTR_VAL;
        //TAVLPTR equals                = INVALID_AVLPTR();
        TAVLPTR idx                     = INVALID_AVLPTR_VAL;
        TAVLPTR parent                  = INVALID_AVLPTR_VAL;

        AVLNode() {} // allow vector initialization
        AVLNode(K given, TAVLPTR idx) : key(given),idx(idx) { }
        static constexpr TAVLPTR INVALID_AVLPTR() {return INVALID_AVLPTR_VAL;}
    };
        
    //using AVLHEAP = std::vector<AVLNode<K>>;

    /**
     * The AVL tree keeps an extra property of the node. It is the heght of the node.
     * 
     * - Height is defined as the longest path to the leaf. So the height of a leaf is 0.
     * - Height of an internal node is max(height of children)
     */
    template <typename TRandomIter>
    void fixHeight(TRandomIter &heap, typename TRandomIter::value_type::idx_type self_idx) {
        auto& self = heap[self_idx];
        self.height = 0;
        if(TRandomIter::value_type::INVALID_AVLPTR() != self.right && (heap[self.right].height > (self.height-1))) {
            self.height = heap[self.right].height+1;
        }
        if(TRandomIter::value_type::INVALID_AVLPTR() != self.left && (heap[self.left].height > (self.height-1))) {
            self.height = heap[self.left].height+1;
        }
        //cout << " height of " << self.key << " is " << self.height << endl;
    }

    template <typename TRandomIter>
    void augment(TRandomIter &heap, typename TRandomIter::value_type::idx_type self_idx) {
        auto& self = heap[self_idx];
        self.key.augment_reset();
        if(TRandomIter::value_type::INVALID_AVLPTR() != self.left) {
            self.key.augment_left(heap[self.left].key);
        }
        if(TRandomIter::value_type::INVALID_AVLPTR() != self.right) {
            self.key.augment_right(heap[self.right].key);
        }
        fixHeight(heap, self_idx);
    }

    template <typename TRandomIter>
    void unplug(TRandomIter &heap, typename TRandomIter::value_type::idx_type self_idx) {
        auto& self = heap[self_idx];
        self.right       = TRandomIter::value_type::INVALID_AVLPTR();
        self.left        = TRandomIter::value_type::INVALID_AVLPTR();
        self.parent      = TRandomIter::value_type::INVALID_AVLPTR();
        self.height      = 0;
        augment(heap, self_idx);
    }

    template <typename TRandomIter>
    auto rotateRight(TRandomIter &heap, typename TRandomIter::value_type::idx_type self_idx) {
        auto& self = heap[self_idx];
        //std::cout << "idx=" << idx << ",rotateRight " << std::endl;
        assert(TRandomIter::value_type::INVALID_AVLPTR() != self.left);
        //cout << " rotating right " << key << endl;
        auto& head = heap[self.left];
        head.parent = self.parent;
        if(TRandomIter::value_type::INVALID_AVLPTR() != self.parent) { // fixup parent
            auto& head_parent = heap[self.parent];
            if(head_parent.right == self.idx)
                head_parent.right = head.idx;
            else
                head_parent.left = head.idx;
        }

        // transplant left
        self.left = head.right;
        if(TRandomIter::value_type::INVALID_AVLPTR() != self.left)
            heap[self.left].parent = self.idx;

        // transplant right
        head.right = self.idx;
        self.parent = head.idx;

        // augment
        augment(heap, self_idx);
        augment(heap, head.idx);
        return head.idx;
    }
    
    template <typename TRandomIter>
    auto rotateLeft(TRandomIter &heap, typename TRandomIter::value_type::idx_type self_idx) {
        auto& self = heap[self_idx];
        //std::cout << "idx=" << idx << ",rotateLeft " << std::endl;
        //dump();
        assert(TRandomIter::value_type::INVALID_AVLPTR() != self.right);
        //cout << " rotating left " << key << endl;
        auto& head = heap[self.right];
        head.parent = self.parent;

        if(TRandomIter::value_type::INVALID_AVLPTR() != self.parent) {
            auto& head_parent = heap[self.parent];
            //cout << " adding link to parent " << parent->key << endl;
            if(head_parent.right == self.idx)
                head_parent.right = head.idx;
            else
                head_parent.left = head.idx;
        }

        // transplant right
        self.right = head.left;
        if(TRandomIter::value_type::INVALID_AVLPTR() != self.right) {
            heap[self.right].parent = self.idx;
        }

        // transplant head->left
        head.left = self.idx;
        self.parent = head.idx;

        // augment
        augment(heap, self.idx);
        augment(heap, head.idx);
        return head.idx;
    }

    template <typename TRandomIter>
    inline auto balanceFactor(const TRandomIter& heap, typename TRandomIter::value_type::idx_type self_idx) {
        const auto& self = heap[self_idx];
        auto rheight = (TRandomIter::value_type::INVALID_AVLPTR() != self.right)?heap[self.right].height:-1;
        auto lheight = (TRandomIter::value_type::INVALID_AVLPTR() != self.left)?heap[self.left].height:-1;
        return lheight - rheight;
    }

    template <typename TRandomIter>
    auto fixAVLProperty(TRandomIter &heap, typename TRandomIter::value_type::idx_type self_idx) {
        auto& self = heap[self_idx];
        auto diff = balanceFactor(heap, self_idx);

#ifdef DEBUG_FIX_AVL
        std::cout << idx << " checking avl property for " << key.avl_key() << " the diff is " << diff << std::endl;
#endif
        /* check AVL condition */
        if(diff == 1 || diff == -1 || diff == 0) {
            augment(heap, self.idx);
            return self.idx; // no worry
        }

        if(diff > 0) { /* left-heavy */
            assert(TRandomIter::value_type::INVALID_AVLPTR() != self.left);
            if(balanceFactor(heap, self.left) < 0) { // zigzag case, where it is middle heavy

#ifdef DEBUG_FIX_AVL
                std::cout << "Double rotate left(middle)-heavy zigzag at " << self.left << std::endl;
#endif
                rotateLeft(heap, self.left);
            }
            // Now there must be a left child of left child
            return rotateRight(heap, self.idx); // rotate it right to lower the left height
        } else { /* right tree is too deep */
            if(balanceFactor(heap, self.right) > 0) { // middle-heavy, zigzag case
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
                std::cout << "Double rotate right(middle)-heavy zigzag at " << self.right << std::endl;
#endif
                rotateRight(heap, self.right);
            }
            return rotateLeft(heap, self.idx); // now rotate left to lower the right height
        }
    }

    template <typename TRandomIter>
    auto fixAVLPropertyBottomUp(TRandomIter& heap, typename TRandomIter::value_type::idx_type bottom) {
        auto root = bottom;
        assert(TRandomIter::value_type::INVALID_AVLPTR() != bottom);
        while(TRandomIter::value_type::INVALID_AVLPTR() != bottom) {
            const auto head = fixAVLProperty(heap, bottom);
            root = head;
            if(bottom != head) {
                // more avl fixing needed
                bottom = head;
                //dump_all(heap, head);
                continue;
            }
            
            bottom = heap[head].parent;
        }
        return root;
    }

    template <typename TRandomIter
        , typename GO_LEFT = std::less< typename TRandomIter::value_type::key_type >
        , typename NO_INSERT = std::equal_to< typename TRandomIter::value_type::key_type > >
    auto insert(TRandomIter&                                              heap
            , typename TRandomIter::value_type::idx_type                  root
            , typename TRandomIter::value_type::idx_type                  target_idx
            , GO_LEFT&                                                    go_left
            , NO_INSERT&                                                  no_insert) {

        if(TRandomIter::value_type::INVALID_AVLPTR() == root) { // base case
            unplug(heap, target_idx);
            augment(heap, target_idx);
            return std::make_pair(target_idx,TRandomIter::value_type::INVALID_AVLPTR());
        }
        
        auto& target = heap[target_idx];
        auto& aKey = target.key;
        auto topidx = root;

        while(TRandomIter::value_type::INVALID_AVLPTR() != topidx) {
            auto& top = heap[topidx];
            if(no_insert(aKey,top.key)) {
                return std::make_pair(root,topidx);
            } else if(go_left(aKey, top.key)) {
                topidx = top.left;
                if(TRandomIter::value_type::INVALID_AVLPTR() == topidx) {
                    // unlink target
                    unplug(heap, target_idx);
                    top.left = target.idx;
                    target.parent = top.idx;
                    augment(heap, top.idx);
                    topidx = target.idx;
                    break;
                }
            } else {
                topidx = top.right;
                if(TRandomIter::value_type::INVALID_AVLPTR() == topidx) {
                    // unlink target
                    unplug(heap, target_idx);
                    top.right = target.idx;
                    target.parent = top.idx;
                    augment(heap, top.idx);
                    topidx = target.idx;
                    break;
                }
            }
        }
        root = fixAVLPropertyBottomUp(heap, topidx);
        
        //std::cout << "inserted " << target_idx << std::endl;
        return std::make_pair(root,TRandomIter::value_type::INVALID_AVLPTR());
    }
    
    template <typename TRandomIter
        , typename GO_LEFT = std::less< typename TRandomIter::value_type::key_type >
        , typename K_IS_EQUAL = std::equal_to< typename TRandomIter::value_type::key_type > >
    static auto search(TRandomIter&                                         heap
            , typename TRandomIter::value_type::idx_type                    root
            , typename TRandomIter::value_type::key_type&                   aKey
            , GO_LEFT&                                                      go_left
            , K_IS_EQUAL&                                                   is_equal) {

        auto topidx = root;
        while(TRandomIter::value_type::INVALID_AVLPTR() != topidx) {
            auto& top = heap[topidx];
            //std::cout << "comparing " << aKey.x << " and " << key.x << std::endl;
            if(is_equal(aKey,top.key)) {
                return top.idx;             // found
            } else if(go_left(aKey,top.key)) {
                topidx = top.left;
            }
            topidx = top.right;
        }
        return topidx;
    }

    template <typename TRandomIter>
    auto transplant(TRandomIter&heap, const typename TRandomIter::value_type::idx_type self_idx, const typename TRandomIter::value_type::idx_type other_idx) {
        auto& self = heap[self_idx];
        auto& other = heap[other_idx];
        // the other must have only one leg or no legs
        assert(TRandomIter::value_type::INVALID_AVLPTR() == other.left || TRandomIter::value_type::INVALID_AVLPTR() == other.right);
        const auto other_leg = (TRandomIter::value_type::INVALID_AVLPTR() == other.left)?other.right:other.left;
        
        // unplug other, and replace with the single leg
        if(TRandomIter::value_type::INVALID_AVLPTR() != other.parent && self.idx != other.parent) {
            auto& other_parent = heap[other.parent];
            if(other_parent.left == other_idx) {
                other_parent.left = other_leg; // unplug from left tree
            } else if(other_parent.right == other_idx) {
                other_parent.right = other_leg;
            }
            if(TRandomIter::value_type::INVALID_AVLPTR() != other_leg) {
                heap[other_leg].parent = other.parent;
            }
            
            // it is done in fixAVLProperty() other_parent.fixHeight(heap); // little costly
            //std::cout << "fixing other parent " << std::endl;
            // fix AVL property
            auto pidx = other.parent;
            while(pidx != self.idx && TRandomIter::value_type::INVALID_AVLPTR() != pidx) { // cost is log(n)
                const auto topidx = fixAVLProperty(heap, pidx);
                if(topidx != pidx) {
                    // more avl fixing needed
                    pidx = topidx;
                    continue;
                }
                // TODO check if we can break out the loop and optimize
                pidx = heap[topidx].parent;
            }
        }
        
        // plug other
        const auto oldparent = other.parent;
        other.parent = self.parent;
        if(TRandomIter::value_type::INVALID_AVLPTR() != self.parent) {
            auto& my_parent = heap[self.parent];
            if(my_parent.left == self.idx) {
                my_parent.left = other.idx;
            } else if(my_parent.right == self.idx) {
                my_parent.right = other.idx;
            }
        }
        if(TRandomIter::value_type::INVALID_AVLPTR() != self.left && other.idx != self.left) {
            other.left = self.left;
            heap[self.left].parent = other.idx;
        } else {
            other.left = TRandomIter::value_type::INVALID_AVLPTR();
        }
        if(TRandomIter::value_type::INVALID_AVLPTR() != self.right && other.idx != self.right) {
            other.right = self.right;
            heap[self.right].parent = other.idx;
        } else {
            other.right = TRandomIter::value_type::INVALID_AVLPTR();
        }

        if(oldparent == self.idx && TRandomIter::value_type::INVALID_AVLPTR() != other_leg) {
            // in case other is direct child of current node
            if(self.left == other.idx) {
                assert(TRandomIter::value_type::INVALID_AVLPTR() == other.left);
                other.left = other_leg;
                assert(heap[other_leg].parent == other.idx);
            } else {
                assert(TRandomIter::value_type::INVALID_AVLPTR() == other.right);
                other.right = other_leg;
                assert(heap[other_leg].parent == other.idx);
            }
        }
        
        // cleanup this node
        //std::cout << "old parent " << self.parent << " other parent "<< other.parent << std::endl;
        unplug(heap, self.idx);
        // this is done in fixAVLProperty other.fixHeight(heap);
        // other.augment(heap);
        
        auto pidx = other.idx;
        // fix heap property
        return fixAVLPropertyBottomUp(heap, pidx);
    }
    
    template <typename TRandomIter>
    auto pop(TRandomIter&heap, typename TRandomIter::value_type::idx_type self_idx) {
        auto& self = heap[self_idx];
        // find successor
        auto successor = TRandomIter::value_type::INVALID_AVLPTR();
        auto root = self.idx;
        if(TRandomIter::value_type::INVALID_AVLPTR() != self.right) {
            // successor should be in the right
            successor = heap[self.right].idx;
            // now successor should be in the left
            while(TRandomIter::value_type::INVALID_AVLPTR() != heap[successor].left) {
                successor = heap[successor].left;
            }
        }
        if(TRandomIter::value_type::INVALID_AVLPTR() != successor) {
            // swap with successor
#ifdef DEBUG_TRANSPLANT
            std::cout << "transplanting succ " << successor << std::endl;
#endif
            root = transplant(heap, self.idx, successor);
        } else {
            //  find predecessor
            auto predecessor = TRandomIter::value_type::INVALID_AVLPTR();
            if(TRandomIter::value_type::INVALID_AVLPTR() != self.left) {
                predecessor = self.left;
                while(TRandomIter::value_type::INVALID_AVLPTR() != heap[predecessor].right) {
                    predecessor = heap[predecessor].right;
                }
            }
            if(TRandomIter::value_type::INVALID_AVLPTR() != predecessor) {
                // swap with predecessor
#ifdef DEBUG_TRANSPLANT
                std::cout << "transplanting pred " << predecessor << std::endl;
#endif
                root = transplant(heap, self.idx, predecessor);
            } else {
                // no successor or predecessor
                // unplug
                if(TRandomIter::value_type::INVALID_AVLPTR() != self.parent) {
                    auto&p = heap[self.parent];
                    if(p.left == self.idx) {
                        p.left = TRandomIter::value_type::INVALID_AVLPTR(); // unplug
                    } else {
                        p.right = TRandomIter::value_type::INVALID_AVLPTR();
                    }
                    auto pidx = self.parent;
#ifdef DEBUG_TRANSPLANT
                    std::cout << "no subtree " << pidx << std::endl;
#endif
                    // fix heap property
                    root = fixAVLPropertyBottomUp(heap, pidx);
                } else {
                    root = TRandomIter::value_type::INVALID_AVLPTR();
                }
            }
        }
        // cleanup this node
        unplug(heap, self.idx);
        return root;
    }
    

    template <typename TRandomIter>
    void in_order(TRandomIter &heap, typename TRandomIter::value_type::idx_type self_idx, int (*cb)(typename TRandomIter::reference key)) { // traverses tree in in-order
        auto& self = heap[self_idx];
        if(TRandomIter::value_type::INVALID_AVLPTR() != self.left)
            in_order(cb, self.left);
        cb(self.key);
        if(TRandomIter::value_type::INVALID_AVLPTR() != self.right)
            in_order(cb, self.right);
    }

    template <typename TRandomIter>
    void assert_tree(const TRandomIter&heap, typename TRandomIter::value_type::idx_type self_idx) {
        const auto& self = heap[self_idx];
        if(TRandomIter::value_type::INVALID_AVLPTR() != self.left) {
            std::cout << self.idx << "==" << heap[self.left].parent << std::endl;
            assert(self.idx == heap[self.left].parent);
            assert_tree(heap, self.left);
        }
        if(TRandomIter::value_type::INVALID_AVLPTR() != self.right) {
            std::cout << self.idx << "==" << heap[self.right].parent << std::endl;
            assert(self.idx == heap[self.right].parent);
            assert_tree(heap, self.right);
        }
        int calcheight = 0;
        int leftheight = 0;
        int rightheight = 0;
        if(TRandomIter::value_type::INVALID_AVLPTR() != self.right) {
            rightheight = heap[self.right].height;
            calcheight = heap[self.right].height+1;
        }
        if(TRandomIter::value_type::INVALID_AVLPTR() != self.left) {
            leftheight = heap[self.left].height;
            calcheight = std::max(calcheight,heap[self.left].height+1);
        }
        assert(calcheight == self.height);

        // check height property
        auto diff = rightheight-leftheight;
        assert( 0 == diff || 1 == diff || -1 == diff );
    }
    template <typename TRandomIter>
    struct inorder_iterator : public std::iterator<std::forward_iterator_tag
                              , typename TRandomIter::value_type
                              , typename TRandomIter::difference_type
                              , typename TRandomIter::pointer
                              , typename TRandomIter::reference > {

        using inorder_state = std::pair<typename TRandomIter::value_type::idx_type,int>;
        std::vector<inorder_state> stk;
        
        auto next(TRandomIter&heap) {
            while(stk.size() > 0) {
                auto top = std::get<0>(stk.back());
                auto state = std::get<1>(stk.back());
                if(0 == state) {
                    if(TRandomIter::value_type::INVALID_AVLPTR() != heap[top].left) {
                        // go left
                        stk.back() = inorder_state(top,1);
                        stk.emplace_back(heap[top].left, 0);
                    } else {
                        stk.back() = inorder_state(top,2);
                        return top;
                    }
                } else if(1 == state) {
                    stk.back() = inorder_state(top,2);
                    return top;
                } else if(2 == state) {
                    if(TRandomIter::value_type::INVALID_AVLPTR() != heap[top].right) {
                        stk.back() = inorder_state(top,3);
                        stk.emplace_back(heap[top].right, 0);
                    } else {
                        stk.pop_back(); // done
                    }
                } else if(3 == state) {
                    stk.pop_back();
                }
            }
            return TRandomIter::value_type::INVALID_AVLPTR();
        }

        //!===========================================================
        //! This search conditionally explores both left and right
        //!
        //! \NOTE Inspired by CLRS SEARCH-INTERVAL
        //!===========================================================
        template <typename GO_LEFT = std::less<typename TRandomIter::value_type::key_type>
            , typename K_IS_EQUAL = std::equal_to<typename TRandomIter::value_type::key_type>
            , typename GO_RIGHT = std::greater<typename TRandomIter::value_type::key_type>  >
        auto search_left_right(const TRandomIter&                   heap
                , const typename TRandomIter::value_type::key_type& aKey
                , const GO_LEFT&                                    go_left     //!< condition for exploring left subtree
                , const K_IS_EQUAL&                                 is_equal
                , const GO_RIGHT&                                   go_right) {

            while(stk.size() > 0) {
                const auto topidx = std::get<0>(stk.back());
                const auto state = std::get<1>(stk.back());
                const auto& top = heap[topidx];
                if(0 == state) {
                    //std::cout << "comparing " << aKey.x << " and " << key.x << std::endl;
                    stk.back() = inorder_state(topidx,1);      // go to state 1
                    if(TRandomIter::value_type::INVALID_AVLPTR() != top.left && go_left(aKey, top.key)) {
                        stk.emplace_back(top.left, 0);
                    }
                    continue;
                } else if(1 == state) {
                    stk.back() = inorder_state(topidx,2);      // go to state 2
                    if(is_equal(aKey,top.key)) {

                        return top.idx;                     // found here
                    }
                    continue;
                } else if(2 == state) {
                    stk.pop_back();
                    if(TRandomIter::value_type::INVALID_AVLPTR() != top.right && go_right(aKey,top.key)) {
                        stk.emplace_back(top.right, 0);
                    }
                    continue;
                }
            }
            return TRandomIter::value_type::INVALID_AVLPTR();
        }
    };

    template <typename TRandomIter>
    auto begin(TRandomIter& heap, typename TRandomIter::value_type::idx_type self_idx) { // traverses tree in in-order
        auto result = inorder_iterator<TRandomIter>();
        result.stk.emplace_back(self_idx,0);
        return result;
    }

    template <typename TAVLNode>
    void dump_node(const TAVLNode& node, std::string& prefix) {
        for(int i = node.height+1; i < prefix.size(); i++) {
            std::cout << prefix[i];
        }
        std::cout << "idx=" << node.idx << ",val=" << node.key.avl_key() << ',' << ",aug=" << node.key.avl_aug_val() << ",height=" << node.height << ",parent=" << node.parent << ",left=" << node.left << ",right=" << node.right << std::endl;
    }

    template <typename TRandomIter>
    static void dump_all(TRandomIter&heap, typename TRandomIter::value_type::idx_type root) {
        std::string prefix = "\t\t\t\t\t\t";
        std::cout << "Dump sorted ========================= " << root << std::endl;
        auto beg = begin(heap, root);
        do {
            auto i = beg.next(heap);
            if(TRandomIter::value_type::INVALID_AVLPTR() == i) {
                break;
            }
            dump_node(heap[i], prefix);
        } while(true);
        std::cout << "End dump ============================ " << std::endl;
    }

    template <typename K>
    struct avl_comp_equal {
        constexpr bool operator()(const K &lhs, const K &rhs) const {
            if(lhs.avl_key() == rhs.avl_key()) {
                return true;
            }
            return false;
        }
    };

    template <typename K>
    struct avl_comp_less {
        constexpr bool operator()(const K &lhs, const K &rhs) const {
            if(lhs.avl_key() < rhs.avl_key()) {
                return true;
            }
            return false;
        }
    };

    //! \brief sort in descending order
    template <typename K>
    struct avl_comp_greater {
        constexpr bool operator()(const K &lhs, const K &rhs) const {
            if(lhs.avl_key() > rhs.avl_key()) {
                return true;
            }
            return false;
        }
    };

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

    template <typename K>
    struct avl_search_go_right {
        constexpr bool operator()(const K &target, const K &pivot) const {
            if(target.avl_key() > pivot.avl_key()) {       // obviously, according to binary tree invariant
                return true;
            }
            return false;
        }
    };

    template <typename K>
    struct avl_search_overlaps {
        constexpr bool operator()(const K &target, const K &pivot) const {
            if(target.avl_key() >= pivot.avl_key() && target.avl_key() < pivot.avl_key_end()) {
                return true;
            }
            if(pivot.avl_key() >= target.avl_key() && pivot.avl_key() < target.avl_key_end()) {
                return true;
            }
            return false;
        }
    };
};

/*****************************************************************************
 * Test sorting
 *
 * ***************************************************************************/

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


using avl_test_number = avltree::AVLNode<test_number<long>>;
// test avl tree sorting
template<const int LIMIT=6>
int test_avl_tree_sorting()
{
    std::vector<avl_test_number > heap;
    auto test_less = avltree::avl_comp_less<test_number<long>>();
    auto test_equal = avltree::avl_comp_equal<test_number<long>>();

    auto x = test_number<long>(0);
    heap.emplace_back(x, 0);
    int explored[LIMIT+1];
    for(int i = 0; i < (LIMIT+1);i++) {
        explored[i] = 0;
    }
 
    std::string prefix = "\t\t\t\t\t\t";
    while(!heap.empty()) {
        if(heap.back().key.avl_key() < LIMIT) {
            
            explored[heap.back().key.avl_key()]--;
            heap.back().key.inc();
            explored[heap.back().key.avl_key()]++;
            std::cout << heap.size() << " inc " << heap.back().key.avl_key() << " ex " << explored[heap.back().key.avl_key()] << std::endl;
            if(explored[heap.back().key.avl_key()] > 1) {
                continue; // already explored
            }
            
        } else {
            //std::cout << heap.size() << " pop " << std::endl;
            explored[heap.back().key.avl_key()]--;
            heap.pop_back();
            continue;
        }
        if(heap.size() == LIMIT) {

            // build tree
            unsigned root = 0;
            for(unsigned i = 1; i < heap.size(); i++) {
                root = avltree::insert(heap, root, i, test_less, test_equal);
            }

            unsigned k = 0;

            do {
                assert(avl_test_number::INVALID_AVLPTR() == heap[root].parent);
                // dump sorted
                avltree::dump_all(heap,root);
                for(unsigned i = 0; i < heap.size(); i++) {
                    avltree::assert_tree(heap, i);
                }
                std::cout << "End assert ========================== " << std::endl;

                root = avltree::pop(heap, k);
                k++;

            } while(k < heap.size() && avl_test_number::INVALID_AVLPTR() != root);
            std::cout << ".............................." << std::endl;

            // unplug all
            for(unsigned i = 0; i < heap.size(); i++) {
                unplug(heap, i);
            }

            std::cout << heap.back().key.avl_key() << " dump " << std::endl;
        } else {
            auto y = test_number<long>(0);
            heap.emplace_back(y, heap.size());
            //std::cout << heap.size() << "push " << std::endl;
        }
    }
    return 0;
}

/*****************************************************************************
 * Test interval sorting
 *
 * ***************************************************************************/

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

    void augment_reset() {
        max_end = end;
        max_left_end = val;
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


// test avl tree sorting
template<const int LIMIT=6>
int test_avl_tree_interval_sorting()
{
    std::vector<avltree::AVLNode<test_interval> > heap;
    auto test_less = avltree::avl_comp_less<test_interval>();
    auto test_equal = avltree::avl_comp_equal<test_interval>();

    auto test_overlaps = avltree::avl_search_overlaps<test_interval>();
    auto test_go_left = avltree::avl_search_go_left<test_interval>();
    auto test_go_right = avltree::avl_search_go_right<test_interval>();

    auto x = test_interval(0,2);
    heap.emplace_back(x, 0);
    int explored[LIMIT+1];
    for(int i = 0; i < (LIMIT+1);i++) {
        explored[i] = 0;
    }
 
    std::string prefix = "\t\t\t\t\t\t";
    while(!heap.empty()) {
        if(heap.back().key.avl_key() < LIMIT) {
            
            explored[heap.back().key.avl_key()]--;
            heap.back().key.inc();
            explored[heap.back().key.avl_key()]++;
            std::cout << heap.size() << " inc " << heap.back().key.avl_key() << " ex " << explored[heap.back().key.avl_key()] << std::endl;
            if(explored[heap.back().key.avl_key()] > 1) {
                continue; // already explored
            }
            
        } else {
            //std::cout << heap.size() << " pop " << std::endl;
            explored[heap.back().key.avl_key()]--;
            heap.pop_back();
            continue;
        }
        if(heap.size() == LIMIT) {

            // build tree
            long root = 0;
            long existing = 0;
            for(unsigned i = 1; i < heap.size(); i++) {
                std::tie(root,existing) = avltree::insert(heap, root, i, test_less, test_equal);
            }

            unsigned k = 0;

            do {
                assert(-1 == heap[root].parent);
                // dump sorted
                avltree::dump_all(heap,root);
                for(unsigned i = 0; i < heap.size(); i++) {
                    avltree::assert_tree(heap, i);
                }
                std::cout << "End assert ========================== " << std::endl;

                // do a search operation
                auto beg = avltree::begin(heap, root);
                std::cout << "Search assert " << k << std::endl;
                assert(k == beg.search_left_right(heap, heap[k].key, test_go_left, test_equal, test_go_right));

                root = avltree::pop(heap, k);
                std::cout << "Popping " << k << std::endl;
                k++;

            } while(k < heap.size() && -1 != root);
            std::cout << ".............................." << std::endl;

            // unplug all
            for(unsigned i = 0; i < heap.size(); i++) {
                avltree::unplug(heap, i);
            }

            std::cout << heap.back().key.avl_key() << " dump " << std::endl;
        } else {
            auto y = test_interval(0,2);
            heap.emplace_back(y, heap.size());
            //std::cout << heap.size() << "push " << std::endl;
        }
    }
    return 0;
}



// test avl tree
int main() {
    //test_avl_tree_sorting<6>();
    test_avl_tree_interval_sorting<6>();
    return 0;
}
