#include "featurelist.h"

#include <functional>

/** Polymorphic wrappers for function objects.
*   Polymorphic wrappers for function objects are similar to function pointers in semantics and syntax, but are less
*   tightly bound and can indiscriminately refer to anything which can be called (function pointers, member function 
*   pointers, or functors) whose arguments are compatible with those of the wrapper.
*
*   Through the example it is possible to understand its characteristics:
*/

std::function<int (int, int)> func; //Wrapper creation using template class 'function'.
std::plus<int> add;                 //'plus' is declared as 'template<class T> T plus (T, T ); ' then 'add is type 'int add (int x, int y)'.
bool adjacent(long x, long y)  { return x && y; }

void Test_Polymorphic_Wrapper_for_function_object()
{
    func = add;                     // OK - Parameters and return types are the same.
    int a = func(1, 2);             // Note: if the wrapper 'func' does not refer to any function, the exception 'std::bad_function_cal is thrown.
    assert(a == 3);

    std::function<bool (short, short)> func2;
    if (!func2){   // True because 'func2' has not yet been assigned a function. 

        func2 = &adjacent; //OK -> Parameters and return types are conbvertible.

        struct Test {
            bool operator()(short x, short y) { return x && y;}

            bool test(short x, short y) { return x && y;}
        };  

        Test car;
        func2 = std::ref(car);     // 'std::ref' is a template function that returns the wrapper of member function 'operator()' of struct 'car'.

        func2 = std::bind(&Test::test, &car, std::placeholders::_1, std::placeholders::_2); // std::function to member function
    }

    func = func2; // OK - parameters and return types are convertible.

    std::cout << func(1, 2) << std::endl;

    std::cout << func(1, 0) << std::endl;
}