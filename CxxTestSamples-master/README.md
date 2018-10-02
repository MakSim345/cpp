CxxTest Examples
by David Ruhmann


REQUIREMENTS:
--------------------------------------------------------------------------------
Python  is required! (Recommend: v3+)
GCC g++ is required! (Recommend: GCC packaged in Strawberry Perl)
Ply, Python plugin, is required (only for FOG examples)! (Recommend: 3.4+)


NOTES:
--------------------------------------------------------------------------------
The batch files look for CxxTest in "..\CxxTest\cxxtest-4.0.3\".  I am going to
 leave this as the reference location because I know the examples work with
 version 4.0.3.

 
STRUCTURE:
--------------------------------------------------------------------------------
    Parent
    	|- CxxTest
    	|	|- cxxtest-4.0.3
    	|		|- cxxtest
    	|			|- *.h
    	|- CxxTestSample
    		|- *.bat, *.cpp, *.h... samples


EXAMPLE DESCRIPTIONS:
--------------------------------------------------------------------------------
1.  Simple language test (100% PASS)
2.  A. Simple language tests, test made to fail (50% PASS)
    B. XML formatted results (50% PASS) (--runner=XmlPrinter)
3.  Template test file test (100% PASS) (--template)
4.  Example 1 using the FOG generator (100% PASS) (--fog)
5.  (COMPILE FAIL) Expected failure due to unparsable code
6.  Simple language test with odd formatting (100% PASS) (--fog)
7.  (COMPILE FAIL) Expected failure due to unsupported comments
8.  Simple language test with multiline comments (100% PASS) (--fog)
9.  (COMPILE FAIL) Expected failure due to no MACRO/directive support
10. (COMPILE FAIL) Expected failure due to no MACRO/directive support
11. Many runs using command line parameters, Outputs to runner11.txt (100% PASS)
12. Use setUp and tearDown (100% PASS)
13. Only run the test suite if using MSVC, test made to fail (0% PASS) (--fog)
14. Fixtures (100% PASS)
15. Custom comparison test, test made to fail (0% PASS)
16. Test with enum, test made to fail (0% PASS)
17. Test value traits, test made to fail (50% PASS) (--fog)
18. Template version of value traits test, test made to fail (50% PASS)
19. A. Test using the mock of a global function (100% PASS)
    B. Run using the real of a global function, No Tests
20. A. Test using the mock of an unknown global function (100% PASS)
       Used when testing and cannot or do not want to include/link to the real.
    B. Run using the real of a global function, No Tests
21. A. Mock global, class (public, protected, private), and namespace methods!
       Also contains examples of how to use real calls in the tests. (100% PASS)
    B. Run using the real methods, No Tests.


FILES FOR EACH EXAMPLE
--------------------------------------------------------------------------------
1.  MyTestSuite1.h, (Example1-MyTestSuite1.bat)
2.  A. MyTestSuite2.h, (Example2-MyTestSuite2.bat)
    B. MyTestSuite2.h, (Example2-MyTestSuite2-XML.bat)
3.  MyTestSuite1.h, MyTestSuite1.tpl, (Example3-MyTestSuite1-Template.bat)
4.  MyTestSuite1.h, (Example4-MyTestSuite1-FOG.bat)
5.  MyTestSuite3.h, (Example5-MyTestSuite3.bat)
6.  MyTestSuite3.h, (Example6-MyTestSuite3-FOG.bat)
7.  MyTestSuite4.h, (Example7-MyTestSuite4.bat)
8.  MyTestSuite4.h, (Example8-MyTestSuite4-FOG.bat)
9.  BadTestSuite1.h, (Example9-MyTestSuite1.bat)
10. BadTestSuite1.h, (Example10-MyTestSuite1-FOG.bat)
11. MyTestSuite1.h, MyTestSuite2.h, MyTestSuite4.h,
    (Example11-MyTestSuite1+2+4.bat)
12. MyTestSuite5.h, (Example12-MyTestSuite5.bat)
13. MyTestSuite6.h, (Example13-MyTestSuite6-FOG.bat)
14. MyTestSuite8.h, (Example14-MyTestSuite8.bat)
15. MyTestSuite7.h, (Example15-MyTestSuite7.bat)
16. MyTestSuite9.h, (Example16-MyTestSuite9.bat)
17. MyTestSuite10.h, MyClass.h, (Example17-MyTestSuite10-FOG.bat)
18. MyTestSuite11.h, (Example18-MyTestSuite11.bat)
19. A. MockTestSuite.h, time_mock.h, time_mock.cpp, rand_example.cpp,
       (Example19-MockTestSuite.bat)
    B. rand_main.cpp, time_mock.h, time_real.cpp,
       (Example19-MockTestSuite-REAL.bat)
20. A. MockGhost.h, ghost.h, ghost_mock.h, ghost_mock.cpp, ghost_example.cpp,
       (Example20-MockGhost.bat)
    B. ghost.h, ghost.cpp, ghost_mock.h, ghost_example.cpp, ghost_main.cpp,
       (Example20-MockGhost-REAL.bat)
21. A. MockGeneric.h, generic.h, generic.cpp, generic_mock.h, generic_mock.cpp,
       generic_example.h, generic_example.cpp, (Example21-MockGeneric.bat)
    B. generic_main.cpp generic.h, generic.cpp, generic_mock.h, generic_real.cpp
       ,generic_example.h, generic_example.cpp, (Example21-MockGeneric-REAL.bat)
