This is the problem of finding the number of inversions in an array.

#### Bubble sort

Bubble sort is inversion bound. It swaps the value for each inversion. The swaps can be counted to get the number of inversions in O(n^2) time.

#### Merge sort

Merge sort is comparison based and it uses divide and conquer approach. In each combine stage of merge sort we can count the number of inversions. 


```Javascript
	// combining [p,q) and [q,last) in the x array
	for(;p< q && q < last;) {
		var pos = x.binarySearch(q, last, x[p]);
		if(pos == -1) {
			p++;
			continue;
		}
		assert(pos >= q && pos <= last);
		/**
		 * [q,pos] elements precede x[p,q). 
		 */
		var chunkLen = pos-q+1;
		inversions+=(q-p)*(chunkLen); // very tricky ..
		x.moveFront(p,q,pos+1);
		p+= chunkLen;
		q+= chunkLen;
	}
```

This algorithm takes `BigO(n\*log n)` time.
