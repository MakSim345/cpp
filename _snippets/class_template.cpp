// header file:

class Window
{
public:
    Window();
    ~Window();

    std::string name() const;
    virtual void display() const;

private:
    std::string _name;
};

// CPP file:
Window::Window()
    :_name("my_window")
{}

Window::~Window()
{}

std::string Window::name() const
{
    return _name;
}

void Window::display() const
{
    cout << "---------------" << "\n";
    cout << "Window - SHOW! " << "\n";
    cout << "---------------" << "\n";
}



