
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <inttypes.h>
#include <stdio.h>

inline void my_memmove_16bit_re(uint16_t*destend, uint16_t*srcend, size_t n) {
	size_t i = n >> 1;
	while(i--) {
		*destend-- = *srcend--;
	}
	if(n & 0x1)
		*((uint8_t*)destend) = *((uint8_t*)srcend);
}

inline void my_memmove_32bit_re(uint32_t*destend, uint32_t*srcend, size_t n) {
	size_t i = n >> 2;
	while(i--) {
		*destend-- = *srcend--;
	}
	my_memmove_16bit_re((uint16_t*)destend, (uint16_t*)srcend, n & 0x3);
}

inline void my_memmove_64bit_re(uint64_t*destend, uint64_t*srcend, size_t n) {
	size_t i = n >> 3;
	while(i--) {
		*destend-- = *srcend--;
	}
	my_memmove_32bit_re((uint32_t*)destend, (uint32_t*)srcend, n & 0x7);
}

inline void my_memmove_16bit(uint16_t*dest, uint16_t*src, size_t n) {
	size_t i = n >> 1;
	while(i--) {
		*dest++ = *src++;
	}
	if(n & 0x1)
		*((uint8_t*)dest) = *((uint8_t*)src);
}

inline void my_memmove_32bit(uint32_t*dest, uint32_t*src, size_t n) {
	size_t i = n >> 2;
	while(i--) {
		*dest++ = *src++;
	}
	my_memmove_16bit((uint16_t*)dest, (uint16_t*)src, n & 0x3);
}

inline void my_memmove_64bit(uint64_t*dest, uint64_t*src, size_t n) {
	size_t i = n >> 3;
	while(i--) {
		*dest++ = *src++;
	}
	my_memmove_32bit((uint32_t*)dest, (uint32_t*)src, n & 0x7);
}

void*my_memmove(void*dest, void*src, size_t n) {
	const uint8_t*destst = (uint8_t*)dest;
	const uint8_t*destend = destst+n;
	const uint8_t*srcst = (uint8_t*)src;
	const uint8_t*srcend = srcst+n;
	if(destst < srcst && destend > srcst) { // we have overlap
		const int diff = srcst - destst;
		if(diff >= 8) {
			my_memmove_64bit((uint64_t*)dest, (uint64_t*)src, n);
		} else if(diff >= 4) {
			my_memmove_32bit((uint32_t*)dest, (uint32_t*)src, n);
		} else if(diff >= 2) {
			my_memmove_32bit((uint32_t*)dest, (uint32_t*)src, n);
		} else {
			int i = n;
			uint8_t*mydest = (uint8_t*)dest;
			uint8_t*mysrc = (uint8_t*)src;
			while(i--) {
				*mydest++ = *mysrc++;
			}
		}
		return dest;
	} else if(destst > srcst && destst < srcend) {
		const int diff = destst - srcend;
		if(diff >= 8) {
			my_memmove_64bit_re((uint64_t*)destend, (uint64_t*)srcend, n);
		} else if(diff >= 4) {
			my_memmove_32bit_re((uint32_t*)destend, (uint32_t*)srcend, n);
		} else if(diff >= 2) {
			my_memmove_32bit_re((uint32_t*)destend, (uint32_t*)srcend, n);
		} else {
			int i = n;
			uint8_t*mydest = (uint8_t*)destend;
			uint8_t*mysrc = (uint8_t*)srcend;
			while(i--) {
				*mydest-- = *mysrc--;
			}
		}
		return dest;

	} else {
		my_memmove_64bit((uint64_t*)dest, (uint64_t*)src, n);
	}
	return dest;
}

static uint8_t heap[4098];
int main(int argc, char*argv[]) {
	int i = 0, j = 0;
	for(i = 1; i < 1000; i++) {
		memset(heap, 0, sizeof(heap));
		uint8_t*src = heap;
		memset(src, 1, i);
		uint8_t*dest = heap+i;
		memmove(dest, src, i);
		for(j = 0; j < i; j++) {
			assert(dest[j] == src[j]);
		}
	}
	printf("Successful\n");
	return 0;
}
