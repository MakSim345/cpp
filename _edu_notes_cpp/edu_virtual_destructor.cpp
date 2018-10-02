2015-FEB

Technical questions on the interview. Varian Medical Oy

- virtual destructor. Why it is virtual and what does it mean?
"http://stackoverflow.com/questions/461203/when-to-use-virtual-destructors"

A virtual destructor ensures a C++ object will correctly call the destructor of the most-derived class when a polymorphic object is deleted through a pointer to its base class.

Virtual destructors are useful when you can delete an instance of a derived class through a pointer to base class:
____________________________
#include <iostream>
using namespace std;
class base
{
public:
    base(){cout<<"Base Constructor Called\n";}
   ~base(){cout<<"Base Destructor called\n";}
    //virtual ~base(){cout<<"Base Destructor called\n";}

};
class derived1:public base
{

public:
    derived1(){cout<<"Derived constructor called\n";}
   ~derived1(){cout<<"Derived destructor called\n";}
};
____________________________

Here, you'll notice that I didn't declare "base" destructor to be virtual.
Now, let's have a look at the following snippet:
____________________________
int main()
{
    base* b;
    b=new derived1;
    delete b; // Here's the problem!
}
____________________________
Output:
Base Constructor Called
Derived constructor called
Base Destructor called
____________________________

Since Base's destructor is not virtual and 'b' is a base* pointing to a derived1 object, 'delete b' has undefined behaviour. 
In most implementations, the call to the destructor will be resolved like any non-virtual code, meaning that the destructor of the base class will be called but not the one of the derived class, resulting in resources leak.

To sum up, always make base classes' destructors 'virtual' when they are meant to be manipulated polymorphically.

If you want to prevent the deletion of an instance through a base class pointer, you can make the base class destuctor protected and nonvirtual; by doing so, the compiler won't let you call delete on a base class pointer.

--------------------------------
Если вы уже знаете и умеете использовать виртуальные функции, то просто обязаны знать, когда и зачем нужны виртуальные деструкторы. 
Иначе нижеследующий текст был написан именно для вас.

Основное правило: если у вас в классе присутствует хотя бы одна виртуальная функция, деструктор также следует сделать виртуальным. При этом не следует забывать, что деструктор по умолчанию виртуальным не будует, поэтому следует объявить его явно. Если этого не сделать, у вас в программе почти наверняка будут утечки памяти (memory leaks). Чтобы понять почему pассмотрим несколько примеров.

В первом случае создадим объект производного класса в стеке:

#include <cstdlib>
#include <iostream>

using std::cout;
using std::endl;

class A 
{
public:
    A() { cout << "A()" << endl; }
    ~A() { cout << "~A()" << endl; }
};

class B : public A 
{
public:
    B() { cout << "B()" << endl; }
    ~B() { cout << "~B()" << endl; }
};

int main()
{
    B b;
    return EXIT_SUCCESS;
}

Всем ясно, что вывод программы будет следующим:
A()
B()
~B()
~A()
потому что сначала конструируется базовая часть класса, затем производная, а при разрушении наоборот — сначала вызывается деструктор производного класса, который по окончании своей работы вызывает по цепочке деструктор базового. Это правильно и так должно быть. 

Попробуем теперь создать тот же объект в динамической памяти, используя при этом указатель на объект базового класса (код классов не изменился, поэтому привожу только код функции main()):

int main()
{
    A *pA = new B;
    delete pA;
    return EXIT_SUCCESS;
}

На сей раз конструируется объект так, как и надо, а при разрушении происходит утечка памяти, потому как деструктор производного класса не вызывается:
A()
B()
~A()
Происходит это потому, что удаление производится через указатель на базовый класс и для вызова деструктора компилятор использует раннее связывание. Деструктор базового класса не может вызвать деструктор производного, потому что он о нем ничего не знает. В итоге часть памяти, выделенная под производный класс, безвозвратно теряется.

Чтобы этого избежать, деструктор в базовом классе должен быть объявлен как виртуальный:

#include <cstdlib>
#include <iostream>

using std::cout;
using std::endl;

class A 
{
public:
    A() { cout << "A()" << endl; }
    virtual ~A() { cout << "~A()" << endl; }
};

class B : public A 
{
public:
    B() { cout << "B()" << endl; }
    ~B() { cout << "~B()" << endl; }
};

int main()
{
    A * pA = new B;
    delete pA;
    return EXIT_SUCCESS;
}

Теперь-то мы получим желаемый порядок вызовов:
A()
B()
~B()
~A()

Происходит так потому, что отныне для вызова деструктора используется позднее связывание, то есть при разрушении объекта берется указатель на класс, затем из таблицы виртуальных функций определяется адрес нужного нам деструктора, а это деструктор производного класса, который после своей работы, как и полагается, вызывает деструктор базового. Итог: объект разрушен, память освобождена.

Виртуальные функции в деструкторах

Давайте для начала рассмотрим ситуацию с вызовом виртуальных функций внутри класса. Предположим, что у нас есть Кот, который просит покушать мяуканьем, а затем приступает к процессу :) Так поступают многие коты, но не Чеширский! Чеширский, как известно, мало того что вечно улыбается, так еще и довольно разговорчив, поэтому мы научим его говорить, переопределив метод 'speak()':

#include <cstdlib>
#include <iostream>

using std::cout; 
using std::endl;

class Cat
{
public:
    void askForFood() const
    {
        speak();
        eat();
    }
    virtual void speak() const { cout << "Meow! "; }
    virtual void eat() const { cout << "*champing*" << endl; }
};

class CheshireCat : public Cat
{
public:
    virtual void speak() const { cout << "WTF?! Where\'s my milk? =) "; }
};

int main()
{
    Cat * cats[] = { new Cat, new CheshireCat };

    cout << "Ordinary Cat: "; cats[0]->askForFood();
    cout << "Cheshire Cat: "; cats[1]->askForFood();

    delete cats[0]; delete cats[1];
    return EXIT_SUCCESS;
}


Вывод этой программы будет следующим:
Ordinary Cat: Meow! *champing*
Cheshire Cat: WTF?! Where's my milk? =) *champing*


Рассмотрим код более подробно. Есть класс Cat с парой виртуальных методов, один из которых переопределен в производном CheshireCat. Но всё самое интересное происходит в методе askForFood() класса Cat.

Как видно, метод всего лишь содержит вызовы двух других методов, однако конструкция speak() в данном контексте эквивалента 
this->speak()
то есть вызов происходит через указатель, а значит — будет использовано позднее связывание. Вот почему при вызове метода askForFood() через указатель на CheshireCat мы видим то, что и хотели: механизм виртуальных функций работает исправно даже несмотря на то, что вызов непосредственно виртуального метода происходит внутри другого метода класса.

А теперь самое интересное: что будет, если попытаться воспользоваться этим в деструкторе? Модернизируем код так, чтобы при деструкции наши питомцы прощались, кто как умеет:

#include <cstdlib>
#include <iostream>

using std::cout; 
using std::endl;

class Cat
{
public:
    virtual ~Cat() { sayGoodbye(); }
    void askForFood() const
    {
        speak();
        eat();
    }
    virtual void speak() const { cout << "Meow! "; }
    virtual void eat() const { cout << "*champing*" << endl; }
    virtual void sayGoodbye() const { cout << "Meow-meow!" << endl; }
};

class CheshireCat : public Cat
{
public:
    virtual void speak() const { cout << "WTF?! Where\'s my milk? =) "; }
    virtual void sayGoodbye() const { cout << "Bye-bye! (:" << endl; }
};

int main()
{
    Cat * cats[] = { new Cat, new CheshireCat };

    cout << "Ordinary Cat: "; cats[0]->askForFood();
    cout << "Cheshire Cat: "; cats[1]->askForFood();

    delete cats[0]; delete cats[1];
    return EXIT_SUCCESS;
}


Можно ожидать, что, как и в случае с вызовом метода speak(), будет выполнено позднее связывание, однако это не так:
Ordinary Cat: Meow! *champing*
Cheshire Cat: WTF?! Where's my milk? =) *champing*
Meow-meow!
Meow-meow!


Почему? Да потому что при вызове виртуальных методов из деструктора компилятор использует не позднее, а раннее связывание. Если подумать, зачем он делает именно так, всё становится очевидным: нужно просто рассмотреть порядок конструирования и разрушения объектов. Все помнят, что конструирование объекта происходит, начиная с базового класса, а разрушение идет в строго обратном порядке. Таким образом, когда мы создаем объект типа CheshireCat, порядок вызовов конструкторов/деструкторов будет таким:
Cat()
CheshireCat()
~CheshireCat()
~Cat()


Если же мы захотим внутри деструктора ~Cat() совершить виртуальный вызов метода sayGoodbye(), то фактически попытаемся обратиться к той части объекта, которая уже была разрушена.

Мораль: если в вашей голове витают помыслы выделить какой-то алгоритм «зачистки» в отдельный метод, переопределяемый в производных классах, а затем виртуально вызывать его в деструкторе, у вас ничего не выйдет.



