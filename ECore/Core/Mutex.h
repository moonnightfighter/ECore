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

#ifndef Core_Mutex_H
#define Core_Mutex_H


#include "ECore/Core/Core.h"
#include "ECore/Core/Exception.h"
#include "ECore/Core/ScopedLock.h"
#include "ECore/Core/Mutex_POSIX.h"


namespace Core {


class Core_API Mutex: private MutexImpl
{
public:
	typedef Core::ScopedLock<Mutex> ScopedLock;
	
	Mutex();
	~Mutex();

	void lock();
	void lock(long milliseconds);
	bool tryLock();
	bool tryLock(long milliseconds);
	void unlock();
	
private:
	Mutex(const Mutex&);
	Mutex& operator = (const Mutex&);
};


class Core_API FastMutex: private FastMutexImpl
{
public:
	typedef Core::ScopedLock<FastMutex> ScopedLock;

	FastMutex();
	~FastMutex();

	void lock();
	void lock(long milliseconds);
	bool tryLock();
	bool tryLock(long milliseconds);
	void unlock();
	
private:
	FastMutex(const FastMutex&);
	FastMutex& operator = (const FastMutex&);
};


class Core_API NullMutex
{
public:
	typedef Core::ScopedLock<NullMutex> ScopedLock;
	
	NullMutex()
	{
	}
		
	~NullMutex()
	{
	}

	void lock()
	{
	}
		
	void lock(long)
	{
	}

	bool tryLock()
	{
		return true;
	}

	bool tryLock(long)
	{
		return true;
	}

	void unlock()
	{
	}
};


//
// inlines
//
inline void Mutex::lock()
{
	lockImpl();
}


inline void Mutex::lock(long milliseconds)
{
	if (!tryLockImpl(milliseconds))
		throw TimeoutException();
}


inline bool Mutex::tryLock()
{
	return tryLockImpl();
}


inline bool Mutex::tryLock(long milliseconds)
{
	return tryLockImpl(milliseconds);
}


inline void Mutex::unlock()
{
	unlockImpl();
}


inline void FastMutex::lock()
{
	lockImpl();
}


inline void FastMutex::lock(long milliseconds)
{
	if (!tryLockImpl(milliseconds))
		throw TimeoutException();
}


inline bool FastMutex::tryLock()
{
	return tryLockImpl();
}


inline bool FastMutex::tryLock(long milliseconds)
{
	return tryLockImpl(milliseconds);
}


inline void FastMutex::unlock()
{
	unlockImpl();
}


} // namespace Core


#endif  // Core_Mutex_H
