
#include <string.h>
#include <vector>
#include <queue> // priority queue
#include <set>
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
	set<int> remaining;
	i = n;
	while(i--) {
		remaining.insert(i);
	}
	while(!remaining.empty()) {
		int minWeight = INFINITY;
		int node = INFINITY;
		i = n;
		while(i--) {
			priority_queue<pair<int, int>, vector<pair<int, int> >, cmp >&pq = adj[i];
			if(!pq.empty()) {
				pair<int,int> min_dist = pq.top();
				if(remaining.find(min_dist.second) == remaining.end()) { // this edge is costly , the adjuscent node is already added in the tree
					pq.pop();
				} else if(min_dist.first < minWeight) {
					node = i;
					minWeight = min_dist.first;
				}
			}
		}
		remaining.erase(node);
		priority_queue<pair<int, int>, vector<pair<int, int> >, cmp >&pq = adj[node];
		assert(!pq.empty());
		pair<int,int> min_dist = pq.top();
		remaining.erase(min_dist.second);
		tree[node*n + min_dist.second] = minWeight;
		tree[min_dist.second*n + node] = minWeight;
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

