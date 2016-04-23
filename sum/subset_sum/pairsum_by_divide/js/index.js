
const subsetsum = require('../../js/subsetsum');
const util = require('util');
const assert = require('assert');


var mysubsetsum = function(x, sum) {
	// sanity check
	if(!util.isArray(x))
		return x;
	var helper = function(x, begin, end, sum) {
		if((end - begin) == 2) {
			var result = ((x[begin] + x[end-1]) == sum)?[begin,end-1]:false;
			return result;
		} else if((end - begin) == 1) {
			return false;
		}

		var mid = (begin+end) >> 1;
		var result = helper(x, begin, mid, sum);
		if(result === false)
			result = helper(x, mid, end, sum);
		if(util.isArray(result)) {
			return result;
		}
		var p = begin;
		for(;p < mid; p++) {
			var q = mid;
			for(; q < end; q++) {
				if((x[p] + x[q]) == sum)
					return [p,q];
			}
		}
		return false;
	}
	return helper(x, 0, x.length, sum);
}

new subsetsum.SubSetSumProblem(mysubsetsum).test();
