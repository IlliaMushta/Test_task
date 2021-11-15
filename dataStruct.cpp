#include "framework.h"

#include <iostream>
#include "dataStruct.h"

template<typename T>
List<T>::List()
{
	size = 0;
	head = nullptr;
}

template<typename T>
List<T>::~List()
{
	clear();
}

template<typename T>
void List<T>::push_back(T data)
{
	if (head == nullptr) {
		head = new Node<T>(data);
	}
	else {
		Node<T> *current = this->head;

		while (current->pNext != nullptr) {
			current = current->pNext;
		}

		current->pNext = new Node <T>(data);
	}

	size++;
}

template<typename T>
void List<T>::pop_front()
{
	Node<T> *temp = head;
	head = head->pNext;
	delete temp;
	size--;
}

template<typename T>
void List<T>::clear()
{
	while (size) {
		pop_front();
	}
}

template<typename T>
int List<T>::getSize()
{
	return size;
}

template<typename T>
void List<T>::push_front(T data)
{
	head = new Node<T>(data, head);
	size++;
}

template<typename T>
void List<T>::insert(T data, int index)
{
	if (!index) {
		push_front(data);
	}
	else {

		Node<T> *previous = this->head;

		for (int i = 0; i < index - 1; i++) {
			previous = previous->pNext;
		}

		Node<T> *newNode = new Node<T>(data, previous->pNext);
		previous->pNext = newNode;

		size++;
	}
}

template<typename T>
void List<T>::removeAt(int index)
{
	if (index == 0) {
		pop_front();
	}
	else {
		Node<T> *previous = this->head;
		for (int i = 0; i < index - 1; i++) {
			previous = previous->pNext;
		}

		Node<T> *toDelete = previous->pNext;
		previous->pNext = toDelete->pNext;

		delete toDelete;
		size--;
	}
}

template<typename T>
void List<T>::pop_back()
{
	removeAt(size - 1);
}

template<typename T>
T & List<T>::operator[](const int index)
{
	int counter = 0;
	Node<T> *current = this->head;

	while (current != nullptr) {
		if (counter == index) {
			return current->data;
		}
		current = current->pNext;
		current++;
	}
}


template<typename T>
int Self_Balancing_Binary_Tree<T>::Height() {
	return height(pRoot);
}

template<typename T>
void Self_Balancing_Binary_Tree<T>::InsertNode(T data) {
	insertNode(pRoot, data);
}

template<typename T>
void  Self_Balancing_Binary_Tree<T>::Clear() {
	clear(pRoot);
}

template<typename T>
void  Self_Balancing_Binary_Tree<T>::Print() {
	print(pRoot);
}

template<typename T>
int Self_Balancing_Binary_Tree<T>::Size() {
	return size;
}

template<typename T>
Self_Balancing_Binary_Tree<T>::Self_Balancing_Binary_Tree()
{
	size = 0;
	pRoot = nullptr;
}

template<typename T>
Self_Balancing_Binary_Tree<T>::~Self_Balancing_Binary_Tree()
{
	clear(pRoot);
}

template<typename T>
void Self_Balancing_Binary_Tree<T>::clear(Node<T> *(&pRoot)) {
	if (pRoot != nullptr)
	{
		clear(pRoot->pLeft);
		clear(pRoot->pRight);
		delete pRoot;
		pRoot = nullptr;
		size--;
	}
}

template<typename T>
void Self_Balancing_Binary_Tree<T>::print(Node<T> *(&pRoot))
{
	if (pRoot != nullptr)
	{
		print(pRoot->pLeft);
		std::cout << "data:" << pRoot->data << '\t' << "balance:" << pRoot->balance << std::endl;
		print(pRoot->pRight);
	}
}

template<typename T>
void Self_Balancing_Binary_Tree<T>::RotateLeft(Node<T>*(&pRoot))
{
	Node<T> *rightSubtree, *rightSubtreeLeftSubtree;
	rightSubtree = pRoot->pRight;
	rightSubtreeLeftSubtree = rightSubtree->pLeft;

	rightSubtree->pLeft = pRoot;
	pRoot->pRight = rightSubtreeLeftSubtree;
	pRoot = rightSubtree;
	setBalance(pRoot->pLeft);
	setBalance(pRoot);
}

template<typename T>
void Self_Balancing_Binary_Tree<T>::RotateRight(Node<T>*(&pRoot))
{
	Node<T> *leftSubtree, *leftSubtreeRightSubtree;
	leftSubtree = pRoot->pLeft;
	leftSubtreeRightSubtree = leftSubtree->pRight;

	leftSubtree->pRight = pRoot;
	pRoot->pLeft = leftSubtreeRightSubtree;
	pRoot = leftSubtree;
	setBalance(pRoot->pRight);
	setBalance(pRoot);
}

template<typename T>
int Self_Balancing_Binary_Tree<T>::height(Node<T>* (&pRoot))
{
	if (pRoot == nullptr) return 0;
	int hLeft = height(pRoot->pLeft);
	int hRight = height(pRoot->pRight);
	if (hLeft > hRight)
		return hLeft + 1;
	else
		return hRight + 1;
}

template<typename T>
void Self_Balancing_Binary_Tree<T>::setBalance(Node<T>* (&pRoot))
{
	if (pRoot != nullptr)
		pRoot->balance = height(pRoot->pRight) - height(pRoot->pLeft);
}

template<typename T>
void Self_Balancing_Binary_Tree<T>::insertNode(Node<T>* (&pRoot), T data)
{
	if (pRoot == nullptr) {
		pRoot = new Node<T>(data, 0, nullptr, nullptr);
		size++;
	}
	else {
		if (data > pRoot->data) {
			insertNode(pRoot->pRight, data);
			if (height(pRoot->pRight) - height(pRoot->pLeft) > 1) {
				if(height(pRoot->pRight->pRight) < height(pRoot->pRight->pLeft))
					RotateRight(pRoot->pRight);
				RotateLeft(pRoot);
			}
		}
		else if (data < pRoot->data) {
			insertNode(pRoot->pLeft, data);
			if (height(pRoot->pLeft) - height(pRoot->pRight) > 1) {
				if (height(pRoot->pLeft->pLeft) < height(pRoot->pLeft->pRight))
					RotateLeft(pRoot->pLeft);
				RotateRight(pRoot);
			}
		}
		setBalance(pRoot);
	}
}