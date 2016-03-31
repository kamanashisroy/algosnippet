
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

struct cmp {
	int operator()(pair<int,int> x, pair<int,int> y) {
		return x.first < y.first;
	}
};


static int prim(const int n, vector<priority_queue<pair<int, int>, vector<pair<int, int> >, cmp > >&adj, int*tree) {
	int i = n;
	list<int> remaining;
	int added[n];
	memset(added, 0, sizeof(added));
	i = n;
	while(i--) {
		remaining.push_back(i);
	}
	while(!remaining.empty()) {
		int minWeight = INFINITY;
		int node = INFINITY;
		int x = n;
		while(x--) {
			priority_queue<pair<int, int>, vector<pair<int, int> >, cmp >&pq = adj[x];
			if(!pq.empty()) {
				pair<int,int> min_dist = pq.top();int y = min_dist.second;int w = min_dist.first;
				if(added[y] && added[x]) { // this edge is costly , the adjuscent node is already added in the tree
					pq.pop();
				} else if(w < minWeight) {
					node = x;
					minWeight = w;
				}
			}
		}
		x = node;
		remaining.remove(x);
		priority_queue<pair<int, int>, vector<pair<int, int> >, cmp >&pq = adj[x];
		assert(!pq.empty());
		pair<int,int> min_dist = pq.top();int y = min_dist.second;
		remaining.remove(y);
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
	vector<priority_queue<pair<int, int>, vector<pair<int, int> >, cmp > > adj(n);
	int i;
	memset(tree, 0, sizeof(tree));
	i = n;
	while(i--) {
		adj[i] = priority_queue<pair<int, int>, vector<pair<int, int> >, cmp >();
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

