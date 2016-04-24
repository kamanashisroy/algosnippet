
const sort = require('../../js/sorter');
const util = require('util');
const assert = require('assert');

var mysort = function(x) {
	// sanity check
	if(!util.isArray(x))
		return x;
	var inversions = 0;
	var inc = 0;
	//var maxmid = (x.length >> 1)+1;
	for(inc=1;inc<x.length;inc = inc<<1) {
		var j = 0;
		for(j = 0; j < x.length;) { // this can be parallelized
			var mid = j+inc;
			var last = mid+inc;
			last = (last > x.length)?(x.length):(last);
			if((mid) >= last) { // base case
				j = last;
				continue;
			}
			// divide
			var p = j;
			var q = mid;
			// merge
			if(x[q-1] < x[q]) {
				// already sorted no inversions
			} else {
				// do insertion sort here
				for(;p< q && q < last;) {
					var pos = x.binarySearch(q, last, x[p]);
					if(pos == -1) {
						p++;
						continue;
					}
					assert(pos >= q && pos <= last);
					//console.log('search[' + q + "," + last + ")," + x[p] + "=" + pos);
					/**
					 * [q,pos] elements precede x[p,q). 
					 */
					var chunkLen = pos-q+1;
					inversions+=(q-p)*(chunkLen); // very tricky ..
					x.moveFront(p,q,pos+1);
					//console.log(x);
					p+= chunkLen;
					q+= chunkLen;
				}
			}
			j = last;
		}
	}
	console.log("Number of inversions:" + inversions);
	return x;
}

var merge = new sort.Sorter(mysort);
merge.test();
