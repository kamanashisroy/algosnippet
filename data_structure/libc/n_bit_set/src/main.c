
#include <inttypes.h>
#include <assert.h>


    static inline int get_set_position(const uint32_t z) {
        switch(z) {
            case 0x1:
                return 0;
            case 0x2:
                return 1;
	    case 0x4:
                return 2;
	    case 0x8:
                return 3;
	    case 0x10:
                return 4;
	    case 0x20:
                return 5;
	    case 0x40:
                return 6;
	    case 0x80:
                return 7;
	    case 0x100:
                return 8;
	    default:
		return -1;
        }
        return -1;
    }

    static inline int get_set_n_position(const uint32_t x, const uint8_t n) {
        if(!n) return -1;
        int i = n-1;
        uint32_t y = x;
        while(y && i--) {
            y = y & (y << 1);
        };
        if(!y) return -1;
        uint32_t z = y - (y & (y-1));
        if(!z) return -1;
        int pos = get_set_position(z);
        if(pos < 0) return -1;
        assert(pos >= (n-1));
        return pos - (n-1);
    }


int main(int argc, char*argv[]) {

	assert(get_set_n_position(0b1100110, 2) == 1);
	assert(get_set_n_position(0b1100110, 3) == -1);
	assert(get_set_n_position(0b1100110, 1) == 1);
	assert(get_set_n_position(0b1100110, 0) == -1);
	assert(get_set_n_position(0b1100110, 4) == -1);
	assert(get_set_n_position(0b1110110, 4) == -1);
	assert(get_set_n_position(0b1110111, 4) == -1);
	assert(get_set_n_position(0b1111111, 4) == 0);
	assert(get_set_n_position(0b11110111, 4) == 4);
	return 0;
}

