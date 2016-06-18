

#include <cstdlib>
#include <iostream>
#include <cassert>
enum {
	STACK_SIZE = 100,
};

template <typename K>
class SimpleStack {
	K arr[STACK_SIZE];
	int top;

	public:
	SimpleStack() {
		top = 0;
	}

	void push(K x) {
		if(top == STACK_SIZE)
			//throw overflow_error("Stack is full");
			throw std::string("Stack is full");
		arr[top++] = x; 
	}

	K pop() throw(const std::string&) {
		if(top == 0)
			//throw new underflow_error("Stack is empty");
			throw std::string("Stack is empty");
		return arr[--top];
	}
};


template <typename K>
class array_queue {
	int head;
	int tail;
	int count;
	SimpleStack<K> enq;
	SimpleStack<K> dq;

	public:
	array_queue() {
		head = 0;
		tail = 0;
		count = 0;
	}

	void enqueue(K x) {
		enq.push(x);
	}

	K dequeue() {
		try {
			for(K y = enq.pop();;y = enq.pop()) {
				dq.push(y);
			}
		} catch(const std::string&emsg) {
			//std::cout << "no more in stack:" << emsg << std::endl;
		}
		return dq.pop();
	}
};

int main(int argc, char*argv[]) {
	array_queue<int> q;
	int i = 0;
	for(i = 0; i < STACK_SIZE; i++) {
		q.enqueue(i);
	}
	for(i = 0; i < STACK_SIZE; i++) {
		assert(i == q.dequeue());
	}
	std::cout << "successful" << std::endl;
	return 0;
}

