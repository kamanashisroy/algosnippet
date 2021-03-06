
#ifndef BTNODE_H
#define BTNODE_H
#include <string.h>
#include <queue>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <assert.h>

using namespace std;

/**
 * Binary tree node
 */
template <typename K>
class btnode {
	public:
	K x;
	btnode*right;
	btnode*left;
	btnode*parent;
	btnode*equals;
	btnode(K given);
	~btnode();
	bool check();
	int insert(btnode*node);
	// @brief it deletes the node from the tree and returns a new root of the tree if necessary
	btnode*remove(btnode*node);
	btnode*search(K given);
	btnode*search_iterative(K given);
	btnode*find_minimum();
	btnode*find_maximum();
	btnode*find_successor();
	btnode*find_predecessor();
	// TODO remove node
	// @brief prints tree in preorder
	void in_order(int (*cb)(K x));
	void in_order_recursive(int (*cb)(K x));
	void in_order_without_stack(int (*cb)(K x));
	// @brief serialize
	void serialize(stringstream&strm);
	// @brief deserialize
	void deserialize(stringstream&strm);
};

#endif // BTNODE_H
