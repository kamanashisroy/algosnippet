

const util = require('util');
const assert = require('assert');

module.exports.TopSortProblem = function(x) {
	Array.prototype.swap = function (x,y) {
		var b = this[x];
		this[x] = this[y];
		this[y] = b;
		return this;
	}
	/**
	 * It searches the next smaller or equal element of p in sorted elements [x,y).
	 */
	Array.prototype.binarySearch = function(x,y,p) {
		y--;
		if(this[x] > p)
			return x;
		if(this[y] <= p)
			return y;
		if(x == y)
			return x;
		//var mid = Math.floor((x+y)/2);
		var mid = (x+y) >> 2;
		if(mid == x)
			return y;
		if(this[mid] <= p)
			return this.binarySearch(mid,y+1,p);
		else
			return this.binarySearch(x,mid,p);
	}
	Array.prototype.moveFront = function(x,y) {
		assert(x<y, "It only moves the element in the position of arg2 in the position of arg0, arg0 must be smaller than arg1");
		var p = this[y];
		for(var i = y; i > x; i--) {
			this[i] = this[i-1];
		}
		this[x] = p;
		return this;
	}
	return {
		'name' : function() {
			return 'Topological sort Problem';
		}
		,'represent' : function(i) {
			const rep = "mnopqrstuvwxyz";
			return rep.charAt(i);
		}
		,'execute' : x
		,'check' : function(graph, prev) {
			var i = 0;
			var marker = [];
			var dumpParent = function(index) {
				if(!(index in prev)) { // base case
					console.log(index);
					return 0;
				}
				marker[index] = 1;
				var ret = dumpParent(prev[index]);
				console.log(' - ' + ret + " : "  + index);
				return ret+1;
			}
			for(i = 1; i <= graph.length; i++) {
				if(!(i in prev))
					continue;
				if(i in marker)
					continue;
				marker[i] = 1;
				dumpParent(i);
			}
			return true;
		}
		,'testWrapper' : function(graph) {
			console.log('testing');
			console.log('graph:');
			console.log(graph);
			var output = this.execute(graph,this.represent);
			console.log(output);
			if(this.check(graph,output)) {
				console.log('successful');
			} else {
				console.log('failed');
			}
		}
		,'test' : function() {
			var graph = [
				// this problem is from page 615 of cormen book where the problem is defind by m,n .. z nodes
				//[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
				[0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0]
				,[0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0]
				,[0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0]
				,[0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1]
				,[0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0]
				,[0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0]
				,[0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0]
				,[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
				,[0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0]
				,[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0]
				,[0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0]
				,[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
			];
			this.testWrapper(graph);
		}
	};
}



