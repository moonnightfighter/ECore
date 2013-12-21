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

#ifndef Core_ScopedLock_H
#define Core_ScopedLock_H


#include "ECore/Core/Core.h"


namespace Core {


template <class M>
class ScopedLock
{
public:
    explicit ScopedLock(M& mutex): _mutex(mutex)
    {
        _mutex.lock();
    }

    ScopedLock(M& mutex, long milliseconds): _mutex(mutex)
    {
        _mutex.lock(milliseconds);
    }

    ~ScopedLock()
    {
        _mutex.unlock();
    }

private:
    M& _mutex;

    ScopedLock();
    ScopedLock(const ScopedLock&);
    ScopedLock& operator = (const ScopedLock&);
};


template <class M>
class ScopedLockWithUnlock
{
public:
    explicit ScopedLockWithUnlock(M& mutex): _pMutex(&mutex)
    {
        _pMutex->lock();
    }

    ScopedLockWithUnlock(M& mutex, long milliseconds): _pMutex(&mutex)
    {
        _pMutex->lock(milliseconds);
    }

    ~ScopedLockWithUnlock()
    {
        unlock();
    }

    void unlock()
    {
        if (_pMutex)
        {
            _pMutex->unlock();
            _pMutex = 0;
        }
    }

private:
    M* _pMutex;

    ScopedLockWithUnlock();
    ScopedLockWithUnlock(const ScopedLockWithUnlock&);
    ScopedLockWithUnlock& operator = (const ScopedLockWithUnlock&);
};


}   // namespace Core


#endif  // Core_ScopedLock_H
