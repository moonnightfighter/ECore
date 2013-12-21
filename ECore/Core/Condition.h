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

#ifndef Core_Condition_H
#define Core_Condition_H


#include "ECore/Core/Core.h"
#include "ECore/Core/Mutex.h"
#include "ECore/Core/ScopedUnlock.h"
#include "ECore/Core/Event.h"
#include "ECore/Core/Exception.h"
#include <deque>


namespace Core {


class Core_API Condition
{
public:
    Condition();
    ~Condition();

    template <class Mtx>
    void wait(Mtx& mutex)
    {
        ScopedUnlock<Mtx> unlock(mutex, false);
        Event event;
        {
            FastMutex::ScopedLock lock(_mutex);
            mutex.unlock();
            enqueue(event);
        }
        event.wait();
    }

    template <class Mtx>
    void wait(Mtx& mutex, long milliseconds)
    {
        if (!tryWait(mutex, milliseconds))
            throw TimeoutException();
    }

    template <class Mtx>
    bool tryWait(Mtx& mutex, long milliseconds)
    {
        ScopedUnlock<Mtx> unlock(mutex, false);
        Event event;
        {
            FastMutex::ScopedLock lock(_mutex);
            mutex.unlock();
            enqueue(event);
        }
        if (!event.tryWait(milliseconds))
        {
            FastMutex::ScopedLock lock(_mutex);
            dequeue(event);
            return false;
        }
        return true;
    }

    void signal();

    void broadcast();

protected:
    void enqueue(Event& event);
    void dequeue();
    void dequeue(Event& event);

private:
    Condition(const Condition&);
    Condition& operator = (const Condition&);

    typedef std::deque<Event*> WaitQueue;

    FastMutex _mutex;
    WaitQueue _waitQueue;
};


} // namespace Core


#endif // Core_Condition_H
