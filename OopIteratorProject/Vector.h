#pragma once
#include <exception>
#include "Iterator.h"

template <class T>
class VectorIterator;

template <class T>
class Vector
{
	int size;
	int capacity;
	T* array;
public:
	Vector<T>()
		: size{ 0 }, capacity{ 0 }, array{ nullptr } {}

	Vector<T>(int size) : size{ size }
	{
		capacity = size;
		if (size)
			array = new T[capacity]{};
	}

	Vector<T>(const Vector<T>& vobj) : size{ vobj.size }, capacity{ vobj.capacity }
	{
		if (this->size)
		{
			array = new T[this->capacity]{};
			for (int i = 0; i < this->size; i++)
				array[i] = vobj.array[i];
		}
	}

	~Vector<T>()
	{
		if (array)
			delete[]array;
	}

	int Size() const
	{
		return this->size;
	}

	int Capacity() const
	{
		return this->capacity;
	}

	T& At(int index)
	{
		//if (index < 0 || index >= size)
		//	throw new std::exception("Index out of range of vector");

		if (index >= 0 && index < this->size)
			return array[index];
	}

	T& operator[](int index)
	{
		if (index >= 0 && index < this->size)
			return array[index];
	}

	Vector<T>& operator=(const Vector& vobj)
	{
		if (this == &vobj)
			return *this;

		if (this->array)
			delete[]this->array;

		this->size = vobj.size;
		this->capacity = vobj.capacity;

		if (this->size)
		{
			array = new T[this->capacity];
			for (int i = 0; i < this->size; i++)
				array[i] = vobj.array[i];
		}

		return *this;
	}

	void PushBack(T value)
	{
		if (size < capacity)
		{
			array[size] = value;
		}
		else
		{
			capacity += (!(capacity / 2) ? 2 : capacity / 2);
			T* arrayNew = new T[capacity];
			for (int i = 0; i < size; i++)
				arrayNew[i] = array[i];
			arrayNew[size] = value;

			delete[]array;
			array = arrayNew;
		}
		size++;
	}

	void Insert(T value, int index)
	{
		if (size < capacity)
		{
			for (int i = size - 1; i >= index; i--)
				array[i + 1] = array[i];
			array[index] = value;
		}
		else
		{
			capacity += (!(capacity / 2) ? 2 : capacity / 2);
			T* arrayNew = new T[capacity];

			for (int i = 0; i < index; i++)
				arrayNew[i] = array[i];

			arrayNew[index] = value;

			for (int i = index; i < size; i++)
				arrayNew[i + 1] = array[i];

			delete[]array;
			array = arrayNew;
		}
		size++;
	}

	T PopBack()
	{
		T value = array[size - 1];

		if (capacity > 2 * size)
		{
			capacity = size + size / 2;
			T* arrayNew = new T[capacity];

			for (int i = 0; i < size - 1; i++)
				arrayNew[i] = array[i];

			delete[]array;
			array = arrayNew;
		}
		size--;
		return value;
	}

	T Remove(int index)
	{
		T value = array[index];

		if (capacity < 2 * size)
		{
			for (int i = index; i < size - 1; i++)
				array[i] = array[i + 1];
		}
		else
		{
			capacity = size + size / 2;
			T* arrayNew = new T[capacity];

			for (int i = 0; i < index; i++)
				arrayNew[i] = array[i];
			for (int i = index + 1; i < size; i++)
				arrayNew[i - 1] = array[i];

			delete[]array;
			array = arrayNew;
		}
		size--;
		return value;
	}

	VectorIterator<T>* GetIterator()
	{
		return new VectorIterator<T>(this);
	}
};

template <class T>
class VectorIterator : public IIterator<T>
{
	Vector<T>* vect;
	int index;
public:
	VectorIterator(Vector<T>* vect) : vect{ vect }, index{ 0 } {}
	VectorIterator(const VectorIterator& iter) 
		: vect{ iter.vect }, index{ iter.index } {}
	VectorIterator& operator=(const VectorIterator& iter)
	{
		vect = iter.vect;
		index = iter.index;
		return *this;
	}

	void SetBegin() override
	{
		index = 0;
	}

	bool Next() override
	{
		if (index >= vect->Size())
			return false;
		else
		{
			index++;
			return true;
		}
	}

	bool IsEnd() override
	{
		return index >= vect->Size();
	}

	T& Current() override
	{
		return vect->At(index);
	}

	int Position() override
	{
		return index;
	}
};
