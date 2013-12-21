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

#ifndef Core_BufferQueue_H
#define Core_BufferQueue_H


#include "ECore/Core/Mutex.h"
#include <list>


namespace Core {


template <class T>
class BufferQueue
{
public:
    typedef T           value_t;
    typedef T&          reference_t;
    typedef const T&    const_reference_t;
    typedef std::size_t size_t;

    BufferQueue(std::size_t max): _max(max)
    {
    }

    ~BufferQueue()
    {
    }

    bool enqueue(const_reference_t pkg)
    {
        FastMutex::ScopedLock lock(_lock);
        if (_pq.size() < _max)
        {
            _pq.push_back(pkg);
            return true;
        }
        else
        {
            return false;
        }
    }

    bool dequeue(value_t& val)
    {
        FastMutex::ScopedLock lock(_lock);
        if (_pq.size() != 0)
        {
            val = _pq.front();
            _pq.pop_front();
            return true;
        }
        else
        {
            return false;
        }
    }

    void dequeue(std::list<value_t>& lst, size_t max)
    {
        FastMutex::ScopedLock lock(_lock);
        while (_pq.size() != 0 && max-- > 0)
        {
            lst.push_back(_pq.front());
            _pq.pop_front();
        }
    }

    size_t size()
    {
        FastMutex::ScopedLock lock(_lock);
        return _pq.size();
    }

    size_t maxSize()
    {
        return _max;
    }

    bool empty()
    {
        FastMutex::ScopedLock lock(_lock);
        return _pq.empty();
    }

    FastMutex& lock()
    {
        return _lock;
    }

private:
    std::size_t _max;
    FastMutex _lock;
    std::list<value_t> _pq;
};


}   // namespace Core


#endif  // Core_BufferQueue_H
