// exersise:
// Given a namespace

namespace Exercize {
   template <class elemType>
      class Array { ... };

   template <class EType>
      void print (Array< EType > );

   class String { ... }
   template <class ListType>
      class List { ... };
}
// and main :

int main() 
{
   const int size = 1024;
   Array<String> as (size);
   List<int> il (size);

   // ...

   Array<String> *pas = new Array<String>(as);
   List<int> *pil = new List<int>(il);

   print (*pas);
}
/*
Tha eapp is not compiling because declaration of used classes are in namespace Exercise. Please modify tha main app using follow:

(a) qualify names
(b) selective directive "using"
(c) aliases
(d) directive using

*/