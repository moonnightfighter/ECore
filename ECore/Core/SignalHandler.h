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

#ifndef Core_SignalHandler_H
#define Core_SignalHandler_H


#include "ECore/Core/Core.h"


#if defined(CORE_OS_FAMILY_UNIX)


#include <vector>
#include <setjmp.h>


namespace Core {


class Core_API SignalHandler
{
public:
    SignalHandler();
    ~SignalHandler();

    sigjmp_buf& jumpBuffer();

    static void throwSignalException(int sig);

    static void install();

protected:
    static void handleSignal(int sig);

    struct JumpBuffer
    {
        sigjmp_buf buf;
    };
    typedef std::vector<JumpBuffer> JumpBufferVec;

    static JumpBufferVec& jumpBufferVec();

private:
    static JumpBufferVec _jumpBufferVec;

    friend class ThreadImpl;
};


#ifndef CORE_NO_SIGNAL_HANDLER
#define core_throw_on_signal \
Core::SignalHandler _core_signalHandler; \
int _core_signal = sigsetjmp(_core_signalHandler.jumpBuffer(), 1); \
if (_core_signal) _core_signalHandler.throwSignalException(_core_signal);
#else
#define core_throw_on_signal
#endif


}   // namespace Core


#endif  // CORE_OS_FAMILY_UNIX


#endif  // Core_SignalHandler_H
