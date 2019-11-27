/*
 * TreeNode.h
 *
 *  Created on: Nov 20, 2017
 *      Author: cglen
 */

#ifndef TREENODE_H_
#define TREENODE_H_

#include <iostream>

using namespace std;

template<class I, class K>
class TreeNode {
public:
	TreeNode(I info, K key);
	TreeNode(const TreeNode<I, K> &node);
	~TreeNode();

	//Accessors
	I getInfo() const;
	K getKey() const;
	TreeNode<I, K>* getPrev() const;
	TreeNode<I, K>* getLeft() const;
	TreeNode<I, K>* getRight() const;

	//Mutators
	void setInfo(I info);
	void setKey(K key);
	void setPrev(TreeNode<I, K> *node);
	void setLeft(TreeNode<I, K> *node);
	void setRight(TreeNode<I, K> *node);
	bool operator<(const TreeNode<I, K>* n) const;
	bool operator>(const TreeNode<I, K>* n) const;
	bool operator=(const TreeNode<I, K>* n) const;

private:
	I info;
	K key;
	TreeNode<I, K> *prev;
	TreeNode<I, K> *left;
	TreeNode<I, K> *right;

};

template<class I, class K>
TreeNode<I, K>::TreeNode(I info, K key) {
	this->info = info;
	this->key = key;
	prev = NULL;
	left = NULL;
	right = NULL;
	return;
}

template<class I, class K>
TreeNode<I, K>::TreeNode(const TreeNode<I, K> &node) {
	info = node.info;
	key = node.key;
	prev = node.prev;
	left = node.left;
	right = node.right;
	return;
}

template<class I, class K>
TreeNode<I, K>::~TreeNode() {
	prev = NULL;
	left = NULL;
	right = NULL;
}

template<class I, class K>
bool TreeNode<I, K>::operator<(const TreeNode<I, K> *n) const {
	if (this->getKey() > n->getKey()) {
		return true;
	}
	return false;
}

template<class I, class K>
bool TreeNode<I, K>::operator>(const TreeNode<I, K> *n) const {
	if (this->key > n->getKey()) {
		return true;
	}
	return false;
}

template<class I, class K>
bool TreeNode<I, K>::operator=(const TreeNode<I, K> *n) const {
	if (this->key == n->getKey()) {
		return true;
	}
	return false;
}

template<class I, class K>
ostream& operator<<(ostream& os, const TreeNode<I, K> *node) {
	os << node->getInfo();
	return os;
}

template<class I, class K>
I TreeNode<I, K>::getInfo() const {
	return this->info;
}

template<class I, class K>
K TreeNode<I, K>::getKey() const {
	return this->key;
}

template<class I, class K>
TreeNode<I, K>* TreeNode<I, K>::getPrev() const {
	return this->prev;
}

template<class I, class K>
TreeNode<I, K>* TreeNode<I, K>::getLeft() const {
	return this->left;
}

template<class I, class K>
TreeNode<I, K>* TreeNode<I, K>::getRight() const {
	return this->right;
}

template<class I, class K>
void TreeNode<I, K>::setInfo(I info) {
	this->info = info;
	return;
}

template<class I, class K>
void TreeNode<I, K>::setKey(K key) {
	this->key = key;
	return;
}

template<class I, class K>
void TreeNode<I, K>::setPrev(TreeNode<I, K>* node) {
	prev = node;
	return;
}

template<class I, class K>
void TreeNode<I, K>::setLeft(TreeNode<I, K>* node) {
	left = node;
	return;
}

template<class I, class K>
void TreeNode<I, K>::setRight(TreeNode<I, K>* node) {
	right = node;
	return;
}

#endif /* TREENODE_H_ */
