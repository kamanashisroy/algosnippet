
#include <string.h>
#include <vector>
#include <algorithm> // sort
#include <iostream>
#include <cstdio>

using namespace std;

bool compare_edge(pair<int, pair<int,int> >x, pair<int, pair<int,int> >y) {
	return x.first < y.first;
}

void join_trees(int*prev, int x, int y) {
	prev[x] = y; // TODO make a balanced tree for undirected graph
}

int find_root(int*prev, int x) {
	int parent = x;
	do {
		x = parent;
		parent = prev[x];
	} while(parent != x);
	return x;
}

static int kruskal(const int n, vector<pair<int, pair<int,int> > > &edges, int*prev) {
	// sort all the edges by weight
	sort(edges.begin(), edges.end(), compare_edge);
	vector<pair<int,pair<int,int> > >::iterator it = edges.begin();
	while(it < edges.end()) {
		pair<int,pair<int,int> > edge = *it++;
		//int w = edge.first;
		pair<int,int> nodes = edge.second;
		int x = nodes.first;
		int y = nodes.second;
		int rootx = find_root(prev, x);
		int rooty = find_root(prev, y);
		if(rootx == rooty)
			continue;
		join_trees(prev,rootx,rooty);
	}
	return 0;
}

static int read_input_and_find_minmum_spanning_tree(const int n, const int k) {
	int prev[n];
	vector<pair<int, pair<int,int> > > edges(k);
	int i;
	i = n;
	while(i--) {
		prev[i] = i;
	}
	i = k;
	while(i--) {
		int x,y,w;
		cin >> x >> y >> w;
		edges.push_back(make_pair(w,make_pair(x,y)));
	}
	kruskal(n, edges, prev);
	i = n;
	while(i--) {
		cout << prev[i] << '\n';
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

