#pragma once
template <class T>
class TElement
{
private:
  T value;
	TElement *next;
public:

	TElement( T newValue, TElement *newNext=NULL )
	{
		setValue( newValue );
		setNext( newNext );
	}

	TElement *getNext()
	{
		return next;
	}

	void setNext( TElement *newNext )
	{
		next = newNext;
	}

	T getValue()
	{
		return value;
	}

	void setValue( T newValue )
	{
		value = newValue;
	}


	~TElement(void)
	{
	}
};
