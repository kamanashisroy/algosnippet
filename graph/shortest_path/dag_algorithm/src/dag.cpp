
#include <string.h>
#include <vector>
#include <map>
#include <iostream>
#include <cstdio>
#include <assert.h>

using namespace std;

enum {
	INFINITY = 10000,
};

/**
 * @brief each pair represents an adjacent edge, pair<weight,destination> .
 */
typedef pair<int,int> edge_t;
/**
 * @brief each pair represent an weighted edge. pair<source, <weight, destination> >
 */
//typedef unordered_multimap<edge_t> adj_t;
typedef multimap<int, edge_t> adj_t;

static int depth_first_from_vertex(const int n, adj_t&adj, const int x, int*marker, int*prev, int*dist, vector<int>&top_sequence) {
	if(marker[x]) {
		return 0;
	}
	marker[x] = 1; // mark as explored
	auto range = adj.equal_range(x);
	for(auto it = range.first; it != range.second;it++) {
		edge_t edge = it->second;
		int y = edge.second;
		//int w = edge.first;
		dist[y] = dist[x] + 1;
		prev[y] = x;
		depth_first_from_vertex(n, adj, y, marker, prev, dist, top_sequence);
	}
	marker[x] = 2;
	top_sequence.push_back(x);
}

/**
 * @brief we are doing topological sort by recursive depth_first_search
 * @returns the topologically sorted sequence in reverse order
 */
static vector<int> topsort(const int n, adj_t&adj) {
	vector<int> top_sequence;
	int i = n;
	int marker[n]; // 0 means unexplored, 1 means discovered, 2 means finished
	int prev[n];
	int dist[n];
	memset(marker, 0, sizeof(marker));
	for(i = 0;i<n;i++) {
		prev[i] = -INFINITY;
		dist[i] = INFINITY;
	}
	prev[n-1] = -1;
	dist[n-1] = 0;
	
	for(i = 0;i<n;i++) {
		depth_first_from_vertex(n, adj, i, marker, prev, dist, top_sequence);
	}
	return top_sequence;
}

static bool general_relax(int source, int destination, int weight, int*dist, int*prev) {
	//cout << "relaxing " << destination << " from " << source << endl;
	if(dist[destination] > dist[source] + weight) {
		dist[destination] = dist[source] + weight;
		prev[destination] = source;
		return true;
	}
	return false;
}

static int dag(const int n, adj_t&adj, int*dist, int*prev, const int root) {
	vector<int>top_sequence = topsort(n, adj);
	int i = 0;
#if 1
	cout << "The topological sequence: ";
	for(auto node: top_sequence) {
		cout << node << ", ";
	}
	cout << endl;
#endif
	prev[root] = -1;
	dist[root] = 0;
	
	auto it = top_sequence.rbegin();
	for(;it < top_sequence.rend();it++) {
		const int source = *it;
		auto range = adj.equal_range(source);
		for(auto edge = range.first; edge != range.second;edge++) {
			general_relax(source, edge->second.second, edge->second.first, dist, prev);
		}
	}
	return 0;
}


static int read_input_and_find_shortest_path(const int n, const int k, const int root) {
	adj_t adj;
	int dist[n];
	int prev[n];
	int i;
	i = n;
	while(i--) {
		dist[i] = INFINITY;
		prev[i] = INFINITY;
	}
	i = k;
	while(i--) {
		int x,y,w;
		cin >> x >> y >> w;
		adj.insert(make_pair(x,make_pair(w,y)));
	}
	dag(n, adj, dist, prev, root);
	i = n;
	while(i--) {
		cout << "dist[" << i << "]=" << dist[i] << endl;
	}
	return 0;
}

int main(int argc, char*argv[]) {
	/* n is the number of nodes and k is the number of edges */
	int n,k,root; 
	cin >> n >> k >> root; 
	read_input_and_find_shortest_path(n,k,root);
	return 0;
}

