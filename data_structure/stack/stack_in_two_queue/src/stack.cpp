
#include <cstdlib>
#include <cassert>
#include <exception>
#include <stdexcept>
#include <iostream>

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

	bool has_more() {
		return count != 0;
	}
};


template <typename K>
class stack_in_queue {
	array_queue<K> one;
	array_queue<K> another;

	public:
	stack_in_queue() {
	}

	void push(K x) {
		if(one.has_more()) {
			one.enqueue(x);
		} else {
			another.enqueue(x);
		}
	}

	K pop() {
		if(one.has_more()) {
			do {
				K x = one.dequeue();
				if(one.has_more())
					another.enqueue(x);
				else
					return x;
			} while(1);
		} else {
			do {
				K x = another.dequeue();
				if(another.has_more())
					one.enqueue(x);
				else
					return x;
			} while(1);
		}
		throw "Underflow error";
	}
};

int main(int argc, char*argv[]) {
	stack_in_queue<int> stack;
	int i = 0;
	for(i = 0; i < QUEUE_SIZE; i++) {
		stack.push(i);
	}
	i = QUEUE_SIZE;
	while(--i) {
		assert(i == stack.pop());
	}
	std::cout << "Successful" << std::endl;
	return 0;
}

