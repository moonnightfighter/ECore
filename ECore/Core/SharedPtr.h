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

#ifndef Core_SharedPtr_H
#define Core_SharedPtr_H


#include "ECore/Core/Core.h"
#include "ECore/Core/Exception.h"
#include "ECore/Core/AtomicCounter.h"
#include <algorithm>


namespace Core {


class ReferenceCounter
{
public:
    ReferenceCounter(): _cnt(1)
    {
    }

    void duplicate()
    {
        ++_cnt;
    }

    int release()
    {
        return --_cnt;
    }

    int referenceCount() const
    {
        return _cnt.value();
    }

private:
    AtomicCounter _cnt;
};


template <class C>
class ReleasePolicy
{
public:
    static void release(C* pObj)
    {
        delete pObj;
    }
};


template <class C>
class ReleaseArrayPolicy
{
public:
    static void release(C* pObj)
    {
        delete [] pObj;
    }
};


template <class C, class RC = ReferenceCounter, class RP = ReleasePolicy<C> >
class SharedPtr
{
public:
    SharedPtr(): _pCounter(new RC), _ptr(0)
    {
    }

    SharedPtr(C* ptr): _pCounter(new RC), _ptr(ptr)
    {
    }

    template <class Other, class OtherRP> 
    SharedPtr(const SharedPtr<Other, RC, OtherRP>& ptr): _pCounter(ptr._pCounter), _ptr(const_cast<Other*>(ptr.get()))
    {
        _pCounter->duplicate();
    }

    SharedPtr(const SharedPtr& ptr): _pCounter(ptr._pCounter), _ptr(ptr._ptr)
    {
        _pCounter->duplicate();
    }

    ~SharedPtr()
    {
        release();
    }

    SharedPtr& assign(C* ptr)
    {
        if (get() != ptr)
        {
            RC* pTmp = new RC;
            release();
            _pCounter = pTmp;
            _ptr = ptr;
        }
        return *this;
    }

    SharedPtr& assign(const SharedPtr& ptr)
    {
        if (&ptr != this)
        {
            SharedPtr tmp(ptr);
            swap(tmp);
        }
        return *this;
    }

    template <class Other, class OtherRP>
    SharedPtr& assign(const SharedPtr<Other, RC, OtherRP>& ptr)
    {
        if (ptr.get() != _ptr)
        {
            SharedPtr tmp(ptr);
            swap(tmp);
        }
        return *this;
    }

    SharedPtr& operator = (C* ptr)
    {
        return assign(ptr);
    }

    SharedPtr& operator = (const SharedPtr& ptr)
    {
        return assign(ptr);
    }

    template <class Other, class OtherRP>
    SharedPtr& operator = (const SharedPtr<Other, RC, OtherRP>& ptr)
    {
        return assign<Other>(ptr);
    }

    void swap(SharedPtr& ptr)
    {
        std::swap(_ptr, ptr._ptr);
        std::swap(_pCounter, ptr._pCounter);
    }

    template <class Other> 
    SharedPtr<Other, RC, RP> cast() const
    {
        Other* pOther = dynamic_cast<Other*>(_ptr);
        if (pOther)
            return SharedPtr<Other, RC, RP>(_pCounter, pOther);
        return SharedPtr<Other, RC, RP>();
    }

    template <class Other> 
    SharedPtr<Other, RC, RP> unsafeCast() const
    {
        Other* pOther = static_cast<Other*>(_ptr);
        return SharedPtr<Other, RC, RP>(_pCounter, pOther);
    }

    C* operator -> ()
    {
        return deref();
    }

    const C* operator -> () const
    {
        return deref();
    }

    C& operator * ()
    {
        return *deref();
    }

    const C& operator * () const
    {
        return *deref();
    }

    C* get()
    {
        return _ptr;
    }

    const C* get() const
    {
        return _ptr;
    }

    operator C* ()
    {
        return _ptr;
    }

    operator const C* () const
    {
        return _ptr;
    }

    bool operator ! () const
    {
        return _ptr == 0;
    }

    bool isNull() const
    {
        return _ptr == 0;
    }

    bool operator == (const SharedPtr& ptr) const
    {
        return get() == ptr.get();
    }

    bool operator == (const C* ptr) const
    {
        return get() == ptr;
    }

    bool operator == (C* ptr) const
    {
        return get() == ptr;
    }

    bool operator != (const SharedPtr& ptr) const
    {
        return get() != ptr.get();
    }

    bool operator != (const C* ptr) const
    {
        return get() != ptr;
    }

    bool operator != (C* ptr) const
    {
        return get() != ptr;
    }

    bool operator < (const SharedPtr& ptr) const
    {
        return get() < ptr.get();
    }

    bool operator < (const C* ptr) const
    {
        return get() < ptr;
    }

    bool operator < (C* ptr) const
    {
        return get() < ptr;
    }

    bool operator <= (const SharedPtr& ptr) const
    {
        return get() <= ptr.get();
    }

    bool operator <= (const C* ptr) const
    {
        return get() <= ptr;
    }

    bool operator <= (C* ptr) const
    {
        return get() <= ptr;
    }

    bool operator > (const SharedPtr& ptr) const
    {
        return get() > ptr.get();
    }

    bool operator > (const C* ptr) const
    {
        return get() > ptr;
    }

    bool operator > (C* ptr) const
    {
        return get() > ptr;
    }

    bool operator >= (const SharedPtr& ptr) const
    {
        return get() >= ptr.get();
    }

    bool operator >= (const C* ptr) const
    {
        return get() >= ptr;
    }

    bool operator >= (C* ptr) const
    {
        return get() >= ptr;
    }

    int referenceCount() const
    {
        return _pCounter->referenceCount();
    }

private:
    C* deref() const
    {
        if (!_ptr)
            throw NullPointerException();

        return _ptr;
    }

    void release()
    {
        core_assert_dbg (_pCounter);
        int i = _pCounter->release();
        if (i == 0)
        {
            RP::release(_ptr);
            _ptr = 0;

            delete _pCounter;
            _pCounter = 0;
        }
    }

    SharedPtr(RC* pCounter, C* ptr): _pCounter(pCounter), _ptr(ptr)
    {
        core_assert_dbg (_pCounter);
        _pCounter->duplicate();
    }

private:
    RC* _pCounter;
    C*  _ptr;

    template <class OtherC, class OtherRC, class OtherRP> friend class SharedPtr;
};


template <class C, class RC, class RP>
inline void swap(SharedPtr<C, RC, RP>& p1, SharedPtr<C, RC, RP>& p2)
{
    p1.swap(p2);
}


}   // namespace Core


#endif  // Core_SharedPtr_H
