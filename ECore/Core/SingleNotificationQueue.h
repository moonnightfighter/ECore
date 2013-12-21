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

#ifndef Core_SingleNotificationQueue_H
#define Core_SingleNotificationQueue_H


#include "ECore/Core/Event.h"
#include <deque>
#include <vector>


namespace Core {


template <class T>
class SingleNotificationQueue
{
public:
    inline SingleNotificationQueue(std::size_t max):
        _max(max)
    {
    }

    inline ~SingleNotificationQueue()
    {
        clear();
    }

public:
    inline bool enqueue(T& ev)
    {
        bool rc = false;
        {
            Core::FastMutex::ScopedLock lock(_lock);

            if (_q.size() < _max)
            {
                _q.push_back(ev);
                rc = true;
            }
        }
        
        if (rc)
        {
            _event.set();
        }

        return rc;
    }

    //bool dequeue(T& ev)
    //{
    //    Core::FastMutex::ScopedLock lock(_lock);

    //    return dequeueOne(ev);
    //}

    inline bool waitDequeue(std::vector<T>& evs)
    {
        _event.wait();

        bool rc = false;
        {
            Core::FastMutex::ScopedLock lock(_lock);
            rc = dequeue(evs);
        }
        
        return rc;
    }

    inline bool waitDequeue(std::vector<T>& evs, long milliseconds)
    {
        bool rc = false;
        try
        {
            _event.wait(milliseconds);
            {
                Core::FastMutex::ScopedLock lock(_lock);
                rc = dequeue(evs);
            }

            return rc;
        }
        catch (...)
        {
            return rc;
        }
    }

    inline bool empty()
    {
        return 0 == size();
    }

    inline std::size_t size()
    {
        Core::FastMutex::ScopedLock lock(_lock);
        return _q.size();
    }

    inline std::size_t maxSize()
    {
        return _max;
    }

    inline void clear()
    {
        Core::FastMutex::ScopedLock lock(_lock);
        _q.clear();
    }

    inline void wakeUpAll()
    {
        _event.set();
    }

protected:
    inline bool dequeue(std::vector<T>& evs)
    {
        while (_q.size() != 0)
        {
            evs.push_back(_q.front());
            _q.pop_front();
        }

        return evs.size() != 0;
    }

private:
    typedef std::deque<T> NfQueue;

    std::size_t _max;
    
    Event _event;
    NfQueue _q;
    mutable FastMutex _lock;
};


}   // namespace Core


#endif  // Core_SingleNotificationQueue_H
