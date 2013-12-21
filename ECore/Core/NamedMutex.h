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

#ifndef Core_NamedMutex_H
#define Core_NamedMutex_H


#include "ECore/Core/Core.h"
#include "ECore/Core/ScopedLock.h"
#if defined(CORE_OS_FAMILY_UNIX)
#include "ECore/Core/NamedMutex_UNIX.h"
#endif


namespace Core {


class Core_API NamedMutex: private NamedMutexImpl
{
public:
    typedef Core::ScopedLock<NamedMutex> ScopedLock;

    NamedMutex(const std::string& name);
    ~NamedMutex();

    void lock();

    bool tryLock();

    void unlock();

private:
    NamedMutex();
    NamedMutex(const NamedMutex&);
    NamedMutex& operator = (const NamedMutex&);
};


//
// inlines
//
inline void NamedMutex::lock()
{
    lockImpl();
}


inline bool NamedMutex::tryLock()
{
    return tryLockImpl();
}


inline void NamedMutex::unlock()
{
    unlockImpl();
}


} // namespace Core


#endif  // Core_NamedMutex_H
