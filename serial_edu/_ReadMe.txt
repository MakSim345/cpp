23-APR-2013

origin:
http://batchloaf.wordpress.com/2013/02/13/writing-bytes-to-a-serial-port-in-c/

This is a (relatively) simple example of a C program to send five bytes to a serial port in Windows. 
In this case, I’m sending the five characters “hello” via COM22 at 38400 baud, 
but of course the program can easily be modified to send a different string, or to use a 
different serial port or baudrate.

This program can be compiled using cl.exe (the C++ compiler used in Visual C++ / Visual Studio)
or using gcc (the C compiler in MinGW). In the former case, the file should be saved as “serial.cpp” 
and compiled as C++, whereas in the latter case, it can simply be saved as “serial.c” and compiled
as plain C. I show an example of each approach in the screenshots at the end of this post. Either way, 
the resulting program “serial.exe” works the exact same.

By the way, for a simpler way to send arbitrary characters to a serial port without compiling
anything at all, see my previous post.

