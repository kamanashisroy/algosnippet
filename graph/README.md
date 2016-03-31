
Graph 
=======

Here is my practice code of all the graph related algorithms.

- [Breadth-first Search](bfs)
- [Depth-first Search](dfs)
- Shortest path search
	- [Dijkstra Algorithm](dijkstra)
	- [Floyd Warshall's algorithm](floyd_warshall)
	- [Dynamic programming](dynamic_undirected)
	- [Bellman Ford algorithm](bellman_ford)

Note,Dijkstra and Breadth-first search are very similar algorithms.

| DFS | BFS | Dijkstra algorithm
| --- | --- | ---
| It uses **stack** | It uses **queue** | It uses **queue**
| cannot find shortest path | finds shortest path in **unweighted** graph | finds shortest path in **weighted** graph
| edges are kept in adjacency matrix | adjacency matrix | adjacency matrix

```C 
	// depth first search
	vector<int>nodes;nodes.push_back(root);level[root] = 1;
	while(!nodes.empty()) { 
		int x = nodes.back();int x = nodes.back();
		int i = n; while(i--) { 
			if(!*(adj+(x*n)+i) || level[i])continue;
			nodes.push_back(i);
			level[i] = level[x]+1;
		}
	}
	// breadth first search
	queue<int>nodes/* queue instead of stack */;nodes.push(root);level[root] = 1;
	while(!nodes.empty()) {
		int x = nodes.front();nodes.pop();
		int i = n; while(i--) {
			if(!*(adj+(x*n)+i) || level[i])continue;
			nodes.push(i);
			level[i] = level[x]+1;
		}
	}
	// Dijkstra algorithm
	queue<int>nodes;nodes.push(root);dist[root] = 0;
	while(!nodes.empty()) {
		int x = nodes.front();nodes.pop();
		int i = n; while(i--) {
			 /* calculate distance instead of level */
			if(!*(adj+(x*n)+i) || (dist[i] < (dist[x]+*(adj+(x*n)+i))))continue;
			nodes.push(i);
			dist[i] = w;prev[i] = x;
 		}
	}
```


Note,Bellman-Ford and Floyd-Warshall are very similar algorithms.

| Bellman Ford-algorithm | Floyd-Warshall's algorithm
| --- | --- 
| complexity `O(|E|\*|V|)` | `O(|V|^3)`
| uses **edge list** | uses **adjacency matrix**
| It loops through all the edges | It loops through all the vertices in two iteration to detect shortest path from one to another
| It relaxes number of times equals to the number of edges minus one | It relaxes number of times equals to the number of vertices

```C
static int bellman_ford(const int n, vector<pair<int, pair<int,int> > > &verts, int*dist, int*prev, const int root) {
	int i;
	const int nvertices = verts.size();
	dist[root] = 0;
	for( i = 1/* strange */ ; i < nvertices; i++) {
		vector<pair<int,pair<int,int> > >::iterator it = verts.begin();
		while(it < verts.end()) {
			pair<int,pair<int,int> > edge = *it++;int w = edge.first;pair<int,int> nodes = edge.second;int x = nodes.first;int y = nodes.second;
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
		pair<int,pair<int,int> > edge = *it++;int w = edge.first;pair<int,int> nodes = edge.second;int x = nodes.first;int y = nodes.second;
		if(dist[y] > dist[x] + w) {
			return -1;
		}
	}
	return 0;
}
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
	return 0;
}
```
