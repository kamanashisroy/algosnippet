
#include <string.h>
#include <queue>
#include <iostream>
#include <cstdio>
#include <assert.h>

using namespace std;

enum {
	INFINITY = 10000,
};

static int floyd_warshall(const int n, int*adj, int*dist, int root) {
	int i,j,k;
	for( k = 0 ; k < n; k++) {
		for( i = 0; i < n; i++) {
			for( j = 0; j < n; j++) {
				int w = (*(dist+(i*n)+k) + *(dist+(k*n)+j));
				if(*(dist+(i*n)+j) > w) {
					*(dist+(i*n)+j) = w;
				}
			}
		}
	}
	for( i = 0; i < n; i++) {
		for( j = 0; j < n; j++) {
			cout << *(dist+(i*n)+j) << ' ';
		}
		cout << '\n';
	}
	return 0;
}


static int read_input_and_find_shortest_path(const int n, const int k, const int root) {
	int adj[n][n];
	int dist[n][n];
	int i,j;
	for( j = 0; j < n; j++) {
		for( i = 0; i < n; i++) {
			adj[i][j] = INFINITY;
			dist[i][j] = INFINITY;
		}
	}
	i = k;
	while(i--) {
		int x,y,w;
		cin >> x >> y >> w;
		adj[x][y] = w;
		dist[x][y] = w;
	}
	return floyd_warshall(n, (int*)adj, (int*)dist, root);
}

int main(int argc, char*argv[]) {
	/* n is the number of nodes and k is the number of edges */
	int n,k,root; 
	cin >> n >> k >> root; 
	read_input_and_find_shortest_path(n,k,root);
	return 0;
}

