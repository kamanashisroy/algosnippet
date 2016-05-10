
const problem = require('../../js/index');
const util = require('util');

var dfs = function(graph, start, cb) {
	var explored = [];
	var i = 0;
	for(i = 0; i < graph.length; i++) {
		if(i in explored)
			continue;
		explored[i] = 1;
		var pool = [i];
		while(pool.length) {
			var u = pool.pop();
			var k = 0;
			cb(null, u+1); // pre-ordering
			for(k = 0; k < graph.length; k++) {
				if(k in explored)
					continue;
				if(!graph[u][k])
					continue;
				pool.push(k);
				explored[k] = 1;
			}
		}
	}
}
var x = new problem.TraversalProblem(dfs);
x.test();

