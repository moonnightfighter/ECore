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

#ifndef Core_Core_H
#define Core_Core_H


#include "ECore/Core/Config.h"


#if !defined(Core_API)
#define Core_API
#endif


#include "ECore/Core/Platform.h"


#define CORE_JOIN(X, Y) CORE_DO_JOIN(X, Y)
#define CORE_DO_JOIN(X, Y) CORE_DO_JOIN2(X, Y)
#define CORE_DO_JOIN2(X, Y) X##Y


#include <assert.h>
#define core_assert(cond) assert(cond)
#define core_assert_printf(cond, msg) do{ if (!(cond)) printf("[%s][%s:%d]\n", msg, __FILE__, __LINE__); core_assert(cond); }while(0);
#if defined(_DEBUG)
#define core_assert_dbg(cond) core_assert_printf(cond, "dbg") //core_assert(cond)
#else
#define core_assert_dbg(cond)
#endif
#define core_check_ptr(ptr) assert(ptr != 0)
#define core_bugcheck() core_assert(0)
#define core_bugcheck_msg(msg) core_assert_printf(0, msg)
#define core_debugger_msg(msg) core_assert_printf(0, msg)


#include "ECore/Core/Types.h"
#include <stdio.h>
#include <string>
#include <string.h>


#endif  // Core_Core_H
