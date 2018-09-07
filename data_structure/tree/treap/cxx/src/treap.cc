
#include <cstddef> // defines size_t


#ifdef ALGO_TEST
#define ALGO_SNIPPET_DEBUG
#include <iostream>
#endif

#ifdef ALGO_SNIPPET_DEBUG
#include <sstream>
#include <cassert>
#endif

namespace algo_snippet {

    template<typename WT, typename KT>
    class algo_treap; // forward declaration

    template<typename WT, typename KT>
    class algo_treap_head {
    public:
        algo_treap_head() : root(NULL), size_(0){ }
        void insert(WT weight, KT key);
        const algo_treap<WT,KT>* query(WT weight_limit, const unsigned int rank);
        const std::size_t size() const {
            return size_;
        }
        #ifdef ALGO_SNIPPET_DEBUG
        const std::string to_string() const {
            if(root) {
                return root->to_string();
            } else {
                return "<empty>";
            }
        }
        #endif
    private:
        algo_treap<WT,KT>*root;
        std::size_t size_;
        friend algo_treap<WT,KT>;
    };

    template<typename WT, typename KT>
    class algo_treap {
    public:

        algo_treap() = default;

        algo_treap(WT weight, KT key, std::size_t id, algo_treap_head<WT,KT> &root)
            : weight_(weight),key_(key), id_(id),left_(NULL),right_(NULL),parent_(NULL),root_(root) {
        }

        ~algo_treap() {
            // cleanup
            if(NULL != left_) {
                delete left_;
                left_ = NULL;
            }
            if(NULL != right_) {
                delete right_;
                right_ = NULL;
            }
            
        }

        // update weight of the treap
        void update(WT weight) {
            // implement update weight
            if(weight < weight_) { // weight is reduced
                // we should go up
                weight_ = weight;
                move_up();
            } else if(weight > weight_) { // weight is increased
                // we should go down
                weight_ = weight;
                if(left_ && !right_) {
                    left_->move_up();
                } else if(right_ && !left_) {
                    right_->move_up();
                } else if(right_ && left_) {
                    if(left_->get_weight() <= right_->get_weight()) {
                        // I guess we can do balancing when the weights are equal
                        left_->move_up();
                    } else {
                        right_->move_up();
                    }
                }
            }
        }

        //! \returns the new root
        algo_treap<WT,KT>*insert(algo_treap*other) {

            // check heap-property
            if(other->get_weight() < get_weight()) { // heap-property needs fix
                // other should be the root
                return other->insert(this);
            } else { // heap-property is good
                if(other->get_key() <= get_key()) {
                    // so other key goes left
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

        inline const KT get_key() const {
            return key_;
        }

        inline const WT get_weight() const {
            return weight_;
        }

        inline const std::size_t id() const {
            return id_;
        }

        #ifdef ALGO_SNIPPET_DEBUG
        const std::string to_string(std::size_t depth=0) const {
            std::ostringstream output;
            to_string(output, depth);
            return output.str();
        }
        const std::string repr() const {
            std::ostringstream output;
            output << "Treap(k=" << get_key() << ",w=" << get_weight() << ",id=" << id() << ")" << std::endl;
            return output.str();
        }
        const void to_string(std::ostringstream& output, std::size_t depth) const {
            if(left_) {
                left_->to_string(output, depth+1);
            }
            for(std::size_t i = 0; i < depth; i++) {
                output << '\t';
            }
            output << "(k=" << get_key() << ",w=" << get_weight() << ",id=" << id() << ")" << std::endl;
            if(right_) {
                right_->to_string(output, depth+1);
            }
        }
        #endif

    private:
        WT weight_; //!< weight sets relative-depth of the node
        KT key_; //!< key is used to order the binary search tree
        std::size_t id_;

        algo_treap<WT,KT>*left_;
        algo_treap<WT,KT>*right_;
        algo_treap<WT,KT>*parent_;
        algo_treap_head<WT,KT> &root_;

        const algo_treap<WT,KT>* get_left() const {
            return left_;
        }

        const algo_treap<WT,KT>* get_right() const {
            return right_;
        }

        void move_up() {
            // implement update weight
            while(NULL != parent_ && parent_->get_weight() > get_weight()) {
                // rotate
                if(parent_->get_key() < get_key()) { // this is right child of parent
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
                    assert(parent_->right_ == this);
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
                        root_.root = this;
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
                    assert(parent_->left_ == this);
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
                        root_.root = this;
                    }
                } // else
            } // while
        }
        friend algo_treap_head<WT,KT>;

    };

}

template<typename WT,typename KT>
void algo_snippet::algo_treap_head<WT,KT>::insert(WT weight, KT key) {
    algo_snippet::algo_treap<WT,KT>*node = new algo_snippet::algo_treap<WT,KT>(weight, key, size_++, *this);
    if(root) {
        root = root->insert(node);
        root->parent_ = NULL;
    } else {
        root = node;
    }
}

#include <vector>
#include <cstring>

template<typename WT,typename KT>
const algo_snippet::algo_treap<WT,KT>*algo_snippet::algo_treap_head<WT,KT>::query(WT weight_limit, const unsigned int rank) {
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

        // limit weight
        if(x->get_weight() > weight_limit) {
            continue;
        }

        if(!expanded[x->id()]) {
            // expand the node
            #ifdef ALGO_TEST
            std::cout << "expanding " << x->repr() << std::endl;
            #endif

            // push the children to the fringe
            if(x->get_right() && x->get_right()->get_weight() <= weight_limit) {
                fringe.push_back(x->get_right());
            }
            fringe.push_back(x); // push it in-order position
            if(x->get_left() && x->get_left()->get_weight() <= weight_limit) {
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

#ifdef ALGO_TEST

using namespace std;
using namespace algo_snippet;

int main() {
    algo_treap_head<int,int> head;
    int heap_key[] = {32,14,12,523,13,1,7,23,7,2,7,4,89,8,3,26,94};
    constexpr int heap_size = (sizeof(heap_key)/sizeof(heap_key[0]));

    for(int i = 0; i < heap_size; i++) {
        cout << "adding key=" << heap_key[i] << " weight= " << i << endl;
        head.insert(i,heap_key[i]);
    }
    cout << "=============Treap======================" << endl;
    cout << head.to_string() << endl;
    cout << "=============Treap======================" << endl;
    cout << "query weight_limit=100 rank=6 " << endl;
    algo_treap<int,int>* result = const_cast<algo_treap<int,int>*>(head.query(100,6));
    cout << "result = " << result->repr() << endl;
    // now increase weight of it
    cout << "Now increasing weight to 11" << endl;
    cout << "=============Treap======================" << endl;
    cout << head.to_string() << endl;
    cout << "=============Treap======================" << endl;
    result->update(11);
    cout << "=============Treap======================" << endl;
    cout << head.to_string() << endl;
    cout << "=============Treap======================" << endl;
    result->update(8);
    cout << "=============Treap======================" << endl;
    cout << head.to_string() << endl;
    cout << "=============Treap======================" << endl;
    return 0;
}
#endif // ALGO_TEST

