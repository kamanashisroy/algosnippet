
const sort = require('../../js/sorter');
const util = require('util');
const assert = require('assert');

var mysort = function(x) {
	// sanity check
	if(!util.isArray(x))
		return x;
	var i = 0;
	for(i=0;i<x.length;i++) {
		var j = 0;
		var pos = -1;
		for(j=1;j<x.length;j++) {
			if(x[j] >= x[j-1]) {
				continue;
			}
			pos = j; // this has unexpected order
			break;
		}
		if(pos == -1) // check if it is sorted already
			break;
		// find the right place for x[pos] in x[0] .. x[pos-1]
		var dest = x.binarySearch(0,pos,x[pos]);
		assert(dest != -1);
		x.moveFront(dest,pos);
	}
	return x;
}

var insertion = new sort.Sorter(mysort);
insertion.test();
