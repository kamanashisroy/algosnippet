// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
kruskal_mst.cc file is part of Algosnippet.
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


#include <cstdlib>
#include <vector>
#include <tuple>


namespace algo_snippet {
    class disjoint_set {
    public:
        disjoint_set(size_t n_universe) : parent(n_universe),rank(n_universe) {
            for(size_t i=0; i<n_universe; i++) {
                parent[i] = i;
                rank[i] = 0;
            }
        }
        void make(size_t x) {
            parent[x] = x;
        }
        void join(size_t x, size_t y){
            x = find(x);
            y = find(y);
            if(x == y) {
                return;
            }

            // check the rank and join
            if(rank[x] == rank[y]) {
                parent[y] = x;
                rank[x] += 1;
            } else if(rank[x] > rank[y]) {
                parent[y] = x;
            } else {
                parent[x] = y;
            }
        }
        size_t find(size_t x) {
            while(parent[x] != x) {
                const size_t oldx = x;
                x = parent[x];
                parent[oldx] = parent[x]; // path halving
            }
            return x;
        }
    private:
        std::vector<size_t> parent;
        std::vector<size_t> rank;
    };
} 

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


#include <cstdlib>
#include <cassert>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <vector>


namespace algo_snippet {
    inline std::size_t dary_heap_parent(std::size_t i,std::size_t order) {
        assert(i != 0);
        return ((i-1) >> order);
    }

    inline std::size_t dary_heap_child(std::size_t i,std::size_t order) {
        return (i << order)+1;
    }

    template<const std::size_t order, typename KT>
    void dary_heap_bubble_down(std::vector<KT>& x, std::size_t ibubble, const std::size_t isize) {

        // size limit
        assert(isize <= x.size());
        for(std::size_t ibegin = dary_heap_child(ibubble, order); ibegin < isize; ibegin = dary_heap_child(ibubble, order)) {
            // bubble down
            const std::size_t iend = ibegin+(1<<order);
            std::size_t imin = ibegin;
            for(std::size_t ii = ibegin+1; (ii < isize) && (ii < iend); ii++) {
                if(x[imin] <= x[ii]) {
                    continue;
                }
                imin = ii;
            }
            if(x[ibubble] <= x[imin]) {
                // heap property holds
                break;
            } else {
                std::swap(x[imin],x[ibubble]);
                ibubble = imin;
            }
        } // end bubble-down
    }

    //! \brief builds heap of (1<<order)-ary heap in Theta(n) time
    template<const std::size_t order, typename KT>
    void dary_heap_build(std::vector<KT>& x) {
        static_assert(order != 0);
        // make bottom up heap Floyd's Theta(n) algorithm
        // starting from the leaf nodes
        for(std::size_t i = x.size()-1;i;--i) {

            // compare with the parent node
            const std::size_t pi = dary_heap_parent(i,order);
            if(x[pi] <= x[i]) { // check minheap property
                continue; // already a minheap
            }

            // fix the minheap property
            std::swap(x[pi],x[i]);

            // bubble down the minheap
            dary_heap_bubble_down<order,KT>(x, i, x.size());

        } // end for all
    }

    template<const std::size_t order, typename KT>
    void dary_heap_pop(std::vector<KT>& x) {
        if(x.size() <= 1) {
            return;
        }

        // swap with last
        std::swap(x[0],x.back());

        // bubble down
        dary_heap_bubble_down<order,KT>(x, 0, x.size()-1/* skip bubbling the back() aka old root aka the min value */);
    }
}


#include <bits/stdc++.h>

using namespace std;
using namespace algo_snippet;

//typedef tuple<int /* weight */,int /* x node */,int /* y node */> edge_t;
struct edge_t {
    edge_t(int w, int x, int y) : w(w),x(x),y(y) {
    }
    edge_t(const edge_t& other) : w(other.w),x(other.x),y(other.y) {
    }
    inline bool operator<=(const struct edge_t& other) const {
        return w<=other.w;
    }
    inline int get_weight() const {
        return w;
    }
    inline int get_x() const {
        return x;
    }
    inline int get_y() const {
        return y;
    }
private:
    int w;
    int x;
    int y;
};

std::ostream& operator<<(std::ostream& ostrm, const std::vector<edge_t>&given) {
    ostrm << "[minheap:";
  for(const auto x : given) {
    ostrm << '(' << x.get_weight() << ':' << x.get_x() << ',' << x.get_y() << ')' << ',';
  }
    ostrm << ']';
    return ostrm;
}

#define HEAP_ORDER 4
int kruskal_mst(const int n_nodes, const int n_edges, vector<edge_t>& edges) {
    dary_heap_build<HEAP_ORDER,edge_t>(edges);
    disjoint_set node_set(n_nodes);
  
    //std::sort(edges.begin(),edges.end());
   
    //cout << edges << endl;
    bool explored[n_nodes]{false};
    int mst_weight = 0;
    for(int i = 0;i < n_nodes && !edges.empty();) {
        dary_heap_pop<HEAP_ORDER,edge_t>(edges);
        const edge_t edg = edges.back();
        edges.pop_back();
        const int px = node_set.find(edg.get_x());
        const int py = node_set.find(edg.get_y());
        //cout << "Checking edge w=" << w << ':' << x << ',' << y << endl;
        if(px == py) {
            // we already considered these nodes
            continue;
        }
        node_set.join(edg.get_x(),edg.get_y());
        if(!explored[edg.get_x()]) {
            i++;
            explored[edg.get_x()] = true;
        }
        if(!explored[edg.get_y()]) {
            i++;
            explored[edg.get_y()] = true;
        }
        mst_weight+=edg.get_weight();
        //cout << "--- counting i=" << i << " mst_weight=" << mst_weight << endl;
    }
    return mst_weight;
}

int main()
{
    int n_nodes;
    int n_edges;

    cin >> n_nodes >> n_edges;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<edge_t> g_edges;

    for (int i = 0; i < n_edges; i++) {
        int x = 0,y = 0,w = 0;
        cin >> x >> y >> w;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        g_edges.emplace_back(w,x,y);
    }

    // Write your code here.
    cout << kruskal_mst(n_nodes, n_edges, g_edges) << endl;
    return 0;
}
