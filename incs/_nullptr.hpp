#ifndef __nullptr_PTR
# define __nullptr_PTR

#include "webserv.hpp"

_BEGIN_NAMESPACE_WEBSERV

struct nullptr_t
{
    void*	ptr;

    struct nat {int b;};

    nullptr_t() : ptr(0) {}
    nullptr_t(int nat::*) : ptr(0) {}
    operator int nat::*() const {return 0;}

    template <class T>
    operator T* () const {return 0;}

    template <class T, class P>
    operator T P::* () const {return 0;}

    friend bool operator==(nullptr_t, nullptr_t) {return true;}
    friend bool operator!=(nullptr_t, nullptr_t) {return false;}
};

#define _nullptr	nullptr_t(0)

_END_NAMESPACE_WEBSERV

#endif