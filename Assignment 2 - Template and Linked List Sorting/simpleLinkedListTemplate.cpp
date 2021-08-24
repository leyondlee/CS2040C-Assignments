#pragma once

#ifndef SIMPLELINKEDLISTTEMPLATEHPP
#define SIMPLELINKEDLISTTEMPLATEHPP

#include <iostream>
#include "simpleLinkedListTemplate.h"

using namespace std;

template <class T>
ListNode<T>::ListNode(T n) {
	_item = n;
	_next = NULL;
}

template <class T>
void List<T>::insertHead(T n) {
	ListNode<T> *aNewNode = new ListNode<T>(n);
	aNewNode->_next = _head;
	_head = aNewNode;
	_size++;
};

template <class T>
void List<T>::removeHead() {
	if (_size > 0) {
		ListNode<T> *temp = _head;
		_head = _head->_next;
		delete temp;
		_size--;
	}
}

template <class T>
void List<T>::print(bool withNL) {

	ListNode<T> *temp = _head;
	while (temp) {
		cout << temp->_item;
		if (withNL)
			cout << endl;
		else
			cout << " ";
		temp = temp->_next;
	}
	cout << endl;

}

template <class T>
bool List<T>::exist(T n) {
	for (ListNode<T> *node = _head; node != NULL; node = node->_next) {
		if (node->_item == n) {
			return true;
		}
	}

	return false;
}

template <class T>
T List<T>::headItem() {
	if (_size)
		return *_head;
}

template <class T>
T List<T>::extractMax() {
	if (_head == NULL) {
		return T();
	}

	// if there are duplicates maximas in the list, return the leftmost one (the one closest to the _head)
	ListNode<T> *max_node = _head;
	for (ListNode<T> *node = _head->_next; node != NULL; node = node->_next) {
		if (node->_item > max_node->_item) {
			max_node = node;
		}
	}

	T item = max_node->_item;

	ListNode<T> *prev_node = NULL;
	for (ListNode<T> *node = _head; node != NULL; node = node->_next) {
		if (node == max_node) {
			if (prev_node == NULL) {
				_head = max_node->_next;
			} else {
				prev_node->_next = max_node->_next;
			}

			delete max_node;
			_size -= 1;

			break;
		}
		prev_node = node;
	}

	return item;
}

template <class T>
void List<T>::reverseOp() {
	ListNode<T> *prev_node = NULL;
	ListNode<T> *curr_node = _head;
	ListNode<T> *next_node = NULL;
	while (curr_node != NULL) {
		next_node = curr_node->_next;
		curr_node->_next = prev_node;
		prev_node = curr_node;
		curr_node = next_node;
	}

	_head = prev_node;
}

template <class T>
List<T>::~List() {
	while (_head)
		removeHead();
};


#endif