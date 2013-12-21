/*
The LGPL License (LGPL)

Copyright (c) 2012-2013 moon

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef Core_Platform_H
#define Core_Platform_H


#define CORE_OS_LINUX         0x0005


#if defined(linux) || defined(__linux) || defined(__linux__)
#define CORE_OS_FAMILY_UNIX 1
#define CORE_OS CORE_OS_LINUX
#endif

#if defined(_WIN32) || defined(_WIN64)
#define CORE_OS_FAMILY_WINDOWS 1
#define CORE_OS CORE_OS_WINDOWS_NT
#endif


#if !defined(CORE_OS)
#error "Unknown Platform."
#endif



#endif  // Core_Platform_H
