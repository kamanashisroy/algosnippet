
const problem = require('../../js/index');
const util = require('util');

var myTop = function(graph, represent) {
	var depend = [];
	var dfs = function(start) {
		var pool = [start];
		var prev = [];
		prev[start] = -1;
		while(pool.length) {
			var u = pool.pop();
			var k = 0;
			depend.unshift(u);
			for(k = 0; k < graph.length; k++) {
				if(k in prev)
					continue;
				if(!graph[u][k])
					continue;
				pool.push(k);
				prev[k] = u;
				console.log(represent(k) + " child of " + represent(u));
			}
		}
		console.log(prev);
	}

	// sort the graph with degree first..
	var i = 0;
	var inDegree = [];
	for(i = 0; i < graph.length; i++) {
		inDegree[i] = 0;
	}
	for(i = 0; i < graph.length; i++) {
		for(var j = 0; j < graph.length; j++) {
			if(graph[i][j]) {
				inDegree[j]++;
			}
		}
	}
	for(i = 0; i < graph.length; i++) {
		if(inDegree[i])
			continue;
		console.log("working for " + represent(i));
		dfs(i);
		console.log("depend: " + depend.map(function(i) { return represent(i)}));
	}
	return []; // return tree
}
var x = new problem.TopSortProblem(myTop);
x.test();

