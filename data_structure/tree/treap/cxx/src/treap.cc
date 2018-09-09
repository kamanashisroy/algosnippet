
#include <cstddef> // defines size_t


#ifdef ALGO_TEST
#define ALGO_SNIPPET_DEBUG
#include <iostream>
#endif

#ifdef ALGO_SNIPPET_DEBUG
#define ALGO_SNIPPET_TO_STRING
#include <cassert>
#endif

#ifdef ALGO_SNIPPET_TO_STRING
#include <sstream>
#endif

namespace algo_snippet {

    template<typename WT, typename KT>
    class algo_treap; // forward declaration

    template<typename WT, typename KT>
    class algo_treap_head {
    public:
        algo_treap_head() : root(NULL), size_(0){ }
        void insert(WT heap_property, KT bst_key, std::allocator<algo_treap<WT,KT>> &allocator);
        void insert(algo_treap<WT,KT>& given);
        void insert(algo_treap<WT,KT>* given);
        const algo_treap<WT,KT>* query(WT heap_property_limit, const unsigned int rank) const;
        const std::size_t size() const {
            return size_;
        }
        const algo_treap<WT,KT>* get_root() const {
            return root;
        }
        #ifdef ALGO_SNIPPET_TO_STRING
        const std::string to_string() const {
            if(root) {
                return root->to_string();
            } else {
                return "<empty>";
            }
        }
        #endif
        const void assert_treap() const;
    private:
        algo_treap<WT,KT>*root;
        std::size_t size_;
        friend algo_treap<WT,KT>;
    };

    template<typename WT, typename KT>
    class algo_treap {
    public:

        algo_treap() = default;

        algo_treap(WT heap_property, KT bst_key, std::size_t id, algo_treap_head<WT,KT> &head)
            : heap_property_(heap_property),bst_key_(bst_key), id_(id),left_(NULL),right_(NULL),parent_(NULL),head_(head) {
        }

        ~algo_treap() {
#if 0
            // cleanup
            if(NULL != left_) {
                head_->get_allocator().deallocate(left);
                left_ = NULL;
            }
            if(NULL != right_) {
                head_->get_allocator().deallocate(left);
                right_ = NULL;
            }
#endif
        }

        // update heap_property of the treap
        void update_heap_property(WT heap_property) {
            // implement update heap_property
            if(heap_property < heap_property_) { // heap_property is reduced
                // we should go up
                heap_property_ = heap_property;
                up_heap();
            } else if(heap_property > heap_property_) { // heap_property is increased
                // we should go down
                heap_property_ = heap_property;
                while( (left_ && left_->get_heap_property() < get_heap_property()) || (right_ && right_->get_heap_property() < get_heap_property()) ) {
                    if(left_ && !right_) {
                        left_->up_heap();
                    } else if(right_ && !left_) {
                        right_->up_heap();
                    } else if(right_ && left_) {
                        if(left_->get_heap_property() <= right_->get_heap_property()) {
                            // I guess we can do balancing when the heap_propertys are equal
                            left_->up_heap();
                        } else {
                            right_->up_heap();
                        }
                    }
                }
            }
        }

        //! \returns the new root
        algo_treap<WT,KT>*insert(algo_treap*other) {

            // check heap-property
            if(other->get_heap_property() < get_heap_property()) { // heap-property needs fix
                // other should be the root
                return other->insert(this);
            } else { // heap-property is good
                if(other->get_bst_key() <= get_bst_key()) {
                    // so other bst_key goes left
                    if(NULL == left_) { // we have empty spot
                        left_ = other; // put the other on left
                        left_->parent_ = this;
                    } else { // insert left
                        left_ = left_->insert(other);
                        left_->parent_ = this;
                    }
                } else {
                    // so the other goes right
                    if(NULL == right_) { // empty spot
                        right_ = other;
                        right_->parent_ = this;
                    } else {
                        right_ = right_->insert(other);
                        right_->parent_ = this;
                    }
                }
                return this;
            }
        }

        inline const KT get_bst_key() const {
            return bst_key_;
        }

        inline const WT get_heap_property() const {
            return heap_property_;
        }

        inline const std::size_t id() const {
            return id_;
        }

        #ifdef ALGO_SNIPPET_TO_STRING
        const std::string to_string(std::size_t depth=0) const {
            std::ostringstream output;
            to_string(output, depth);
            return output.str();
        }
        const std::string repr() const {
            std::ostringstream output;
            output << "Treap(k=" << get_bst_key() << ",w=" << get_heap_property() << ",id=" << id() << ")";
            return output.str();
        }
        const void to_string(std::ostringstream& output, std::size_t depth) const {
            if(left_) {
                left_->to_string(output, depth+1);
            }
            for(std::size_t i = 0; i < depth; i++) {
                output << '\t';
            }
            output << "(k=" << get_bst_key() << ",w=" << get_heap_property() << ",id=" << id() << ")" << std::endl;
            if(right_) {
                right_->to_string(output, depth+1);
            }
        }
        #endif

        //! \brief rebuild the node.
        //! \NOTE it must be done before inserting into the head/tree
        void rebuild(WT heap_property, KT bst_key) {
            heap_property_ = heap_property;
            bst_key_ = bst_key;
            left_ = NULL;
            right_ = NULL;
            parent_ = NULL;
            head_ = NULL;
            id_ = 0;
        }

        const void assert_treap() const {
            if(get_left()) {
                assert(get_left()->parent_ == this);
                assert(get_left()->get_bst_key() <= get_bst_key());
                assert(get_left()->get_heap_property() >= get_heap_property());
                get_left()->assert_treap();
            }
            if(get_right()) {
                assert(get_right()->parent_ == this);
                assert(get_right()->get_bst_key() >= get_bst_key());
                assert(get_right()->get_heap_property() >= get_heap_property());
                get_right()->assert_treap();
            }
        }

    protected:
        //! \brief overloading rebuild here allow to override the id
        virtual void rebuild_link(std::size_t id, algo_treap_head<WT,KT> &head) {
            id_ = id;
            head_ = &head;
        }


    private:
        WT heap_property_; //!< heap_property sets relative-depth of the node
        KT bst_key_; //!< bst_key is used to order the binary search tree
        std::size_t id_;

        algo_treap<WT,KT>*left_;
        algo_treap<WT,KT>*right_;
        algo_treap<WT,KT>*parent_;
        algo_treap_head<WT,KT> *head_;

        const algo_treap<WT,KT>* get_left() const {
            return left_;
        }

        const algo_treap<WT,KT>* get_right() const {
            return right_;
        }

        void up_heap() {
            // implement update heap_property
            while(NULL != parent_ && parent_->get_heap_property() > get_heap_property()) {
                // rotate
                if(parent_->right_ == this) { // this is right child of parent
                    // before p=parent, x=this
                    //                 p
                    //            pl          x
                    //                    l       r
                    // so parent has to be our left child now
                    // after
                    //                           x
                    //                    p            r
                    //                pl     l
                    // update parent
                    #ifdef ALGO_SNIPPET_DEBUG
                    assert(parent_->get_bst_key() <= get_bst_key());
                    #endif
                    parent_->right_ = left_;
                    if(parent_->right_) {
                        #ifdef ALGO_SNIPPET_DEBUG
                        assert(parent_->right_->parent_ == this);
                        #endif
                        parent_->right_->parent_ = parent_; // link middle
                    }

                    // update this
                    left_ = parent_;
                    // grand-parent is parent now
                    parent_ = left_->parent_; // link grand-parent
                    left_->parent_ = this; // link left
                    
                    // fix grand-parent
                    if(parent_) {
                        #ifdef ALGO_SNIPPET_DEBUG
                        assert(parent_->right_ == left_ || parent_->left_ == left_);
                        #endif
                        if(parent_->right_ == left_) {
                            parent_->right_ = this;
                        } else {
                            parent_->left_ = this;
                        }
                    } else {
                        // update root
                        head_->root = this;
                    }
                } else { // >= this is left child of parent
                    // before p=parent, x=this
                    //                 p
                    //            x         pr
                    //        l      m
                    // so parent has to be our right child now
                    // after
                    //            x    
                    //        l         p
                    //              m       pr
                    // update parent
                    #ifdef ALGO_SNIPPET_DEBUG

                    std::cout << repr() << "this is left child of =" << parent_->repr() << std::endl;
                    std::cout << repr() << "==" << parent_->left_->repr() << std::endl;
                    assert(parent_->left_ == this);
                    assert(parent_->get_bst_key() >= get_bst_key());
                    #endif
                    parent_->left_ = right_;
                    if(parent_->left_) {
                        #ifdef ALGO_SNIPPET_DEBUG
                        assert(parent_->left_->parent_ == this);
                        #endif
                        parent_->left_->parent_ = parent_; // link middle
                    }

                    // update this
                    right_ = parent_;
                    // grand-parent is parent now
                    parent_ = right_->parent_; // link grand-parent
                    right_->parent_ = this; // link right(previously parent)
                    
                    // fix grand-parent
                    if(parent_) {
                        #ifdef ALGO_SNIPPET_DEBUG
                        std::cout << "moving-up =" << repr() << std::endl;
                        std::cout << "grandpa =" << parent_->repr() << std::endl;
                        std::cout << "prev pa = " << right_->repr() << std::endl;
                        if(parent_->right_) {
                            std::cout << "right-uncle = " << parent_->right_->repr() << std::endl;
                        }
                        if(parent_->left_) {
                            std::cout << "left-uncle= " << parent_->left_->repr() << std::endl;
                        }
                        assert(parent_->right_ == right_ || parent_->left_ == right_);
                        #endif
                        if(parent_->right_ == right_) {
                            parent_->right_ = this;
                        } else {
                            parent_->left_ = this;
                        }
                    } else {
                        // update root
                        head_->root = this;
                    }
                } // else
            } // while
        }
        friend algo_treap_head<WT,KT>;

    };

}

template<typename WT,typename KT>
void algo_snippet::algo_treap_head<WT,KT>::insert(algo_snippet::algo_treap<WT,KT>*node) {
    node->rebuild_link(size_++,*this);
    if(root) {
        root = root->insert(node);
        root->parent_ = NULL;
    } else {
        root = node;
    }
}

template<typename WT,typename KT>
void algo_snippet::algo_treap_head<WT,KT>::insert(WT heap_property, KT bst_key, std::allocator<algo_treap<WT,KT>> &allocator) {
    algo_snippet::algo_treap<WT,KT>*node = allocator.allocate(1);
    node->rebuild(heap_property,bst_key);
    insert(node);
}

template<typename WT,typename KT>
void algo_snippet::algo_treap_head<WT,KT>::insert(algo_snippet::algo_treap<WT,KT>&node) {
    insert(&node);
}

#include <vector>
#include <cstring>

template<typename WT,typename KT>
const algo_snippet::algo_treap<WT,KT>*algo_snippet::algo_treap_head<WT,KT>::query(WT heap_property_limit, const unsigned int rank) const {
    if(!root || 0 == rank) {
        return NULL;
    }
    bool expanded[size()];
    memset(expanded, 0, sizeof(expanded));
    
    unsigned int xrank = 0;
    static std::vector<const algo_treap<WT,KT>*> fringe;
    fringe.clear();
    fringe.push_back(root);
    while(!fringe.empty()) {
        const algo_snippet::algo_treap<WT,KT>*x = fringe.back();
        fringe.pop_back();

        // limit heap_property
        if(x->get_heap_property() > heap_property_limit) {
            continue;
        }

        if(!expanded[x->id()]) {
            // expand the node
            #ifdef ALGO_TEST
            std::cout << "expanding " << x->repr() << std::endl;
            #endif

            // push the children to the fringe
            if(x->get_right() && x->get_right()->get_heap_property() <= heap_property_limit) {
                fringe.push_back(x->get_right());
            }
            fringe.push_back(x); // push it in-order position
            if(x->get_left() && x->get_left()->get_heap_property() <= heap_property_limit) {
                fringe.push_back(x->get_left());
            }
            expanded[x->id()] = true;
        } else {
            xrank++;
            #ifdef ALGO_TEST
            std::cout << "collecting " << xrank << "=" << x->repr() << std::endl;
            #endif
            if(xrank == rank) {
                return x;
            }
        }
    }
    return NULL;
}

template<typename WT,typename KT>
const void algo_snippet::algo_treap_head<WT,KT>::assert_treap() const {
    if(get_root()) {
        get_root()->assert_treap();

        // traverse in-order and check the order
        std::size_t rank = 0;
        KT prev;
        bool expanded[size()];
        memset(expanded, 0, sizeof(expanded));
        
        static std::vector<const algo_treap<WT,KT>*> fringe;
        fringe.clear();
        fringe.push_back(get_root());
        while(!fringe.empty()) {
            const algo_snippet::algo_treap<WT,KT>*x = fringe.back();
            fringe.pop_back();

            if(!expanded[x->id()]) {
                // expand the node

                // push the children to the fringe
                if(x->get_right() ) {
                    fringe.push_back(x->get_right());
                }
                fringe.push_back(x); // push it in-order position
                if(x->get_left()) {
                    fringe.push_back(x->get_left());
                }
                expanded[x->id()] = true;
            } else {
                rank++;
                if(rank > 1) {
                    assert(prev <= x->get_bst_key());
                }
                prev = x->get_bst_key();
            }
        }
    }
}



#ifdef ALGO_TEST

using namespace std;
using namespace algo_snippet;

int main() {
    algo_treap_head<int,int> head;
    int heap_key[] = {32,14,12,523,13,1,7,23,7,2,7,4,89,8,3,26,94};
    constexpr int heap_size = (sizeof(heap_key)/sizeof(heap_key[0]));
    algo_treap<int,int> nodes[heap_size];

    for(int i = 0; i < heap_size; i++) {
        cout << "adding key=" << heap_key[i] << " heap_property= " << i << endl;
        //head.insert(i,heap_key[i]);
        nodes[i].rebuild(i,heap_key[i]);
        head.insert(nodes[i]);
    }
    cout << "=============Treap======================" << endl;
    cout << head.to_string() << endl;
    cout << "=============Treap======================" << endl;
    cout << "query heap_property_limit=100 rank=6 " << endl;
    algo_treap<int,int>* result = const_cast<algo_treap<int,int>*>(head.query(100,6));
    cout << "result = " << result->repr() << endl;
    // now increase heap_property of it
    cout << "Now increasing heap_property to 11" << endl;
    cout << "=============Treap======================" << endl;
    cout << head.to_string() << endl;
    cout << "=============Treap======================" << endl;
    result->update_heap_property(11);
    cout << "=============Treap======================" << endl;
    cout << head.to_string() << endl;
    cout << "=============Treap======================" << endl;
    cout << "Now going back to original(8)" << endl;
    result->update_heap_property(8);
    cout << "=============Treap======================" << endl;
    cout << head.to_string() << endl;
    cout << "=============Treap======================" << endl;
    head.assert_treap();

    int heap_key2[] = {7,8,9,12,15};
    int heap_weight2[] = {6,7,2,15,9};
    constexpr int heap_size2 = (sizeof(heap_key2)/sizeof(heap_key2[0]));
    algo_treap_head<int,int> head2;
    algo_treap<int,int> nodes2[heap_size2];
    for(int i = 0; i < heap_size2; i++) {
        cout << "adding key=" << heap_key2[i] << " heap_property= " << heap_weight2[i] << endl;
        //head.insert(i,heap_key[i]);
        nodes2[i].rebuild(heap_weight2[i],heap_key2[i]);
        head2.insert(nodes2[i]);
        head2.assert_treap();
        cout << head2.to_string() << endl;
        cout << "=============Treap======================" << endl;
    }

    return 0;
}
#endif // ALGO_TEST

