
const problem = require('../../js/index');
var dijkstra = function(graph, start, end) {
	var dist = [];
	var prev = [];
	const n = graph.length;
	for(var i = 0; i < n; i++) {
		dist[i] = 10000;
		prev[i] = -1;
	}
	dist[start] = 0;
	var pool = [start];
	while(pool.length) {
		var u = pool.pop();
		console.log("u = " + u);
		for(var k = 0; k < graph[u].length; k++) {
			console.log(graph[u][k]);
			var v = graph[u][k].n;
			cost = dist[u] + graph[u][k].w; 
			console.log(graph[u][k].w + " cost : " + cost + " dist : " + dist[v]);
			if(dist[v] > cost) {
				dist[v] = cost;
				prev[v] = u;
				pool.push(v);
			}
		}
	}
	console.log(dist);
	return dist[end]; // return distrance
}

var x = new problem.ShortestPathProblem(dijkstra);
x.test();

