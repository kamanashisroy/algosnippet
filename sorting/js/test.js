
var sort = require('./sorter');
var fillme = function(x) {
	console.log("fill me");
	return x;
}
var x = new sort.Sorter(fillme);
x.test();

