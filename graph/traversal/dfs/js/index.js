
const problem = require('../../js/index');
const util = require('util');

var dfs = function(graph, start, cb) {
	var pool = [start];
	var prev = [];
	prev[start] = -1;
	while(pool.length) {
		var u = pool.pop();
		cb(null, u);
		var k = 0;
		for(k = 0; k < graph.length; k++) {
			var v = k+1;
			if(v in prev)
				continue;
			if(!graph[u-1][k])
				continue;
			pool.push(v);
			prev[v] = u;
		}
	}
	console.log(prev);
}
var x = new problem.TraversalProblem(dfs);
x.test();

