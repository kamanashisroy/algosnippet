
var search = require('./index.js');
var training_fillme = function(x) {
	console.log("fill me: training");
	return x;
}
var search_fillme = function(x, y) {
	console.log("fill me:search");
	return x;
}
var x = new search.SearchInterval(training_fillme, search_fillme);
x.test();

