# Very simple C++ logger library

This shared library (DLL) is rudimentary (100 lines of code) and easy to hack so adapt it to your own C++ projects!

Tested under Visual C++ 2008 and 2010 (x86 + x64 mode), the source code should be multiplatform.
Build system must be adapted ([CMake](http://www.cmake.org/)?).

Class Logger was inspired by [QDebug from the Qt library](http://developer.qt.nokia.com/doc/qt-4.8/qdebug.html).

## Examples

```C++
// Prints "[DEBUG] [Function or method name given by macro __FUNCTION__] Hello world!"
// "[DEBUG] [ClassName::methodName] Hello world!" with Visual C++
// "[DEBUG] [methodName] Hello world!" with GCC
logDebug() << "Hello" << "world!";

// Prints "[INFO] [...] This is an integer: 10"
logInfo() << "This is an integer:" << 10;

// Prints "[FATAL] [...] Fatal error" and then provokes an assert
logFatal() << "Fatal error";
```

## How it works

log*() functions can take any data type that is streamable (string, integer, float...).
Logger uses std::ostringstream so it works the same way as the standard output stream (std::cout).
If you encounter an object that is not streamable or you want to change the output,
overloads `operator<<()` for std::ostream:

```C++
class MyObject {
public:
    std::string id;
    std::string type;

    friend std::ostream & operator<<(std::ostream & os, const MyObject & myObject);
};

std::ostream & operator<<(std::ostream & os, const MyObject & myObject) {
    os << myObject.id;
    os << ", " << myObject.type;
    return os;
}
```

## Configuration

What level the Logger class outputs can be configured using class LoggerConfig.
This class depends on [Boost](http://www.boost.org/) in order to parse the INI format
but since the code is very simple you can easily remove this dependency if needed.

## License

Do whatever you like with it, this is public domain.
