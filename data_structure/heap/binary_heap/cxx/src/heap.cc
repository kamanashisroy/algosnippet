
#include <cstdlib>
#include <cassert>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <vector>

template <typename K>
class maxheap {
	public:
	std::vector<K> elem;
	maxheap() {
	}

	void heapify_bottom_up(const int index) {
		if(index == 0)
			return;
		const int x = elem[index];
		const int pindex = ((index+1) >> 1 ) - 1;
		const int parent = elem[pindex];
		if(parent < x) {
			elem[pindex] = x;
			elem[index] = parent;
			heapify_bottom_up(pindex);
		}
		
	}


	void heapify_top_down(const int index) {
		if(index >= elem.size())
			return;
		const int right_index = (index+1)<<1;
		const int left_index = right_index-1;

		// check the heap property
		if(elem[index] >= elem[right_index]) {
			if(elem[index] >= elem[left_index]) // the heap property holds true
				return;
			else {
				std::swap(elem[index], elem[left_index]);
				return heapify_top_down(left_index);
			}
		} else {
			std::swap(elem[index], elem[right_index]);
			return heapify_top_down(right_index);
		}
		return;
		
	}

	void push(K x) {
		elem.push_back(x);
		heapify_bottom_up(elem.size()-1);
	}

	K pop() {
		if(elem.size() == 0) {
			throw std::string("Underflow");
		}
		K root = elem.front();
		elem[0] = elem.back();
		elem.pop_back();
		if(elem.size() > 1) {
			heapify_top_down(0);
		}
		return root;
	}
};

template<typename KT>
std::ostream& operator<<(std::ostream& ostrm, const maxheap<KT>&given) {
    ostrm << "[maxheap:";
	for(const auto x : given.elem) {
		ostrm << x << ',';
	}
    ostrm << ']';
    return ostrm;
}

enum {
	HEAP_SIZE = 5,
};

int main(int argc, char*argv[]) {
	maxheap<int> hp;
	int i = 0;
	for(i = 0; i < HEAP_SIZE; i++) {
		hp.push(i);
	}
	//std::for_each(hp.elem.begin(),hp.elem.end(),[](int x){std::cout << x << std::endl;})
	i = HEAP_SIZE;
	while(--i) {
        std::cout << hp << std::endl;
		std::cout << i << " - " << hp.pop() << std::endl;
	}
	std::cout << "Successful" << std::endl;
	return 0;
}

