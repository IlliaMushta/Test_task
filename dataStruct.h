#pragma once

template<typename T>
class List
{
public:
	List();
	~List();

	void push_back(T data);
	void pop_front();
	void clear();
	int getSize();
	void push_front(T data);
	void insert(T data, int index);
	void removeAt(int index);
	void pop_back();

	T& operator[](const int index);

private:

	template<typename T>
	class Node
	{
	public:
		Node *pNext;
		T data;

		Node(T data = T(), Node* pNex = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
		}
	};

	int size;
	Node<T> *head;
};

template<typename T>
class Self_Balancing_Binary_Tree
{
private:

	template<typename T>
	class Node
	{
	public:
		Node *pLeft;
		Node *pRight;
		T data;
		int balance;

		Node(T data = T(), int balance = 0, Node* pLeft = nullptr, Node* pRight = nullptr)
		{
			this->data = data;
			this->balance = balance;
			this->pLeft = pLeft;
			this->pLeft = pRight;
		}
	};

	int size;
	Node<T> *pRoot;

	int height(Node<T> *(&pRoot));
	void insertNode(Node<T> *(&pRoot), T data);
	void setBalance(Node<T> *(&pRoot));
	void clear(Node<T> *(&pRoot));
	void print(Node<T> *(&pRoot));
	void RotateLeft(Node<T> *(&pRoot));
	void RotateRight(Node<T> *(&pRoot));

public:

	Self_Balancing_Binary_Tree();
	~Self_Balancing_Binary_Tree();

	int Height();

	void InsertNode(T data);

	void Clear();

	void Print();

	int Size();
};


