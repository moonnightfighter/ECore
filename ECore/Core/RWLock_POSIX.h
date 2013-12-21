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

#ifndef Core_RWLock_POSIX_H
#define Core_RWLock_POSIX_H


#include "ECore/Core/Core.h"
#include "ECore/Core/Exception.h"
#include <pthread.h>
#include <errno.h>


namespace Core {


class Core_API RWLockImpl
{
protected:
    RWLockImpl();
    ~RWLockImpl();
    void readLockImpl();
    bool tryReadLockImpl();
    void writeLockImpl();
    bool tryWriteLockImpl();
    void unlockImpl();

private:
    pthread_rwlock_t _rwl;
};


//
// inlines
//
inline void RWLockImpl::readLockImpl()
{
    if (pthread_rwlock_rdlock(&_rwl)) 
        throw SystemException("cannot lock reader/writer lock");
}


inline bool RWLockImpl::tryReadLockImpl()
{
    int rc = pthread_rwlock_tryrdlock(&_rwl);
    if (rc == 0)
        return true;
    else if (rc == EBUSY)
        return false;
    else
        throw SystemException("cannot lock reader/writer lock");

}


inline void RWLockImpl::writeLockImpl()
{
    if (pthread_rwlock_wrlock(&_rwl)) 
        throw SystemException("cannot lock reader/writer lock");
}


inline bool RWLockImpl::tryWriteLockImpl()
{
    int rc = pthread_rwlock_trywrlock(&_rwl);
    if (rc == 0)
        return true;
    else if (rc == EBUSY)
        return false;
    else
        throw SystemException("cannot lock reader/writer lock");

}


inline void RWLockImpl::unlockImpl()
{
    if (pthread_rwlock_unlock(&_rwl))
        throw SystemException("cannot unlock mutex");
}


}   // namespace Core


#endif  // Core_RWLock_POSIX_H
