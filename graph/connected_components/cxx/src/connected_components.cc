#include <bits/stdc++.h>
#include <functional>

using namespace std;
typedef unsigned int node_t;
typedef int weight_t;

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
    graph_traverse(){}
    virtual ~graph_traverse() {}
    void dfs(const node_t num_nodes, const KGRAPH& root) {
        dfs_start(root);

        bool explored[num_nodes]{false};
        bool expanded[num_nodes]{false};
        bool augmented[num_nodes]{false};
        vector<reference_wrapper<const KGRAPH>> fringe;
        fringe.push_back(root); // start from the root
        dfs_explore(root);
        explored[root.get_nid()] = true;
        while(!fringe.empty()) {
            const KGRAPH& x = fringe.back();

            if(!expanded[x.get_nid()]) {
                // we are going to expand this node.
                for(const KGRAPH& y : x.get_connected()) {
                    if(explored[y.get_nid()]) {
                        // explored already = must be root, so avoid it
                        continue;
                    }
                    fringe.push_back(y);
                    dfs_explore(y);
                    explored[y.get_nid()] = true;
                }
                expanded[x.get_nid()] = true;
            } else {
                // update the subtree size
                dfs_augment(x,augmented);
                augmented[x.get_nid()] = true;
                fringe.pop_back(); // done with x
            }
        }
        dfs_end();
    }
    
    virtual void dfs_start(const KGRAPH& x) {
    
    }
    
    virtual void dfs_end() {
    
    }
    
    virtual void dfs_explore(const KGRAPH& x) {
        // FILLME explore
    }
    
    virtual void dfs_augment(const KGRAPH& x, const bool*augmented) {
        //for(const KGRAPH& y : x.get_connected()) {
            //if(!augmented[y.get_nid()]) {
                // skip parent
                //continue;
            //}
            // also skip multiple edges
            // FILLME augment
            // subtree_size[x.get_nid()] += subtree_size[y.get_nid()];
        //}
        // FILLME augment
        // subtree_size[x.get_nid()] += x.get_weight();
    }
};

template <typename KGRAPH>
class connected_component : public graph_traverse<KGRAPH> {
public:
    connected_component(node_t num_nodes) 
        :num_nodes(num_nodes)
        ,smallest_component(num_nodes)
        ,largest_component(0)
        ,explored_flag(num_nodes,false) {
    }
    virtual ~connected_component() override {
    
    }
    virtual void dfs_start(const KGRAPH& root) override {
        num_nodes_component = 0;
    }
    virtual void dfs_explore(const KGRAPH& x) override {
        num_nodes_component += 1;
        explored_flag[x.get_nid()] = true;
    }
    virtual void dfs_end() override {
        if(1 == num_nodes_component) {
            return;
        }
        smallest_component = min(num_nodes_component,smallest_component);
        largest_component = max(largest_component,num_nodes_component);
    }
    node_t get_smallest() const {
        return smallest_component;
    }
    node_t get_largest() const {
        return largest_component;
    }
    bool is_explored(node_t nid) const {
        return explored_flag[nid];
    }
private:
    const node_t num_nodes;
    node_t smallest_component;
    node_t largest_component;
    node_t num_nodes_component;
    vector<bool> explored_flag;
};

// Complete the cut_the_tree function below.
void min_max_connected_components(const node_t num_edges) {
    if(num_edges == 0) {
        return;
    }
    vector<graph_node> graph;
    graph.reserve(num_edges<<1);
  
    for(node_t i = 0; i < (num_edges<<1); i++) {
        graph.emplace_back(i,i);
    }
  
    // read inputs
    node_t num_valid_nodes = 0;
    for(node_t i = 0; i < num_edges; i++) {
        node_t x=0,y=0;
        cin >> x >> y;
        graph[x-1].add(graph[y-1]);
        graph[y-1].add(graph[x-1]);
        num_valid_nodes = max(num_valid_nodes,x);
        num_valid_nodes = max(num_valid_nodes,y);
    }

    //cout << " total " << num_valid_nodes << endl;
    // skip invalid nodes
    graph.resize(num_valid_nodes);
    graph.shrink_to_fit();
    //for(const graph_node& x : graph) {
    //    cout << x << endl;
    //}
  
  
    connected_component<graph_node> compgen(num_valid_nodes);
    for(const graph_node& x : graph) {
        if(compgen.is_explored(x.get_nid())) {
            continue;
        }
        compgen.dfs(num_valid_nodes,x);
    }
    cout << compgen.get_smallest() << ' ' << compgen.get_largest() << endl;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));
    node_t num_edges=0;
    cin >> num_edges;
    min_max_connected_components(num_edges);
    return 0;
}
