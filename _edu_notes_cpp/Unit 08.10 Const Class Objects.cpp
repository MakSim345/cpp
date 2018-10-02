8.10 — Const class objects and member functions


In the lesson on passing arguments by reference, we covered the merits of passing function parameters as const variables. To recap, making variables const ensures their values are not accidentally changed. This is particularly important when passing variables by reference, as callers generally will not expect the values they pass to a function to be changed.

Just like the built-in data types (int, double, char, etc…), class objects can be made const by using the const keyword. All const variables must be initialized at time of creation. In the case of built-in data types, initilization is done through explicit or implicit assignment:
    
const int nValue = 5; // initialize explicitly
const int nValue2(7); // initialize implictly

In the case of classes, this initialization is done via constructors:

const Date cDate; // initialize using default constructor
const Date cDate2(10, 16, 2020); // initialize using parameterized constructor

If a class is not initialized using a parameterized constructor, a public default constructor must be provided -- if no public default constructor is provided in this case, a compiler error will occur.

Once a const class object has been initialized via constructor, any attempt to modify the member variables of the object is disallowed, as it would violate the constness of the object. This includes both changing member variables directly (if they are public), or calling member functions that sets the value of member variables:
    
class Something
{
public:
    int m_nValue;
 
    Something() { m_nValue = 0; }
 
    void ResetValue() { m_nValue = 0; }
    void SetValue(int nValue) { m_nValue = nValue; }
 
    int GetValue() { return m_nValue; }
};
 
int main()
{
    const Something cSomething; // calls default constructor
 
    cSomething.m_nValue = 5; // violates const
    cSomething.ResetValue(); // violates const
    cSomething.SetValue(5); // violates const
 
    return 0;
}

All three of the above lines involving cSomething are illegal because they violate the constness of cSomething by attempting to change a member variable or calling a member function that attempts to change a member variable.

Now, consider the following call:
    
   std::cout << cSomething.GetValue();

Surprisingly, this will cause a compile error! This is because const class objects can only call const member functions, GetValue() has not been marked as a const member function. A const member function is a member function that guarantees it will not change any class variables or call any non-const member functions.

To make GetValue() a const member function, we simply append the const keyword to the function prototype:
    
class Something
{
public:
    int m_nValue;
 
    Something() { m_nValue = 0; }
 
    void ResetValue() { m_nValue = 0; }
    void SetValue(int nValue) { m_nValue = nValue; }
 
    int GetValue() const { return m_nValue; }
};

Now GetValue() has been made a const member function, which means we can call it on any const objects.

Const member functions declared outside the class definition must specify the const keyword on both the function prototype in the class definition and on the function prototype in the code file:
    
class Something
{
public:
    int m_nValue;
 
    Something() { m_nValue = 0; }
 
    void ResetValue() { m_nValue = 0; }
    void SetValue(int nValue) { m_nValue = nValue; }
 
    int GetValue() const;
};
 
int Something::GetValue() const
{
    return m_nValue;
}

Any const member function that attempts to change a member variable or call a non-const member function will cause a compiler error to occur. For example:
    
class Something
{
public:
    int m_nValue;
 
    void ResetValue() const { m_nValue = 0; }
};

In this example, ResetValue() has been marked as a const member function, but it attempts to change m_nValue. This will cause a compiler error.

Note that constructors should not be marked as const. This is because const objects should initialize their member variables, and a const constructor would not be able to do so.

Finally, although it is not done very often, it is possible to overload a function in such a way to have a const and non-const version of the same function:
    
class Something
{
public:
    int m_nValue;
 
    const int& GetValue() const { return m_nValue; }
    int& GetValue() { return m_nValue; }
};

The const version of the function will be called on any const objects, and the non-const version will be called on any non-const objects:
    
Something cSomething;
cSomething.GetValue(); // calls non-const GetValue();
 
const Something cSomething2;
cSomething2.GetValue(); // calls const GetValue();

Overloading a function with a const and non-const version is typically done when the return value needs to differ in constness. In the example above, the const version of GetValue() returns a const reference, whereas the non-const version returns a non-const reference.

Let’s take a look at making our date class member functions const so they can be used with const Date objects:
    
class Date
{
private:
    int m_nMonth;
    int m_nDay;
    int m_nYear;
 
    Date() { } // private default constructor
 
public:
    Date(int nMonth, int nDay, int nYear)
    {
        SetDate(nMonth, nDay, nYear);
    }
    void SetDate(int nMonth, int nDay, int nYear)
    {
        m_nMonth = nMonth;
        m_nDay = nDay;
        m_nYear = nYear;
    }
    int GetMonth() { return m_nMonth; }
    int GetDay()  { return m_nDay; }
    int GetYear() { return m_nYear; }
};

The only non-constructor member functions that do not modify member variables (or call functions that modify member variables) are the access functions. Consequently, they should be made const. Here is the const version of our Date class:
    
class Date
{
private:
    int m_nMonth;
    int m_nDay;
    int m_nYear;
 
    Date() { } // private default constructor
 
public:
    Date(int nMonth, int nDay, int nYear)
    {
        SetDate(nMonth, nDay, nYear);
    }
    void SetDate(int nMonth, int nDay, int nYear)
    {
        m_nMonth = nMonth;
        m_nDay = nDay;
        m_nYear = nYear;
    }
    int GetMonth() const { return m_nMonth; }
    int GetDay() const { return m_nDay; }
    int GetYear() const { return m_nYear; }
};

The following is now valid code:
    
void PrintDate(const Date &cDate)
{
    // although cDate is const, we can call const member functions
    std::cout << cDate.GetMonth() << "/" <<
        cDate.GetDay() << "/" <<
        cDate.GetYear() << std::endl;
}
 
int main()
{
    const Date cDate(10, 16, 2020);
    PrintDate(cDate);
 
    return 0;
}
