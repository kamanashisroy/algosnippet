
#include <string.h>
#include <queue>
#include <iostream>
#include <cstdio>
#include <assert.h>

using namespace std;

enum {
	INFINITY = 10000,
};

/**
 * @brief each pair represents an edge, pair<source,destination> .
 */
typedef pair<int,int> edge_t;
/**
 * @brief each pair represent an edge of specific weight. pair<weight, <source, destination> >
 */
typedef pair<int, edge_t> weighted_edge_t;

static bool bellman_ford_relax(int source, int destination, int weight, int*dist, int*prev) {
	//assert(source < n && destination < n);
	if(dist[destination] > dist[source] + weight) {
		dist[destination] = dist[source] + weight;
		prev[destination] = source;
		return true;
	}
	return false;
}

static int bellman_ford(const int n, vector<weighted_edge_t> &edges, int*dist, int*prev, const int root) {
	int i;
	dist[root] = 0;
	for( i = 1/* we need to relax |V|-1 times */ ; i < n; i++) {
		for(auto edge: edges) {
			bellman_ford_relax(edge.second.first, edge.second.second, edge.first, dist, prev);
		}
	}
	// check negative loop
	for(auto edge: edges) {
		if(bellman_ford_relax(edge.second.first, edge.second.second, edge.first, dist, prev)) {
			// as there is more relaxation position so there is negative loop
			return -1;
		}
	}
	// dump output
	for( i = 0; i < n; i++) {
		cout << dist[i] << ' ';
	}
	cout << '\n';
	return 0;
}


static int read_input_and_find_shortest_path(const int n, const int k, const int root) {
	vector<weighted_edge_t> edges;
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
		edges.push_back(make_pair(w,make_pair(x,y)));
	}
	return bellman_ford(n, edges, dist, prev, root);
}

int main(int argc, char*argv[]) {
	/* n is the number of nodes and k is the number of edges */
	int n,k,root; 
	cin >> n >> k >> root; 
	read_input_and_find_shortest_path(n,k,root);
	return 0;
}

