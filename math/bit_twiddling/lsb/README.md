

Get The least significant bit
=============================

This technique is useful in `Fenewick tree/binary indexed tree`.

```
namespace algo_snippet {
    template <typename KINT>
    KINT lsb(const KINT given) {
        static_assert(numeric_limits<given>::is_signed);
        return given & -given;
    }
}
```

Output

```
11111111111111111111111111111110 >mask=(-2)>>31> 11111111111111111111111111111111 >-2+mask> 11111111111111111111111111111101 >(-2+mask)^mask> 00000000000000000000000000000010
11111111111111111111111111111111 >abs> 00000000000000000000000000000001
successful
```

