
#include <cstdlib>
#include <cassert>
#include <exception>
#include <stdexcept>
#include <iostream>

enum {
	STACK_SIZE = 100,
};

template <typename K>
class DoubleStack {
	K arr[STACK_SIZE];
	int top;
	int bottom;

	public:
	DoubleStack() {
		top = 0;
		bottom = STACK_SIZE-1;
	}

	void pushA(K x) throw(const std::string&) {
		if(top == STACK_SIZE || top > bottom)
			throw "Stack is full";
		arr[top++] = x; 
	}

	void pushB(K x) throw(const std::string&) {
		if(top == STACK_SIZE || top > bottom || bottom == -1)
			throw "Bottom Stack is full";
		arr[bottom--] = x; 
	}


	K popA() throw(const std::string&) {
		if(top == 0)
			throw "Stack is empty";
		return arr[--top];
	}

	K popB() throw(const std::string&) {
		if(bottom >= (STACK_SIZE-1))
			throw "Bottom stack is empty";
		return arr[++bottom];
	}
};

int main(int argc, char*argv[]) {
	DoubleStack<int> stack;
	int i = 0;
	try {
		for(i = 0; i < STACK_SIZE; i++) {
			if((i & 1) == 1)
				stack.pushA(i);
			else
				stack.pushB(i);
		}
		i = STACK_SIZE;
		while(--i) {
			if((i & 1) == 1)
				assert(i == stack.popA());
			else
				assert(i == stack.popB());
		}
		std::cout << "Successful" << std::endl;
	} catch(const std::string& msg) {
		std::cout << "Failed:" << msg << std::endl;
	}
	return 0;
}

