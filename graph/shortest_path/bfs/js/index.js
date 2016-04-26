'use strict';

const problem = require('../../js/index');

var bfs = function(graph, start, end) {
	var pool = [];
	var level = [];
	pool.push(start);level[start] = 0;
	while(pool.length) {
		var u = pool.shift();
		for(var i = 0; i < graph.length; i++) {
			var v = i+1;
			if(!graph[u-1][v-1]) continue;
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



