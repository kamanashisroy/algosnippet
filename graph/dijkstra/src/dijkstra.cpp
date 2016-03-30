
#include <string.h>
#include <queue>
#include <iostream>
#include <cstdio>
#include <assert.h>

using namespace std;

enum {
	INFINITY = 10000,
};

static int dijkstra(const int n, int*adj, int*dist, int*prev, int root) {
	queue<int>nodes;
	nodes.push(root);
	int i = 0;
	dist[root] = 0; // source to source is 0
	while(!nodes.empty()) {
		int x = nodes.front();
		nodes.pop();
		assert(dist[x] < INFINITY);
		i = n;
		while(i--) {
			int w = *(adj+(x*n)+i);
			if(!w)
				continue;
			//cout << "dist[i]:" << i << ":" << dist[i] << ",(dist[x]+w):" << x << ":" << (dist[x] + w) << "\n";
			w += dist[x];
			if(dist[i] < w)
				continue;
			dist[i] = w;
			nodes.push(i);
			prev[i] = x;
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
	int adj[n][n];
	int dist[n];
	int prev[n];
	memset(adj, 0, sizeof(adj));
	memset(dist, 0, sizeof(dist));
	memset(prev, 0, sizeof(prev));
	int i = k;
	while(i--) {
		int x,y,w;
		cin >> x >> y >> w;
		adj[x][y] = w;
		adj[y][x] = w;
	}
	i = n;
	while(i--) {
		dist[i] = INFINITY;
		prev[i] = INFINITY;
	}
	return dijkstra(n, (int*)adj, dist, prev, root);
}

int main(int argc, char*argv[]) {
	/* n is the number of nodes and k is the number of edges */
	int n,k,root; 
	cin >> n >> k >> root; 
	read_input_and_find_shortest_path(n,k,root);
	return 0;
}

