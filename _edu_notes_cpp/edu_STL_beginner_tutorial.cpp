A beginner tutorial on STL.

Ok, guys, here is one more beginner tutorial. This time it iss STL. Are you new to STL and interested in knowing what STL is? Or how to use STL in your program? I bet this tutorial is for you. If you are an advanced user of the STL then see my references and links at the end of this tutorial.

The Evolution

The Standard Template Library (STL) is not a new library as compared to other libraries. Originally, the development of the STL was started by Alexander Stepanow at HP in 1979. Later, he was joined by David Musser and Meng Lee. In 1994, STL was included into ANSI and ISO C++.

"Why the STL?"

In one of my projects, I needed a doubly linked-list to store a tree node values. One of my fellow developers created this class which has general functions such as addNode, deleteNode, SeachNode, InsertNode and others. It took him more than a week and we still had some memory problems in it.

The STL provides general purpose utility classes which programmers can use in their applications and they do not have to worry about allocating and freeing memory. These classes are array, link, stack and map. The STL provides general algorithms for sort, search, or reverse arrays or links. Besides these two things, the STL also provides some iterators and other options you can apply on these classes.

Features: The STL-s generic algorithms work on native C++ data structures such as strings and vectors. STL containers are very close to the efficiency of hand-coded, type-specific containers. Learning of STL is very simple. You need some knowledge of templates and C++.

"When to use the STL?"

If you need to provide any STL features in your program, you can use them.

Advantages of the STL
You do not have to write your classes and algorithms. It saves time. You do not have to worry about allocating and freeing memory. That iss a big problem when you create your own linked-list, queue or other classes.Reduces your code size because STL uses templates to develop these classes.You have to override your functions or classes to operate on different types of data while STL lets you apply these classes on different kinds of data.Easy to use and easy to learn.
Templates

The STL classes are template based classes. You should know about templates before starting using the STL in your programs.

A template is a mechanism for generating functions and classes which can apply on different types of data. You can design a single class that operates on different type data. For example, you can create a linked list class which can work on int, long, or double data types. We will see this in the following example.

There are two types of templates: function templates and class templates.

Function Templates

Function templates allow you to write type safe functions and it can reduce size of code and create code flexibility. For example, you have an overloaded function Add() which is defined here:

int Add (int a, int b ) 
    { return a + b; } ;

long Add( long a, long b)
    { return a + b; } ;

double Add( double a, double b ) 
    { return a + b; } ;

Instead, you can write a template function, Add, which will solve this overloading problem.

template <class T>
T Add( T a, T b) 
    { return a + b };

Now you can use this template on different types of data. Such as:

int total = Add<int>(12, 35);
long total = Add<long>(10245, 35234);
double total = Add<double>(12.60, 35.98);

Fairly easy.

"Class Templates"

Templates allows you to create classes that do not operate on a specific data type. Instead, the data type can be provided by the user at runtime. Here is an example. We have a class Math, which has three functions, Add, Divide, and Multiply.

template <class T>
class Math
{
public:
    Math(){ };
    T Add( T a, T b) { return a + b };
    T Divide( T a, T b) { return a + b };
    T Multiply( T a, T b) { return a + b };
};

Now you can use this class with different data types. Here is how to use it:

Math<double> dMath; // Instantiating the class for double data type.
double dReturn = dMath.Add ( 12.34, 34.654 );
double dReturn = dMath.Multiply ( 12.34, 34.654 );
Math<int> iMath; // Instantiating the class for integer data type.
int iReturn = dMath.Add ( 12, 34 );
int iReturn = dMath.Multiply ( 12, 34 );

Does it make sense? Ok, that is enough about templates.

"Basic elements of the STL"

Here is a list of elements of the STL. The first three of them are fundamental items.
ItemDescriptionContainerAn object that holds other objectsAlgorithmA function that acts on containersIteratorA pointer-like objectAllocatorThis item manages memory allocation in a containerAdaptorTransforms one object into anotherPredicateA function that returns a boolean value, true or false.

FunctionObject A class that defines operator().

Containers are the basic elements of the STL. A container is the component that actually stores data. For example, the deque container class creates a doubly linked-list and the list class creates a linked-list.
Algorithms are the second most useful element of the STL. Algorithms act on the containers. They are used to perform operations on the containers such as sorting, searching and others.

Iterators work as their name says. They  provide iterations for the STL containers. Iterations mean looping. For example, if you want to search a container item from beginning to the end, you would have to use iterators for this loop.

Allocators manage memory allocations for the containers.

An adaptor is used to convert from one object to another. They are a kind of conversion utilities. For example, you can convert a dque container to queue using a queue adaptor.

Function Objects are utility functions that are used on the containers. Some of them are less(), greater(), divides(), plus(), minus() etc. We will see how to use them in our sample programs.

"The Containers"

Containers are the base elements of the STL. Containers holds actual data. I should say that containers are data structures that store, and manage a set of items. Containers have constructors and destructors to provide allocation and deallocation for stored items. These items can be a basic data type such as int, char, string etc. All containers are implemented using templates. The good thing about containers is all containers have the same specification.

Sequence A sequence is a linear list which stores all of its elements in linear order. For example an array is a sequence.

char ch[10] is an array of char types (10 elements) which are ordered in a linear fashion.

Those were two types of containers and the third type is container adaptors:
TypeContainer classesDescriptionSequencevector, list, dequeDynamic arrays, support insertion or deletion in the beginning or at the end. They do not support insertion or deletion at a specific position.Associativemap, multimap, set, multisetThis type of container is a variable-sized Container that supports efficient retrieval of elements based on keys. They store data in the form of a key and value. A key has corresponding value or values.Container adaptorsstack, queue, priority_queueThey are restricted containers and do not support all the functionality provided by containers. We will see this in out definitions later in this tutorial.
Here is a list of the STL container classes and their descriptions.ContainerHeader filevector<vector>deque<deque>list<list>set<set>multiset<set>map<map>multimap<map>queue<queue>priority_queue<queue>stack<stack>
Lets see these containers in detail now.

"The Vector container"

Vector container is the simplest container. It supports random access. It provides insertion, and deletion of elements at the end. It is a dynamic array which varies according to need. It supports automatic memory management. For example:

vector<int> vList; // Initializes a vector list of integers
// Fill values in vList using push_back
for ( int i=1; i<20; i++ ) vList.push_back(i);

The deque container

This container is the same as vector container except that the deque container is a queue with both ends. That means elements can be added or deleted from both front and back ends. Elements can also be inserted at any specific position. For example:

deque<int> d1;
d1.push_front(2);
d1.push_back(4);

The list container

A list is a doubly linked list. It supports both forward and backward traversal, and (amortized) constant time insertion and removal of elements at the beginning or the end, or in the middle. Another list container is slist which is a singly linked list. A list container is really useful when elements will be frequently added or removed from the middle of the container and random access to elements is not required.

The map and multimap containers

The map and multimap containers store data in the form of a pair. Each pair has a key and corresponding value(s). For example, pair stdRec = (name<string>, marks<int>). A map can store data of type stdRec which has two elements, a key, and its value. The basic data type of the key might differ from the values. In our example, key name is a string type while the value is int type.

Map containers allow only unique keys. A key can have some value but there will not be any duplicate key. A key may be a name. So basically map is a list of (key,value) pairs. Value can be accessed by using key. For example:

map<string, int> data;
for(int i=0; i<10; i++)
    data.insert(pair<string><char>('mcb'+i, 100+i );

Multimap containers are similar to map except they store duplicate keys. That means one key can have more than one value.

The set and multiset containers

Set containers are similar to map containers except that the key part is not separated from the value part. Sets store data in a form where key is a part of value.

Set class supports a set in which unique keys are stored. While multiset lets you have duplicate keys.

set<string> sdata;
sdata.insert("mahesh");
sdata.insert("Owen");
sdata.insert("lara");
set<string>::iterator p = sdata.begin();
do
{
  cout<< *p <<" ";
  p++ ;
} while (p!= sdata.end() );

The queue container adaptor

The queue is a FIFO queue which has certain restrictions in comparison to other containers. Elements are inserted into a queue from the tail end and removed from the head. Its like a queue on a gas station. The first vehicle fills gas first and the next vehicle comes after the last vehicle. Push and pop are two major operation of the queue.

queue<string> sdata;
sdata.push("mahesh");
sdata.push("Owen");
sdata.push("lara");
while ( !sdata.end() )
{
  cout<< sdata.front() <<" ";
  sdata.pop();
}

The stack container adaptor

The stack is a LIFO queue. Operations are similar to queue except elements are inserted from the top of the stack and removed from the top of the stack too. For example, a stack of plates in the kitchen. Push and pop are two major operation of the stack.

stack<string> sdata;
sdata.push("mahesh");
sdata.push("Owen");
sdata.push("lara");
while ( !sdata.empty() )
{
  cout<< sdata.top() <<" ";
  sdata.pop();
}

The Algorithms

Algorithms are used on the data of containers.

Some basic algorithms are sort, search, count, reverse, or merge. Using these algorithms on containers is pretty easy. For example, if you have a vector container with some data in it, here is how to use the count algorithm to count its elements:

vector<int> vdata;
//add some data
int i = count( vdata.begin(), vdata.end(), 3 );

Here is reverse algorithm:

vector<int> vdata;
// add some data
reverse( vdata.begin(), vdata.end() );

Lets see one more example of sorting the data.

vector<int> vdata;
vdata.push_back(5);
vdata.push_back(3);                                                                  vdata.push_back(8);
sort(vdata);

STL has over 60 algorithms listed here with their description.
AlgorithmDescriptionadjacent_findSearches for adjacent matching elements within a sequence and returns and iterator to the first matchbinary_searchPerforms a binary search on an ordered sequence
copyCopies a sequence.copy_backward Same as copy except that it moves the elements from the end of the sequence firstcountReturns the number of elements in the sequence.count_ifReturns the number of elements in the sequence that satisfy some predicate.equalChecks if two ranges are sameequal_rangeReturns a range in which an element can be inserted into a sequence without disrupting the ordering of the sequence.fill and fill_nFills a range with a specified valuefindSearches and returns the iterator  to the first occurencefind_endLast iteratorfind_first_ofFinds the first elementfind_ifSearches with a predicatefor_eachApplies a function to a range of elementsgenerate and generate_nAssigns elements in a range of the values returned by a generator function.includesDetermines if one sequence includes all elements of other sequence.implace_mergeMerges a range with another rangeiter_swapExchange the values pointed to by its iterator argumentslexicographical _compareCompares two sequences alphabeticallylower_boundFind the first point in the sequence that is less than a specified value.make_heapConstructs a heap from a sequence.maxReturns the maximum of two values.minReturns minimum of two values.min_elementReturns the iterator to the min element within a range.mismatchFinds the first mismatch between the elements in two sequences.next_permutationConstructs next permutation of a sequence.nth_elementArranges all elements in an order so all element less than nth element come before it and greater than come after it.partial_sortSorts a range.partial_sort_copySorts and copies elements.partition, stable_partitionArranges elements so all elements return true for a predicate coming before it and false coming after it.pop_heapExchanges first and last-1 elementsprev_permutationConstructs previous permutationpush_heapPushes elements onto the end of the heap.random_shuffleRandomize a sequence.remove, remove-if, remove_copy, remove_fopy_ifRemoves elementsreverse and reverse_copyReverses the order of a rangereplace, replace_if, replace_copy, replace_copy_ifReplaces elements within a range.rotate, rotate_copyLeft-rotatesearch, search_insearches a subsequence within a sequenceset_differenceProvides difference between two ordered sets.set_intersectionProvides intersection output between two sets.set_symmetric_ differenceProvides symmetric output between two sets.set_unionProvides union of two sets.sort, stable_sortSorts a range.sort_heapSorts a heap.swap, swap_rangesExchanges two values, ranges.transformApplies a function to a range of elements and stores outcome in a new sequence.unique, unique_copyEliminates duplicate elements.upper_boundFinds the last point in a sequence.mergeMerges two sequences.

Iterators

Containers do not provide access to their elements. They use iterators to traverse the elements within a container. In other words, the iterators provides a way to cycle through the contents of containers. Each container defines one or more iterator types that we can declare iterators for that container. There are five types of iterators. Iterators are very similar to smart pointers and have increment and dereferencing operations.
TypeDescriptionRandom AccessStores and retrieves elements randomly.BidirectionalStores and retrieves elements forward and backward both directions.ForwardStores and retrieves forward only.InputForward retrieve only.OutputForward, store only.
As we have seen in our previous examples, we can use iterators like in this sample : set<string> sdata;
sdata.insert("mahesh");
sdata.insert("Owen");
sdata.insert("lara");
set<string>::iterator p = sdata.begin();
do
{
  cout<< *p <<" ";
  p++ ;
}while (p!= sdata.end() ) ;
Function Objects

A function object is an object that can be called as a function. The header for functional objects is <functional>. There are three types of function objects:
NameDescriptionGeneratorGenerator is a function object which does not take any parameters. Such as Do();BinaryA binary function object is a function object which takes two arguments. Such as Do( int a, char b). Some of them are plus, minus, divides, modulus, equal_to, not_equal_to, greater_equal, greater, less, less_equal, local_and, logical_orUnary A unary function object takes a single argument as a parameter. Such as Do(false); logical_notnegate

Function Adaptors
The same class header <functional> defines function adaptors. Function Adaptors are template classes that provide an existing class with a new interface. They can be applies on container or iterators.

Container Adaptors

What if you need to create a new container from an existing one? That means you need to extend the functionality of an existing one and add some more to new one. You can do that by mapping the interface of an existing container to that of the new container.

The STL provides three container adaptors: stack<Container>, queue<Container>, and deque<Container>. The following program demonstrates the use of a stack that has been implemented as a vector:
#include <vector.h>
#include <stack.h>
void
main() 
{
   stack <vector<int> > st;
   for (int i=0; i < 10; i++)
      st.push (i);

   while ( !st.empty() )
   {
      cout << st.top() << " ";
      st.pop();
   }
   cout << endl;
}

Iterator Adaptors

Adaptors can also be used to extend the functionality of an existing iterator. The reverse, insert, and row storage iterators are example of iterator adaptors in the STL.

Allocator

Allocators are responsible of memory management in the STL. Each container has one its allocator. Allocators allocate and deallocate memory automatically for a container. But you can even create your own custom allocators.

The default allocator is Allocator. It is defined in the <memory> header file. This table shows allocator functions and their description:
FunctionDescriptionpointer address(reference ob) const; const_pointer address ( const_reference ob) const;Returns the address of object ob.pointer allocate(size_tpe num, typename allocator<void>::const_pointer h=0);Returns a pointer to allocated memoryvoid construct(pointer ptr, const_reference val);Constructs an objectvoid deallocate(pointer ptr, sise_type num);Deallocates num objectvoid destroy(pointer ptr)Destroys ptr object.size_type max_size() const throw();Returns the maximum number of objects that can be allocated.

Example:

vector<double>::allocator_type d_a;
cout<< d_a.max_size();

