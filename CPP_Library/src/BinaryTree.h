/*
 * BinaryTree.h
 *
 *  Created on: Nov 20, 2017
 *      Author: cglen
 */

#ifndef BINARYTREE_H_
#define BINARYTREE_H_

#include <iostream>
using namespace std;
#include "TreeNode.h"

template<class i>
class BinaryTree {
public:
	BinaryTree();
	BinaryTree(const BinaryTree &tree);
	~BinaryTree();
	void createTree(i info, int key);

	//Accessors
	TreeNode<i, int>* getRoot() const;
	TreeNode<i, int>* find(TreeNode<i, int> *p, int key) const;
	TreeNode<i, int>* traverseLeft(TreeNode<i, int> *p) const;
	TreeNode<i, int>* traverseRight(TreeNode<i, int> *p) const;
	void inOrderPrint(TreeNode<i, int> *p, ostream& o);
	void preOrderPrint(TreeNode<i, int> *p, ostream& o);
	void postOrderPrint(TreeNode<i, int> *p, ostream& o);

	//Mutators
	void remove(TreeNode<i, int> *&p, int key);
	void insert(TreeNode<i, int> *prev, TreeNode<i, int> *&p, i info, int key);

	void rotateLeftOnce(TreeNode<i, int>* node);
	void rotateLeftTwice(TreeNode<i, int>* node);
	void rotateRightOnce(TreeNode<i, int>* node);
	void rotateRightTwice(TreeNode<i, int>* node);
	int height(TreeNode<i, int> *node);

private:

	TreeNode<i, int> *root;
};

template<class i>
BinaryTree<i>::BinaryTree() {
	root = 0;
	return;
}

template<class i>
BinaryTree<i>::BinaryTree(const BinaryTree &tree) {
	root = tree.root;
	return;
}

template<class i>
BinaryTree<i>::~BinaryTree() {
	root = 0;
	return;
}

template<class i>
void BinaryTree<i>::createTree(i info, int key) {
	root = new TreeNode<i, int>(info, key);
	return;
}

template<class i>
TreeNode<i, int>* BinaryTree<i>::getRoot() const {
	return root;
}

template<class i>
TreeNode<i, int>* BinaryTree<i>::find(TreeNode<i, int> *p, int key) const {
	if (p->getKey() < key) {
		if (p->getRight() == NULL) {
			return p;
		}
		p = find(p->getRight(), key);
	}
	if (p->getKey() > key) {
		if (p->getLeft() == NULL) {
			return p;
		}
		p = find(p->getLeft(), key);
	}
	return p;
}

template<class i>
TreeNode<i, int>* BinaryTree<i>::traverseLeft(TreeNode<i, int> *p) const {
	if (p->getLeft() != 0) {
		p = traverseLeft(p->getLeft());
	}
	return p;
}

template<class i>
TreeNode<i, int>* BinaryTree<i>::traverseRight(TreeNode<i, int> *p) const {
	if (p->getRight() != 0) {
		p = traverseRight(p->getRight());
	}
	return p;
}

template<class i>
void BinaryTree<i>::insert(TreeNode<i, int> *prev, TreeNode<i, int> *&p, i info,
		int key) {

	if (p == 0) {
		p = new TreeNode<i, int>(info, key);
		p->setPrev(prev);
		if (key < p->getPrev()->getKey()) {
			p->getPrev()->setLeft(p);
		}
		if (key > p->getPrev()->getKey()) {
			p->getPrev()->setRight(p);
		}
		return;
	} else if (key < p->getKey()) {
		prev = p;
		p = p->getLeft();
		insert(prev, p, info, key);
		if (height(p->getLeft()) - height(p->getRight()) == 2) {
			if (key < p->getLeft()->getKey())
				rotateLeftOnce(p);
			else
				rotateLeftTwice(p);
		}
	} else if (key > p->getKey()) {
		prev = p;
		p = p->getRight();
		insert(prev, p, info, key);
		if (height(p->getRight()) - height(p->getLeft()) == 2) {
			if (key > p->getRight()->getKey())
				rotateRightOnce(p);
			else
				rotateRightTwice(p);
		}
	} else {
		return;
	}

	return;
}

template<class i>
void BinaryTree<i>::remove(TreeNode<i, int> *&p, int key) {
	TreeNode<i, int> *par = p->getPrev();
	TreeNode<i, int> *q = 0;

	while (p != 0) {
		if (p->getKey() == key) {
			if (p->getLeft() == 0 && p->getRight() == 0) {
				if (par == 0) {
					root = 0;
				} else if (par->getLeft() == p) {
					par->setLeft(0);
				} else {
					par->setRight(0);
				}
			} else if (p->getLeft() != 0 && p->getRight() == 0) {
				if (p->getPrev() == 0) {
					root = p->getLeft();
				} else if (par->getLeft() == p) {
					par->setLeft(p->getLeft());
				} else {
					par->setRight(p->getLeft());
				}
			} else if (p->getLeft() == 0 && p->getRight() != 0) {
				if (par == 0) {
					root = p->getRight();
				} else if (par->getLeft() == p) {
					par->setLeft(p->getRight());
				} else {
					par->setRight(p->getRight());
				}
			} else {
				q = p->getRight();
				while (q->getLeft() != 0) {
					q = q->getLeft();
				}
				p->setInfo(q->getInfo());
				p->setKey(q->getKey());
				p = p->getRight();
				if (height(p->getRight()) - height(p->getLeft()) == 2) {
					if (key > p->getRight()->getKey())
						rotateRightOnce(p);
					else
						rotateRightTwice(p);
				}
				if (height(p->getLeft()) - height(p->getRight()) == 2) {
					if (key < p->getLeft()->getKey())
						rotateLeftOnce(p);
					else
						rotateLeftTwice(p);
				}
				remove(p, q->getKey());
				return;
			}
		} else if (p->getKey() < key) {
			par = p;
			p = p->getRight();
			remove(p, key);
		} else {
			par = p;
			p = p->getLeft();
			remove(p, key);
		}

		return;
	}
}

template<class i>
void BinaryTree<i>::inOrderPrint(TreeNode<i, int> *p, ostream& o) {
	if (p == 0) {
		return;
	}
	inOrderPrint(p->getLeft(), o);
	o << p->getInfo() << " ";
	inOrderPrint(p->getRight(), o);
	return;
}

template<class i>
void BinaryTree<i>::preOrderPrint(TreeNode<i, int> *p, ostream& o) {
	if (p == 0) {
		return;
	}
	o << p->getInfo() << " ";
	preOrderPrint(p->getLeft(), o);
	preOrderPrint(p->getRight(), o);
	return;
}

template<class i>
void BinaryTree<i>::postOrderPrint(TreeNode<i, int> *p, ostream& o) {
	if (p == 0) {
		return;
	}
	postOrderPrint(p->getLeft(), o);
	postOrderPrint(p->getRight(), o);
	o << p->getInfo() << " ";
	return;
}

template<class i>
void BinaryTree<i>::rotateLeftOnce(TreeNode<i, int>* node) {
	TreeNode<i, int> *p;

	p = node->getLeft();
	node->setLeft(p->getRight());
	p->setRight(node);
	node = p;
}

template<class i>
void BinaryTree<i>::rotateRightOnce(TreeNode<i, int>* node) {
	TreeNode<i, int> *p;

	p = node->getRight();
	node->setRight(p->getLeft());
	p->setLeft(node);
	node = p;
}

template<class i>
void BinaryTree<i>::rotateLeftTwice(TreeNode<i, int>* node) {
	rotateRightOnce(node->getLeft());
	rotateLeftOnce(node);
}

template<class i>
void BinaryTree<i>::rotateRightTwice(TreeNode<i, int>* node) {
	rotateLeftOnce(node->getRight());
	rotateRightOnce(node);
}

template<class i>
int BinaryTree<i>::height(TreeNode<i, int> *node) {
	if (node == 0) {
		return 0;
	}

	int left = height(node->getLeft());
	int right = height(node->getRight());
	if (left > right)
		return left + 1;
	else
		return right + 1;
}

#endif /* BINARYTREE_H_ */
