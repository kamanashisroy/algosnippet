
Radix-tree
=============

Radix-tree has order-property which is not available in hash-table. (NOTE normal Radix-tree is not cache friendly as in linear probing).

```
Hash tables are commonly said to have expected O(1) insertion and deletion times, but this is only true when considering computation of the hash of the key to be a constant-time operation. When hashing the key is taken into account, hash tables have expected O(k) insertion and deletion times, but may take longer in the worst case depending on how collisions are handled. Radix trees have worst-case O(k) insertion and deletion. The successor/predecessor operations of radix trees are also not implemented by hash tables.
```
