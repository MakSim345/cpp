Ставим объекты на поток
- паттерн фабрика объектов.

http://habrahabr.ru/blogs/cpp/129202/

Я хочу поделиться знаниями об одном из наиболее часто используемых мною паттернов — фабрики объектов, для данного паттерна так же подходит другое название — виртуальный конструктор.

"Что представляет из себя этот паттерн?"

Исходя из названия легко догадаться, что это некая, определенная, фабрика (или завод), который создает объекты. Еще раз выражу слово определенная. Как и в реальной жизни фабрика имеет некую специализацию, создавая товары или устройства какого-либо определенного типа. И фабрика, которая выпускает, например, мебель, не может производить, например, еще и компоненты для смартфонов. По аналогии с программированием фабрика объектов может создавать только объекты определенного типа, которые используют единый интерфейс. Самыми главными преимуществами данного паттерна в С++, является упрощение создания объектов различных классов, использующих единый интерфейс. Зачастую библиотекам, которые разрабатывают программисты нужно не только уметь работать с определенными объектами, но и создавать их. Самый очевидный пример загрузка файлов различных форматов. Мы не знаем, какой файл мы будем загружать заранее, но у нас есть список возможных форматов. Пользователь указывает файл, библиотека пытается определить тип файла и вызвать соответствующий загрузчик для него. В большинстве случаев программисты использует конструкции типа switch или if, чтобы определить экземпляр какого класса им необходимо создать. И чем больше возможных вариантов появляется, тем больше разрастается эта конструкция, в последствии превращающиеся в уродливого монстра.

"Что нам может предложить фабрика объектов?"
Во-первых, простой метод создания объектов, который сократит switch/if до 1ой строчки.
Во-вторых, удобные методы для работы с объектами фабрики. Мы всегда точно можем узнать, зарегистрирован ли у нее определенный класс, количество зарегистрированных классов, а так же удобные методы для добавления и удаления экземпляров классов в фабрику. С помощью фабрики можно ограничивать набор возможных классов, которая она будет создавать, используя некую конфигурацию.


Создание конкретной фабрики

Для начала, реализуем конкретную фабрику, не используя шаблоны, чтобы понять как же она должна работать.
Итак, нам нужен класс, который сможет создавать объекты, поддерживающие единый интерфейс. Назовем этот интерфейс Foo, а фабрику соответственно FooFactory. В качестве идентификатора для создания объекта возьмем строку.

сlass FooFactory
{
public:
    FooFactory();
    ~virtual FooFactory();

    Foo * create(const std::string & id) const;   
};


И так, пока все отлично, но и написано всего пара строк кода. А как же мы будем добавлять классы и собственно создавать их экземпляры?

Разберем проблемы по порядку. Прежде чем создать объект, нужно добавить класс в фабрику. Очевидно, что нужна какая-та функция. Но как передать в функцию класс, а не объект?

Как вариант, можно использовать стратегию клонирования. То есть создавать объект, помещать его в фабрику, а при вызове метода фабрики create вызывать функцию типа clone(). Вариант прямо скажем плохой, который заставляет программиста мало того что добавлять в интерфейс Foo функцию clone, и реализовывать ее во всех конкретных классах. И к тому же при добавлении объекта в фабрику нам нужно будет его создавать — то есть выделять для объекта память. А объекты могут быть достаточно тяжелыми. 

Да конечно, в современном мире проблема памяти/производительности стоит не так остро, но С++ такой язык, который позволяет оптимизировать как и высокоуровневые конструкции, так и низкоуровневые и почему бы этим не пользоваться.

Еще один вариант, при добавлении класса в фабрику передавать в метод указатель на функцию, которая будет создать объект нужно типа. В таком случае возникает еще больше проблем, чем в предыдущим варианте. Нужно будет реализовывать данную функцию для каждого создаваемого конкретного класса, а при добавлении класса в фабрику передавать эту функции как параметр. Можно конечно сделать макросы, но выглядеть это будет очень не красиво, не говоря уже о том, что многие считают, что макросы в С++ — зло.

Но зато, у С++ есть шаблоны, которые и помогут решить эту не простую задачу. Для создания объектов типа Foo мы будем использовать другие объекты, вспомогательные, которые возьмут на себя работу по созданию объектов нужного нам класса. В простонародье такие классы называют creator или instantiator. Создается абстрактный класс creator, у которого обычно есть только один метод — создание объекта определенного интерфейса, в текущем варианте объекты типа Foo. А на его основе уже создаются конкретные классы creator'ы. Благодаря абстрактному классу creator, мы можем хранить набор конкретных creator'ов в любом контейнере. В данном случае шаблоны исполнят роль макросов, позволяя генерировать код для конкретного creator'а на основе параметра шаблона.

Абстракный класс для создания объектов типа "Foo":

class abstractFooCreator
{
public:
    virtual fooCreator() {}
    virtual Foo * create() const = 0;
};


И шаблонный класс, в котором будет генерироваться собственно код для создания объекта конкретного класса:

template <class C>
class fooCreator : public abstractFooCreator
{
public:
    virtual Foo * create() const { return new C(); }
};


Таким образом мы уже можем написать наш шаблонный метод для добавления класса в фабрику. Единственное, что нам нужно уже выбрать контейнер для хранения наших creator'ов. Очевидным выбором будет std::map.

typedef std::map<std::string, abstractFooCreator*> FactoryMap;
FactoryMap _factory;

template <class C>
void add(const std::string & id)
{
    typename FactoryMap::iterator it = _factory.find(id);
    if (it == _factory.end())
        _factory[id] = new fooCreator<C>();
}


Теперь у нас появился первый рабочий вариант фабрики, в которую можно добавлять классы поддерживающие интерфейс Foo.

Ну и собственно наша 2-ая проблема, а именно создания объектов нужного типа, практически уже решена, так как по сути она зависела только от того каким образом мы будем хранить creator'ы.

void Foo * create(const std::string & id) const
{
    typename FactoryMap::iterator it = _factory.find(id);
    if (it != _factory.end())
        return it->second->create();
    return 0;
}


Соберем весь код, чтобы увидеть полную картину.

class abstractFooCreator
{
public:
    virtual fooCreator() {}
    virtual Foo * create() const = 0;
};

template <class C>
class fooCreator : public abstractFooCreator
{
public:
    virtual Foo * create() const { return new C(); }
};

сlass FooFactory
{
protected:
    typedef std::map<std::string, abstractFooCreator*> FactoryMap;
    FactoryMap _factory;

public:
    FooFactory();
    ~virtual FooFactory();

    template <class C>
    void add(const std::string & id)
    {
        typename FactoryMap::iterator it = _factory.find(id);
        if (it == _factory.end())
            _factory[id] = new fooCreator<C>();
    }

    Foo * create(const std::string & id)
    {
        typename FactoryMap::iterator it = _factory.find(id);
        if (it != _factory.end())
            return it->second->create();
        return 0;
    }
};


Ну и небольшой пример, как данную фабрику использовать. Добавление классов в фабрику:

    FooFactory factory;
    factory.add<MyFoo>("MyFoo");
    factory.add<MyFoo2>("MyFoo2");
    factory.add<ImprovedFoo>("ImprovedFoo");

Создание объекта с помощью фабрики:

    Foo * p = factory.create("MyFoo2");


Вот так просто с помощью фабрики можно управлять созданием объектов, поддерживающих единый интерфейс.

Создание шаблонной фабрики

Ну, а теперь создадим, на основе этого конкретного примера, вполне конкретный паттерн.

Что нужно нашей фабрике, чтобы удовлетворять наши возможности? Конечно, это задание типа идентификатора, который можем быть как и enum'ом, так и "std::string" или любым другим типом подходящим для идентификатора. Второе — это собственно тип объектов, которые мы будем создавать, роль которого в примере выше исполнял класс Foo.

template <class Base, class IdType>
class ObjectFactory
{
public:
    ObjectFactory() {}
    virtual ~ObjectFactory();

    template <class C>
    void add(const IdType & id);

    Base * create() const;
};

Вот так будет выглядеть наша шаблонная фабрика.

Приступим к ее реализации. Как и в примере с Foo, нам нужно решить проблему создания объектов конкретного типа. То есть нам нужен абстрактный класс, у которого есть метод для создания объекта типа Base, и конкретный creator класс, который наследует этот абстрактный класс и реализует этот метод, используя шаблонный параметр.

template <class Base>
class AbstractCreator
{
public:
    AbstractCreator() {}
    virtual ~AbstractCreator(){}
    virtual Base* create() const = 0;
};

template <class C, class Base>
class Creator : public AbstractCreator<Base>
{
public:
    Creator() { }
    virtual ~Creator()     {}
    Base * create() const { return new C(); }
};


Ну, а теперь нужно лишь использовать эти классы в нашей фабрике.

template <class Base, class IdType>
class ObjectFactory
{
protected:
    typedef AbstractCreator<Base> AbstractFactory;
    typedef std::map<IdType, AbstractFactory*> FactoryMap;
    FactoryMap     _factory;

public:
    ObjectFactory() {}
    virtual ~ObjectFactory();

    template <class C>
    void add(const IdType & id)
    {
        registerClass(id, new Creator<C, Base>());
    }

protected:
    void registerClass(const IdType & id, AbstractFactory * p)
    {
        typename FactoryMap::iterator it = _factory.find(id);
        if (it == _factory.end())
            _factory[id] = p;
        else
            delete p;
    }
};


Что существенного добавилось по сравнению с примером Foo? Конечно же это метод registerClass, который в качестве параметра принимает объект типа AbstractFactory, который, в свою очередь, умеет создавать объекты того класса, который мы указываем как шаблонный параметр для метода add.

Добавляем возможность задания поведения фабрики

Опущу, пока что создание остальных простых методов, таких как проверка существование нужного класса в фабрике, их количество и удаление — полный листинг можно посмотреть в конце. Я же предлагаю сделать фабрику еще более гибкой. Ведь помимо того что мы задаем для фабрики тип идентификатора и базовый класс, интерфейс которого должны реализовывать помещаемые в фабрику классы, можно еще добавить настройку поведения нашей фабрики в случае определенных ошибок. Что делать если запрашиваемого типа нет в фабрики при создании? Возвращать нуль или бросать исключение? Что делать при попытке удаления несуществующего класса или при попытке добавить в фабрику уже зарегистрированный объект? Чтобы уметь изменять поведение фабрики нам нужно использовать другой паттерн проектирования — стратегия, так же известного под именем политика. Данный паттерн очень хорошо освещен в книге А.Александреску «Современное проектирование на С++».

В проектах, которые я поддерживаю необходимо, пока что, только 2 поведения. Отсутствие реакции при ошибке, и выбрасывание исключение особого типа, используемых в моих проектах. Единственным параметром, который нужен для отладки и вообще для детального описания ошибки — это идентификатор, который мы передаем в функции создания, удаления итд. Таким образом интерфейс нашей политики должен выглядеть приблизительно так:

template <class Base, class Type>
class ObjectFactoryIgnoreErrorPolicy
{
public:
    Base * onCreateFailed(const Type & type) const
    {
        return 0;
    }
    void onRemoveFailed(const Type & type) {}
    void onDuplicateRegistered(const Type & type) {}
};


Помимо собственно самих функций реализующих поведение, для класса политики нужны так же и тип интерфейса, который реализует фабрика и тип идентификатора для которого произошла ошибка и который передается во все методы. По аналогии c IgnoreErrorPolicy приведу в пример так же политику, которая выбрасывает исключение в случае ошибки.

class ObjectFactoryException : public std::exception
{
    std::string     _msg;
public:
    ObjectFactoryException(const std::string & msg) throw() : _msg(msg) {}
    virtual ~ObjectFactoryException() throw() {}
  
    virtual const char * what() const throw()
    {
        return _msg.c_str();
    }
};

template <class Base, class Type>
class ObjectFactoryThrowExceptionErrorPolicy
{
public:
    std::string generateMessage(const char * msg, const Type & type) const
    {
        std::stringstream strm;
        strm << msg << ", requested type id : " << type;
        return strm.str();
    }

    Base * onCreateFailed(const Type & type) const
    {
        throw ObjectFactoryException(generateMessage("ObjectFactory - can't create object (not registered)", type));
    }

    void onRemoveFailed(const Type & type)
    {
        throw ObjectFactoryException(generateMessage("ObjectFactory - can't remove class (not registered)", type));
    }
  
    void onDuplicateRegistered(const Type & type)
    {
        throw ObjectFactoryException(generateMessage("ObjectFactory - class already registered", type));
    }
};


Теперь встроим нашу политику в фабрику. Это можно сделать несколькими способами — просто наследоваться от класса политики, или использовать класс политики как атрибут фабрики. В обоих случаях единственная проблема в том, каким образом из класса фабрики задавать шаблонные параметры для класса политики. В этом нам поможет замечательная особенность С++ — шаблонные шаблонные параметры. Когда при объявлении класса фабрики указываем что мы хотим передать в качестве параметра не просто какой-то класс, а шаблонный класс. Выглядеть это будет вот так:

template <class Base, class IdType, template <class, class> class ObjectFactoryErrorPolicy = ObjectFactoryIgnoreErrorPolicy >
class ObjectFactory : public ObjectFactoryErrorPolicy<Base, IdType>
{
…


В качестве 3-го параметра указывается template <class, class> class …
Так же сразу же для этого параметра задается политика по умолчанию. Если необходимо задать другую политику, то при typedef фабрики нужно указать ей в качестве последнего параметра имя класса с необходимой политикой, например:

typedef ObjectFactory<Foo, FooType, ObjectFactoryThrowExceptionPolicy> FooFactory;


В моем случае я намного чаще использую политику игнорирования ошибок, поэтому и установил ее как параметр по умолчанию. Можно пойти еще дальше и сделать политику динамической, с возможностью изменять ее во время выполнения, но для меня на данный момент это не является актуальным и пока что в моей небольшой практике такой механизм не требовался. Собственно по этому я и выбрал метод наследования от класса политики, а не использование ее как атрибута фабрики.

Листинг


Ну, а теперь самое время подвести итоги и представить полный листинг паттерна с моей реализацией.

#include <map>
#include <string>
#include <memory>
#include <sstream>

namespace grs
{

/*
    Прокси классы, для генерации кода для создания объектов
*/

template <class Base>
class AbstractCreator
{
public:
    AbstractCreator()
    {
    }

    virtual ~AbstractCreator()
    {
    }

    virtual Base* create() const = 0;

private:
    AbstractCreator(const AbstractCreator&);
    AbstractCreator& operator = (const AbstractCreator&);
};


template <class C, class Base>
class Creator : public AbstractCreator<Base>
{
public:
    Creator()
    {
    }

    virtual ~Creator()        
    {
    }

    Base * create() const
    {
        return new C();
    }
};

/*
    Политики для фабрики
*/

class ObjectFactoryException : public std::exception
{
    std::string     _msg;
public:
    ObjectFactoryException(const std::string & msg) throw() : _msg(msg) {}
    virtual ~ObjectFactoryException() throw() {}
  
    virtual const char * what() const throw()
    {
        return _msg.c_str();
    }
};

template <class Base, class Type>
class ObjectFactoryIgnoreErrorPolicy
{
public:
    Base * onCreateFailed(const Type & type) const
    {
        return 0;
    }
    void onRemoveFailed(const Type & type)
    {
    }
    void onDuplicateRegistered(const Type & type)
    {
    }
};

template <class Base, class Type>
class ObjectFactoryThrowExceptionErrorPolicy
{
public:
    std::string generateMessage(const char * msg, const Type & type) const
    {
        std::stringstream strm;
        strm << msg << ", requested type id : " << type;
        return strm.str();
    }

    Base * onCreateFailed(const Type & type) const
    {
        throw ObjectFactoryException(generateMessage("ObjectFactory - can't create object (not registered)", type));
    }

    void onRemoveFailed(const Type & type)
    {
        throw ObjectFactoryException(generateMessage("ObjectFactory - can't remove class (not registered)", type));
    }
  
    void onDuplicateRegistered(const Type & type)
    {
        throw ObjectFactoryException(generateMessage("ObjectFactory - class already registered", type));
    }
};

/*
    Фабрика
*/

template <class Base, class IdType = int, template <class, class> class ObjectFactoryErrorPolicy = ObjectFactoryIgnoreErrorPolicy >
class ObjectFactory : public ObjectFactoryErrorPolicy<Base, IdType>
{
protected:
    typedef AbstractCreator<Base> AbstractFactory;
    typedef std::map<IdType, AbstractFactory*> FactoryMap;

public:
    ObjectFactory()
    {
    }

    virtual ~ObjectFactory()
    {
        for (typename FactoryMap::iterator it = _map.begin(), endIt = _map.end(); it != endIt; ++it)   
            delete it->second;
    }

    Base * create(const IdType & id) const
    {
        typename FactoryMap::const_iterator it = _map.find(id);
        if (it != _map.end())
            return it->second->create();
        return onCreateFailed(id);
    }

    template <class C>
    void add(const IdType & id)
    {
        registerClass(id, new Creator<C, Base>);
    }

    void remove(const IdType & id)
    {
        typename FactoryMap::iterator it = _map.find(id);
        if (it != _map.end())
        {
            delete it->second;
            _map.erase(it);
        }
        else
            onRemoveFailed(id);
    }

    bool isRegistered(const IdType & id) const
    {
        return _map.find(id) != _map.end();
    }

    size_t size() const
    {
        return _map.size();
    }
  
  
protected:
    void registerClass(const IdType & id, AbstractFactory * pAbstractFactory)
    {
        std::auto_ptr<AbstractFactory> ptr(pAbstractFactory);
        typename FactoryMap::iterator it = _map.find(id);
        if (it == _map.end())
            _map[id] = ptr.release();
        else
            onDuplicateRegistered(id);
    }

private:
    ObjectFactory(const ObjectFactory&);
    ObjectFactory& operator = (const ObjectFactory&);   

    FactoryMap _map;
};

}     // end of grs namespace



И небольшой пример использования фабрики:

#include "ObjectFactory.h"
#include <iostream>

enum Type
{
    fooType,
    barType,
    maskedType,
    unknownType,
    firstType = fooType,
    lastType = maskedType,
};

std::ostream & operator << (std::ostream & strm, const Type & type)
{   
    const char * names[] = {"foo", "bar", "masked"};
    if (type < firstType || type > lastType)
        return strm << "unknown type(" << int(type) << ")";   
    return strm << names[type];   
};

class Base
{
public:
    virtual ~Base() {}
    virtual Type type() const = 0;
};

class Foo : public Base
{
public:
    virtual Type type() const { return fooType; }
};

class Bar : public Foo
{
public:
    virtual Type type() const { return barType; }
};

class MaskedFoo : public Foo
{
public:
    virtual Type type() const { return barType; }
};

typedef grs::ObjectFactory<Base, Type> TypeFactory;

void checkType(TypeFactory & factory, Type type)
{
    std::auto_ptr<Base> p;
    p.reset(factory.create(type));
    std::cout << "Object with type : " << type;
    if (p.get())
    {
        if (type == p->type())   
            std::cout << " - successfully created\n";
        else
            std::cout << " - created, but type mismatch\n";
    }
    else
        std::cout << " - create failed\n";
}

int main()
{   
    TypeFactory factory;
    factory.add<Foo>(fooType);
    factory.add<Bar>(barType);
    factory.add<MaskedFoo>(maskedType);
  
    checkType(factory, fooType);
    checkType(factory, barType);
    checkType(factory, maskedType);
    checkType(factory, unknownType);
  
    return 0;
}


Так же вместе с примером паттерн можно скачать отсюда.

На этом — все. Хорошего и креативного кодинга!

Ссылки

Если вас заинтересовали шаблоны проектирования, советую обратить внимание на эти книги. В книге А.Александреску очень хорошо переданы особенности синтаксиса С++ при работе с шаблонами. А в книге банды 4-х можно найти все самые популярные паттерны, используемые во многих языках программирования.

