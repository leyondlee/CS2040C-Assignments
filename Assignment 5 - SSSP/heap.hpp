#pragma once
#include <math.h>

#include <iostream>
using namespace std;

#ifndef HEAPHPP
#define HEAPHPP

template <class T>
void Heap<T>::_swap(int index1, int index2) {
	T temp = _heap[index1];
	_heap[index1] = _heap[index2];
	_heap[index2] = temp;
}

template <class T>
void Heap<T>::_bubbleUp(int index) {
	if (index <= 0) {
		return;
	}
	
	int parentIndex = _getParentIndex(index);
	if (_heap[index] > _heap[parentIndex]) {
		_swap(index, parentIndex);
		_bubbleUp(parentIndex);
	}
}

template <class T>
void Heap<T>::_bubbleDown(int index) {
	int leftIndex = (2 * index) + 1;
	int rightIndex = (2 * index) + 2;
	if (leftIndex >= _n || rightIndex >= _n) {
		return;
	}
	
	bool isLeftValid = _isValidIndex(leftIndex);
	bool isRightValid = _isValidIndex(rightIndex);
	if (isLeftValid && isRightValid) {
		int largerChildIndex = (_heap[rightIndex] > _heap[leftIndex]) ? rightIndex : leftIndex;
		if (_heap[largerChildIndex] > _heap[index]) {
			_swap(index, largerChildIndex);
			_bubbleDown(largerChildIndex);
		}
	} else if (isLeftValid) {
		if (_heap[leftIndex] > _heap[index]) {
			_swap(index, leftIndex);
			_bubbleDown(leftIndex);
		}
	} else if (isRightValid) {
		if (_heap[rightIndex] > _heap[index]) {
			_swap(index, rightIndex);
			_bubbleDown(rightIndex);
		}
	}
}

template <class T>
void Heap<T>::insert(T item) {
	_heap[_n] = item;
	_bubbleUp(_n);

	_n += 1;
}

template <class T>
T Heap<T>::extractMax() {
	if (_n == 0) {
		return T();
	}

	T root = _heap[0];
	deleteItem(root);

	return root;
}


template <class T>
void Heap<T>::printHeapArray() {
	for (int i = 0; i < _n; i++)
		cout << _heap[i] << " ";
	cout << endl;
}

template <class T>
int Heap<T>::_lookFor(T x){ // not a very good implementation, but just use this for now.
    int i;
    for(i=0;i<_n;i++)
        if (_heap[i] == x)
            return i;
    
    return -1;
}

template <class T>
void Heap<T>::decreaseKey(T from, T to)
{
	int index = _lookFor(from);
	if (index == -1) {
		return;
	}
	
	_heap[index] = to;
	_bubbleDown(index);
}


template <class T>
void Heap<T>::increaseKey(T from, T to)
{
	int index = _lookFor(from);
	if (index == -1) {
		return;
	}
	
	_heap[index] = to;
	_bubbleUp(index);
}

template <class T>
void Heap<T>::deleteItem(T x)
{
	int index = _lookFor(x);
	if (index == -1) {
		return;
	}
	
	_n -= 1;
	_swap(index, _n);
	
	int parent = _getParentIndex(index);
	if (index > 0 && _heap[index] > _heap[parent]) {
		_bubbleUp(index);
	} else {
		_bubbleDown(index);
	}
}

template <class T>
void Heap<T>::printTree() {
    int parity = 0;
	if (_n == 0)
		return;
	int space = pow(2,1 + (int) log2f(_n)),i;
	int nLevel = (int) log2f(_n)+1;
	int index = 0,endIndex;
    int tempIndex;
	
	for (int l = 0; l < nLevel; l++)
	{
		index = 1;
        parity = 0;
		for (i = 0; i < l; i++)
			index *= 2;
		endIndex = index * 2 - 1;
		index--;
        tempIndex = index;
        while (index < _n && index < endIndex) {
            for (i = 0; i < space-1; i++)
                cout << " ";
            if(index==0)
                cout << "|";
            else if (parity)
                cout << "\\";
            else
                cout << "/";
            parity = !parity;
            for (i = 0; i < space; i++)
                cout << " ";
			index++;
		}
        cout << endl;
        index=tempIndex;
		while (index < _n && index < endIndex) {
			for (i = 0; i < (space-1-((int) log10(_heap[index]))); i++)
				cout << " ";
			cout << _heap[index];
			for (i = 0; i < space; i++)
				cout << " ";
			index++;
		}
		
		cout << endl;
		space /= 2;
	}
}

// Additional
template <class T>
bool Heap<T>::_isValidIndex(int index) {
	if (index >= 0 && index < _n) {
		return true;
	}
	
	return false;
}

template <class T>
int Heap<T>::_getParentIndex(int index) {
	if (index <= 0) {
		return -1;
	}
	
	return ((index - 1) / 2);
}

#endif
