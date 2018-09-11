
#include <string.h>
#include <queue>
#include <iostream>
#include <cstdio>
#include <assert.h>

using namespace std;

template <typename K>
struct TrieNode {
	K x;
	TrieNode*children_head;
	TrieNode*next_sibling;

	TrieNode(K given) : x(given),children_head(NULL),next_sibling(NULL) { }

	int insert(const K*given, const int n, int index) {
		TrieNode*node = children_head;
		while(node) {
			if(node->x == given[index]) {
				if((index+1) < n)
					node->insert(given, n, index+1);
				return 0;
			}
			if(node->next_sibling)
				node = node->next_sibling;
			else
				break;
		}
		if(!node) {
			node = children_head = new TrieNode<K>(given[index]);
			if((index+1) < n)
				node->insert(given, n, index+1);
		} else {
			node->next_sibling = new TrieNode<K>(given[index]);
			if((index+1) < n)
				node->next_sibling->insert(given, n, index+1);
		}
		return 0;
	}

	int search(const K*given, const int n, int index) {
		TrieNode*node = children_head;
		while(node) {
			if(node->x == given[index]) {
				if((index+1) < n)
					return node->search(given, n, index+1);
				else
					return 0;
			}
			if(node->next_sibling)
				node = node->next_sibling;
			else
				break;
		}
		return -1;
	}

	~TrieNode() {
		if(children_head) delete children_head;
	}

};

template <typename K>
static int in_order_dump_cb(K x) {
	cout << x << ',';
	return 0;
}

static int read_input_and_build_tree_and_search(const int n) {
	TrieNode<char>*root = new TrieNode<char>('\0');
	string target;
	cin >> target;
	int i = n;
	while(i--) {
		string word;
		cin >> word;
		root->insert(word.c_str(), word.size(), 0);
	}
	if(!root->search(target.c_str(), target.size(), 0)) {
		cout << "found\n";
	} else {
		cout << "not found\n";
	}
	if(root)
		delete root;
	return 0;
}

int main(int argc, char*argv[]) {
	/* n is the number of nodes and k is the number of edges */
	int n; 
	cin >> n;
	read_input_and_build_tree_and_search(n);
	return 0;
}

