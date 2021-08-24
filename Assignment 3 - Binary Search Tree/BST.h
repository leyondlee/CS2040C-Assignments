#pragma once
#include <iostream>

using namespace std;

template <class T>
class BinarySearchTree;

template <class T>
class TreeNode {
private:
	T _item;
	TreeNode<T> *_left;
	TreeNode<T> *_right;
	int _height;
public:
	TreeNode(T x) { _left = _right = NULL; _item = x; _height = 0; };

	friend BinarySearchTree<T>;

	// Additional
	void rectifyHeight();
};

template <class T>
class BinarySearchTree {
private:
	int _size;
	TreeNode<T> *_root;
	void _printTree(int indent, TreeNode<T> *, bool withHeight);

	void _preOrderPrint(TreeNode<T> *);

	TreeNode<T> *_rightRotation(TreeNode<T> *);
	TreeNode<T> *_leftRotation(TreeNode<T> *);
	void _destroySubTree(TreeNode<T> *);

	// Additional
	TreeNode<T> *_insert(TreeNode<T> *, T);
	void _setHeight(TreeNode<T> *);
	TreeNode<T> *_balanceNode(TreeNode<T> *);
	int _getBalanceFactor(TreeNode<T> *);
	int _getHeight(TreeNode<T> *);
	TreeNode<T> *_getNode(TreeNode<T> *, T);
	TreeNode<T> *_searchMax(TreeNode<T> *);
	TreeNode<T> *_searchMin(TreeNode<T> *);
	TreeNode<T> *_successor(TreeNode<T> *, T);
	void _inOrderPrint(TreeNode<T> *);
	void _postOrderPrint(TreeNode<T> *);

public:
	BinarySearchTree() { _root = NULL; _size = 0; }
	~BinarySearchTree();
	int size() { return _size; };
	void insert(T);
	void printTree(bool withHeight = 1);
	void inOrderPrint();
	void postOrderPrint();
	void preOrderPrint();
	T searchMax();
	T searchMin();
	bool exist(T x);
	T successor(T);
};

#include "BST.hpp"