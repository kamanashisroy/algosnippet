
Binomial Heap
==============

In binaomial heap a `k-order` node contains `2^k` elements.

Example Heap
==============

```
appending  32
binomial-heap
<binomial-order=1,32>
--------------------

appending  14
binomial-heap
	<binomial-order=1,32>
<binomial-order=2,14>
--------------------

appending  12
binomial-heap
	<binomial-order=1,32>
<binomial-order=2,14>
<binomial-order=1,12>
--------------------

appending  523
binomial-heap
		<binomial-order=1,32>
	<binomial-order=2,14>
	<binomial-order=1,523>
<binomial-order=3,12>
--------------------

appending  13
binomial-heap
		<binomial-order=1,32>
	<binomial-order=2,14>
	<binomial-order=1,523>
<binomial-order=3,12>
<binomial-order=1,13>
--------------------

appending  1
binomial-heap
		<binomial-order=1,32>
	<binomial-order=2,14>
	<binomial-order=1,523>
<binomial-order=3,12>
	<binomial-order=1,13>
<binomial-order=2,1>
--------------------

appending  7
binomial-heap
		<binomial-order=1,32>
	<binomial-order=2,14>
	<binomial-order=1,523>
<binomial-order=3,12>
	<binomial-order=1,13>
<binomial-order=2,1>
<binomial-order=1,7>
--------------------

appending  23
binomial-heap
			<binomial-order=1,32>
		<binomial-order=2,14>
		<binomial-order=1,523>
	<binomial-order=3,12>
		<binomial-order=1,23>
	<binomial-order=2,7>
	<binomial-order=1,13>
<binomial-order=4,1>
--------------------

appending  7
binomial-heap
			<binomial-order=1,32>
		<binomial-order=2,14>
		<binomial-order=1,523>
	<binomial-order=3,12>
		<binomial-order=1,23>
	<binomial-order=2,7>
	<binomial-order=1,13>
<binomial-order=4,1>
<binomial-order=1,7>
--------------------

appending  2
binomial-heap
			<binomial-order=1,32>
		<binomial-order=2,14>
		<binomial-order=1,523>
	<binomial-order=3,12>
		<binomial-order=1,23>
	<binomial-order=2,7>
	<binomial-order=1,13>
<binomial-order=4,1>
	<binomial-order=1,7>
<binomial-order=2,2>
--------------------

appending  7
binomial-heap
			<binomial-order=1,32>
		<binomial-order=2,14>
		<binomial-order=1,523>
	<binomial-order=3,12>
		<binomial-order=1,23>
	<binomial-order=2,7>
	<binomial-order=1,13>
<binomial-order=4,1>
	<binomial-order=1,7>
<binomial-order=2,2>
<binomial-order=1,7>
--------------------

appending  4
binomial-heap
			<binomial-order=1,32>
		<binomial-order=2,14>
		<binomial-order=1,523>
	<binomial-order=3,12>
		<binomial-order=1,23>
	<binomial-order=2,7>
	<binomial-order=1,13>
<binomial-order=4,1>
		<binomial-order=1,7>
	<binomial-order=2,4>
	<binomial-order=1,7>
<binomial-order=3,2>
--------------------

appending  89
binomial-heap
			<binomial-order=1,32>
		<binomial-order=2,14>
		<binomial-order=1,523>
	<binomial-order=3,12>
		<binomial-order=1,23>
	<binomial-order=2,7>
	<binomial-order=1,13>
<binomial-order=4,1>
		<binomial-order=1,7>
	<binomial-order=2,4>
	<binomial-order=1,7>
<binomial-order=3,2>
<binomial-order=1,89>
--------------------

appending  8
binomial-heap
			<binomial-order=1,32>
		<binomial-order=2,14>
		<binomial-order=1,523>
	<binomial-order=3,12>
		<binomial-order=1,23>
	<binomial-order=2,7>
	<binomial-order=1,13>
<binomial-order=4,1>
		<binomial-order=1,7>
	<binomial-order=2,4>
	<binomial-order=1,7>
<binomial-order=3,2>
	<binomial-order=1,89>
<binomial-order=2,8>
--------------------

appending  3
binomial-heap
			<binomial-order=1,32>
		<binomial-order=2,14>
		<binomial-order=1,523>
	<binomial-order=3,12>
		<binomial-order=1,23>
	<binomial-order=2,7>
	<binomial-order=1,13>
<binomial-order=4,1>
		<binomial-order=1,7>
	<binomial-order=2,4>
	<binomial-order=1,7>
<binomial-order=3,2>
	<binomial-order=1,89>
<binomial-order=2,8>
<binomial-order=1,3>
--------------------

appending  26
binomial-heap
				<binomial-order=1,89>
			<binomial-order=2,8>
			<binomial-order=1,26>
		<binomial-order=3,3>
			<binomial-order=1,7>
		<binomial-order=2,4>
		<binomial-order=1,7>
	<binomial-order=4,2>
			<binomial-order=1,32>
		<binomial-order=2,14>
		<binomial-order=1,523>
	<binomial-order=3,12>
		<binomial-order=1,23>
	<binomial-order=2,7>
	<binomial-order=1,13>
<binomial-order=5,1>
--------------------

appending  94
binomial-heap
				<binomial-order=1,89>
			<binomial-order=2,8>
			<binomial-order=1,26>
		<binomial-order=3,3>
			<binomial-order=1,7>
		<binomial-order=2,4>
		<binomial-order=1,7>
	<binomial-order=4,2>
			<binomial-order=1,32>
		<binomial-order=2,14>
		<binomial-order=1,523>
	<binomial-order=3,12>
		<binomial-order=1,23>
	<binomial-order=2,7>
	<binomial-order=1,13>
<binomial-order=5,1>
<binomial-order=1,94>
--------------------

binomial-heap
				<binomial-order=1,89>
			<binomial-order=2,8>
			<binomial-order=1,26>
		<binomial-order=3,3>
			<binomial-order=1,7>
		<binomial-order=2,4>
		<binomial-order=1,7>
	<binomial-order=4,2>
			<binomial-order=1,32>
		<binomial-order=2,14>
		<binomial-order=1,523>
	<binomial-order=3,12>
		<binomial-order=1,23>
	<binomial-order=2,7>
	<binomial-order=1,13>
<binomial-order=5,1>
<binomial-order=1,94>
--------------------
```

Now, searching the min-node yields `1`.


