'use strict';

const problem = require('../../js/index');

var bfs = function(graph, start, end) {
	var pool = [];
	var parentList = [];
	var reverseParentList = [];
	pool.push(start);parentList[start] = 0;
	pool.push(end);reverseParentList[end] = 0;
	while(pool.length) {
		var u = pool.shift();
		for(var i = 0; i < graph.length; i++) {
			var v = i+1;
			if(!graph[u-1][v-1]) continue;
			if(u in parentList) {
				if(v in parentList)
					continue;
				if(v in reverseParentList) {
					// found result 
					while(reverseParentList[v]) {
						parentList[reverseParentList[v]] = v;
					}
					parentList[v] = u;
					break;
				}
				parentList[v] = u;
			} else { // u is in reverseParentList
				if(v in reverseParentList)
					continue;
				if(v in parentList) {
					while(reverseParentList[u]) {
						parentList[reverseParentList[u]] = u;
					}
					parentList[u] = v;
					break;
				}
				reverseParentList[v] = u;
			}
			pool.push(v);
		}
	}
	var level = 0;
	var u = end;
	while((u = parentList[u])) level++;
	return level;
}

var x = new problem.UnweightedShortestPathProblem(bfs);
x.test();



