/*
 * AVLTree.h
 *
 * This class creates a templated Binary Search
 * Tree that modifies itself as objects are inserted
 * into it. This allows for fastest retreival of information.
 *
 *  Created on: Dec 1, 2017
 *      Author: Clayton Glenn
 *      Source: http://www.sanfoundry.com/cpp-program-implement-avl-trees/
 *      Source: Provided structure for the class, but templation was introduced
 */

#ifndef AVLTREE_H_
#define AVLTREE_H_

#include "ResizableArray.h"
#include "DoublyLinkedList.h"
#include "TreeNode.h"

template<class i>
class AVLTree {
public:
	AVLTree();
	AVLTree(const AVLTree<i> &tree);
	~AVLTree();

	//ACCESSORS
	int getSize() const;
	DoublyLinkedList<i>* getList();
	ResizableArray<i>* getArray();
	i find(i info);

	//MUTATORS
	void insert(i value, ostream &o);
	void del(i item);

	//PRINTERS
	void preorder(ostream &o);
	void inorder(ostream &o);
	void postorder(ostream &o);

private:
	DoublyLinkedList<i>* getList(TreeNode<i>* ptr, DoublyLinkedList<i>* ll);
	ResizableArray<i>* getArray(TreeNode<i>* ptr, ResizableArray<i>* a);
	void find(i item, TreeNode<i> **par, TreeNode<i> **loc);
	TreeNode<i>* insert(TreeNode<i> *root, i value, ostream &o);
	void del_a(TreeNode<i> *par, TreeNode<i> *loc);
	void del_b(TreeNode<i> *par, TreeNode<i> *loc);
	void del_c(TreeNode<i> *par, TreeNode<i> *loc);
	void preorder(TreeNode<i> *ptr, ostream &o);
	void inorder(TreeNode<i> *ptr, ostream &o);
	void postorder(TreeNode<i> *ptr, ostream &o);
	int height(TreeNode<i> *temp);
	int diff(TreeNode<i> *temp);
	TreeNode<i>* rr_rotation(TreeNode<i> *par);
	TreeNode<i>* ll_rotation(TreeNode<i> *par);
	TreeNode<i>* lr_rotation(TreeNode<i> *par);
	TreeNode<i>* rl_rotation(TreeNode<i> *par);
	TreeNode<i>* balance(TreeNode<i> *temp);

	TreeNode<i> *root;
	int size;
};

/**
 * CONSTRUCTOR:
 * Creates a null avl tree
 */
template<class i>
AVLTree<i>::AVLTree() {

	//Set to null
	root = NULL;
	size = 0;
}

/**
 * COPY CONSTRUCTOR:
 * Copies the root and size from one tree to this one
 */
template<class i>
AVLTree<i>::AVLTree(const AVLTree<i> &tree) {

	//Copy all elements
	root = tree.root;
	size = tree.size;
}

/**
 * DESTRUCTOR:
 * Destroys the avltree
 */
template<class i>
AVLTree<i>::~AVLTree() {

	//break the tree from the object
	root = NULL;
	size = 0;
}

/**
 * GET SIZE:
 * Returns the size of the avl tree
 */
template<class i>
int AVLTree<i>::getSize() const {

	//Return size
	return size;
}

/**
 * GET LIST:
 * Primes the recursive get list and catches exceptions
 */
template<class i>
DoublyLinkedList<i>* AVLTree<i>::getList() {

	//Create new list and prime getlist
	DoublyLinkedList<i>* ll = new DoublyLinkedList<i>();
	try {
		ll = getList(root, ll);
	} catch (out_of_range &except) {
		ll = new DoublyLinkedList<i>();
	}
	return ll;
}

/**
 * PRIMED RECURSIVE GET LIST:
 * returns a linked list of the avl tree elements
 * Follows same path as in order printing
 */
template<class i>
DoublyLinkedList<i>* AVLTree<i>::getList(TreeNode<i>* ptr,
		DoublyLinkedList<i>* ll) {

	//If root is null then tree is not created
	if (root == NULL) {
		throw out_of_range("Tree not created");
		return ll;
	}

	//recurse until pointer equals null.
	if (ptr != NULL) {

		//get all left elements of the branch
		ll = getList(ptr->left, ll);

		//Add to linked list
		if (ll->count() == 0) {
			ll->create_list(ptr->info);
		} else {
			ll->add_end(ptr->info);
		}

		//Get all right elements of the branch
		ll = getList(ptr->right, ll);
	}
	return ll;
}

/**
 * GET ARRAY:
 * Primes the recursive get array and catches exceptions
 */
template<class i>
ResizableArray<i>* AVLTree<i>::getArray() {

	//Create an array for return
	ResizableArray<i> *a = new ResizableArray<i>();

	//Add elements to array by primed GetArray
	try {
		a = getArray(root, a);
	} catch (out_of_range &except) {
		a = new ResizableArray<i>();
	}
	return a;
}

/**
 * PRIMED RECURSIVE GET ARRAY:
 * Returns a resizable array with the tree's elements
 * Follows same path as in order printing
 */
template<class i>
ResizableArray<i>* AVLTree<i>::getArray(TreeNode<i>* ptr,
		ResizableArray<i> *a) {

	//If root is null, then no tree is there
	if (root == NULL) {
		return a;
	}

	//Recurse until pointer is null
	if (ptr != NULL) {

		//Recurse the left branch of the tree
		a = getArray(ptr->left, a);

		//Add the element to the array
		a->add(ptr->info);

		//Recurse the right branch of the tree
		a = getArray(ptr->right, a);
	}
	return a;
}

/**
 * FIND:
 * Primes find and catches exceptions
 */
template<class i>
i AVLTree<i>::find(i info) {

	//Set both pointers to the root of tree
	TreeNode<i> *loc = root;
	TreeNode<i> *par = root;

	//Prime and get node by reference with FIND
	try {
		find(info, &par, &loc);
	} catch (out_of_range &except) {
		throw out_of_range("Object not found");
		loc = NULL;
		return loc->info;
	}
	return loc->info;

}

/**
 * PRIMED FIND:
 * Finds a certain node that matches the
 * templated variable and returns it by pointer
 */
template<class i>
void AVLTree<i>::find(i item, TreeNode<i> **par, TreeNode<i> **loc) {

	//Declare helper pointers
	TreeNode<i> *ptr, *temp;

	//If root is null, then tree not created
	if (root == NULL) {
		throw out_of_range("Tree Not Created");
		*loc = NULL;
		*par = NULL;
		return;
	}

	//If object is found, return the loc
	if (*item == *root->info) {
		*loc = root;
		*par = NULL;
		return;
	}

	//If item is less, branch to the left
	if (*item < *root->info) {
		ptr = root->left;
	} else {
		//If item is more, branch to the right
		ptr = root->right;
	}
	temp = root;

	//While item ! match, branch conditionally
	while (ptr != NULL) {
		if (*item == *ptr->info) {
			*loc = ptr;
			*par = temp;
			return;
		}
		temp = ptr;
		if (*item < *ptr->info) {
			ptr = ptr->left;
		} else {
			ptr = ptr->right;
		}
	}

	//If item not found, return null
	*loc = NULL;
	*par = temp;
	return;
}

/*
 * INSERT:
 * Primes the recursive insert and catches exceptions
 */
template<class i>
void AVLTree<i>::insert(i value, ostream &o) {

	//Set loc as root for priming
	TreeNode<i> *loc = root;

	//call the primed insert and assign a new root if tree rotates
	root = insert(loc, value, o);
	return;
}

/**
 * PRIMED RECURSIVE INSERT:
 * Inserts an element binarily and returns the new root if tree is rebalanced
 */
template<class i>
TreeNode<i>* AVLTree<i>::insert(TreeNode<i> *root, i value, ostream &o) {

	//If root is null, create a root
	if (root == NULL) {
		root = new TreeNode<i>(value);
		root->left = NULL;
		root->right = NULL;
		size++;
		return root;
	} else if (*value < *root->info) { //If object is less than, recurse left
		root->left = insert(root->left, value, o);
		root = balance(root);
	} else if (*value > *root->info) { //If object is more than, recurse Right
		root->right = insert(root->right, value, o);
		root = balance(root);
	} else { //If object already found, replace the info of the node with the object
		root->info = value;
	}
	return root;
}

/*
 * DELETE:
 * Deletes a specified element in the tree.
 *
 */
template<class i>
void AVLTree<i>::del(i item) {

	//Set par and loc to root
	TreeNode<i> *par = root, *loc = root;

	//If root is null, tree needs created
	if (root == NULL) {
		throw out_of_range("Tree not created");
		return;
	}

	//Find the right node for deletion
	find(item, &par, &loc);

	//If the item is not found return
	if (loc == NULL) {
		throw out_of_range("Object not found");
		return;
	}

	//Branch to del_a if loc is root
	if (loc->left == NULL && loc->right == NULL) {
		del_a(par, loc);
	}

	//Branch to del_b if loc has one successor
	if (loc->left != NULL && loc->right == NULL) {
		del_b(par, loc);
	}
	if (loc->left == NULL && loc->right != NULL) {
		del_b(par, loc);
	}

	//Branch to del_c if loc has both successors
	if (loc->left != NULL && loc->right != NULL) {
		del_c(par, loc);
	}

	//Delete location and decrement size
	free(loc);
	size--;
}

/*
 * CASE A DELETION: !LEFT & !RIGHT
 * Delete the tallest element in the tree
 */
template<class i>
void AVLTree<i>::del_a(TreeNode<i> *par, TreeNode<i> *loc) {

	//If par is null then set root to null
	if (par == NULL) {
		root = NULL;
	} else {
		//If not, then node is at bottom of list
		//Detach node
		if (loc == par->left)
			par->left = NULL;
		else
			par->right = NULL;
	}
}

/*
 * CASE B DELETION: (!LEFT & RIGHT) OR (LEFT & !RIGHT)
 * Deletes the element and reconnects the tree
 *
 */
template<class i>
void AVLTree<i>::del_b(TreeNode<i> *par, TreeNode<i> *loc) {
	TreeNode<i> *child;

	//If left is not null store it
	if (loc->left != NULL) {
		child = loc->left;
	} else {		//If right is not null store it
		child = loc->right;
	}

	//If par is root, child is now root
	if (par == NULL) {
		root = child;
	} else { //If not, then detach location and set par->child to node->child
		if (loc == par->left)
			par->left = child;
		else
			par->right = child;
	}
}

/*
 * CASE C DELETION: LEFT & RIGHT
 * deletes the element and recurses
 * through until case b or case a are reached
 */
template<class i>
void AVLTree<i>::del_c(TreeNode<i> *par, TreeNode<i> *loc) {
	TreeNode<i> *ptr, *temp, *suc, *parsuc;

	temp = loc;

	//Point to next highest node
	ptr = loc->right;
	while (ptr->left != NULL) {
		temp = ptr;
		ptr = ptr->left;
	}

	//Set successor as the ptr
	suc = ptr;
	parsuc = temp;
	//If successor is at bottom, delete it
	if (suc->left == NULL && suc->right == NULL)
		del_a(parsuc, suc);
	else
		//if not, break it and delete it
		del_b(parsuc, suc);
	if (par == NULL) { // if loc is root, root is next highest
		root = suc;
	} else {
		//set suc as parents child
		if (loc == par->left)
			par->left = suc;
		else
			par->right = suc;
	}
	//restucture succesor as location
	suc->left = loc->left;
	suc->right = loc->right;
}

/*
 * PREORDER:
 * Primes the recursive pre order function
 */
template<class i>
void AVLTree<i>::preorder(ostream &o) {

	//Prime preorder print
	preorder(root, o);
	return;
}

/*
 * PRIMED RECURSIVE PREORDER:
 * Prints pre order to the specified
 * out stream. Prints Node, left, right
 */
template<class i>
void AVLTree<i>::preorder(TreeNode<i> *ptr, ostream &o) {

	//If tree is null, return
	if (root == NULL) {
		cout << "Tree is empty" << endl;
		return;
	}

	//Recurse until all object printed in tree
	if (ptr != NULL) {
		o << ptr->info;
		preorder(ptr->left, o);
		preorder(ptr->right, o);
	}
}

/*
 * INORDER:
 * Primes the recursive in order function
 */
template<class i>
void AVLTree<i>::inorder(ostream &o) {

	//Prime inorder print
	inorder(root, o);
	return;
}

/*
 * PRIMED RECURSIVE INORDER:
 * Prints in order to the specified
 * out stream. Prints left, Node, right
 */
template<class i>
void AVLTree<i>::inorder(TreeNode<i> *ptr, ostream &o) {

	//If tree is null, return
	if (root == NULL) {
		cout << "Tree is empty" << endl;
		return;
	}

	//Recurse until all object printed in tree
	if (ptr != NULL) {
		inorder(ptr->left, o);
		o << ptr->info;
		inorder(ptr->right, o);
	}
}

/*
 * POSTORDER:
 * Primes the recursive post order function
 */
template<class i>
void AVLTree<i>::postorder(ostream &o) {

	//Prime postorder print
	postorder(root, o);
	return;
}

/*
 * PRIMED RECURSIVE POSTORDER:
 * Prints post order to the specified
 * out stream. Prints left, right, Node
 */
template<class i>
void AVLTree<i>::postorder(TreeNode<i> *ptr, ostream &o) {

	//If tree is null, return
	if (root == NULL) {
		cout << "Tree is empty" << endl;
		return;
	}

	//Recurse until all object printed in tree
	if (ptr != NULL) {
		postorder(ptr->left, o);
		postorder(ptr->right, o);
		o << ptr->info;
	}
}

/*
 * PRIMED RECURSIVE HEIGHT:
 * Function used to find the highest branch of the tree
 */
template<class i>
int AVLTree<i>::height(TreeNode<i> *temp) {
	int h = 0;
	if (temp != NULL) {
		//Find left branch height
		int l_height = height(temp->left);
		//Find right branch height
		int r_height = height(temp->right);

		//Find max between the two
		int max_height;
		if (l_height >= r_height) {
			max_height = l_height;
		} else {
			max_height = r_height;
		}

		//Add one to max and return
		h = max_height + 1;
	}
	return h;
}

/*
 * PRIMED HEIGHT RECURSOR DIFF:
 * This function finds the most populated side of the tree
 */
template<class i>
int AVLTree<i>::diff(TreeNode<i> *temp) {

	//Check the height of both sides of
	//the trees and return the difference
	int l_height = height(temp->left);
	int r_height = height(temp->right);
	int b_factor = l_height - r_height;

	return b_factor;
}

/*
 * RR_ROTATION:
 * This function rotates the par->right
 */
template<class i>
TreeNode<i>* AVLTree<i>::rr_rotation(TreeNode<i> *par) {
	TreeNode<i> *temp;
	temp = par->right;
	par->right = temp->left;
	temp->left = par;
	return temp;
}

/*
 * LL_ROTATION:
 * This function rotates the par->left
 */
template<class i>
TreeNode<i>* AVLTree<i>::ll_rotation(TreeNode<i> *par) {
	TreeNode<i> *temp;
	temp = par->left;
	par->left = temp->right;
	temp->right = par;
	return temp;
}

/*
 * LR_ROTATION:
 * This function rotates par->Right then par->left
 */
template<class i>
TreeNode<i>* AVLTree<i>::lr_rotation(TreeNode<i> *par) {
	TreeNode<i> *temp;
	temp = par->left;
	par->left = rr_rotation(temp);
	return ll_rotation(par);
}

/*
 * RL_ROTATION:
 * This function rotates par->left and then par->right
 */
template<class i>
TreeNode<i>* AVLTree<i>::rl_rotation(TreeNode<i> *par) {
	TreeNode<i> *temp;
	temp = par->right;
	par->right = ll_rotation(temp);
	return rr_rotation(par);
}

/*
 * BALANCE:
 * This function checks if tree is balanced,
 * if not, it rotates the nodes accordingly
 */
template<class i>
TreeNode<i>* AVLTree<i>::balance(TreeNode<i> *temp) {
	int bal_factor = diff(temp);

	//If left is more
	if (bal_factor > 1) {
		//Check left branch
		if (diff(temp->left) > 0) {
			//Rotate left to left
			temp = ll_rotation(temp);
		} else { //Rotate left right
			temp = lr_rotation(temp);
		}
	} else if (bal_factor < -1) { //If right is more
		if (diff(temp->right) > 0) {
			//Rotate right to left
			temp = rl_rotation(temp);
		} else {
			//Rotate right to right
			temp = rr_rotation(temp);
		}
	}

	//Return the rotated node
	return temp;
}

#endif /* AVLTREE_H_ */
