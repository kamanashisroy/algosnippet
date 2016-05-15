
var search = require('./index.js');
var fillme = function(x, y, z) {
	console.log("fill me");
	return x;
}
var x = new search.SearchInterval(fillme);
x.test();

