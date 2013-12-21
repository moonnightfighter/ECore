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

#ifndef Core_ThreadLocal_H
#define Core_ThreadLocal_H


#include "ECore/Core/Core.h"
#include <map>


namespace Core {


class Core_API TLSAbstractSlot
{
public:
    TLSAbstractSlot();
    virtual ~TLSAbstractSlot();
};


template <class C>
class TLSSlot: public TLSAbstractSlot
{
public:
    TLSSlot():
      _value()
      {
      }

      ~TLSSlot()
      {
      }

      C& value()
      {
          return _value;
      }

private:
    TLSSlot(const TLSSlot&);
    TLSSlot& operator = (const TLSSlot&);

    C _value;
};


class Core_API ThreadLocalStorage
{
public:
    ThreadLocalStorage();
    ~ThreadLocalStorage();

    TLSAbstractSlot*& get(const void* key);

    static ThreadLocalStorage& current();

    static void clear();

private:
    typedef std::map<const void*, TLSAbstractSlot*> TLSMap;

    TLSMap _map;

    friend class Thread;
};


template <class C>
class ThreadLocal
{
    typedef TLSSlot<C> Slot;

public:
    ThreadLocal()
    {
    }

    ~ThreadLocal()
    {
    }

    C* operator -> ()
    {
        return &get();
    }

    C& operator * ()
    {
        return get();
    }

    C& get()
    {
        TLSAbstractSlot*& p = ThreadLocalStorage::current().get(this);
        if (!p) p = new Slot;
        return static_cast<Slot*>(p)->value();
    }

private:
    ThreadLocal(const ThreadLocal&);
    ThreadLocal& operator = (const ThreadLocal&);
};


}   // namespace Core


#endif  // Core_ThreadLocal_H
