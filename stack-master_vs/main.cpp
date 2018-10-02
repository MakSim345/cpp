#include "Stack.h"

void onPush(int pushedValue)
{
  printf( "Pushed: %d\n", pushedValue );
}

void onPop( int popedValue)
{
	printf( "Poped: %d\n", popedValue );
}

int _tmain(int argc, _TCHAR* argv[])
{

	TStack<int> *stack = new TStack<int>();
	stack->addPushListener( &onPush );
	stack->addPopListener( &onPop );

	//Обычный режим
	puts( "Regular mode");

	stack->push( 1 );
	stack->push( 2 );
	stack->push( 3 );

	int a = stack->pop();
	a = stack->pop();
	a = stack->pop();

	//очистка стека
	puts( "Stack clear mode");

	stack->push( 1 );
	stack->push( 2 );
	stack->push( 3 );

	stack->clear();

	a = stack->pop();
	a = stack->pop();
	a = stack->pop();

	//работа с вершиной и дном
	puts( "Top/bottom mode");
	stack->push( 1 );
	stack->push( 2 );
	stack->push( 3 );

	int top = stack->getTop()->getValue();
	int bottom = stack->getBottom()->getValue();

	printf( "top=%d, bottom=%d\n", top, bottom );

	system( "pause");
	return 0;
}
