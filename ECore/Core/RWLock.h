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

#ifndef Core_RWLock_H
#define Core_RWLock_H


#include "ECore/Core/Core.h"
#include "ECore/Core/Exception.h"
#include "ECore/Core/RWLock_POSIX.h"


namespace Core {


class ScopedRWLock;
class ScopedReadRWLock;
class ScopedWriteRWLock;


class Core_API RWLock: private RWLockImpl
{
public:
    typedef ScopedRWLock ScopedLock;
    typedef ScopedReadRWLock ScopedReadLock;
    typedef ScopedWriteRWLock ScopedWriteLock;

    RWLock();
    ~RWLock();

    void readLock();
    bool tryReadLock();
    void writeLock();
    bool tryWriteLock();

    void unlock();

private:
    RWLock(const RWLock&);
    RWLock& operator = (const RWLock&);
};


class Core_API ScopedRWLock
{
public:
    ScopedRWLock(RWLock& rwl, bool write = false);
    ~ScopedRWLock();

private:
    RWLock& _rwl;

    ScopedRWLock();
    ScopedRWLock(const ScopedRWLock&);
    ScopedRWLock& operator = (const ScopedRWLock&);
};


class Core_API ScopedReadRWLock : public ScopedRWLock
{
public:
    ScopedReadRWLock(RWLock& rwl);
    ~ScopedReadRWLock();
};


class Core_API ScopedWriteRWLock : public ScopedRWLock
{
public:
    ScopedWriteRWLock(RWLock& rwl);
    ~ScopedWriteRWLock();
};


//
// inlines
//
inline void RWLock::readLock()
{
    readLockImpl();
}


inline bool RWLock::tryReadLock()
{
    return tryReadLockImpl();
}


inline void RWLock::writeLock()
{
    writeLockImpl();
}


inline bool RWLock::tryWriteLock()
{
    return tryWriteLockImpl();
}


inline void RWLock::unlock()
{
    unlockImpl();
}


inline ScopedRWLock::ScopedRWLock(RWLock& rwl, bool write): _rwl(rwl)
{
    if (write)
        _rwl.writeLock();
    else
        _rwl.readLock();
}


inline ScopedRWLock::~ScopedRWLock()
{
    _rwl.unlock();
}


inline ScopedReadRWLock::ScopedReadRWLock(RWLock& rwl): ScopedRWLock(rwl, false)
{
}


inline ScopedReadRWLock::~ScopedReadRWLock()
{
}


inline ScopedWriteRWLock::ScopedWriteRWLock(RWLock& rwl): ScopedRWLock(rwl, true)
{
}


inline ScopedWriteRWLock::~ScopedWriteRWLock()
{
}


}   // namespace Core


#endif  // Core_RWLock_H
