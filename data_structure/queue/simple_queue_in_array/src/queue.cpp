

#include <cstdlib>
#include <iostream>
#include <cassert>

enum {
	QUEUE_SIZE = 100,
};

template <typename K>
class array_queue {
	int head;
	int tail;
	K array[QUEUE_SIZE];
	int count;

	public:
	array_queue() {
		head = 0;
		tail = 0;
		count = 0;
	}

	void enqueue(K x) {
		if(count == QUEUE_SIZE)
			throw "Overflow error";
		if(tail == QUEUE_SIZE)
			tail = 0;

		count++;
		array[tail++] = x;
	}

	K dequeue() {
		if(!count)
			throw "Underflow error";
		if(head == QUEUE_SIZE)
			head = 0;
		count--;
		return array[head++];
	}
};

int main(int argc, char*argv[]) {
	array_queue<int> q;
	int i = 0;
	for(i = 0; i < QUEUE_SIZE; i++) {
		q.enqueue(i);
	}
	for(i = 0; i < QUEUE_SIZE; i++) {
		assert(i == q.dequeue());
	}
	std::cout << "successful" << std::endl;
	return 0;
}

