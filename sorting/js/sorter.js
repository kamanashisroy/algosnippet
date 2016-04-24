

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

module.exports.Sorter = function(x) {
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
	return {
		'name' : function() {
			return 'Sorter';
		}
		,'sort' : x
		,'check' : function(input, output) {
			if(!util.isArray(input) || !util.isArray(output))
				return false;
			if(input.length != output.length)
				return false;
			var i = 0;
			for(i = 1; i < output.length; i++) {
				if(output[i] < output[i-1])
					return false;
			}
			return true;
		}
		,'testWrapper' : function(input) {
			console.log('testing');
			console.log('input:');
			console.log(input);
			var output = this.sort(input);
			console.log(output);
			if(this.check(input,output)) {
				console.log('successful');
			} else {
				console.log('failed');
			}
		}
		,'test' : function() {
			this.testWrapper([12,34,23,3,13,4,2]);
			this.testWrapper([2, 4, 1, 3, 5]);
			this.testWrapper([1, 20, 6, 4, 5]);
		}
	};
}



