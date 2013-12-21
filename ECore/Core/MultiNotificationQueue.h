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

#ifndef Core_MultiNotificationQueue_H
#define Core_MultiNotificationQueue_H


#include "ECore/Core/Mutex.h"
#include "ECore/Core/Event.h"
#include <deque>


namespace Core {


template <class T>
class MultiNotificationQueue
{
public:
    inline MultiNotificationQueue(std::size_t max):
        _max(max)
    {
    }

    inline ~MultiNotificationQueue()
    {
        clear();
    }

    inline bool enqueue(T& ev)
    {
        FastMutex::ScopedLock lock(_mutex);
        if (_waitQueue.empty())
        {
            if (_nfQueue.size() < _max)
            {
                _nfQueue.push_back(ev);
                return true;
            }
            return false;
        }
        else
        {
            WaitInfo* pWI = _waitQueue.front();
            _waitQueue.pop_front();
            pWI->pNf = ev;
            pWI->nfAvailable.set();
            return true;
        }	
    }

    inline bool enqueueUrgent(T& ev)
    {
        FastMutex::ScopedLock lock(_mutex);
        if (_waitQueue.empty())
        {
            if (_nfQueue.size() < _max)
            {
                _nfQueue.push_front(ev);
                return true;
            }
            return false;
        }
        else
        {
            WaitInfo* pWI = _waitQueue.front();
            _waitQueue.pop_front();
            pWI->pNf = ev;
            pWI->nfAvailable.set();
            return true;
        }	
    }

    inline void waitDequeue(T& ev)
    {
        WaitInfo* pWI = 0;
        {
            FastMutex::ScopedLock lock(_mutex);
            if (dequeueOne(ev))
            {
                return;
            }
            pWI = new WaitInfo;
            _waitQueue.push_back(pWI);
        }
        pWI->nfAvailable.wait();
        ev = pWI->pNf;
        delete pWI;
    }

    inline void waitDequeue(T& ev, long milliseconds)
    {
        WaitInfo* pWI = 0;
        {
            FastMutex::ScopedLock lock(_mutex);
            if (dequeueOne(ev))
            {
                return;
            }
            pWI = new WaitInfo;
            _waitQueue.push_back(pWI);
        }

        if (pWI->nfAvailable.tryWait(milliseconds))
        {
            ev = pWI->pNf;
        }
        else
        {
            FastMutex::ScopedLock lock(_mutex);
            ev = pWI->pNf;
            for (typename WaitQueue::iterator it = _waitQueue.begin(); it != _waitQueue.end(); ++it)
            {
                if (*it == pWI)
                {
                    _waitQueue.erase(it);
                    break;
                }
            }
        }
        delete pWI;
    }

    inline void wakeUpAll()
    {
        FastMutex::ScopedLock lock(_mutex);
        for (typename WaitQueue::iterator it = _waitQueue.begin(); it != _waitQueue.end(); ++it)
        {
            (*it)->nfAvailable.set();
        }
        _waitQueue.clear();
    }

    inline bool empty() const
    {
        FastMutex::ScopedLock lock(_mutex);
        return _nfQueue.empty();
    }

    inline std::size_t size() const
    {
        FastMutex::ScopedLock lock(_mutex);
        return _nfQueue.size();
    }

    inline std::size_t maxSize()
    {
        return _max;
    }

    inline void clear()
    {
        FastMutex::ScopedLock lock(_mutex);
        _nfQueue.clear();
    }

    inline bool hasIdleThreads() const
    {
        FastMutex::ScopedLock lock(_mutex);
        return !_waitQueue.empty();
    }

protected:
    inline bool dequeueOne(T& ev)
    {
        if (!_nfQueue.empty())
        {
            ev = _nfQueue.front();
            _nfQueue.pop_front();
            return true;
        }
        return false;
    }

private:
    typedef std::deque<T> NfQueue;
    struct WaitInfo
    {
        T pNf;
        Event nfAvailable;
    };
    typedef std::deque<WaitInfo*> WaitQueue;

    std::size_t _max;

    NfQueue           _nfQueue;
    WaitQueue         _waitQueue;
    mutable FastMutex _mutex;
};


}  // namespace Core


#endif  // Core_MultiNotificationQueue_H
