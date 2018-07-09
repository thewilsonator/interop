/**
 * __dslice : C++ interoperation with D dynamic arrays
 *
 * Copyright:   Copyright (C) 2018 by The D Language Foundation, All Rights Reserved
 * Author:      Nicholas Wilson
 * License:     $(LINK2 http://www.boost.org/LICENSE_1_0.txt, Boost License 1.0)
 */

#ifndef DSLICE_H
#define DSLICE_H
#ifdef __has_include
#  if __has_include(<span>) // Do we have std::span?
#    include<span>
#  elif __has_include(<gsl/span>) // Do we have gsl::span
#    include <gsl/span>
#  endif
#endif
/**
 * __dslice is the C++ equivalent to D's T[] dynamic array and is to be used whenever
 * a T[] shows up in an extern(C++) declaration in D.
 *
 * It is in all but name (for mangling, availability and layout guarantee reasons) a
 * std::span<T,dynamic_extent>.
 *
 * It provides constructors for anything that have size() and data() member functions
 * (e.g. std::vector, std::string, std::string_view and friends), so that the following
 * will work:
 * -------
 * // Defined in D as extern(C++) void foo(const(char)[] a) { ... }
 * void foo(__dslice<const char> a);
 *
 * void bar()
 * {
 *     std::vector<char> vc = ...;
 *     std::string s = "blah"s;
 *     std::string_view sv = "blah"sv;
 *     foo(vc);
 *     foo(s);
 *     foo(sv);
 * }
 * -------
 *
 * N.B. Like string_view, __dslice has reference semantics, so be careful to not let it outlive 
 * the memory that it spans.
 */
template<typename T>
struct __dslice
{
    size_t length;
    T* ptr;

    __dlisce(size_t len, T* p)
    {
        length = len;
        ptr    = p;
    }

    /**
     * Container constructor: 
     *
     * Accepts any type U that satisfies `U u; size_t i = u.size(); T* = u.data();`
     * This includes types like:
     *      std::vector,
     *      std::string,
     *      std::string_view
     *      std::span
     *
     * TODO: Constrain this properly such that U::value_type == T (modulo const)
     * TODO: Make this const correct
     */
    template<typename U>
    __dslice(U& u)
    {
        length = u.size();
        ptr    = const_cast<T*>(u.data());
    }
    
#ifdef __has_include
#  if __has_include(<span>)
    operator std::span<T>(){ return std::span<T>(ptr,length);};
#  elif __has_include(<gsl/span>)
    operator gsl::span<T>(){ return gsl::span<T>(ptr,length);};
#  endif
#endif

};

#endif
