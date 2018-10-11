
Edit distance/Levenshtein distance problem
===========================================

Edit distance is the minimum number of edit needed to convert one given string to other given string.

                Edit Distance = Number of edits
Source-string -------------------------------------> Destination-string

The problem can be solved by,

- Backtracking
- **Dynamic Programming**
- `A*`/Dijkstra like algorithm

When the two string has equal length, the edit distance may be comparable to hamming distance.

Here is the program output.

```
*		.		    w		    o		    r		    d		
.		0,M 		1,A 		2,A 		3,A 		4,A 		
f		1,D*		1,C 		2,C 		3,C 		4,C 		
o		2,D*		2,C 		1,M 		3,C 		4,C 		
r		3,D*		3,C 		3,C 		1,M 		2,A 		
w		11,M 		3,M*		4,C 		2,D 		2,C 		
a		11,M 		4,D 		4,C*		3,D 		3,C 		
r		11,M 		5,D 		5,C 		4,M*		4,C 		
d		11,M 		6,D 		6,C 		6,C 		4,M*		
dist(forward,word) 4
*		.		    s		    i		    t		    t		    i		    n		    g		
.		0,M 		1,A 		2,A 		3,A 		4,A 		5,A 		6,A 		7,A 		
k		1,D 		1,C*		2,C 		3,C 		4,C 		5,C 		6,C 		7,C 		
i		2,D 		2,C 		1,M*		3,C 		4,C 		4,M 		5,A 		6,A 		
t		3,D 		3,C 		3,C 		1,M*		3,M 		4,A 		5,C 		6,C 		
t		4,D 		4,C 		4,C 		3,M 		1,M*		2,A 		3,A 		4,A 		
e		5,D 		5,C 		5,C 		4,D 		2,D 		2,C*		3,C 		4,C 		
n		6,D 		6,C 		6,C 		5,D 		3,D 		3,C 		2,M*		3,A*		
dist(kitten,sitting) 3
*		.		    k		    i		    t		    t		    e		    n		
.		0,M 		1,A 		2,A 		3,A 		4,A 		5,A 		6,A 		
s		1,D 		1,C*		2,C 		3,C 		4,C 		5,C 		6,C 		
i		2,D 		2,C 		1,M*		3,C 		4,C 		5,C 		6,C 		
t		3,D 		3,C 		3,C 		1,M*		3,M 		4,A 		5,A 		
t		4,D 		4,C 		4,C 		3,M 		1,M*		2,A 		3,A 		
i		5,D 		5,C 		4,M 		4,D 		2,D 		2,C*		3,C 		
n		6,D 		6,C 		5,D 		5,C 		3,D 		3,C 		2,M*		
g		7,D 		7,C 		6,D 		6,C 		4,D 		4,C 		3,D*		
dist(sitting,kitten) 3
```

