
Шаблоны классов в С++


Мы уже ранее рассматривали в С++ такой инструмент, как  шаблоны, когда создавали шаблоны функций. Почему стоит пользоваться шаблонами, было написано в статье, с шаблонами функций. Там мы рассмотрели основные положения шаблонов в С++. Давайте их вспомним.

Любой шаблон начинается со слова template, будь то шаблон функции или шаблон класса. После  ключевого слова template идут угловые скобки - < >, в которых перечисляется список параметров шаблона. Каждому параметру должно предшествовать зарезервированное слово class или typename. Отсутствие этих ключевых слов будет расцениваться компилятором как синтаксическая ошибка. Некоторые примеры объявления шаблонов:

template <class T>
template <typename T>
template <typename T1, typename T2>

Ключевое слово typename говорит о том, что в шаблоне будет использоваться встроенный тип данных, такой как: int, double,float, char и т. д. А ключевое слово class сообщает компилятору, что в шаблоне функции в качестве параметра будут использоваться пользовательские типы данных, то есть классы. Но ни в коем случае не путайте параметр шаблона и шаблон класса. Если нам надо создать шаблон класса, с одним параметром типа int и char, шаблон класса будет выглядеть так:

template <typename T>
class Name
{
    //тело шаблона класса
};

где T — это параметр шаблона класса, который может принимать любой из встроенных типов данных, то, что нам и нужно.

А если параметр шаблона класса должен пользовательского типа, например типа Array, где Array — это класс, описывающий массив, шаблон класса будет иметь следующий вид:

template <class T>
class Name
{
    //тело шаблона класса
};

C этим вам лучше разобраться изначально, чтобы потом не возникало никаких ошибок, даже, если шаблон класса написан правильно.

Давайте создадим шаблон класса Стек, где стек — структура данных,  в которой хранятся однотипные элементы данных. В стек можно помещать и извлекать данные. Добавляемый элемент в стек, помещается в вершину стека. Удаляются элементы стека, начиная с его вершины. В шаблоне класса Stack необходимо создать основные методы:

    "Push" - добавить элемент в стек;
    "Pop"   - удалить элемент из стека
    "printStack" — вывод стека на экран;

Итак реализуем эти три метода, в итоге получим самый простой класс, реализующий работу структуры стек. Не забываем про конструкторы и деструкторы. Смотрим код:

#include "stdafx.h"
#include <iostream>
 
using namespace std;
 
#include <iomanip>
 
template <typename T>
class Stack
{
private:
    T *stackPtr; // указатель на стек
    int size; // размер стека
    T top; // вершина стека
public:
    Stack(int = 10);// по умолчанию размер стека равен 10 элементам
    ~Stack(); // деструктор
    bool push(const T  ); // поместить элемент в стек
    bool pop(); // удалить из стека элемент
    void printStack();
};
 
int main()
{
    Stack <int> myStack(5);
 
    // заполняем стек
    cout << "Заталкиваем элементы в стек: ";
    int ct = 0;
    while (ct++ != 5)
    {
        int temp;
        cin >> temp;
        myStack.push(temp);
    }
 
    myStack.printStack(); // вывод стека на экран
 
    cout << "\nУдаляем два элемента из стека:\n";
 
    myStack.pop(); // удаляем элемент из стека
    myStack.pop(); // удаляем элемент из стека
    myStack.printStack(); // вывод стека на экран
 
    return 0;
}
 
// конструктор
template <typename T>
Stack<T>::Stack(int s)
{
    size = s > 0 ? s: 10;   // инициализировать размер стека
    stackPtr = new T[size]; // выделить память под стек
    top = -1; // значение -1 говорит о том, что стек пуст
}
 
// деструктор
template <typename T>
Stack<T>::~Stack()
{
    delete [] stackPtr; // удаляем стек
}
 
// элемент функция класса  Stack для помещения элемента в стек
// возвращаемое значение - true, операция успешно завершена
//                                    false, элемент в стек не добавлен
template <typename T>
bool Stack<T>::push(const T value)
{
    if (top == size - 1)
        return false; // стек полон
 
    top++;
    stackPtr[top] = value; // помещаем элемент в стек
 
    return true; // успешное выполнение операции
}
 
// элемент функция класса  Stack для удаления элемента из стек
// возвращаемое значение - true, операция успешно завершена
//                                    false, стек пуст
template <typename T>
bool Stack<T>::pop()
{
    if (top == - 1)
        return false; // стек пуст
 
    stackPtr[top] = 0; // удаляем элемент из стека
    top--;
 
    return true; // успешное выполнение операции
}
 
// вывод стека на экран
template <typename T>
void Stack<T>::printStack()
{
    for (int ix = size -1; ix >= 0; ix--)
        cout << "|" << setw(4) << stackPtr[ix] << endl;
}

Как видите шаблон класса Stack объявлен и определен в файле с main-функцией. Конечно же такой способ утилизации шаблонов никуда не годится, но для примера сойдет. В строках 7 — 20 объявлен интерфейс шаблона класса.  Объявление класса выполняется привычным для нас образом, а перед классом находится объявление шаблона, в строке 7. При объявлении шаблона класса, всегда используйте такой синтаксис.

Строки 47 — 100 содержат элемент-функции шаблона класса Stack, причем перед каждой функцией необходимо объявлять шаблон, точно такой же, как и перед классом - template <typename T>. То есть получается, элемент-функции шаблона класса, объявляются точно также, как и обычные шаблоны функций. Если бы мы описали реализацию методов внутри класса, то заголовок шаблона - template <typename T> для каждой функции прописывать не надо.

Чтобы привязать каждую элемент-функцию к шаблону класса, как обычно используем бинарную операцию разрешения области действия — :: с именем шаблона класса - Stack<T>. Что мы и сделали в строках 49, 58, 68, 83, 96.

Обратите внимание на объявление объекта myStack шаблона класса Stack в функции main, строка 24. В угловых скобочка необходимо явно указывать используемый тип данных, в шаблонах функций этого делать не нужно было. Далее в main запускаются некоторые функции, которые демонстрируют работу шаблона класса Stack.
END.
----------------

