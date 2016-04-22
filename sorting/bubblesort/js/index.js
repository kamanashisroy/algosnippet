
const sort = require('../../js/sorter');
const util = require('util');


var mysort = function(x) {
	// sanity check
	if(!util.isArray(x))
		return x;
	var i = 0;
	var swapped = true;
	for(i=0;i<x.length && swapped;i++) {
		var j = 0;
		swapped = false;
		for(j=1;j<x.length;j++) {
			if(x[j] >= x[j-1]) {
				continue;
			}
			// swap
			x.swap(j,j-1);
			swapped = true;
		
		}
	}
	return x;
}

var bubble = new sort.Sorter(mysort);
bubble.test();
