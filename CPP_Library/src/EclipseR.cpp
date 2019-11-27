#include <iostream>
using namespace std;
#include "AVLTree.h"
#include "BinaryTree.h"
#include "TreeNode.h"

int main() {

	cout << "Testing Construction : ";
	AVLTree<int> *tree = new AVLTree<int>();
	cout << "Complete" << endl;

	cout << "Testing Tree Creation : ";
	tree->createTree(5, 5);
	cout << "Complete" << endl;

	cout << "Testing Insertion : ";
	tree->insert(9, 9);
	tree->insert(7, 7);
	tree->insert(10, 10);
	tree->insert(6, 6);
	tree->insert(3, 3);
	tree->insert(2, 2);
	tree->insert(4, 4);
	tree->insert(1, 1);
	tree->insert(8, 8);
	tree->inOrderPrint(cout);
	cout << endl;

	cout << "Testing Size : ";
	cout << tree->getSize() << endl;

	cout << "Testing Left Traversion : ";
	cout << tree->traverseLeft() << endl;

	cout << "Testing Right Traversion : ";
	cout << tree->traverseRight() << endl;

	cout << "Testing In Order Printing : ";
	tree->inOrderPrint(cout);
	cout << endl;

	cout << "Testing Pre Order Printing : ";
	tree->preOrderPrint(cout);
	cout << endl;

	cout << "Testing Post Order Printing : ";
	tree->postOrderPrint(cout);
	cout << endl;

	cout << "Testing Removal : ";
	tree->remove(2);
	tree->remove(6);
	tree->remove(8);
	tree->inOrderPrint(cout);
	cout << endl;

	cout << "Testing Size : ";
	cout << tree->getSize() << endl;

	cout << "Testing Find with 3 : ";
	cout << tree->find(3) << endl;

	cout << "Testing Find with 6 : ";
	try{
		cout << tree->find(6) << endl;
	} catch (invalid_argument &except) {

	}
}

