

const util = require('util');
const assert = require('assert');

module.exports.TraversalProblem = function(x) {
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
			return 'Shortest Path Problem';
		}
		,'execute' : x
		,'check' : function(graph, output) {
			for(var i = 1; i <= graph.length; i++) {
				if(output.indexOf(i) === -1)
					return false;
			}
			return true;
		}
		,'testWrapper' : function(graph, start) {
			console.log('testing');
			console.log('graph:');
			console.log(graph);
			var output = "";
			var cb = function(error, node) {
				output+= node + ",";
			}
			this.execute(graph, start, cb);
			console.log(output);
			if(this.check(graph,output)) {
				console.log('successful');
			} else {
				console.log('failed');
			}
		}
		,'test' : function() {
			var graph = [[0,1,1,1],[1,1,0,0],[1,0,1,1],[1,0,1,0]];
			this.testWrapper(graph, 1);
		}
	};
}



