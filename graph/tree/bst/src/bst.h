
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
	int insert(btnode*node);
	btnode*search(K given);
	btnode*search_iterative(K given);
	btnode*find_minimum();
	btnode*find_maximum();
	btnode*find_successor();
	btnode*find_predecessor();
	// TODO remove node
	// @brief prints tree in preorder
	void in_order(int (*cb)(K x));
	// @brief serialize
	void serialize(stringstream&strm);
	// @brief deserialize
	void deserialize(stringstream&strm);
};

#endif // BTNODE_H
