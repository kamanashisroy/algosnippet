
#include <string.h>
#include <vector>
#include <queue> // priority queue
#include <list>
#include <iostream>
#include <cstdio>
#include <assert.h>

using namespace std;

enum {
	INFINITY = 1000,
};

/* pair<weight, vertex> */
typedef pair<int, int> edge_t;

struct cmp {
	int operator()(edge_t x, edge_t y) {
		return x.first < y.first; // compare weight 
	}
};

typedef priority_queue<edge_t, vector<edge_t>, cmp> edge_pq_t;

static int find_nearest_vertex(const int n, vector<edge_pq_t>&adj, int*marker) {
	int minWeight = INFINITY;
	int nearest_vertex = INFINITY;
	int x = n;
	while(x--) {
		edge_pq_t &pq = adj[x];
		if(!pq.empty()) {
			edge_t min_edge = pq.top(); // get the edge of minimum weight
			int y = min_edge.second; // other vertex
			int w = min_edge.first; // weight

			// check if the two vertices are already added
			if(marker[y] && marker[x]) {
				pq.pop();
			} else if(w < minWeight) {
				nearest_vertex = x;
				minWeight = w;
			}
		}
	}
	return nearest_vertex;
}

static int prim(const int n, vector<edge_pq_t>&adj, int*tree) {
	int i = n;
	list<int> remaining;
	int added[n];
	memset(added, 0, sizeof(added));
	i = n;
	while(i--) {
		remaining.push_back(i);
	}
	while(!remaining.empty()) {
		/**
		 * Find the node with minumum edge from reamining
		 */
		int x = find_nearest_vertex(n, adj, added);
		remaining.remove(x); // we are done with x
		edge_pq_t &pq = adj[x];
		assert(!pq.empty());
		edge_t min_edge = pq.top();

		int y = min_edge.second;
		int minWeight = min_edge.first;
		remaining.remove(y); // we are done with y
		tree[x*n + y] = minWeight;
		tree[y*n + x] = minWeight;
		added[x] = 1;
		added[y] = 1;
		pq.pop();
	}
	return 0;
}

static int read_input_and_find_minmum_spanning_tree(const int n, const int k) {
	int tree[n][n];
	vector<edge_pq_t> adj(n);
	int i;
	memset(tree, 0, sizeof(tree));
	i = n;
	while(i--) {
		adj[i] = edge_pq_t();
	}
	i = k;
	while(i--) {
		int x,y,w;
		cin >> x >> y >> w;
		adj[x].push(make_pair(w,y));
	}
	prim(n, adj, (int*)tree);
	for(i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			cout << tree[i][j] << ' ';
		}
		cout << '\n';
	}
	return 0;
}

int main(int argc, char*argv[]) {
	/* n is the number of nodes and k is the number of edges */
	int n,k; 
	cin >> n >> k; 
	read_input_and_find_minmum_spanning_tree(n,k);
	return 0;
}

