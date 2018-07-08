Using D with C
==============

While D has binary compatibility with C it is not source compatible. 
There are two parts to interfacing with C: name mangling and calling convention.
This is achieved with the use of the `extern(C)` linkage attribute.

For variables only the name needs to match, but classic C style global variables 
should also have `__gshared` storage class to indicate that they are not thread local.
Globals defined with `__thread` do not require `__gshared`.

For functions both the name and the calling convention need to match. In most cases 
`extern(C)` does both, except for (D) `static` nested functions and `static` (struct/class)
member functions which only affect the calling convention. This is so they can e.g. be templated.

A note about Windows
--------------------

`__cdecl` is the calling convention for windows and is covered with `extern(Windows)`.
`extern(System)` is `extern(Windows)` on Windows and `extern(C)` on other systems.
`extern(System)` should be used for the C idiom
```C
#ifdef (WINDOWS)
#define FOO_API __cdecl
#else
#define FOO_API
#endif

int FOO_API foo(int);
```
in D becomes:
```D
extern(System) int foo(int);
```

Tools
-----

There are a number of tools to Automate the translation of C headers to D

* [Dstep](https://github.com/jacob-carlborg/dstep) 
* [dpp](https://github.com/atilaneves/dpp)


See also
--------
https://dlang.org/spec/interfaceToC.html
