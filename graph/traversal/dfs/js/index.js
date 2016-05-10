
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


var dfs_with_finishing_time = function(graph, start, cb) {
	var explored = [];
	var parent = [];
	var i = 0;
	for(i = 0; i < graph.length; i++) {
		if(i in explored)
			continue;
		explored[i] = 1;
		var pool = [i];
		parent[i] = -1;
		var last_parent = -1;
		while(pool.length) {
			var u = pool.pop();
			var k = 0;
			var no_way = true;
			for(k = 0; k < graph.length; k++) {
				if(k in explored)
					continue;
				if(!graph[u][k])
					continue;
				pool.push(k);
				explored[k] = 1;
				parent[k] = u;
				no_way = false;
			}
			if(no_way) {
				cb(null, u+1); // post ordering (finishing time)
			}
			if(last_parent != parent[u] && last_parent != -1) {
				cb(null, last_parent+1); // post ordering (finishing time)
			}
			last_parent = parent[u];
		}
		if(last_parent != -1) {
			cb(null, last_parent+1); // post ordering (finishing time)
		}
	}
}

//var x = new problem.TraversalProblem(dfs_with_finishing_time);
var x = new problem.TraversalProblem(dfs);
x.test();

