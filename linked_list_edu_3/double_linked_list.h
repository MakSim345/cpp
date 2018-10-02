#include <iostream>
using namespace std;
//Описание узла списка.

struct Node
{
    int d;
    Node *next;
    Node *prev;
    Node():next(NULL),prev(NULL), d(-332215) {}
    Node(Node* ptr_n, Node *ptr_p , int data): next(ptr_n),prev(ptr_p), d(data) {}
};


//Функции для работы со списком.
//--------------------------------------------------------
Node * Create(int data);                 //создает список.
int add(Node**const pend , int data);    //добавить в конец списка.
int pop(Node**const pbeg);               //выборка  из начала списка.

//полная выборка.
void Update(Node **const pbeg ){ while(*pbeg)pop(pbeg); }

void ShowE(Node *pend);                  //показать с конца.
void ShowB(Node *pbeg);                  //показать с начала.
/*выводить в зависимости от того: какой указатель передан: на конец или начало. для кольцевых не работает. */
void Show(Node *ptr);
//--------------------------------------------------------
int main()
{

    Node *pbeg = NULL;     //на начало списка.
    Node *pend = NULL;     //на конец  списка.
    int numb;
    cout<<"Input numb\t"; cin>>numb;
    pend = Create(numb);    //создаем   список.
    pbeg = pend;

    int i = 0;
    while(i<10)
    {
        cout<<"Input numb\t"; cin>>numb;
        add(&pend,numb);
        i++;
    }
    Show(pend);
    Show(pbeg);
    Update(&pbeg);
    return 0;
}

//создает список.
Node* Create(int data)
{
    Node *pv = new Node(NULL, NULL, data);
    return pv;
}

//добавить в конец списка.
int add(Node**const pend , int data)
{
    Node *pv = new Node(NULL, *pend, data);
    (*pend)->next = pv;
    (*pend) = pv;
    return 0;
}

//выборка  из начала списка.
int pop(Node**const pbeg)
{
    Node *tmp = (*pbeg);
    if(tmp)
    {
        int d = tmp->d;
        (*pbeg)=(*pbeg)->next;
        delete tmp;
        return d;
    }
    return -1;
}

//показать с конца.
void ShowE(Node *pend)
{
    while(pend)
    {
        cout << pend->d << ' ';
        pend = pend->prev;
    } cout<<endl;
}
//показать с начала.
void ShowB(Node *pbeg)
{
    while(pbeg)
    {
        cout<<pbeg->d<<' ';
        pbeg = pbeg->next;
    }
    cout<<endl;
}

/*выводить в зависимости от того: какой указатель передан: на конец или начало. для кольцевых не работает. */
void Show(Node *ptr)
{
    //Выводим список с конца. если:
    if((ptr->next == NULL)&&(ptr->prev!=NULL))
    {
        while(ptr)
        {
            cout<<ptr->d<<' ';
            ptr=ptr->prev;
        }
        cout<<endl; return;
    }
    //Выводим сначала если
    if((ptr->next != NULL)&&(ptr->prev==NULL))
    {
        while(ptr)
        {
            cout<<ptr->d<<' ';
            ptr=ptr->next;
        }
        cout<<endl; return;
    }
    return ;
}



// ----------------------
//
#include <iostream.h>

/*Ниже приведена программа,которая формирует стек из пяти целых чисел (1,2,3,4,5)
и выводит его на экран. Функция помещения в стек по традиции называется push,а выборки pop.
Указатель для работы со стеком(top) всегда ссылается на его вершину.*/

//Структура - элемент стека
struct Node
{
    int d;         //данные элемента структуры
    Node *p;       //Указатель для связи между структурами такого же типа
};

//-----------------------------
Node *first(int d);            //Формирование первого элемента(new)
void push(Node **top,int d);   //Добавление в стек (new)
int pop(Node **top);           //Выборка из стека  (delete)
//-----------------------------

//Главная функция
int main()
{
    Node *top=NULL;          //Начальная инициализация указателя-вершины нулевым адресом .
    top=first(1);            //Создание первого элемента стека

    for(int i=2;i<6;i++)
        push(&top,i); //Добавление в стек четырёх элементов

    while(top)            //Цикл вывода на экран значений элементов стека,и удаление их из памяти.
    {                     //Цикл длится пока на вершину(в указатель top) не попадёт нулевой адрес.
        cout<<'\n';           //Переход на следующую строку в консоли.
        cout<<pop(&top)<<' '; //Вывод значений возвращаемых функцией pop(...)
    }
    cout<<'\n';           //Переход на следующую строку в консоли.
    return 0;       //Возвращаем,что всё норм.
}

//------------------------------
//Начальное формирование стека
Node *first(int d)
{
    Node *pv=new Node;   //Создаём элемент: структура.
    pv->d=d;             //Присваиваем полю данных значения.
    pv->p=0;             //Первый элемент даёт признак конца стека NULL нужно при выборке.
    cout << pv->d << ' ';//Выводи значение поля структуры. Это тоже можно убрать.
    return pv;           //Возвращаем адрес структуры.
}

//Занесение в стек
void push(Node **top,int d)
{
    Node *pv = new Node;         //Создаём элемент: структура.
    pv->d = d;                   //Присваиваем полю данных значения.
    pv->p = *top;                //Созданный Элемент. Связыва-ся с элементом,который сейчас на Вершине
    *top = pv;                   //Созданный Элемент: помещ-тся на вершину стека вместо старой вершины
    cout << (*top)->d << ' ';      //Выводится значение Созданного элемента Этот момент можно убрать.
}

//Выборка из стека
int pop(Node **top)
{
    int temp=(*top)->d;        //Получаем значение элемента из вершины.
    Node *pv = *top;             //Получаем адрес елемента из вершины.
    (*top) = (*top)->p;            //В вершину помещаем новый элемент.
    delete pv;                 //Удаляем старую вершину.
    return temp;               //Возвращаем значение элемента из старой вершины.
}


