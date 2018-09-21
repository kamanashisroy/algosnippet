'use strict';

const problem = require('../../js/index');

var bfs = function(graph, start, end) {
	var pool = [];
	var level = [];
	pool.push(start);level[start] = 0;
	while(pool.length) {
		var u = pool.shift();
		for(var i = 0; i < graph[u].length; i++) {
			var v = graph[u][i].n;
			if(v in level) continue;
			pool.push(v);
			level[v] = level[u] + 1;
			if(v == end)
				return level[v];
		}
	}
	return 1000;
}

var x = new problem.UnweightedShortestPathProblem(bfs);
x.test();



