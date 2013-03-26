#include <iostream>
#include <cassert>

#include "featurelist.h"

/** Wrapper Reference
*   A wrapper reference is obtained from an instance of the template class reference_wrapper. Wrapper
*   references are similar to normal references ('&') of the C++ language. To obtain a wrapper reference 
*   from any object the function template ref is used (for a constant reference cref is used).
*
*   Wrapper references are useful above all for function templates, where references to parameters rather 
*   than copies are needed. 
*
*   This new utility was added to the existing <utility> header and didn't need further extensions of the
*   C++ language. 
*/

// This function will obtain a reference to the parameter 'r' and increment it
void func(int &r) { r++; }

// template function. 
template<class F, class P> void g (F f, P t) { f(t); }

void Test_Wrapper_Reference()
{
    int i = 0;
    g (func, i);                    // 'g<void (int &r), int>' is instantiated then 'i' will not be modified. 
    assert(i == 0);
    std::cout << i << std::endl;    // output -> 0

    g (func, std::ref(i));          // 'g<void(int &r), reference_wrapper<int>>' is instantiated then 'i' will be modified.
    assert(i == 1);
    std::cout << i << std::endl;    // output -> 1
}

