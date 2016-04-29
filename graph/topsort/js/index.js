

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
		,'check' : function(graph, depend) {
			if(!util.isArray(depend))
				return false;
			var represent = this.represent;
			console.log(depend.map(function(i){return represent(i)}));
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
			/*var graph = [
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
			];*/
			var graph = [
				// this problem is from page 615 of cormen book where the problem is defind by m,n .. z nodes
				[4,5,11]
				,[4,8,2]
				,[5,6,9]
				,[2,6,13]
				,[7]
				,[8,12]
				,[5]
				,[]
				,[7]
				,[10,11]
				,[13]
				,[]
				,[9]
				,[]
			];
			this.testWrapper(graph);
		}
	};
}



