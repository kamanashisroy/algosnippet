
Longest common subsequence
============================

Dynamic programming takes `O(m*n)` time.

```C
for(int i = 0; i < m; i++) {
    for(int j = 0; j < n; j++) {
        if(x[i] == y[j]) {
            // case 0: match case
            // NOTE relaxation is not needed here because none did set mtx[i+1][j+1] yet
            mtx[i+1][j+1] = mtx[i][j]+1;
            result = std::max(result,mtx[i+1][j+1]);
        } else {
            // case 1: try to discard x[i] 
            if(mtx[i+1][j] < mtx[i][j]) {
                mtx[i+1][j] = mtx[i][j];
            }
            // case 2: try to discard y[j]
            if(mtx[i][j+1] < mtx[i][j]) {
                mtx[i][j+1] = mtx[i][j];
            }
        }
    }
}
```

Here is the matrix

```
.		a		t		a		n		a
b		0,*		0,*		0, 		0, 		0,
a		1, 		1,*		1, 		0, 		1,
n		1, 		1, 		0,*		2, 		0,
a		1, 		1, 		2,*		0, 		3,
n		1, 		1, 		0, 		3,*		0,
a		1, 		0, 		2, 		0, 		4,*
```


