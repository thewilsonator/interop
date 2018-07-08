Using D with C++
================

D dynamic arrays
----------------

When a dynamic array appears in an `extern(C++)` function signature is mangled as if it were 
```C++
template<typename T> struct __dslice { ... };
```


See also
--------
[dslice.h](c++/dslice.h)
https://dlang.org/spec/cpp_interface.html
