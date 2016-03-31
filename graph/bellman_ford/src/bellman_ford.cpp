
#include <string.h>
#include <queue>
#include <iostream>
#include <cstdio>
#include <assert.h>

using namespace std;

enum {
	INFINITY = 10000,
};

static int bellman_ford(const int n, vector<pair<int, pair<int,int> > > &verts, int*dist, int*prev, int root) {
	int i;
	const int nvertices = verts.size();
	dist[root] = 0;
	for( i = 1 ; i < nvertices; i++) {
		vector<pair<int,pair<int,int> > >::iterator it = verts.begin();
		while(it < verts.end()) {
			pair<int,pair<int,int> > edge = *it++;
			int w = edge.first;
			pair<int,int> nodes = edge.second;
			int x = nodes.first;
			int y = nodes.second;
			assert(x < n && y < n);
			if(dist[y] > dist[x] + w) {
				dist[y] = dist[x] + w;
				prev[y] = x;
			}
		}
	}
	// check negative loop
	vector<pair<int,pair<int,int> > >::iterator it = verts.begin();
	while(it < verts.end()) {
		pair<int,pair<int,int> > edge = *it++;
		int w = edge.first;
		pair<int,int> nodes = edge.second;
		int x = nodes.first;
		int y = nodes.second;
		if(dist[y] > dist[x] + w) {
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
	vector<pair<int,pair<int,int> > > verts;
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
		verts.push_back(make_pair(w,make_pair(x,y)));
	}
	return bellman_ford(n, verts, dist, prev, root);
}

int main(int argc, char*argv[]) {
	/* n is the number of nodes and k is the number of edges */
	int n,k,root; 
	cin >> n >> k >> root; 
	read_input_and_find_shortest_path(n,k,root);
	return 0;
}

