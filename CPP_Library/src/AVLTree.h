#ifndef AVLTREE_H_
#define AVLTREE_H_

#include "BinaryTree.h"
#include "TreeNode.h"

template<class i>
class AVLTree {
public:

	AVLTree();
	AVLTree(const AVLTree &et);
	~AVLTree();
	void createTree(i info, int key);

	//Accessors
	int getSize() const;
	i find(int key) const;
	int traverseLeft() const;
	int traverseRight() const;
	void inOrderPrint(ostream& o);
	void preOrderPrint(ostream& o);
	void postOrderPrint(ostream& o);

	//Mutators
	void remove(int key);
	void insert(i info, int key);

private:

	int size;
	BinaryTree<i> *tree;
};

template<class i>
AVLTree<i>::AVLTree() {
	size = 0;
	tree = new BinaryTree<i>();
	return;
}

template<class i>
AVLTree<i>::AVLTree(const AVLTree &et) {
	size = et.size;
	tree = et.tree;
	return;
}

template<class i>
AVLTree<i>::~AVLTree() {
	size = 0;
	tree = new BinaryTree<i>();
	return;
}

template<class i>
void AVLTree<i>::createTree(i info, int key) {
	tree->createTree(info, key);
	size++;
	return;
}

template<class i>
int AVLTree<i>::getSize() const {
	return this->size;
}

template<class i>
i AVLTree<i>::find(int key) const {
	if (size == 0) {
		throw out_of_range("Tree Remove : Tree not created");
		return 0;
	}
	TreeNode<i,int> *p = tree->find(tree->getRoot(), key);
	if(p->getKey() != key){
		return 0;
	}
	return p->getInfo();
}

template<class i>
int AVLTree<i>::traverseLeft() const {
	if (size == 0) {
		throw out_of_range("Tree Remove : Tree not created");
		return 0;
	}
	return tree->traverseLeft(tree->getRoot())->getKey();
}

template<class i>
int AVLTree<i>::traverseRight() const {
	if (size == 0) {
		throw out_of_range("Tree Remove : Tree not created");
		return 0;
	}
	return tree->traverseRight(tree->getRoot())->getKey();
}

template<class i>
void AVLTree<i>::inOrderPrint(ostream& o) {
	if (size == 0) {
		throw out_of_range("Tree Remove : Tree not created");
		return;
	}
	tree->inOrderPrint(tree->getRoot(), o);
	return;
}

template<class i>
void AVLTree<i>::preOrderPrint(ostream& o) {
	if (size == 0) {
		throw out_of_range("Tree Remove : Tree not created");
		return;
	}
	tree->preOrderPrint(tree->getRoot(), o);
	return;
}

template<class i>
void AVLTree<i>::postOrderPrint(ostream& o) {
	if (size == 0) {
		throw out_of_range("Tree Remove : Tree not created");
		return;
	}
	tree->postOrderPrint(tree->getRoot(), o);
	return;
}

template<class i>
void AVLTree<i>::remove(int key) {
	if (size == 0) {
		throw out_of_range("Tree Remove : Tree not created");
		return;
	}

	TreeNode<i, int> *p = tree->getRoot();
	tree->remove(p, key);
	size--;

	return;
}

template<class i>
void AVLTree<i>::insert(i info, int key) {
	if (size == 0) {
		throw out_of_range("Tree Insert : Tree not created");
		return;
	}

	TreeNode<i, int>* p = tree->getRoot();
	tree->insert(NULL, p, info, key);

	size++;
	return;
}

#endif /* AVLTREE_H_ */
