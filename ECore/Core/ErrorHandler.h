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

#ifndef Core_ErrorHandler_H
#define Core_ErrorHandler_H


#include "ECore/Core/Core.h"
#include "ECore/Core/Exception.h"
#include "ECore/Core/Mutex.h"


namespace Core {


class Core_API ErrorHandler
{
public:
    ErrorHandler();
    virtual ~ErrorHandler();

    virtual void exception(const Exception& exc);

    virtual void exception(const std::exception& exc);

    virtual void exception();

    static void handle(const Exception& exc);

    static void handle(const std::exception& exc);

    static void handle();

    static ErrorHandler* set(ErrorHandler* pHandler);

    static ErrorHandler* get();

protected:	
    static ErrorHandler* defaultHandler();

private:
    static ErrorHandler* _pHandler;
    static FastMutex     _mutex;
};


//
// inlines
//
inline ErrorHandler* ErrorHandler::get()
{
    return _pHandler;
}


}   // namespace Core


#endif  // Core_ErrorHandler_H
