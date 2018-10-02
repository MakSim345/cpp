#pragma once

#include "Element.h"

template <class T>
class TStack
{
  typedef void (*OnPushListener)( T );
	typedef void (*OnPopListener)( T );

private:
	TElement<T> *top;
	TElement<T> *bottom;

	OnPushListener pushListener;
	OnPopListener  popListener;

public:
	TStack(void)
	{
		top = NULL;
		bottom = NULL;
	}

	TElement<T> *getTop()
	{
		return top;
	}

	TElement<T> *getBottom()
	{
		return bottom;
	}

	bool isEmpty()
	{
		bool result;

		if( top == bottom && top == NULL )
		{
			result = true;
		}
		else
		{
			result = false;
		}

		return result;
	}

	T pop()
	{
		//основной код
		T result = 0;

		if( !isEmpty() )
		{
			result = getTop()->getValue();
		
			TElement<T> *elemToDelete = top;
			top = top->getNext();

			if( elemToDelete != NULL )
			{
				delete( elemToDelete );
			}
		}
		
		//событие
		if( popListener != NULL )
		{
			(*popListener)(  result );
		}

		return result;
	}

	void push( T newValue )
	{
		//основной код
		TElement<T> *newTop = NULL;
		try{
			newTop = new TElement<T>( newValue, top );
			if( isEmpty() )
			{ 
				bottom = newTop;
			}
			top = newTop;
		}
		catch( int e ){
			if( newTop != NULL )
			{
				delete( newTop );
			}
		}

		//событие
		if( pushListener!=NULL )
		{
			(*pushListener)( newValue );
		}
	}

	void clear()
	{
		if( !isEmpty() )
		{
			TElement<T> *prevElement = NULL;
			TElement<T> *curElement = top;
			while( curElement!=NULL )
			{
				prevElement = curElement;
				curElement = prevElement->getNext();
				delete( prevElement );
			}
		}

		top = bottom = NULL;
	}
	
	~TStack(void)
	{
		Clear();
	};

	void addPushListener( OnPushListener newListener )
	{
		pushListener = newListener;
	}

	void addPopListener( OnPopListener newListener )
	{
		popListener = newListener;
	}
};

