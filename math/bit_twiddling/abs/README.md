

Get absolute value.

```
namespace algo_snippet {
    template <typename KINT>
    KINT abs(const KINT given) {
        constexpr unsigned int shift_bits = (sizeof(KINT)*CHAR_BIT)-1;
        // NOTE C/C++ 'usually' implements an arithmetic shift on signed values
        int mask = given >> shift_bits; // mask is 0 when given >= 0, 11111111111(all 1) otherwise
        return (given + mask) ^ mask;
    }
    template <typename KINT>
    KINT twos_complement(const KINT given) {
        return ~given + 1;
    }
}
```

Output

```
11111111111111111111111111111110 >mask=(-2)>>31> 11111111111111111111111111111111 >-2+mask> 11111111111111111111111111111101 >(-2+mask)^mask> 00000000000000000000000000000010
11111111111111111111111111111111 >abs> 00000000000000000000000000000001
successful
```

