
#include <climits> // defines CHAR_BIT
#include <limits>  // defines numeric_limits

namespace algo_snippet {
    template <typename KINT>
    KINT lsb(const KINT given) {
        static_assert(std::numeric_limits<KINT>::is_signed);
        return given & -given;
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

    const int ix = 5;
    x = ix;
    cout << "lsb(" << x << ") = " << " lsb(" << ix << ") = " << algo_snippet::lsb(ix) << std::endl;
    assert(algo_snippet::lsb(5) == 1);
    cout << "successful" << endl;
    assert(algo_snippet::lsb(4) == 4);
    return 0;
}

#endif // DEBUG
