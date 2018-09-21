'use strict';

const problem = require('../../js/index');

var bfs = function(graph, start, cb) {
	var pool = [];
	var marker = [];
	pool.push(start);marker.push(start);
	while(pool.length) {
		var u = pool.shift();
		cb(null, u);
		for(var i = 0; i < graph.length; i++) {
			var v = i+1;
			if(!graph[u-1][v-1]) continue;
			if(marker.indexOf(v) !== -1) continue;
			marker.push(v);
			pool.push(v);
		}
	}
}

var x = new problem.TraversalProblem(bfs);
x.test();



