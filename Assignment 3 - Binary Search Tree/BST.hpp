#pragma once
#ifndef BSTHPP
#define BSTHPP
#include "BST.h"

template <class T>
void BinarySearchTree<T>::insert(T x) {
	if (_root == NULL) {
		_root = new TreeNode<T>(x);
	} else {
		_root = _insert(_root, x);
	}

	_size += 1;
}

template <class T>
bool BinarySearchTree<T>::exist(T x) {
	TreeNode<T> *node = _getNode(_root, x);
	if (node == NULL) {
		return false;
	}

	return true;
}

template <class T>
T BinarySearchTree<T>::searchMax() {
	TreeNode<T> *_node = _searchMax(_root);
	if (_node == NULL) {
		return T();
	}

	return _node->_item;
}

template <class T>
T BinarySearchTree<T>::searchMin() {
	TreeNode<T> *_node = _searchMin(_root);
	if (_node == NULL) {
		return T();
	}

	return _node->_item;
}

template <class T>
T BinarySearchTree<T>::successor(T x) {
	TreeNode<T> *node = _successor(_root, x);
	if (node == NULL) {
		return T();
	}

	return node->_item;
}


template <class T>
TreeNode<T> *BinarySearchTree<T>::_leftRotation(TreeNode<T> *node) {
	if (node == NULL) {
		return NULL;
	}
	TreeNode<T> *newRoot = node->_right;

	node->_right = newRoot->_left;
	newRoot->_left = node;

	_setHeight(node);
	_setHeight(newRoot);

	return newRoot;
}

template <class T>
TreeNode<T> *BinarySearchTree<T>::_rightRotation(TreeNode<T> *node) {
	if (node == NULL) {
		return NULL;
	}

	TreeNode<T> *newRoot = node->_left;

	node->_left = newRoot->_right;
	newRoot->_right = node;

	_setHeight(node);
	_setHeight(newRoot);

	return newRoot;
}

template <class T>
void BinarySearchTree<T>::printTree(bool withHeight) {
	_printTree(0, _root, withHeight);
}

template <class T>
void BinarySearchTree<T>::preOrderPrint() {
	_preOrderPrint(_root);
	cout << endl;
}


template <class T>
void BinarySearchTree<T>::_preOrderPrint(TreeNode<T> *node) {
	if (!node) return;
	cout << node->_item << " ";
	_preOrderPrint(node->_left);
	_preOrderPrint(node->_right);
}

template <class T>
void BinarySearchTree<T>::inOrderPrint() {
	_inOrderPrint(_root);
	cout << endl;
}


template <class T>
void BinarySearchTree<T>::postOrderPrint() {
	_postOrderPrint(_root);
	cout << endl;
}

template <class T>
void BinarySearchTree<T>::_printTree(int indent, TreeNode<T> *node, bool withHeight) {

	if (!node)
		return;

	if (node->_right)
		_printTree(indent + 2, node->_right, withHeight);
	for (int i = 0; i < indent; i++)
		cout << "  ";
	cout << node->_item;
	if (withHeight)
		cout << "(h=" << node->_height << ")";
	cout << endl;
	if (node->_left)
		_printTree(indent + 2, node->_left, withHeight);


};


template <class T>
void BinarySearchTree<T> ::_destroySubTree(TreeNode<T> *node) {
	if (node->_left)
		_destroySubTree(node->_left);
	if (node->_right)
		_destroySubTree(node->_right);
	delete node;
}

template <class T>
BinarySearchTree<T> :: ~BinarySearchTree() {
	if (_root)
		_destroySubTree(_root);
}

// Additional
template <class T>
void TreeNode<T>::rectifyHeight() {
	int leftHeight;
	if (_left == NULL) {
		leftHeight = -1;
	} else {
		leftHeight = _left->_height;
	}

	int rightHeight;
	if (_right == NULL) {
		rightHeight = -1;
	} else {
		rightHeight = _right->_height;
	}

	_height = max(leftHeight, rightHeight) + 1;
}

template <class T>
TreeNode<T> *BinarySearchTree<T>::_insert(TreeNode<T> *current, T x) {
	if (current->_item > x) {
		if (current->_left) {
			current->_left = _insert(current->_left, x);
		} else {
			current->_left = new TreeNode<T>(x);
		}
	} else if (x > current->_item) {
		if (current->_right) {
			current->_right = _insert(current->_right, x);
		} else {
			current->_right = new TreeNode<T>(x);
		}
	} else {
		return current;
	}

	_setHeight(current);
	current = _balanceNode(current);

	return current;
}

template <class T>
void BinarySearchTree<T>::_setHeight(TreeNode<T> *node) {
	if (node == NULL) {
		return;
	}

	node->rectifyHeight();
}

template <class T>
TreeNode<T> *BinarySearchTree<T>::_balanceNode(TreeNode<T> *node) {
	if (node == NULL) {
		return NULL;
	}

	int balanceFactor = _getBalanceFactor(node);
	if (abs(balanceFactor) <= 1) {
		return node;
	}

	if (balanceFactor > 1) {
		// Right Heavy
		if (_getBalanceFactor(node->_right) < 0) {
			TreeNode<T> *rightNode = _rightRotation(node->_right);
			node->_right = rightNode;
		}

		node = _leftRotation(node);
	} else {
		// Left Heavy
		if (_getBalanceFactor(node->_left) > 0) {
			TreeNode<T> *leftNode = _leftRotation(node->_left);
			node->_left = leftNode;
		}

		node = _rightRotation(node);
	}

	return node;
}

template <class T>
int BinarySearchTree<T>::_getBalanceFactor(TreeNode<T> *node) {
	if (node == NULL) {
		return 0;
	}

	return (_getHeight(node->_right) - _getHeight(node->_left));
}

template <class T>
int BinarySearchTree<T>::_getHeight(TreeNode<T> *node) {
	if (node == NULL) {
		return -1;
	}

	return node->_height;
}

template <class T>
TreeNode<T> *BinarySearchTree<T>::_getNode(TreeNode<T> *node, T x) {
	if (node == NULL) {
		return NULL;
	}

	if (x == node->_item) {
		return node;
	}

	if (x < node->_item) {
		return _getNode(node->_left, x);
	}

	return _getNode(node->_right, x);
}

template <class T>
TreeNode<T> *BinarySearchTree<T>::_searchMax(TreeNode<T> *node) {
	if (node == NULL) {
		return NULL;
	}

	TreeNode<T> *res = _searchMax(node->_right);
	if (res == NULL) {
		return node;
	}

	return res;
}

template <class T>
TreeNode<T> *BinarySearchTree<T>::_searchMin(TreeNode<T> *node) {
	if (node == NULL) {
		return NULL;
	}

	TreeNode<T> *res = _searchMin(node->_left);
	if (res == NULL) {
		return node;
	}

	return res;
}

template <class T>
TreeNode<T> *BinarySearchTree<T>::_successor(TreeNode<T> *node, T x) {
	if (node == NULL) {
		return NULL;
	}

	TreeNode<T> *res;
	if (node->_item > x) {
		res = _successor(node->_left, x);
	} else {
		res = _successor(node->_right, x);
	}

	if (res == NULL) {
		if (node->_item > x) {
			return node;
		}
		return NULL;
	}

	if (node->_item > x && node->_item < res->_item) {
		return node;
	}

	return res;
}

template <class T>
void BinarySearchTree<T>::_inOrderPrint(TreeNode<T> *node) {
	if (node == NULL) {
		return;
	}

	_inOrderPrint(node->_left);
	cout << node->_item << " ";
	_inOrderPrint(node->_right);
}

template <class T>
void BinarySearchTree<T>::_postOrderPrint(TreeNode<T> *node) {
	if (node == NULL) {
		return;
	}

	_postOrderPrint(node->_left);
	_postOrderPrint(node->_right);
	cout << node->_item << " ";
}

#endif