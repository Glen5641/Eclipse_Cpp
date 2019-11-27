/*
 * This stucture used to create a node for a Self Modifying
 * Binary Search Tree. I is neccessary for the linking of
 * leaves of the tree by introducing pointers to successor
 * nodes. Allowing for a tree like data structure.
 *
 *  Created on: Nov 20, 2017
 *      Author: cglen
 */

#ifndef TREENODE_H_
#define TREENODE_H_

#include <iostream>

using namespace std;

template<class I>
class TreeNode {
public:
	TreeNode();
	TreeNode(I info);
	TreeNode(const TreeNode<I> &node);
	~TreeNode();

	bool operator<(const TreeNode<I>* n) const;
	bool operator>(const TreeNode<I>* n) const;
	bool operator=(const TreeNode<I>* n) const;

	I info;
	TreeNode<I> *left;
	TreeNode<I> *right;
};

/*
 * CONSTUCTOR:
 * Creates a null node with all null values.
 */
template<class I>
TreeNode<I>::TreeNode() {
	this->info = 0;
	left = NULL;
	right = NULL;
	return;
}

/*
 * CONSTRUCTOR:
 * Creates a tree node with set info and
 * left and right pointers are set to NULL
 */
template<class I>
TreeNode<I>::TreeNode(I info) {
	this->info = info;
	left = NULL;
	right = NULL;
	return;
}

/*
 * COPY CONSTRUCTOR:
 * Copies the info, left, and right values
 * of one node into this node.
 */
template<class I>
TreeNode<I>::TreeNode(const TreeNode<I> &node) {
	info = node.info;
	left = node.left;
	right = node.right;
	return;
}

/*
 * DESTRUCTOR:
 * Destroys said node to clean up garbage.
 */
template<class I>
TreeNode<I>::~TreeNode() {
	left = NULL;
	right = NULL;
}

#endif /* TREENODE_H_ */
