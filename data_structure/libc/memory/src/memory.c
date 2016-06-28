
#include <unistd.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

enum {
	HEAP_SIZE = 1024,
	OCTATE_MASK_SIZE = (HEAP_SIZE + 63) >> 6, /* HEAP_SIZE/64, HEAP_SIZE/(2*2*2*2*2*2) */
	SUPER_OCTATE_MASK_SIZE = (OCTATE_MASK_SIZE + 7) >> 8,
};


static uint8_t chunk[HEAP_SIZE];
static uint64_t octate_mask[OCTATE_MASK_SIZE]; // suppose we have 64 bit processor
#if 0
static uint64_t super_octate_mask[SUPER_OCTATE_MASK_SIZE]; // suppose we have 64 bit processor

inline static void*get_super_octates(const size_t octate_count, const size_t fraction) {
	uint64_t so_mask = ~(1<<((octate_count >> 8)+1));
	int i = 0;
	for(i = 0; i < SUPER_OCTATE_MASK_SIZE; i++) {
		uint64_t mask = super_octate_mask[i];
		do {
			if((so_mask & (~mask)) == so_mask) {
				// found ..
				// check fraction
			}
		} while(0);
	}
}
#endif


static inline int get_set_n_position(uint64_t x, const uint8_t n) {
	if(!n) return -1;
	int i = n-1;
	while(x && i--) {
	    x = x & (x << 1);
	};
	if(!x) return -1;
	int pos = __builtin_ctzll(x);
	return pos - (n-1);
}


struct memory_info {
	uint8_t sz;
	uint8_t pos;
	uint16_t oct;
} __attribute__((__packed__));

void* my_malloc(size_t expected_size) {
	expected_size+=sizeof(struct memory_info);
	int i = 0;
	if(expected_size == 0 || expected_size > 63) // sanity check
		return NULL;
	for(i = 0; i < OCTATE_MASK_SIZE; i++) {
		int pos = get_set_n_position(~octate_mask[i], (uint8_t)expected_size);
		if(pos == -1)
			continue;
		uint64_t mask = (1LL<<expected_size);
		mask = (mask - 1) << pos;
		octate_mask[i] |= mask;
		struct memory_info*mem = (struct memory_info*)(chunk+(i<<6)+pos);
		mem->sz = expected_size;
		mem->pos = pos;
		mem->oct = i;
		assert(OCTATE_MASK_SIZE < ((1LL << 16)-1));
		return mem+1;
	}
	return NULL; // heap is full
}

void my_free(void*x) {
	struct memory_info*mem = (struct memory_info*)x;
	mem--;
	uint64_t mask = (1LL<< (mem->sz) );
	mask = (mask - 1) << (mem->pos);
	octate_mask[mem->oct] &= ~mask;
}

int my_memory_check_empty() {
	int i = 0;
	for(i = 0; i < OCTATE_MASK_SIZE; i++) {
		if(octate_mask[i]) {
			return -1;
		}
	}
	return 0;
}

int my_memory_static_init() {
	memset(octate_mask, 0, sizeof(octate_mask));
	//memset(super_octate_mask, 0, sizeof(super_octate_mask));
	return 0;
}

struct my_obj {
	int x;
	char str[32];
};

int main(int argc, char*argv[]) {
	my_memory_static_init();
	struct my_obj*obj = my_malloc(sizeof(struct my_obj));
	assert(obj);
	obj->x = 10;
	obj->str[0] = 'a';
	obj->str[1] = '\0';
	my_free(obj);
	obj = NULL;
	assert(my_memory_check_empty() == 0);
	return 0;
}
