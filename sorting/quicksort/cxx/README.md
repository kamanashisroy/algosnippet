
Quick Sort
===========================================


Normal quick-sort output

```
Sorting string:
2,4,465,6,67,3,3,56,7,8,4,56,part-quick bucket 0,12
2,3,3,4,67,465,56,56,7,8,4,6,
part-quick bucket 4,12
2,3,3,4,6,4,56,56,7,8,67,465,
part-quick bucket 4,10
2,3,3,4,4,6,56,56,7,8,67,465,
part-quick bucket 6,10
2,3,3,4,4,6,8,7,56,56,67,465,
part-quick bucket 6,8
2,3,3,4,4,6,7,8,56,56,67,465,
part-quick bucket 0,3
2,3,3,4,4,6,7,8,56,56,67,465,
Sorted string:
2,3,3,4,4,6,7,8,56,56,67,465,
successful 
```

Now the three-way quick sort uses count to avoid worst case for equal keys. It may increase the performance by reducing the number of partition.

```
Sorting string:
2,4,465,6,67,3,3,56,7,8,4,56,
part-quick bucket 0,12
4
2,6,465,4,67,3,3,56,7,8,4,56,
2,3,3,4,67,6,465,56,7,8,4,56,
2,3,3,4,4,6,465,56,7,8,67,56,
part-quick bucket 5,12
56
6,465,7,56,8,67,56,
6,8,7,56,56,67,465,
2,3,3,4,4,6,8,7,56,56,67,465,
part-quick bucket 10,12
2,3,3,4,4,6,8,7,56,56,67,465,
part-quick bucket 5,8
2,3,3,4,4,6,7,8,56,56,67,465,
part-quick bucket 0,3
2,3,3,4,4,6,7,8,56,56,67,465,
Sorted string:
2,3,3,4,4,6,7,8,56,56,67,465,
successful 
```


