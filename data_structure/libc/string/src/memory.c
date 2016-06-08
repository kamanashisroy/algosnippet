
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <inttypes.h>
#include <stdio.h>

inline void my_memcpy_16bit(uint16_t*dest, uint16_t*src, size_t n) {
	size_t i = n >> 1;
	while(i--) {
		*dest++ = *src++;
	}
	if(n & 0x1)
		*((uint8_t*)dest) = *((uint8_t*)src);
}

inline void my_memcpy_32bit(uint32_t*dest, uint32_t*src, size_t n) {
	size_t i = n >> 2;
	while(i--) {
		*dest++ = *src++;
	}
	my_memcpy_16bit((uint16_t*)dest, (uint16_t*)src, n & 0x3);
}

inline void my_memcpy_64bit(uint64_t*dest, uint64_t*src, size_t n) {
	size_t i = n >> 3;
	while(i--) {
		*dest++ = *src++;
	}
	my_memcpy_32bit((uint32_t*)dest, (uint32_t*)src, n & 0x7);
}

void*my_memcpy(void*dest, void*src, size_t n) {
	my_memcpy_64bit((uint64_t*)dest, (uint64_t*)src, n);
	return (void*)dest;
}

static uint8_t src_heap[1024];
static uint8_t dest_heap[1024];
int main(int argc, char*argv[]) {
	int i = 0, j = 0;
	memset(src_heap, 0, sizeof(src_heap));
	memset(dest_heap, 0, sizeof(dest_heap));
	for(i = 1; i < 1000; i++) {
		uint8_t*src = src_heap;
		uint8_t*dest = dest_heap;
		memset(src, 1, i);
		memset(dest, 0, i);
		memcpy(dest, src, i);
		for(j = 0; j < 1000; j++) {
			assert(dest[j] == src[j]);
		}
	}
	printf("Successful\n");
	return 0;
}
