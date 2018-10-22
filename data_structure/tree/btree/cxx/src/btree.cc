// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
dary_heap.cc file is part of Algosnippet.
Algosnippet is a collection of practice data-structures and algorithms
Copyright (C) 2018  Kamanashis Roy
Algosnippet is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
Algosnippet is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with Algosnippet.  If not, see <https://www.gnu.org/licenses/>.
*/


#include <array>
#ifdef DEBUG_BGEN_TREE
#include <iostream>
#include <cassert>
#endif

namespace algo_snippet {
    //! \brief generalized b-tree
    //! \NOTE MAX_ORDER Must be odd
    template <typename KEYTYPE, typename VALTYPE, unsigned int MAX_ORDER>
    class bgen_tree {
    public:
        bgen_tree() : order(0) {
            // MAX_ORDER Must be odd
            static_assert((MAX_ORDER & 0x1) == 0x1 && MAX_ORDER >= 3);
            child.fill(NULL);
        }

        
        bool insert(KEYTYPE xkey, VALTYPE xval) {
            return insert_internal(xkey, xval, NULL, 0);
        }

        bool find(KEYTYPE xkey, bgen_tree*container, unsigned int &index) {
            if(0 == order) {
                return false; // empty tree
            }
            for(unsigned int i = 0; i < order; i++) {
                if(xkey < key[i]) {
                    if(child[i]) {
                        return child[i].find(xkey, container, index);
                    }
                    return false;
                } else if(xkey == key[i]) {
                    // found
                    container = this;
                    index = i;
                    return true;
                }
            }
            if(child[order]) {
                return child[order].find(xkey, container, index);
            }
            return false;
        }

        const VALTYPE& get(unsigned int index) const {
#ifdef DEBUG_BGEN_TREE
            assert(index < order);
#endif // DEBUG_BGEN_TREE
            return val[index];
        }

#ifdef DEBUG_BGEN_TREE
        void dump(std::ostream& out, unsigned int level) {
            if(child[order]) {
                child[order]->dump(out, level+1);
            }
            for(int i = order-1; i >= 0; i--) {
                for(unsigned int i = 0; i < level; i++) {
                    //out << ' ';
                    out << '\t';
                }
                out << '[' << key[i] << ',' << val[i] << ']' << std::endl;
                if(child[i]) {
                    child[i]->dump(out, level+1);
                }
            }
        }
#endif // DEBUG_BGEN_TREE
    private:
        void split_root() {
#ifdef DEBUG_BGEN_TREE
            assert(MAX_ORDER == order);
#endif // DEBUG_BGEN_TREE

            // make 2 half nodes

            // left
            bgen_tree* lchild = new bgen_tree();
            const unsigned int half_order = order>>1;
            for(unsigned int i = 0; i < half_order; i++) {
                lchild->key[i] = key[i];
                lchild->val[i] = val[i];
                lchild->child[i] = child[i];
            }
            lchild->child[half_order] = child[half_order];
            lchild->order = half_order;

            // make center node
            child[0] = lchild;
            key[0] = key[half_order];
            val[0] = val[half_order];

            // right
            bgen_tree* rchild = new bgen_tree();
            for(unsigned int i = half_order+1; i < order; i++) {
                rchild->key[i-half_order-1] = key[i];
                rchild->val[i-half_order-1] = val[i];
                rchild->child[i-half_order-1] = child[i];
            }
            rchild->child[half_order] = child[order];
            rchild->order = half_order;
            child[1] = rchild;

            // Now the order of current tree is 1
            order = 1;
        }
        void split(bgen_tree*parent, unsigned int spot) {
            const unsigned int half_order = order>>1;

            // left sibling
            bgen_tree* lchild = new bgen_tree();
            for(unsigned int i = 0; i < half_order; i++) {
                lchild->key[i] = key[i];
                lchild->val[i] = val[i];
                lchild->child[i] = child[i];
            }
            lchild->child[half_order] = child[half_order];
            lchild->order = half_order;

            // move the middle node to parent
            parent->split_insert(key[half_order],val[half_order], lchild, spot);

            // move last half to the first
            for(unsigned int i = half_order+1; i < order; i++) {
                key[i-half_order-1] = key[i];
                val[i-half_order-1] = val[i];
                child[i-half_order-1] = child[i];
            }
            child[half_order] = child[order];
            order = half_order;
        }
        //! \return true when successful, false when key is duplicate
        bool insert_internal(KEYTYPE xkey, VALTYPE xval, bgen_tree*parent, unsigned int parent_spot) {
            if(order >= MAX_ORDER) {
                // needs splitting
                if(parent) {
                    split(parent, parent_spot);
                } else {
                    split_root();
                }
            }

            // try to find the child-node
            if(0 == order) {
                // base case
                key[order] = xkey;
                val[order] = xval;
                child[0] = NULL;
                child[1] = NULL;
                order++;
                return true;
            } else {

                // find empty spot or insert to child node
                int spot = -1;
                for(unsigned int i = 0; i < order; i++) {
                    if(xkey < key[i]) {
                        if(child[i]) {
                            return child[i]->insert_internal(xkey, xval, this, i);
                        }
                        spot = i;
                        break;
                    } else if(xkey == key[i]) {
                        // already inserted
                        return false;
                    }
                }
                if(-1 == spot) {
                    if(child[order]) {
                        return child[order]->insert_internal(xkey, xval, this, order);
                    } else {
                        spot = order;
                    }
                }
#ifdef DEBUG_BGEN_TREE
                assert(-1 != spot);
#endif // DEBUG_BGEN_TREE
                
                split_insert(xkey,xval,NULL,spot);
                return true;
            }
        }
        void split_insert(KEYTYPE xkey, VALTYPE xval, bgen_tree*xchild, unsigned int spot) {
#ifdef DEBUG_BGEN_TREE
            assert(order < MAX_ORDER);
#endif // DEBUG_BGEN_TREE
            // Before split
            // -----------------------------------
            //              spot
            //         k1     k2     k3  ....
            //      C1     C2     C3    C4 ....
            //
            // -----------------------------------
            
            // increase the order
            order++;
            // move elements
            child[order] = child[order-1];
            for(int i = (int)order-1; i > ((int)spot); i--) {
                key[i] = key[i-1];
                val[i] = val[i-1];
                child[i] = child[i-1];
            }
            // After split
            // -----------------------------------
            //              spot
            //         k1     kx    k2  ....
            //      C1     Cx     C2    C3 ....
            //
            // -----------------------------------
            

            key[spot] = xkey;
            val[spot] = xval;
            child[spot] = xchild;
        }


        std::array<bgen_tree*, MAX_ORDER+1> child;
        std::array<KEYTYPE, MAX_ORDER> key;
        std::array<VALTYPE, MAX_ORDER> val;
        unsigned int order;
    }; // bgen_tree

} // algo_snippet

#ifdef TEST_BGEN_TREE

#include <cstdlib>
#include <cassert>
#include <vector>

#include <iostream>
template<typename KT>
std::ostream& operator<<(std::ostream& ostrm, const std::vector<KT>&given) {
    ostrm << "[content:";
	for(const auto x : given) {
		ostrm << x << ',';
	}
    ostrm << ']';
    return ostrm;
}

using namespace std;
using namespace algo_snippet;

template<unsigned int BGEN_ORDER>
int test_bgen_tree(std::vector<int>& content) {
    // (2^order)-ary heap
    bgen_tree<int,int, BGEN_ORDER> btree;
    cout << "Order " << BGEN_ORDER << content << endl;

    for(int x : content) {
        btree.insert(x,x);
        btree.dump(cout, 0);
        cout << "---------------------------" << endl;
    }

    btree.dump(cout, 0);
    cout << "===========================" << endl;
    cout << "Successful" << endl;
    return 0;
}

int main(int argc, char*argv[]) {
    vector<int> elem1 = {10,9,8,7,6,5,4,3,2,1};
    test_bgen_tree<3>(elem1);
    vector<int> elem2 = {1,2,3,4,5,6,7,8,9,10};
    test_bgen_tree<5>(elem2);
    return 0;

}

#endif // TEST_BGEN_TREE
