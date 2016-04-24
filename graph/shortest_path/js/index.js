

//var args = process.argv.slice(2); // read the command line arguments

/**
 * read from pipe
 */

/*process.stdin.resume();
process.stdin.setEncoding('utf8');
process.stdin.on('data', function(data) {
  process.stdout.write(data);
});*/

const util = require('util');
const assert = require('assert');

module.exports.ShortestPathProblem = function(x) {
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
			return (output == 15)?true:false;
		}
		,'testWrapper' : function(graph, start, end) {
			console.log('testing');
			console.log('graph:');
			console.log(graph);
			var output = this.execute(graph, start, end);
			console.log(output);
			if(this.check(graph,output)) {
				console.log('successful');
			} else {
				console.log('failed');
			}
		}
		,'test' : function() {
			var graph = [[0,24,3,20],[24,0,10000,10000],[3,10000,0,12],[20,10000,12,0]];
			this.testWrapper(graph, 1, 4);
		}
	};
}



