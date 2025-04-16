
#include <unique_ptr>

using namespace std;

// Please refer to this post https://leetcode.com/problems/dot-product-of-two-sparse-vectors/solutions/6658012/two-bin-trie-lcrs-and-dfs

template <typename T, typename INTKEY>
struct LL
{
    LL(INTKEY aKey): key(aKey) {}
    INTKEY key = 0;
    T node;
    unique_ptr<LL<T,INTKEY>> next = nullptr;
};

template<typename INTKEY,typename INTVAL, const int ORDER=2>
struct BinTrie
{
    using BinTreeLink = LL<BinTrie<INTKEY,INTVAL,ORDER>, INTKEY>;

    constexpr static int order = ORDER;
    BinTrie() { }
    BinTrie(int unused) {
    }

    BinTreeLink*make_key(INTKEY cidx) {
        auto*cur = this;
        auto*sibling = cur->children.get();
        if(not sibling) {
            cur->children =  make_unique<BinTreeLink>(cidx);
            assert(cur->children);
            return cur->children.get();
        } else if (sibling->key == cidx) {
            return sibling;
        } else if (sibling->key < cidx) {
            // insert before sibling
            while(sibling->key < cidx and sibling->next and sibling->next->key <= cidx) {
                sibling = sibling->next.get();
            }
            assert(sibling->key <= cidx);
            if(sibling->key != cidx) {
                auto sibling2 = std::move(sibling->next);
                sibling->next = make_unique<BinTreeLink>(cidx);
                sibling->next->next = std::move(sibling2);
                sibling = sibling->next.get();
                assert(sibling);
            }
            return sibling;
        } else if(sibling->key > cidx) {
            // insert at first position
            auto sibling2 = std::move(cur->children);
            cur->children =  make_unique<BinTreeLink>(cidx);
            cur->children->next = std::move(sibling2);
            return cur->children.get();
        }
        return sibling;
    }

    void insert(INTKEY given, INTVAL value) {
        auto*cur = this;

        if(not given) {
            cur->content = value;
            return;
        }
        auto x = given;
        for(int depth = 0;; depth++) {
            for(int i = (ORDER-1); i >= 0 ;i--) {
                INTKEY cidx = x & (i<<depth);
                cidx >>= depth;
                if(i == cidx) {
                    auto*child = cur->make_key(cidx);
                    assert(child);
                    cur = &child->node;
                    x -= (i<<depth);
                    if(not x) {
                        cur->content = value;
                        return;
                    }
                    break;
                }
            }
        }
    }

    unique_ptr<BinTreeLink> children;
    optional<INTVAL> content;
    //size_t numNodes = 0;
};


// n = 10**5 
// log2 n = 16
using Dict = BinTrie<size_t, int, 16>;
class SparseVector {
public:
    
    Dict root;
    SparseVector(vector<int> &nums) {
        for(size_t i = 0; i < nums.size(); i++) {
            root.insert(i, nums[i]);
        }
    }

    // Return the dotProduct of two sparse vectors
    int dotProduct(SparseVector& vec) {
        long long ret = 0;
        vector< pair<decltype(&root), decltype(&root)> > stack;

        //std::cout << root.numNodes << std::endl;
        //std::cout << vec.root.numNodes << std::endl;

        stack.emplace_back(&root, &vec.root); 
        while(not stack.empty() ) {
            auto [left,right] = stack.back();
            stack.pop_back();

            if(left->content.has_value() and right->content.has_value()) {
                ret += left->content.value()*right->content.value();
            }
            auto*sibleft = left->children.get();
            auto*sibright = right->children.get();
            while(sibleft and sibright) {
                if(sibleft->key < sibright->key) {
                    sibleft = sibleft->next.get();
                } else if(sibleft->key > sibright->key) {
                    sibright = sibright->next.get();
                } else {
                    // when equal
                    stack.emplace_back(&sibleft->node,&sibright->node);
                    sibleft = sibleft->next.get();
                    sibright = sibright->next.get();
                }
            }
        }
        return ret;
    }
};
