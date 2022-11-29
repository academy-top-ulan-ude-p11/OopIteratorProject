#pragma once
#include "Iterator.h"

template <class T>
class ForwardListIterator;

template <class T>
struct Node
{
	T value;
	Node<T>* next;
};

template <class T>
class ForwardList
{
	Node<T>* head;
	int size;
public:
	ForwardList() : head{ nullptr }, size{ 0 } {}

	Node<T>* GetHead()
	{
		return head;
	}

	int Size()
	{
		return size;
	}

	void Add(T value)
	{
		Node<T>* nodeNew = new Node<T>();
		nodeNew->value = value;
		nodeNew->next = head;

		head = nodeNew;

		size++;
	}

	void Insert(int index, T value)
	{
		if (index >= size - 1)
		{
			Add(value);
			return;
		}


		Node<T>* nodeCurr = At(index);
		Node<T>* nodeNew = new Node<T>();

		nodeNew->value = value;
		nodeNew->next = nodeCurr->next;
		nodeCurr->next = nodeNew;
	}

	T Delete()
	{
		T value = head->value;

		Node<T>* nodeDel{ head };
		head = head->next;
		delete nodeDel;

		size--;

		return value;
	}

	T Remove(int index)
	{
		if (size <= 0)
			throw 1;

		if (index >= size - 1)
			return Delete();

		Node<T>* nodeCurr = At(index + 1);
		T value = nodeCurr->next->value;

		Node<T>* nodeDel = nodeCurr->next;
		nodeCurr->next = nodeCurr->next->next;

		delete nodeDel;

		return value;
	}

	Node<T>* At(int index)
	{
		if (index < 0 || index >= size)
			throw new std::exception("Index out of range of forward list");

		Node<T>* nodeCurr{ head };
		for (int i = 0; i < size - 1 - index; i++)
			nodeCurr = nodeCurr->next;

		return nodeCurr;
	}

	T& operator[](int index)
	{
		return this->At(index)->value;
	}
	
	ForwardListIterator<T>* GetIterator()
	{
		return new ForwardListIterator<T>(this);
	}
};

template <class T>
class ForwardListIterator : public IIterator<T>
{
	ForwardList<T>* list;
	Node<T>* node;
	int index;
public:
	ForwardListIterator()
	{
		list = node = nullptr;
		index = 0;
	}
	ForwardListIterator(ForwardList<T>* list) 
		: list{ list }, node{ list->GetHead() }, index{ 0 } {}

	ForwardListIterator(const ForwardListIterator& iter)
		: list{ iter->list }, node{ iter->node }, index{ iter->index } {}

	ForwardListIterator& operator=(const ForwardListIterator& iter) 
	{
		list = iter->list;
		node = iter->node;
		index = iter->index;

		return *this;
	}

	void SetBegin() override
	{
		node = list->GetHead();
	}

	bool Next() override
	{
		if (node)
		{
			node = node->next;
			index++;
		}
			

		return node;
	}

	bool IsEnd() override
	{
		return !node;
	}
	
	T& Current() override
	{
		return node->value;
	}

	int Position() override
	{
		return index;
	}
};



