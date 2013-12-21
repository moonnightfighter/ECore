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

#ifndef Core_AtomicCounter_H
#define Core_AtomicCounter_H


#include "ECore/Core/Core.h"
#if ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 3) || __GNUC__ > 4)
#if !defined(CORE_HAVE_GCC_ATOMICS) && !defined(CORE_NO_GCC_ATOMICS)
#define CORE_HAVE_GCC_ATOMICS
#endif
#endif // CORE_OS
#include "ECore/Core/Mutex.h"


namespace Core {


class Core_API AtomicCounter
{
public:
    typedef int ValueType;

    AtomicCounter();
    explicit AtomicCounter(ValueType initialValue);
    AtomicCounter(const AtomicCounter& counter);
    ~AtomicCounter();

    AtomicCounter& operator = (const AtomicCounter& counter);

    AtomicCounter& operator = (ValueType value);

    operator ValueType () const;

    ValueType value() const;

    ValueType operator ++ (); // prefix

    ValueType operator ++ (int); // postfix

    ValueType operator -- (); // prefix

    ValueType operator -- (int); // postfix

    bool operator ! () const;

private:
#if defined(CORE_HAVE_GCC_ATOMICS)
    typedef int ImplType;
#else
    struct ImplType
    {
        mutable FastMutex mutex;
        volatile int      value;
    };
#endif // CORE_OS

    ImplType m_counter;
};


//
// inlines
//


#if defined(CORE_HAVE_GCC_ATOMICS)


inline AtomicCounter::operator AtomicCounter::ValueType () const
{
    return m_counter;
}


inline AtomicCounter::ValueType AtomicCounter::value() const
{
    return m_counter;
}


inline AtomicCounter::ValueType AtomicCounter::operator ++ () // prefix
{
    return __sync_add_and_fetch(&m_counter, 1);
}


inline AtomicCounter::ValueType AtomicCounter::operator ++ (int) // postfix
{
    return __sync_fetch_and_add(&m_counter, 1);
}


inline AtomicCounter::ValueType AtomicCounter::operator -- () // prefix
{
    return __sync_sub_and_fetch(&m_counter, 1);
}


inline AtomicCounter::ValueType AtomicCounter::operator -- (int) // postfix
{
    return __sync_fetch_and_sub(&m_counter, 1);
}


inline bool AtomicCounter::operator ! () const
{
    return m_counter == 0;
}


#else


inline AtomicCounter::operator AtomicCounter::ValueType () const
{
    ValueType result;
    {
        FastMutex::ScopedLock lock(m_counter.mutex);
        result = m_counter.value;
    }
    return result;
}


inline AtomicCounter::ValueType AtomicCounter::value() const
{
    ValueType result;
    {
        FastMutex::ScopedLock lock(m_counter.mutex);
        result = m_counter.value;
    }
    return result;
}


inline AtomicCounter::ValueType AtomicCounter::operator ++ () // prefix
{
    ValueType result;
    {
        FastMutex::ScopedLock lock(m_counter.mutex);
        result = ++m_counter.value;
    }
    return result;
}


inline AtomicCounter::ValueType AtomicCounter::operator ++ (int) // postfix
{
    ValueType result;
    {
        FastMutex::ScopedLock lock(m_counter.mutex);
        result = m_counter.value++;
    }
    return result;
}


inline AtomicCounter::ValueType AtomicCounter::operator -- () // prefix
{
    ValueType result;
    {
        FastMutex::ScopedLock lock(m_counter.mutex);
        result = --m_counter.value;
    }
    return result;
}


inline AtomicCounter::ValueType AtomicCounter::operator -- (int) // postfix
{
    ValueType result;
    {
        FastMutex::ScopedLock lock(m_counter.mutex);
        result = m_counter.value--;
    }
    return result;
}


inline bool AtomicCounter::operator ! () const
{
    bool result;
    {
        FastMutex::ScopedLock lock(m_counter.mutex);
        result = m_counter.value == 0;
    }
    return result;
}


#endif // CORE_OS


}   // namespace Core


#endif  // Core_AtomicCounter_H

