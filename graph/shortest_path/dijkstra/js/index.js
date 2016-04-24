
const problem = require('../../js/index');
var dijkstra = function(graph, start, end) {
	var dist = [];
	var prev = [];
	const n = graph[0].length;
	for(var i = 0; i < n; i++) {
		dist[i] = 10000;
		prev[i] = -1;
	}
	dist[start-1] = 0;
	var pool = [start];
	while(pool.length) {
		var u = pool.pop();
		for(var v = 1; v <= n; v++) {
			if((u == v) || (graph[u-1][v-1] == 10000))
				continue;
			cost = dist[u-1] + graph[u-1][v-1]; 
			if(dist[v-1] > cost) {
				dist[v-1] = cost;
				prev[v-1] = u;
				pool.push(v);
			}
		}
	}
	return dist[end-1]; // return distrance
}

var x = new problem.ShortestPathProblem(dijkstra);
x.test();

