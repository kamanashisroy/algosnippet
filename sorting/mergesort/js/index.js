
const sort = require('../../js/sorter');
const util = require('util');
const assert = require('assert');

var mysort = function(x) {
	// sanity check
	if(!util.isArray(x))
		return x;
	var inc = 0;
	var maxmid = (x.length >> 1)+1;
	for(inc=1;inc<=maxmid;inc = inc<<1) {
		var j = 0;
		for(j = 0; j < x.length;) { // this can be parallelized
			var mid = j+inc;
			var last = mid+inc;
			last = (last > x.length)?(x.length):(last);
			if((mid) >= last) {
				j = last;
				continue;
			}
			// divide
			var p = j;
			var q = mid;
			// merge
			if(x[q-1] < x[q]) {
				// already sorted
			} else {
				for(;p< q && q < last;) {
					if(x[p] > x[q]) {
						x.moveFront(p,q);
						p++;q++;
					} else {
						p++;
					}
				}
			}
			j = last;
		}
	}
	return x;
}

var merge = new sort.Sorter(mysort);
merge.test();
