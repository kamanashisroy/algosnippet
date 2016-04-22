
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
		var minpos = i;
		for(j=i+1;j<x.length;j++) {
			if(x[j] >= x[minpos]) {
				continue;
			}
			minpos = j;
		}
		if(minpos == i) // check if it is sorted already
			continue;
		x.moveFront(i, minpos);
	}
	return x;
}

var selection = new sort.Sorter(mysort);
selection.test();
