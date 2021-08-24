#include <iostream>
#include "simpleIntLinkedList.h"

using namespace std;

ListNode::ListNode(int n) {
	_item = n;
	_next = NULL;
}

void List::insertHead(int n) {
	ListNode *aNewNode = new ListNode(n);
	aNewNode->_next = _head;
	_head = aNewNode;
	_size++;
};

void List::removeHead() {
	if (_size > 0) {
		ListNode *temp = _head;
		_head = _head->_next;
		delete temp;
		_size--;
	}
}

void List::print() {
	ListNode *node = _head;
	while (node != NULL) {
		cout << node->content() << " ";
		node = node->_next;
	}

	cout << endl;
}

bool List::exist(int n) {
	ListNode *node = _head;
	while (node != NULL) {
		if (node->content() == n) {
			return 1;
		}
		node = node->_next;
	}

	return 0;
}

int List::headItem() {
	return _head->_item;
}

List::~List() {
	while (_size != 0)
		removeHead();
};