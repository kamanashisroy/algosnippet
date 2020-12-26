

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

module.exports.SubSetSumProblem = function(x) {
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
			return 'SubsetSum Problem';
		}
		,'execute' : x
		,'check' : function(input, output, sum) {
			if(!util.isArray(input) || !util.isArray(output))
				return false;
			if(output.length != 2)
				return false;
			if((input[output[0]] + input[output[1]]) != sum)
				return false;
			return true;
		}
		,'testWrapper' : function(input, sum) {
			console.log('testing');
			console.log('input:');
			console.log(input);
			console.log('sum:');
			console.log(sum);
			var output = this.execute(input, sum);
			console.log(output);
			if(this.check(input,output, sum)) {
				console.log('successful');
			} else {
				console.log('failed');
			}
		}
		,'test' : function() {
			var sample = [12,34,23,3,13,4,2];
			this.testWrapper(sample, 6);
		}
	};
}



