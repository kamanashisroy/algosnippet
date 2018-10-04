// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
cut_vertices.cc file is part of Algosnippet.
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

#include <bits/stdc++.h>
#include <functional>

using namespace std;
typedef unsigned int node_t;
typedef int weight_t;

namespace algo_snippet {

    class graph_node {
    public:
        graph_node() : _nid(0),_w(0),connected() {}
        // move constructor
        graph_node(graph_node&& other) : _nid(other._nid),_w(other._w),connected(std::move(other.connected)) {}
        graph_node(node_t nid, weight_t w) : _nid(nid),_w(w), connected(){
            
        }
        void add(const graph_node& other) {
            connected.push_back(other);
        }
        node_t get_nid() const {
            return _nid;
        }
        weight_t get_weight() const {
            return _w;
        }
        const auto& get_connected() const {
            return connected;
        }
    private:
        const node_t _nid;
        const node_t _w;
        vector<std::reference_wrapper<const graph_node> > connected;
    };

    ostream& operator<<(ostream& ostrm, const graph_node& xnode) {
        ostrm << '<' << xnode.get_nid() << ':';
        for(const graph_node& other : xnode.get_connected()) {
            ostrm << other.get_nid() << ',';
        }
        ostrm << '>';
        return ostrm;
    }


    template<typename KGRAPH>
    class graph_traverse {
    public:
        graph_traverse() : root_nid(0) {}
        virtual ~graph_traverse() {}
        void dfs(const node_t num_nodes, const KGRAPH& root) {
            root_nid = root.get_nid();
            dfs_start(root);

            bool explored[num_nodes]{false};
            bool expanded[num_nodes]{false};
            bool processed[num_nodes]{false};
            node_t entry[num_nodes]{num_nodes};
            parent_table.clear();
            parent_table.resize(num_nodes,root);

            vector<reference_wrapper<const KGRAPH>> fringe;
            fringe.push_back(root); // start from the root
            dfs_edge_explore(root, root);
            while(!fringe.empty()) {
                const KGRAPH& x = fringe.back();

                if(expanded[x.get_nid()]) {
                    if(!processed[x.get_nid()]) {
                        // update the subtree size
                        dfs_augment(x,parent_table[x.get_nid()],processed);
                        processed[x.get_nid()] = true;
                    } else {
                        // forward edge
                        // dfs_forward_edge();
                    }
                    fringe.pop_back();
                    continue; // we already expanded it
                }

                // explore after popping(unlinke bfs)
                dfs_explore(x, parent_table[x.get_nid()]);
                expanded[x.get_nid()] = true;

                // we are going to expand this node.
                for(const KGRAPH& y : x.get_connected()) {
                    if(expanded[y.get_nid()]) {
                        // expand already = Tree edge/cross-edge
                        if(processed[y.get_nid()]) {
                            // cross-edge
                            //dfs_cross_edge_explore(y, x);
                        } else {
                            // tree-edge
                            //dfs_tree_edge_explore(y, x);
                        }
                        continue;
                    } else {
                        if(explored[y.get_nid()]) {
                            // forward edge
                        }
                        parent_table[y.get_nid()] = x;
                    }
                    entry[y.get_nid()] = min(entry[y.get_nid()],entry[x.get_nid()]+1);
                    if(entry[y.get_nid()] < entry[x.get_nid()]) {
                        // back-edge
                        dfs_back_edge_explore(y,x);
                    }
                    fringe.push_back(y);
                    dfs_edge_explore(y, x);
                    explored[y.get_nid()] = true;
                }
            }
            dfs_end();
            parent_table.clear();
        }
        
        virtual void dfs_start(const KGRAPH& x) {
        
        }
        
        virtual void dfs_end() {
        
        }
        
        virtual void dfs_explore(const KGRAPH& x, const KGRAPH& other_root) {
            // FILLME explore
        }

        virtual void dfs_edge_explore(const KGRAPH& x, const KGRAPH& other_root) {
            // FILLME process edge, mark entry time
        }
        
        virtual void dfs_back_edge_explore(const KGRAPH& x, const KGRAPH& other_root) {
            // FILLME process back-edge
        }

        virtual void dfs_augment(const KGRAPH& x, const KGRAPH& parent, const bool*augmented) {
            //for(const KGRAPH& y : x.get_connected()) {
                //if(!augmented[y.get_nid()]) {
                    // skip parent
                    //continue;
                //}
                // TODO also skip multiple edges
                // FILLME augment
                // subtree_size[x.get_nid()] += subtree_size[y.get_nid()];
            //}
            // FILLME augment
            // subtree_size[x.get_nid()] += x.get_weight();
        }
        bool is_root(const KGRAPH& x) const {
            return x.get_nid() == root_nid;
        }
    private:
        vector<reference_wrapper<const KGRAPH>> parent_table;
        node_t root_nid;
    };

    template <typename KGRAPH>
    class biconnected_component : public graph_traverse<KGRAPH> {
    public:
        biconnected_component(node_t num_nodes) 
            :num_nodes(num_nodes)
            ,explored_flag(num_nodes,false)
            ,depth(num_nodes,0)
            ,low_points(num_nodes,0)
            ,cut_vertex_flag(num_nodes,false)
            ,num_root_children(0) {
        }
        virtual ~biconnected_component() override {
        
        }
        virtual void dfs_start(const KGRAPH& root) override {
            num_root_children = 0; // reset
        }
        virtual void dfs_explore(const KGRAPH& x, const KGRAPH& parent_x) override {
            // setup depth
            explored_flag[x.get_nid()] = true;
            if(x.get_nid() == parent_x.get_nid()) {
                // when root
                low_points[x.get_nid()] = depth[x.get_nid()] = 0;
            } else {
                // derive depth from parent
                low_points[x.get_nid()] = depth[x.get_nid()] = depth[parent_x.get_nid()]+1;
            }
            #ifdef DEBUG
            std::cout << "Exploring:" << x.get_nid() << std::endl;
            #endif
        }
        virtual void dfs_augment(const KGRAPH& x, const KGRAPH& xparent, const bool*augmented) override {
            
            // calculate low point from neighbors
            node_t xlow = depth[x.get_nid()];
            for(const KGRAPH& y : x.get_connected()) {
                if(y.get_nid() == xparent.get_nid()) {
                    // skip parent
                    continue;
                }
                /////////////////////////////////////////////////////////////////////////
                // Non-root node
                //
                // The key fact is that a non-root vertex v is a cut vertex (or articulation point) separating two biconnected components
                // if and only if there is a child y of v such that lowpoint(y) ≥ depth(v)
                //
                if(!this->is_root(x) && low_points[y.get_nid()] >= depth[x.get_nid()]) {
                    cut_vertex_flag[x.get_nid()] = true;
                }
                /////////////////////////////////////////////////////////////////////////
                xlow = min(low_points[y.get_nid()],xlow);
            }
            /////////////////////////////////////////////////////////////////////////
            // root node
            if(this->is_root(x)) {
                //
                // The root vertex must be handled separately: it is a cut vertex if and only if it has at least two children.
                //
                if(num_root_children > 1) {
                    cut_vertex_flag[x.get_nid()] = true;
                }
            }
            /////////////////////////////////////////////////////////////////////////

            // calculate low point from neighbors
            low_points[x.get_nid()] = xlow;
            #ifdef DEBUG
            std::cout << "vertex:" << x.get_nid() << ",depth " << depth[x.get_nid()] << ", low point " << xlow << std::endl;
            #endif
            if(this->is_root(xparent)) {
                num_root_children+= 1;
            }
        }
        bool is_explored(node_t nid) const {
            return explored_flag[nid];
        }
        bool is_cut_vertex(node_t nid) const {
            return cut_vertex_flag[nid];
        }
    private:
        const node_t num_nodes;
        vector<bool> explored_flag;
        vector<node_t> depth;
        vector<node_t> low_points;
        vector<bool> cut_vertex_flag;
        node_t num_root_children;
    };
}

using namespace algo_snippet;

//! Dumps the cut vertices in sorted order
void list_all_cut_vertices(const node_t num_nodes, const node_t num_edges) {
    if(0 == num_nodes) {
        return;
    }
    vector<graph_node> graph;
    graph.reserve(num_nodes);
  
    for(node_t i = 0; i < num_nodes; i++) {
        graph.emplace_back(i,i);
    }
  
    // read inputs
    for(node_t i = 0; i < num_edges; i++) {
        node_t x=0,y=0;
        cin >> x >> y;
        graph[x-1].add(graph[y-1]);
        graph[y-1].add(graph[x-1]);
    }

    biconnected_component<graph_node> compgen(num_nodes);
    compgen.dfs(num_nodes,graph[0]);

    // dump the cut vertices in sorted order
    for(const graph_node& x : graph) {
        if(compgen.is_cut_vertex(x.get_nid())) {
            cout << x.get_nid() << ' ';
        }
    }
    cout << endl;
}

int main()
{
    node_t num_nodes=0,num_edges=0;
    cin >> num_nodes >> num_edges;
    list_all_cut_vertices(num_nodes, num_edges);
    return 0;
}
