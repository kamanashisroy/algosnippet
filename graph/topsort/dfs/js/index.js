
const problem = require('../../js/index');
const util = require('util');

var myTop = function(graph, represent) {
	var depend = [];
	var prev = [];
	var dfs = function(u) {
		var k = 0;
		for(k = 0; k < graph[u].length; k++) {
			var v = graph[u][k];
			if(v in prev)
				continue;
			/**
			 * Node is marked, but not traversed
			 */
			prev[v] = u;
			dfs(v);
		}
		/**
		 * node is traversed completely.
		 */
		depend.push(u); // finishes
	}

	for(i = 0; i < graph.length; i++) {
		if(i in prev)
			continue;
		prev[i] = -1;
		dfs(i);
	}
	return depend; // return tree
}
var x = new problem.TopSortProblem(myTop);
x.test();

