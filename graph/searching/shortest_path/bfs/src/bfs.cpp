
#include <string.h>
#include <queue>
#include <iostream>
#include <cstdio>

using namespace std;

static int bfs(const int n, int*adj, int*level, int root) {
	queue<int>nodes;
	nodes.push(root);
	level[root] = 1; // it should be 0 , but for easier calculation we put it '1'
	while(!nodes.empty()) {
		int x = nodes.front();
		cout << x << '\n';
		nodes.pop();
		int i = n;
		while(i--) {
			if(!*(adj+(x*n)+i))
				continue;
			if(level[i])
				continue;
			nodes.push(i);
			level[i] = level[x]+1;
		}
	}
	return 0;
}


static int read_input_and_do_bfs(const int n, const int k, const int root) {
	int adj[n][n];
	int level[n];
	memset(adj, 0, sizeof(adj));
	memset(level, 0, sizeof(level));
	int i = k;
	while(i--) {
		int x,y;
		cin >> x >> y;
		adj[x][y] = 1;
		adj[y][x] = 1;
	}
	return bfs(n, (int*)adj, level, root);
}

int main(int argc, char*argv[]) {
	/* n is the number of nodes and k is the number of edges */
	int n,k,root; 
	cin >> n >> k >> root; 
	read_input_and_do_bfs(n,k,root);
	return 0;
}

