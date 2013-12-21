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

#ifndef Core_Thread_POSIX_H
#define Core_Thread_POSIX_H


#include "ECore/Core/Core.h"
#include "ECore/Core/Runnable.h"
#include "ECore/Core/SignalHandler.h"
#include "ECore/Core/Event.h"
#include "ECore/Core/RefCountedObject.h"
#include "ECore/Core/AutoPtr.h"
#include <pthread.h>
#include <limits.h>
#if !defined(CORE_NO_SYS_SELECT_H)
#include <sys/select.h>
#endif
#include <errno.h>


namespace Core {


class Core_API ThreadImpl
{
public:	
    typedef pthread_t TIDImpl;
    typedef void (*Callable)(void*);

    enum Priority
    {
        PRIO_LOWEST_IMPL,
        PRIO_LOW_IMPL,
        PRIO_NORMAL_IMPL,
        PRIO_HIGH_IMPL,
        PRIO_HIGHEST_IMPL
    };

	enum Policy
	{
		POLICY_DEFAULT_IMPL = SCHED_OTHER
	};
	
    struct CallbackData: public RefCountedObject
    {
        CallbackData(): callback(0), pData(0)
        {
        }

        Callable  callback;
        void*     pData; 
    };

    ThreadImpl();				
    ~ThreadImpl();

    TIDImpl tidImpl() const;
    void setPriorityImpl(int prio);
    int getPriorityImpl() const;
	void setOSPriorityImpl(int prio, int policy = SCHED_OTHER);
    int getOSPriorityImpl() const;
	static int getMinOSPriorityImpl(int policy);
	static int getMaxOSPriorityImpl(int policy);
    void setStackSizeImpl(int size);
    int getStackSizeImpl() const;
    void startImpl(Runnable& target);
    void startImpl(Callable target, void* pData = 0);

    void joinImpl();
    bool joinImpl(long milliseconds);
    bool isRunningImpl() const;
    static void sleepImpl(long milliseconds);
    static void yieldImpl();
    static ThreadImpl* currentImpl();
    static TIDImpl currentTidImpl();

protected:
    static void* runnableEntry(void* pThread);
    static void* callableEntry(void* pThread);
	static int mapPrio(int prio, int policy = SCHED_OTHER);
	static int reverseMapPrio(int osPrio, int policy = SCHED_OTHER);

private:
    class CurrentThreadHolder
    {
    public:
        CurrentThreadHolder()
        {
            if (pthread_key_create(&_key, NULL))
                throw SystemException("cannot allocate thread context key");
        }
        ~CurrentThreadHolder()
        {
            pthread_key_delete(_key);
        }
        ThreadImpl* get() const
        {
            return reinterpret_cast<ThreadImpl*>(pthread_getspecific(_key));
        }
        void set(ThreadImpl* pThread)
        {
            pthread_setspecific(_key, pThread);
        }

    private:
        pthread_key_t _key;
    };

    struct ThreadData: public RefCountedObject
    {
        ThreadData():
            pRunnableTarget(0),
            pCallbackTarget(0),
            thread(0),
            prio(PRIO_NORMAL_IMPL),
			policy(SCHED_OTHER),
            done(false),
            stackSize(CORE_THREAD_STACK_SIZE)
        {
        }

        Runnable*     pRunnableTarget;
        AutoPtr<CallbackData> pCallbackTarget;
        pthread_t     thread;
        int           prio;
        int           osPrio;
		int           policy;
        Event         done;
        std::size_t   stackSize;
    };

    AutoPtr<ThreadData> _pData;

    static CurrentThreadHolder _currentThreadHolder;

#if defined(CORE_OS_FAMILY_UNIX)
    SignalHandler::JumpBufferVec _jumpBufferVec;
    friend class SignalHandler;
#endif
};


//
// inlines
//
inline int ThreadImpl::getPriorityImpl() const
{
    return _pData->prio;
}


inline int ThreadImpl::getOSPriorityImpl() const
{
    return _pData->osPrio;
}


inline bool ThreadImpl::isRunningImpl() const
{
    return _pData->pRunnableTarget != 0 ||
        (_pData->pCallbackTarget.get() != 0 && _pData->pCallbackTarget->callback != 0);
}


inline void ThreadImpl::yieldImpl()
{
    sched_yield();
}


inline int ThreadImpl::getStackSizeImpl() const
{
	return static_cast<int>(_pData->stackSize);
}


inline ThreadImpl::TIDImpl ThreadImpl::tidImpl() const
{
    return _pData->thread;
}


}   // namespace Core


#endif  // Core_Thread_POSIX_H
