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

#ifndef Core_Thread_H
#define Core_Thread_H


#include "ECore/Core/Core.h"
#include "ECore/Core/Mutex.h"
#include "ECore/Core/Thread_POSIX.h"


namespace Core {


class Runnable;
class ThreadLocalStorage;


class Core_API Thread: private ThreadImpl
{
public:	
    typedef ThreadImpl::TIDImpl TID;

    using ThreadImpl::Callable;

    enum Priority
    {
        PRIO_LOWEST  = PRIO_LOWEST_IMPL,
        PRIO_LOW     = PRIO_LOW_IMPL,
        PRIO_NORMAL  = PRIO_NORMAL_IMPL,
        PRIO_HIGH    = PRIO_HIGH_IMPL,
        PRIO_HIGHEST = PRIO_HIGHEST_IMPL
    };
	
	enum Policy
	{
		POLICY_DEFAULT = POLICY_DEFAULT_IMPL
	};

    Thread();
    Thread(const std::string& name);
    ~Thread();

    int id() const;

    TID tid() const;

    std::string name() const;

    std::string getName() const;

    void setName(const std::string& name);

    void setPriority(Priority prio);

    Priority getPriority() const;

	void setOSPriority(int prio, int policy = POLICY_DEFAULT);
    int getOSPriority() const;

	static int getMinOSPriority(int policy = POLICY_DEFAULT);
	static int getMaxOSPriority(int policy = POLICY_DEFAULT);

    void setStackSize(int size);
    int getStackSize() const;

    void start(Runnable& target);
    void start(Callable target, void* pData = 0);

    void join();
    void join(long milliseconds);
    bool tryJoin(long milliseconds);

    bool isRunning() const;

    static void sleep(long milliseconds);

    static void yield();

    static Thread* current();

    static TID currentTid(); 

protected:
    ThreadLocalStorage& tls();

    void clearTLS();

    std::string makeName();

    static int uniqueId();

private:
    Thread(const Thread&);
    Thread& operator = (const Thread&);

    int                 _id;
    std::string         _name;
    ThreadLocalStorage* _pTLS;
    mutable FastMutex   _mutex;

    friend class ThreadLocalStorage;
    friend class PooledThread;
};


//
// inlines
//
inline Thread::TID Thread::tid() const
{
    return tidImpl();
}


inline int Thread::id() const
{
    return _id;
}


inline std::string Thread::name() const
{
    FastMutex::ScopedLock lock(_mutex);

    return _name;
}


inline std::string Thread::getName() const
{
    FastMutex::ScopedLock lock(_mutex);

    return _name;
}


inline bool Thread::isRunning() const
{
    return isRunningImpl();
}


inline void Thread::sleep(long milliseconds)
{
    sleepImpl(milliseconds);
}


inline void Thread::yield()
{
    yieldImpl();
}


inline Thread* Thread::current()
{
    return static_cast<Thread*>(currentImpl());
}


inline void Thread::setOSPriority(int prio, int policy)
{
	setOSPriorityImpl(prio, policy);	
}


inline int Thread::getOSPriority() const
{
    return getOSPriorityImpl();
}


inline int Thread::getMinOSPriority(int policy)
{
	return ThreadImpl::getMinOSPriorityImpl(policy);
}


inline int Thread::getMaxOSPriority(int policy)
{
	return ThreadImpl::getMaxOSPriorityImpl(policy);
}


inline void Thread::setStackSize(int size)
{
    setStackSizeImpl(size);
}


inline int Thread::getStackSize() const
{
    return getStackSizeImpl();
}


inline Thread::TID Thread::currentTid()
{
    return currentTidImpl();
}


}   // namespace Core


#endif  // Core_Thread_H
