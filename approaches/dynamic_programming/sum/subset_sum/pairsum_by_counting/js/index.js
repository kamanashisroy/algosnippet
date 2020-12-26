
const subsetsum = require('../../js/subsetsum');
const util = require('util');
const assert = require('assert');


var mysubsetsum = function(x, sum) { // we assume all the numbers in x are positive.
	// sanity check
	if(!util.isArray(x))
		return x;
	var pos = [];
	for(var i = 0; i < x.length; i++) {
		assert(x[i] >= 0);
		var p = x[i];
		var q = sum-p;
		
		if(pos[q]) {
			return [pos[q],i]
		}
		pos[p] = i;
	}
	
	return 0;
}

new subsetsum.SubSetSumProblem(mysubsetsum).test();
