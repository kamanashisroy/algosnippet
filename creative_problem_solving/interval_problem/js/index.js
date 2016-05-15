

const util = require('util');
const assert = require('assert');

module.exports.SearchInterval = function(train, search) {
	Array.prototype.swap = function (x,y) {
		var b = this[x];
		this[x] = this[y];
		this[y] = b;
		return this;
	}
	/**
	 * It searches the next smaller or equal element of p in sorted elements [x,y). If the target is found the the index is returned otherwise -1 is returned.
	 */
	Array.prototype.binarySearch = function(x,y,p) {
		if(x == y)
			return -1;
		y--;
		if(this[x] > p)
			return -1;
		if(this[y] <= p)
			return y;
		assert(x != y);
		//var mid = Math.floor((x+y)/2);
		var mid = (x+(y+1)) >> 1;
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
	Array.prototype.moveFront = function(x, start, end) {
		assert(x<start, "It only moves the element in the position of arg2 in the position of arg0, arg0 must be smaller than arg1");
		var chunk = this.splice(start, end - start);
		var k = 0;
		var ar = this;
		chunk.forEach(function(p) {ar.splice(x++,0,p);});
		//this.splice.call(this, [x,0].join(chunk));
		return this;
	}
	var intrand = function() {
		return Math.floor(Math.random()*1000);
	}
	var pairrand = function() {
		var x = intrand();
		var y = x+intrand();
		return [x,y];
	}
	return {
		'name' : function() {
			return 'SearchInterval';
		}
		,'train' : train
		,'searchInterval' : search 
		,'check' : function(intervals, target, output) {
			if(!util.isArray(intervals) || !util.isArray(target) || !util.isArray(output)) {
				console.log("Test failed while in sanity check");
				return false;
			}
			var i = 0;
			for(i = 0; i < output.length; i++) {
				if(output[i][0] > target[1] || output[i][1] < target[0]) {
					console.log("The following is not overlapping");
					console.log(output[i]);
					console.log("Where the target is");
					console.log(target);
					return false;
				}
				// TODO check if output[i] is in intervals and check if there is any solution that is not in array
			}
			return true;
		}
		,'testWrapper' : function(intervals, target) {
			var tdata = this.train(intervals);
			var output = this.searchInterval(tdata, target);
			if(this.check(intervals, target, output)) {
				console.log('successful');
			} else {
				console.log('failed');
			}
		}
		,'test' : function() {
			var intervals = [];
			var N = 1000;
			for(var i = 0; i < N; i++) {
				intervals.push(pairrand());
			}
			this.testWrapper(intervals, pairrand());
		}
	};
}



