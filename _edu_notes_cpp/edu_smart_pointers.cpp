Smart pointers ��� ����������

��� ��������� ������ � ������ ������� ������������� ��� ���������� C++ �������������, ������� ���� ������� �� ����� ����������, �� ������� �� ���������, ���� ��� ������ ������� �� new-delete.


����, ������������ �++ �����, ��� ������ ����� �����������. ���������� ������. � ��� �����, ��� ���� ���-�� ������� new, ����������� ������ ���� ��������������� delete. �� ������ ����������� � ������� ����� ���� �������, ��������, ���������� ��������:

    - ������ ������;
    - ��������������� �������� ���������, ���� ��������� � ������������������ ������� ������;
    - �������� ��� ���������� �������;

������ � �������� �� ��� ��������, ���� ��������� �� �������� 24/7, ���� ���, �� ����������, �� ��������� � �����. ��� ��������������� �������� ��������� �� �������������� ������� �������, �������� ������ ����� ��� ������ ����� �� ���������� ������� (�� �� ��������� � ��� �). ��� ��������� �������� ����� ��������� ������ ���, ��� ������. ������ (���� ����� ���� � �� ������), ���� ��� ���������� ���� ������, �� ���-�� � ��� �� ��������� ����� ��������, ������������ ���������� ���������� ������. ������ ������� �� �����������, �� ��������, ��� �� �������� 1 �� ������ ������� � ���������� ������. ����� �� ����������� ������ ����� ��������� ����� 1024, ����� ������� ������ ��������� ��� ������ delete ������� ����� 1024 ���� ������, �� ������ � �� ������. ��� ������ ������ delete ��� �������, ��� ������ �� ������� �� �� ������. ����� ����� ����� ��������, ���� ��������� ����������� ��������� ��������� ���� ������, � ���� ��������� ����� ���������.

��������

���������� ������� ���������� ��������� ����������� ��������� ��������, ���������� RAII. �� ����, ��� ��������� ������-���� �������, ��� �������������� � ������������, �, ��������� � ��� � �������, ��������� ����������� � �����������. �������� ����� ���� ��� ������, � ������� ����, ������� ����������, � � ����� ������ ���� ������. ��� ���������� ������:

        class VideoBuffer 
        {
            int *myPixels;
        public:
            VideoBuffer() 
            {
                pixels = new int[640 * 480];
            }
            void makeFrame() 
            { /* �������� � ������� */ }

            ~VideoBuffer() 
            {
                delete [] pixels;
            }
        };
        int game() 
        {
            VideoBuffer screen;
            screen.makeFrame();
        }


��� ������: �� ������ �� ������� ��� �� ����� ���������� �� ������������ ������, ��� ��� ��� ������� screen ��������� ����������, ������� � ���� ������� ��������� ����������������� � ���� ������ ��������. �������, ����� �������� � ���:

        int game() 
        {
            int *myPixels = new int[640 * 480];
            // ��������
            delete [] pixels;
        }


� ��������, ������� �������, �� ���������� ���� ����� ���:

        int game() 
        {
            int *myPixels = new int[640 * 480];
            // ��������
            if (someCondition)
                return 1;        
            // �������� ������    
            if (someCondition)
                return 4;        
            // ����������
            delete [] pixels;
        }

�������� � ������ ����� ������ �� ������� ������ delete [], ���� �������� �����-���� �������������� ������� ���������������. � ���� ��������� ������ �����, ���� ��� ���������� � ������ ������ �������? �������� �� ���� ���� ����� ��� ������� � �������. �������� �������� ���������, ���� �� � �������� ������� ������� ����������: �������������, ��� ������� �� ����� ����� ����������, �� � ����� �������� �������� ��������.

��, ����� ������������ RAII, � ������������� ���������������� ������, � ����������� �����������. � ����� ���� ������ ������ ����� ����������� �� ������� ������������ ������:

        class Foo 
        {
            int    *data1;
            double *data2;
            char   *data3;
        
            public:
            Foo() 
            {
                data1 = new int(5);
                ...
            }
            ~Foo() 
            {
                delete data1;
                ...
            }
        }


������ �����������, ��� ����� �� 3, � 30, � ������ � ����������� �������� ��� ���� ��� �������� delete. � ���� �� �������� ������� ����� ����, �� ������� ��� ����� � �����������, �� ����������� ����� �����������. � ����� ���������� �����, ����������� ���������� ���������\������������ ������, �� ��� � ���������, ��� �� ���� ��������� �������.

������� ������������ ������������ "����� ���������": ��� �������, ������� ������ ��������� �� ����������� �������������� ������� ������ ������������� ����. ������ ��� ������������� ������� ������ �� ������ �� ������� ���������.

������� ���������� ��, ��� ��� �������� � �++, ����� �������� � ������ ��������� ���������������� ����� ����� ����������.

���������� "smart pointer"

        // ����� ������ ������ ���������
        template <typename T>
        class smart_pointer 
        {
            T *m_obj;
        public:
            // ������ ��� �� �������� ����� ������
            smart_pointer(T *obj)
                : m_obj(obj)
            { }
            // �� ������ �� ������� ��������� ���� ������ �� ���������
            ~smart_pointer() 
            {
                delete m_obj;
            }
            // ������������� ���������
            // ��������. ��������� ���������� � ������ ���� T ����������� "���������"
            T* operator->() { return m_obj; }
            // � ������� ������ ��������� �� ����� ������������ ��������� � �������� ������ ��
            // ������, ������� �� ������
            T& operator* () { return *m_obj; }
        }
        
        int test 
        {
            // ������ myClass �� �������� ������ ���������
            smart_pointer<MyClass> pMyClass(new MyClass(/*params*/);    
            // ���������� � ������ ������ MyClass ����������� ���������
            pMyClass->something();    
            // ��������, ��� ��� ������ ������ ���� ������� ������ ��� � ostream
            // ��� ������� ����� �� ���������� ������ �������� ������ �� ������,
            // ������� ������ ���� ������� �� �����
            std::cout << *pMyClass << std::endl;    
            // �� ������ �� ������ ������ MyClass ����� ������
         }

�������, ��� ��� smart pointer �� ����� ����������� (��������, ��� ������� � ��� ������?), �� �� � ������ ���� ��������� ������ RAII. �� ����� ���� ��� ��, ��� � ������� ��������� (��������� ������������� ����������), ������ ��� �� ����� ���������� �� ������������ ������: ��� ����� ������� �������������. �� ������� � ������������� ���������� ����� �������� const, ������������ ������������ ������, �� ������� ��������� ���������.

������, ���� �� ������, ��� ��������� ������������ ������������, ��� ������������� ����� ����������, ���������� �� ���������� ����������. ���� ��� �� �������� ��� ����, �� ��� �����, ���������� ������������ �� � �����-������ ����� ��������� ����������, ������, ��� ������ �����������.

����, ���� smart pointers:

    boost::scoped_ptr
    std::auto_ptr
    std::tr1::shared_ptr (�� �� std::shared_ptr � C++11, ���� boost::shared_ptr �� boost)


������� � "boost::scoped_ptr".

�� ��������� � ���������� "boost"

���������� ������� � ��������, ����������� ���������� �����, �� ����������� ������������, ���� �� ���: ���� ������� �� ����� ���� ���������� (�� ���� � ���� ��������� ����������� ����������� � �������� ������������). ������ �� �������:

        #include <boost/scoped_ptr.hpp>
        int test() 
        {
            boost::scoped_ptr<int> p1(new int(6));
            boost::scoped_ptr<int> p2(new int(1));    
            p1 = p2; // ������!
        }


��� � �������, ���� �� ���� ��������� ������������, �� � p1 � p2 ����� ��������� �� ���� � �� �� ������� ������. � �� ������ �� ������� ��� ��������. ��� �����? ����� �� �����. ��������������, ���� ������� ������ ���������� � � �������.
����� ����� �� �����? ������� ��������� ��� ��� ���������-������� ��� �����-���� ������, ������� ���������� ����������� � ������ ������� � ��������� � �����, ����� �������� ���� �� �������� ���� �� ������ ���������� ������� ��������.



������� �� "std::auto_ptr"

����-���� ���������� ������� �����������, � ���� �� �� ���� � ����������� ���������� (���� � C++11 ��� "deprecated"). � ���� ���� �������� ������������ � �����������-����������, �� �������� ��� ��������� ��������.
�������:

        #include <memory>
        int test() 
        {
            std::auto_ptr<MyObject> p1(new MyObject);
            std::auto_ptr<MyObject> p2;    
            p2 = p1;
        }


������ ��� ������������ � p2 ����� ������ ��������� �� MyObject (������� �� ��������� ��� p1), � � p1 �� ����� ������. �� ���� p1 ������ �������. ��� ��� ���������� ��������� �����������. ������, �������� ����������� ��������� ����� �� �������.
����� ��� �����? �� �������� � ��� ���� �������, ������� ������ ��������� �����-�� ������:

        std::auto_ptr<MyObject> giveMeMyObject();

��� ��������, ��� ������� ������� ����� ������ ���� MyObject � ������ ��� ��� � ������������. �������� ������, ���� ��� ������� ���� �������� ������ ������ (�������� Factory): �� �������, ��� ���� ����� (Factory) �� ������ � ���� ��� ���� ��������� �� ����� ������. ������ ��� � ��������� �� ���� ����.

� ���� ����� ��������� ��������� auto_ptr ������ ������������ � ����������� STL. 
�� � ��� ���� shared_ptr.


������� �� "std::shared_ptr" (�++11)

����� ��������� � ��������� ������. ��� ��� ������. ��� ������, ��� ���-�� ���� ����� ����������, ������� ������ ���������� ����������, ������� ��������� �� ������. ���� ��� ���������� ���������� ������ ����, �� ������ ������������. ������� ���������������� ��� ������ ������ ���� ��������� ����������� ���� ��������� ������������. ��� �� � shared_ptr ���� �������� ���������� � bool, ��� � ����� ���� ��� ��������� ��������� ����������, �� �������� �� ������������ ������.

        #include <memory> // ���� <tr1/memory> ��� ������������, ��� �� �������������� C++11
        #include <iostream>
        int test() 
        {
            std::shared_ptr<MyObject> p1(new MyObject);
            std::shared_ptr<MyObject> p2;    
            p2 = p1;    
            if (p2)
            {
                std::cout << "Hello, world!\n";
            }
        }

������ � p2 � p1 ��������� �� ���� ������, � ������� ������ ����� 2, �� ������ �� ������ ������� ����������, � ������ ������������. �� ����� ���������� ���� ��������� � �������:

        int test(std::shared_ptr<MyObject> p1) 
        {
            // ������ ���-��
        }

��������, ���� �� ��������� ��������� �� ������, �� ������� �� ����� ��������. �� ������ ���� �������, ��� ������ MyObject ����� ���, ���� ����� ����������� ������� test.

����, smart pointers ��� ������, �� ���� � ������.
��-������ ��� ��������� �������, �� � ����� � ��� �������� ��������� ������ ���������� ���� ������ ��������.
��-������ ��� boiler-plate, ��������

        std::tr1::shared_ptr<MyNamespace::Object> ptr = std::tr1::shared_ptr<MyNamespace::Object>(new MyNamespace::Object(param1, param2, param3))

��� �������� ����� ������ ��� ������ ��������, ��������:

        #define sptr(T) std::tr1::shared_ptr<T>

���� ��� ������ typedef.

�-�������, ���������� �������� ����������� ������. ������������� �� ����� �� ����, ����� �� ����������� ������. ��� �� �������� ���������������� boost::weak_ptr, boost::intrusive_ptr � ��������� ��� ��������.

������, smart pointers ���������� ������ ������� � ������ ������� � ����� "�++ for real programmers".

=============================================================
��������� �� ������������� ����� ���������� � C++
26 ������� 2018

��������� ������� ����������, ���� C++ ��������� ��������� �������� ������ ���������� � ��������� ������, �� ����� �� � ���� ����. ��� ���� ����� ������. ������ ������ �� ���� ������ � ������������ �������, ��� ����� ���� �������� ��� ����������. ������ ��������� ��������� ������ ��������. �������� ��� �������� ��� ������ ������������ � ������ RAII. �������, �������������� ���� ������ ���������� ������������� ��� ������������� ����������. �������� ��� ������������� �� �� ��� ������ ������, � ������ ��� ���������� � �������. �� ���� � ���� �������, � ����������� ���������� ����� ���� ����� ��������� (smart pointers), ����������� ������ ��� ����� ������. ��������� �� C++ � ���� �� ���������, �� ������ ������� ��������� ������ ������������� ����� ����������, � ����� � ��� ����� ��� ��������� ��������� ���������.

�����! 
� ������ ������� � ������� ����� ��������� ���������� auto_ptr. ���� ��� ����� ���������� �������� � C++, ����� � ����� ��� �� ���� move semantics. ��-�� ����� ������������� auto_ptr ����� ����� ��������� � ������� � ����������� �������. � ��������� C++17 auto_ptr ��� ������. ������� �������, ���, ��� �� ������ ����� �� auto_ptr � ��� ��, ��� ��� �� ������ ���� � ����������� ����. ������ ���� ������ ����������� unique_ptr.

1. unique_ptr
��������� ����� unique_ptr ������������ ����� ���������� ��������� �� ������. ��������� ������ ����������, �� ����� ���������� �������� �� � ������� std::move. ��� ����������� ��������� ������������� ���������� ���������� �������, �� ������� �� ���������.

��������� unique_ptr ���:

std::unique_ptr<SomeClass> unq(new SomeClass(/* ctor args */));

� �� ������ ���������� ������ make_unique, ��� ������:

auto unq = std::make_unique<SomeClass>(/* ctor args */);

����� unique_ptr ����������� �������� ->, ��� ��������� ���������� � ����� ������ � �������� ��� ������, ������ �� �������� � ������� ����������:

unq->sayHello();

��� ��� ����������, unique_ptr ��������� ����������:

// will not compile!
auto cpy = unq;

������ �������� �� ����� �������� ��� ������ std::move, ��������:

auto mov = std::move(unq);
// unq is invalid now!
mov->sayHello();

���� � �����, �� ������ ����� �������� �� unique_ptr ������� ��������� �� ������:

SomeClass* ptr = mov.get();
ptr->sayHello();

� ���� ��� � �������� code smell. ����� ����, ����� �� ������ ��������� ������ (reference) �� unique_ptr:

auto& ref = mov;
ref->sayHello();

�� ����, � ���� ������ �� ��� �� �� �������� �������� ��������, � ��������� ���������� ���, ��������� � ���� ����� ��� ��� �� ����� ���������.

���������, ��� unique_ptr ��������� ������� �������, ������� �� ����� �������� ������ �����������, ��� ���������� custom deleter. ��� ��������� ������������ unique_ptr � ���������, ������������ �� ��������� ��� ����� C, � ���� ����������� ������ defer �� ����� Go:

/* g++ custom-deleter.cpp -o custom-deleter */

#include <memory>
#include <functional>
#include <iostream>
#include <stdio.h>

template<typename T>
using auto_cleanup = std::unique_ptr<T,std::function<void(T*)>>;

static char dummy[] = "";

#define _DEFER_CAT_(a,b) a##b
#define _DEFER_NAME_(a,b) _DEFER_CAT_(a,b)
#define defer(...) \
  auto _DEFER_NAME_(_defer_,__LINE__) = \
    auto_cleanup<char>(dummy, [&](char*) { __VA_ARGS__; });

int main() 
{
    auto_cleanup<FILE> f(
        fopen("test.txt", "w"),
        [](FILE* f) { fclose(f); }
    );

    defer( std::cout << "Bye #1" << std::endl );
    defer( std::cout << "Bye #2" << std::endl );

    fwrite("Hello!\n", 7, 1, f.get());
}

��������, ��� � ������� "defer" ��� �������� �������� � unique_ptr ��������� ���������. ���� �� �� �������� nullptr, custom deleter �� ��� �� ������.

�����! 
���� � ����� ��������� �� ������� ������� �� ������ ��������, �� ������� ������� custom deleter, ���������� ��� ����� ������� delete[] ������ delete. ���� ����� �� �������, ����� ���������� ������ ������ ������ �� �������, ��������� �� ������.

2. shared_ptr � weak_ptr

����� shared_ptr �������� �������� �� ������, ������� ������� ����� ��������� ��������. ��������� ����� ��� ����������, ��� � ����������. ����� ������������ ���������� ������������� ��� ������ �������� ������. ����� ������� ������ ����������, ���������� ���������� �������. ��� �� ���� shared_ptr �������� thread-safe, �� �� �� ������ ���������� ������� thread-safe ������, �� ������� ���������. �� ����, ���� ������ � ������� ����� �������������� �� ���������� �������, �� ������ �� ������ ������������� � ��� �������� ��� ���-�� �����.

��� �������� shared_ptr ������ ������������ ������ "make_shared":

auto ptr = std::make_shared<SomeClass>(/* ctor args */);

� ��������� ������ � ��� ���� ���������� �� ������ � unique_ptr, �� ��� �����������, ��� shared_ptr ����� ����� ����������.

���������� ������ ��� ������������� shared_ptr ����������� � ���, ��� � ��� ������� ����� ������� ����������� ������. ��������, ���� ��� �������. ������ ��������� ��� ������ shared_ptr �� ������, � ������ � �� ������. ���� ���� �� �� ���� �� �������� ��� ������ ������, �������� ������ ������� �� ���������, � ������� ������� �� ����� ����������.

��� �������� ��������� ��� ������ weak_ptr, ��� ����������� ������� ���������. ����� weak_ptr ����� �� shared_ptr, �� �� ��������� � �������� ������. ����� � weak_ptr ���� ����� lock(), ������������ ��������� shared_ptr �� ������. ������ �������������:

#include <memory>
#include <iostream>

class SomeClass 
{
public:
    void sayHello() 
    {
        std::cout << "Hello!" << std::endl;
    }

    ~SomeClass() 
    {
        std::cout << "~SomeClass" << std::endl;
    }
};

int main() 
{
    std::weak_ptr<SomeClass> wptr;

    {
        auto ptr = std::make_shared<SomeClass>();
        wptr = ptr;

        if(auto tptr = wptr.lock()) 
        {
            tptr->sayHello();
        } 
        else 
        {
            std::cout << "lock() failed" << std::endl;
        }
    }

    if(auto tptr = wptr.lock()) 
    {
        tptr->sayHello();
    }
    else 
    {
        std::cout << "lock() failed" << std::endl;
    }
}

��������� �������:

Hello!
~SomeClass
lock() failed
����� ������ � weak_ptr ��� �� ���������, ����������� �������� ��������� �������� ��������. ���� ����� ����������, ���� ��� ���������� ��������� �� ������ ���������� ������������, � ��������� ������ ���������, ���������� ��� ������ ������ lock() ������ weak_ptr, ������ ��������� ���� �������������. �� ����� ��������� ������ �����, ����� �� ������ �� ��������� ������ ������� ����������.

3. ����� ��������� � ������������
������, � ������� ����� �������� � ��� ���������� ����� ���������� ����� � ���� �� �������� �������. ��� shared_ptr � ����������� ���������� ���� ������� static_pointer_cast, dynamic_pointer_cast � ������. ��� unique_ptr ����� �� �������� ������-�� �� �������, �� �� �������� ����� �� StackOverflow.

������ ����:

#include <memory>
#include <iostream>

// https://stackoverflow.com/a/21174979/1565238
template<typename Derived, typename Base, typename Del>
std::unique_ptr<Derived, Del> 
static_unique_ptr_cast( std::unique_ptr<Base, Del>&& p )
{
    auto d = static_cast<Derived *>(p.release());
    return std::unique_ptr<Derived, Del>(d,
        std::move(p.get_deleter()));
}

template<typename Derived, typename Base, typename Del>
std::unique_ptr<Derived, Del> 
dynamic_unique_ptr_cast( std::unique_ptr<Base, Del>&& p )
{
    if(Derived *result = dynamic_cast<Derived *>(p.get())) 
    {
        p.release();
        return std::unique_ptr<Derived, Del>(result,
            std::move(p.get_deleter()));
    }
    return std::unique_ptr<Derived, Del>(nullptr, p.get_deleter());
}

class Base 
{
public:
    Base(int num): num(num) {};

    virtual void sayHello() 
    {
        std::cout << "I'm Base #" << num << std::endl;
    }

    virtual ~Base() 
    { 
        std::cout << "~Base #" << num << std::endl;
    }

protected:
    int num;
};

class Derived: public Base 
{
public:
    Derived(int num): Base(num) {}

    virtual void sayHello() 
    {
        std::cout << "I'm Derived #" << num << std::endl;
    }

    virtual ~Derived()
    { 
        std::cout << "~Derived #" << num << std::endl;
    }
};

void testUnique() 
{
    std::cout << "=== testUnique begin ===" << std::endl;

    auto derived = std::make_unique<Derived>(1);
    derived->sayHello();

    std::unique_ptr<Base> base = std::move(derived);
    base->sayHello();

    auto derived2 = static_unique_ptr_cast<Derived>(std::move(base));
    derived2->sayHello();

    std::unique_ptr<Base> base2 = std::make_unique<Derived>(2);
    base2->sayHello();

    std::cout << "=== testUnique end ===" << std::endl;
}

void testShared() 
{
    std::cout << "=== testShared begin ===" << std::endl;

    auto derived = std::make_shared<Derived>(1);
    derived->sayHello();

    auto base = std::static_pointer_cast<Base>(derived);
    base->sayHello();

    auto derived2 = std::static_pointer_cast<Derived>(base);
    derived2->sayHello();

    std::shared_ptr<Base> base2 = std::make_shared<Derived>(2);
    base2->sayHello();

    std::cout << "=== testShared end ===" << std::endl;
}

int main() 
{
    testUnique();
    testShared();
}

��� ������, ��� ��������� �� ��� �� � ������.

����������
�� ���� ��������������, ����������� ��������� ������ ������� � ~99% �������� �����. � ���������� �� 1% ������� ��� ������� ������������ �� cppreference.com. �������, � �� ������� ���� C++, � ������ ��� � ���-�� ������ ��� ����-�� �� ������. ��� ���, ���� �� ������ � ����������� ������ �����-���� ������, ��� ��� ����, ��� � ���� ��������, �� ����������� ��������������� �������������!
