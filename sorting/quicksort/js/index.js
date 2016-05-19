
const sort = require('../../js/sorter');
const util = require('util');
const assert = require('assert');

function select_pivote(x) {
	// sanity check
	if(!util.isArray(x) || x.length == 0)
		return null;

	// if smaller than 3 then return x[0]
	if(x.length < 3) {
		return 0;
	}

	// otherwise return the median
	if(x[0] <= x[1]) {
		if(x[1] <= x[2])
			return 1;
		else if(x[0] < x[2])
			return 2;
		else
			return 0;
	} else {
		if(x[0] <= x[2])
			return 0;
		else if(x[1] < x[2])
			return 2;
		else
			return 1;
	}
}

var quicksort = function(x) {
	// sanity check
	if(!util.isArray(x))
		return x;

	// base case
	if(x.length == 1 || x.length == 0) {
		return x;
	}
	if(x.length == 2) {
		if(x[0] > x[1]) {
			x.swap(0,1);
		}
		return x;
	}
	//console.log("Sorting " + x);

	// select a pivote
	var pvt_index = select_pivote(x);
	var i = 0;
	var j = x.length-1;
	var pvt = x[pvt_index];
	//console.log("Pivote index " + pvt_index + " = " + pvt);

	// do in-place partition
	x.swap(pvt_index, j);
	//console.log("after swapping the pivote " + x);

	j--;
	for(i = 0;i<j;) {
		while(x[i] < pvt && i < j)
			i++;
		while(x[j] >= pvt && j > i)
			j--;
		if(i < j ) {
			//console.log("swapping " + x[i] + " and " + x[j]);
			x.swap(i,j);
			//console.log(x);
		} 
	}
	x.swap(j,x.length-1);
	//console.log("after the last swap " + x);
	//console.log("left part " + x.slice(0,j) + " pivote " + pvt + " right part " + x.slice(j+1, x.length));

	// joining
	p = arguments.callee(x.slice(0,j));
	//console.log(p);
	p.push(pvt);
	//console.log("added pivote " + p);
	r = arguments.callee(x.slice(j+1,x.length));
	p = p.concat(r);
	//console.log("added right " + p);
	return p;
}

var qsort = new sort.Sorter(quicksort);
qsort.test();
