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

#ifndef Core_Buffer_H
#define Core_Buffer_H


#include "ECore/Core/Core.h"
#include <cstring>
#include <cstddef>


namespace Core {


template <class T>
class Buffer
{
public:
    Buffer():
      _size(0),
      _ptr(0)
    {
    }

    Buffer(std::size_t size):
    _size(size),
      _ptr(new T[size])
    {
    }

    ~Buffer()
    {
        if (_ptr)
        {
            delete [] _ptr;
        }
    }

    void resize(std::size_t newSize, bool preserveContent = true)
    {
        T* ptr = 0;
        if (newSize != 0)
        {
            ptr = new T[newSize];
        }

        if (preserveContent)
        {
            std::size_t n = newSize > _size ? _size : newSize;
            std::memcpy(ptr, _ptr, n*sizeof(T));
        }

        if (_ptr)
        {
            delete [] _ptr;
        }

        _ptr  = ptr;
        _size = newSize;
    }

    std::size_t size() const
    {
        return _size;
    }

    T* begin()
    {
        return _ptr;
    }

    const T* begin() const
    {
        return _ptr;
    }

    T* end()
    {
        return _ptr + _size;
    }

    const T* end() const
    {
        return _ptr + _size;
    }

    T& operator [] (std::size_t index)
    {
        core_assert_printf (index < _size, "index < _size");
        return _ptr[index];
    }

    const T& operator [] (std::size_t index) const
    {
        core_assert_printf (index < _size, "index < _size");
        return _ptr[index];
    }

private:
    //Buffer();
    Buffer(const Buffer&);
    Buffer& operator = (const Buffer&);

    std::size_t _size;
    T* _ptr;
};


}   // namespace Core


#endif  // Core_Buffer_H
