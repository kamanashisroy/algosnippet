
#include <climits> // defines CHAR_BIT

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

#define DEBUG
#ifdef DEBUG

#include <bitset>
#include <iostream>
#include <cassert>

using namespace std;

int main(int argc, char*argv[]) {
    std::bitset<sizeof(int)*CHAR_BIT> x;

    const int ix = -2;
    x = -2;
    cout << x << " >mask=(-2)>>31> ";
    const int imask = ix >> ((sizeof(ix)*CHAR_BIT)-1);
    x = imask;
    cout << x << " >-2+mask> ";
    int ixx = (ix+imask);
    x = ixx;
    cout << x << " >(-2+mask)^mask> ";
    ixx = ixx^(imask);
    x = ixx;
    cout << x << endl;
    



    x = -1;
    cout << x << " >abs> ";
    x = algo_snippet::abs(-1);
    cout << x << endl;
    
    assert(algo_snippet::abs(-1) == 1);
    cout << "successful" << endl;
    assert(algo_snippet::abs(-2) == 2);
    return 0;
}

#endif // DEBUG
