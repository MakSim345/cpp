25 июля 2020 в 01:32

"Пишем простую систему регистрации и входа в аккаунт"

Всем привет! Сегодня мы напишем простейшую систему входа и регистрации аккаунта. Данные мы будем хранить в файле. Здесь не будет базы данных, и подобных систем. Заранее говорю, не советую использовать этот код для больших проектов, т.к любой пользователь может открыть файл, и вписывать случайные данные, тем самым попасть в чужой аккаунт. И так, приступим.

PS: Целый код будет в конце.

Подключаем библиотеку fstream и iostream.

#include<iostream>
#include<fstream>
using namespace std;

Создаем класс Password, затем 2 функции, первую функцию я назвал Entrance, то есть вход, а вторую Sign_Up, то есть регистрация.


class Password
{
public:

    int Entrance()
    {

    }
    int Sign_up()
    {

    }
};

Начнем со второй функции (Sign_up).
Создаем 2 переменные типа "string". Первую я назвал "login", а вторую "password". В них мы пишем название файла и его расширение. Как пример, я написал в переменную "login" название "login.txt", а в "password": "password.txt". 

Также создаем 2 переменные "fstream": Первую я назвал "log", а вторую "pass".

string login = "login.txt";
string password = "password.txt";

fstream log;
fstream pass;

Далее пишем логику создание/открытие файла. Ниже опишу код.


log.open(login, fstream::in | fstream::out | fstream::app);
pass.open(password, fstream::in | fstream::out | fstream::app);

Сверху мы создаем/открываем файл, затем, после переменной, мы подключаем чтение, запись, и сохранение текста в файл. Далее делаем проверку, создался/открылся ли наш файл.


if (!log.is_open() && !pass.is_open())
{
    cout << "Ошибка!" << endl;
}
else
{

}

Если все прошло без ошибок, то мы идем в else. Далее мы создаем 2 переменные типа "string". Они будут хранить данные, которые ввел пользователь, они нам будут нужны для записи в файл.
Затем говорим пользователю, чтобы он ввел свой логин и пароль.

string log_cheker;
string pass_cheker;
cout << "Введите логин: "; cin >> log_cheker;
cout << endl;
cout << "Введите пароль: "; cin >> pass_cheker;

Далее мы записываем в файлы данные, которые ввел пользователь.

log << log_cheker;
pass << pass_cheker;
cout << "Регистрация прошла успешно!" << endl;

Всё! С регистрацией закончили, переходим ко входу. В первую функцию ("Entrance") мы можем скопировать немного кода со второй, чтобы поменьше тратить время.

string login = "login.txt";
string password = "password.txt";

fstream log;
fstream pass;

log.open(login, fstream::in | fstream::out | fstream::app);
pass.open(password, fstream::in | fstream::out | fstream::app);

if (!log.is_open() && !pass.is_open())
{
    cout << "Ошибка!" << endl;
}
else
{
    string log_cheker;
    string pass_cheker;
}

Далее мы будем считывать данные с файла, который мы указали в переменную login и password.
Делать мы будем это с помощью цикла while.


while (!log.eof()) //Пока не закончатся символы, идем по циклу.
{
    log_cheker = "";
    log >> log_cheker; //Передаем данные с файла в переменную.
}
while (!pass.eof()) //Пока не закончатся символы, идем по циклу.
{
    pass_cheker = "";
    pass >> pass_cheker; //Передаем данные с файла в переменную.
}

Далее мы создаем ещё 2 переменные типа string. Они нам нужны для проверки данных, которые введет пользователь. Первую переменную я назвал login_correct, а вторую pass_correct.


string login_correct;
string pass_correct;

Далее просим пользователя ввести логин и пароль, и делаем проверку. Ниже опишу подробней.


cout << "Введите свой логин: "; cin >> login_correct;
cout << endl;
cout << "Введите свой пароль: "; cin >> pass_correct;

if (login_correct != log_cheker && pass_correct != pass_cheker)
{
    cout << "Пароль или логин введен не правильно!" << endl;
}
else
{
    cout << "Данные введены верно!" << endl;
}

Теперь подробней. Мы просим пользователя ввести логин и пароль, далее идет проверка, на то, совпадают ли данные пользователя, с теми, которые мы считали с файлов, если да, то пишем "Данные введены верно", а если нет, то выводим "Пароль или логин введен не верно". Ну и теперь давайте сделаем мини меню, чтобы опробовать нашу программу. Создаем новый класс, я его назвал меню, и создаем функцию, назвал ее RunMenu.


class menu
{
public:

    int RunMenu()
    {
        int punkt;
        cout << "Добро пожаловать!" << endl;
        cout << "1.Вход" << endl;
        cout << "2.Регистрация" << endl;
        cin >> punkt;

        if (punkt != 1 && punkt != 2)
        {
            cout << "Выбран неверный пункт меню!" << endl;
        }
        if (punkt == 1)
        {
            system("cls");
            Password pass;
            pass.Entrance();
        }
        if (punkt == 2)
        {
            system("cls");
            Password pass;
            pass.Sign_up();
        }
        return 0;
    }
};

Думаю тут все понятно, теперь давайте вызовем наше меню.


int main()
{
    setlocale(LC_ALL, "ru");

    menu Menu;

    Menu.RunMenu();

    return 0;
}

Вот и всё! Мы написал простейшую систему регистрации и входа, для новичков будет полезно. Как и обещал, вот полный код.


class Password
{
public:

    int Entrance()
    {
        string login = "login.txt";
        string password = "password.txt";

        fstream log;
        fstream pass;

        log.open(login, fstream::in | fstream::out | fstream::app);
        pass.open(password, fstream::in | fstream::out | fstream::app);

        if (!log.is_open() && !pass.is_open())
        {
            cout << "Ошибка!" << endl;
        }
        else
        {
            string log_cheker;
            string pass_cheker;

            while (!log.eof()) //Пока не закончатся символы, идем по циклу.
            {
                log_cheker = "";
                log >> log_cheker; //Передаем данные с файла в переменную.
            }
            while (!pass.eof()) //Пока не закончатся символы, идем по циклу.
            {
                pass_cheker = "";
                pass >> pass_cheker; //Передаем данные с файла в переменную.
            }

            string login_correct;
            string pass_correct;

            cout << "Введите свой логин: "; cin >> login_correct;
            cout << endl;
            cout << "Введите свой пароль: "; cin >> pass_correct;

            if (login_correct != log_cheker && pass_correct != pass_cheker)
            {
                cout << "Пароль или логин введен не правильно!" << endl;
            }
            else
            {
                cout << "Данные введены верно!" << endl;
            }
            return 0;
        }
    }
    int Sign_up()
    {
        string login = "login.txt";
        string password = "password.txt";

        fstream log;
        fstream pass;

        log.open(login, fstream::in | fstream::out | fstream::app);
        pass.open(password, fstream::in | fstream::out | fstream::app);

        if (!log.is_open() && !pass.is_open())
        {
            cout << "Ошибка!" << endl;
        }
        else
        {
            string log_cheker;
            string pass_cheker;
            cout << "Введите свой логин: "; cin >> log_cheker;
            cout << endl;
            cout << "Введите свой пароль: "; cin >> pass_cheker;

            log << log_cheker;
            pass << pass_cheker;

            cout << "Регистрация прошла успешно!" << endl;

            return 0;

        }
    }

};

class menu
{
public:

    int RunMenu()
    {
        int punkt;
        cout << "Добро пожаловать!" << endl;
        cout << "1.Вход" << endl;
        cout << "2.Регистрация" << endl;
        cin >> punkt;

        if (punkt != 1 && punkt != 2)
        {
            cout << "Выбран неверный пункт меню!" << endl;
        }
        if (punkt == 1)
        {
            system("cls");
            Password pass;
            pass.Entrance();
        }
        if (punkt == 2)
        {
            system("cls");
            Password pass;
            pass.Sign_up();
        }
        return 0;
    }
};

int main()
{
    setlocale(LC_ALL, "ru");

    menu Menu;

    Menu.RunMenu();

    return 0;
}
