#pragma once
template <class T>
class IIterator
{
public:
	virtual void SetBegin() = 0;
	virtual bool Next() = 0;
	virtual bool IsEnd() = 0;
	virtual T& Current() = 0;

	//virtual int Position() = 0;
};

