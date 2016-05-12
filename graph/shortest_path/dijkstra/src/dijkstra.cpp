
#include <string.h>
#include <queue>
#include <map>
#include <iostream>
#include <cstdio>
#include <assert.h>

using namespace std;

enum {
	INFINITY = 10000,
};

static bool general_relax(int source, int destination, int weight, int*dist, int*prev) {
	//cout << "relaxing " << destination << " from " << source << endl;
	if(dist[destination] > dist[source] + weight) {
		dist[destination] = dist[source] + weight;
		prev[destination] = source;
		return true;
	}
	return false;
}

/**
 * @brief pair<int,int> represents pair<distance, vertex>
 */
typedef pair<int,int> dist_t;
struct cmp {
	bool operator()(dist_t x, dist_t y) {
		return x.first < y.first;
	}
};

typedef priority_queue<dist_t,vector<dist_t>, cmp> dijkstra_pq_t;

/**
 * @brief edge is weight and destination. pair<weight,destination>
 */
typedef pair<int,int> edge_t;
/**
 * @brief adjucency list 
 */
typedef multimap<int,edge_t> adj_t;

static int dijkstra(const int n, adj_t&adj, int*dist, int*prev, int root) {
	dijkstra_pq_t nodes;
	nodes.push(make_pair(0,root));
	int i = 0;
	dist[root] = 0; // source to source is 0
	while(!nodes.empty()) {
		const int x = nodes.top().second;
		nodes.pop();
		assert(dist[x] < INFINITY);
		auto range = adj.equal_range(x);
		for(auto it = range.first; it != range.second; it++) {
			dist_t distance = it->second;
			if(general_relax(x, distance.second, distance.first, dist, prev)) {
				nodes.push(make_pair(dist[distance.second], distance.second));// FIXIT, sometimes there are two insertions.
			}
		}
	}
	i = n;
	while(i--) {
		cout << "(" << prev[i] << "->" << i << ":" << dist[i] << ")";
	}
	cout << "\n";

	return 0;
}


static int read_input_and_find_shortest_path(const int n, const int k, const int root) {
	adj_t adj;
	int dist[n];
	int prev[n];
	memset(dist, 0, sizeof(dist));
	memset(prev, 0, sizeof(prev));
	int i = k;
	while(i--) {
		int x,y,w;
		cin >> x >> y >> w;
		adj.insert(make_pair(x, make_pair(w,y)));
	}
	i = n;
	while(i--) {
		dist[i] = INFINITY;
		prev[i] = INFINITY;
	}
	return dijkstra(n, adj, dist, prev, root);
}

int main(int argc, char*argv[]) {
	/* n is the number of nodes and k is the number of edges */
	int n,k,root; 
	cin >> n >> k >> root; 
	read_input_and_find_shortest_path(n,k,root);
	return 0;
}

