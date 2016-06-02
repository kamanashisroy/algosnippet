
#include <cstdlib>
#include <cassert>
#include <exception>
#include <stdexcept>
#include <iostream>

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
			throw "Stack is full";
		arr[top++] = x; 
	}

	K pop() {
		if(top == 0)
			//throw new underflow_error("Stack is empty");
			throw "Stack is empty";
		return arr[--top];
	}
};

int main(int argc, char*argv[]) {
	SimpleStack<int> stack;
	int i = 0;
	for(i = 0; i < STACK_SIZE; i++) {
		stack.push(i);
	}
	i = STACK_SIZE;
	while(--i) {
		assert(i == stack.pop());
	}
	std::cout << "Successful" << std::endl;
	return 0;
}

