
var search = require("../../js/index.js");

/**
 * We can configure bucketing by specifying the number of buckets(n).
 * Otherwise we can define the bucket number by the length of intervals.
 */

function find_limits(intervals) {
	if(intervals.length == 0) { // sanity check
		return [0,0];
	}
	var min = intervals[0][0];
	var max = intervals[0][1];
	for(var i = 0; i < intervals.length; i++) {
		if(min > intervals[i][0]) {
			min = intervals[i][0];
		}
		if(max < intervals[i][1]){
			max = intervals[i][1];
		}
	}
	return [min,max];
}

function make_buckets(limits, N) {
	if(limits[0] == limits[1]) // sanity check
		return [];
	if(N == 0) // sanity check
		return [];
	var buckets = [];
	var interval_len = N/(limits[1]-limits[0]);
	for(var i = 0; i < N; i++) {
		var start = limits[0] + i*interval_len;
		buckets[i] = [start,start + interval_len - 1];
	}
	buckets[N-1][1] = limits[1]; // extend the last one .
	return buckets;
}

/**
 * Given the intervals and buckets, this function distributes the intervals into buckets for fast retrieval.
 * @intervals array of intervals(pair of numbers)
 * @buckets array of intervals(pair of numbers) that defines some buckets. The buckets are sorted in increasing order.
 * @returns array of content arrays. The outer array corresponds to bucket. And the inner array corresponds to the index of intervals.
 */
function distribute_in_buckets(intervals, buckets) {
	var contents = [];
	for(var i = 0; i < intervals.length; i++) {
		var bucketIndex = Math.floor((intervals[i][0] - buckets[0][0])/(buckets.length));
		//console.log(bucketIndex);
		for(;bucketIndex < buckets.length && buckets[bucketIndex][1] <= intervals[i][1]; bucketIndex++) {
			if(!(bucketIndex in contents)) {
				contents[bucketIndex] = [];
			}
			contents[bucketIndex].push(i); // add only the index of the interval
		}
	}
	return contents;
}

var find_overlapping = function(intervals, buckets, contents, target) {
	console.log(target);
	var output = [];
	var bucketIndex = Math.floor((target[0] - buckets[0][0])/(buckets.length));
	var marker = [];
	for(;bucketIndex < buckets.length && buckets[bucketIndex][1] <= target[1]; bucketIndex++) {
		if(!(bucketIndex in contents)) {
			continue;
		}
		for(var j = 0; j < contents[bucketIndex].length; j++) {
			var xIndex = contents[bucketIndex][j];
			if(intervals[xIndex][0] > target[1] || intervals[xIndex][1] < target[0]) {
				continue;
			}
			if(xIndex in marker) {
				continue; // already added
			}
			marker[xIndex] = 1;
			output.push(intervals[xIndex]);
		}
	}
	console.log(output.length);
	return output;
}

var distribution_bucketing = function(intervals, target) {

	// create search buckets
	var N = intervals.length; // number of buckets is the number of intervals, we could set it to 2 or any other value.
	var limits = find_limits(intervals);
	var buckets = make_buckets(limits, N);
	var contents = distribute_in_buckets(intervals, buckets);
	return {
		'intervals' : intervals
		,'buckets' : buckets
		,'contents' : contents
	};
}

var distribution_bucket_search = function(training_data, target) {
	return find_overlapping(training_data.intervals, training_data.buckets, training_data.contents, target);
}

var x = new search.SearchInterval(distribution_bucketing, distribution_bucket_search);
x.test();

