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

#ifndef Core_SmartBuffer_H
#define Core_SmartBuffer_H


#include "ECore/Core/Core.h"
#include <cstring>
#include <cstddef>


namespace Core {


template <class T, std::size_t alloc_block_size = 1024>
class SmartBuffer
{
public:
    inline SmartBuffer():
        _max(0),
        _size(0),
        _ptr(0)
    {
    }

    inline SmartBuffer(std::size_t size):
        _max(0),
        _size(0),
        _ptr(0)
    {
        realloc(size);
    }

    inline SmartBuffer(const SmartBuffer& other):
        _max(0),
        _size(0),
        _ptr(0)
    {
        if (this != &other)
        {
            assign((T*)other.begin(), other.size());
        }
    }

    inline SmartBuffer& operator = (const SmartBuffer& other)
    {
        if (this != &other)
        {
            assign((T*)other.begin(), other.size());
        }
    }

    inline ~SmartBuffer()
    {
        if (_ptr)
        {
            delete [] _ptr;
        }
    }

    inline void realloc(std::size_t newSize, bool preserveContent = false)
    {
        if (newSize != 0)
        {
            std::size_t alloc_size = newSize / alloc_block_size * alloc_block_size;
            if (alloc_size < newSize)
            {
                alloc_size += alloc_block_size;
            }

            if (alloc_size != _max)
            {
                T* ptr = new T[alloc_size];
                std::size_t n = newSize > _size ? _size : newSize; // min
                if (preserveContent)
                {
                    //std::size_t n = newSize > _size ? _size : newSize; // min
                    std::memcpy(ptr, _ptr, n*sizeof(T));
                }

                if (_ptr) delete [] _ptr;

                _ptr = ptr;
                _max = alloc_size;
                _size = n;
            }
        }
        else
        {
            if (_ptr) delete [] _ptr;
            _ptr = 0;
            _max = 0;
            _size = 0;
        }
    }

    inline void resize(std::size_t size)
    {
        core_assert_printf (size <= _max, "size <= _max");
        _size = size;
    }

    inline void clear()
    {
        _size = 0;
    }

#if 0
    inline void resizeEx(std::size_t newSize, bool preserveContent = false)
    {
        if (newSize == _size)
        {
            return;
        }

        T* ptr = 0;
        if (newSize != 0)
        {
            ptr = new T[newSize];
            if (preserveContent)
            {
                std::size_t n = newSize > _size ? _size : newSize;
                std::memcpy(ptr, _ptr, n);
            }
        }

        if (_ptr)
        {
            delete [] _ptr;
        }

        _ptr  = ptr;
        _size = newSize;
    }
#endif

    inline void assign(T* src, std::size_t size)
    {
        realloc(size, false);
        if (size != 0)
        {
            memcpy(_ptr, src, size*sizeof(T));
        }
        _size = size;
    }

    inline void append(T* src, std::size_t size)
    {
        realloc(_size+size, true);
        if (size != 0)
        {
            memcpy(_ptr+_size*sizeof(T), src, size*sizeof(T));
        }
        _size += size;
    }

    inline void appendEnding(T ending)
    {
        if (_size == 0 || _ptr[_size-1] != ending)
        {
            append(&ending, sizeof(T));
        }
    }

    inline std::size_t size() const
    {
        return _size;
    }

    inline std::size_t capacity() const
    {
        return _max;
    }

    inline T* begin()
    {
        return _ptr;
    }

    inline const T* begin() const
    {
        return _ptr;
    }

    inline T* end()
    {
        return _ptr + _size;
    }

    inline const T* end() const
    {
        return _ptr + _size;
    }

    inline T& operator [] (std::size_t index)
    {
        core_assert_printf (index < _size, "index < _size");
        return _ptr[index];
    }

    inline const T& operator [] (std::size_t index) const
    {
        core_assert_printf (index < _size, "index < _size");
        return _ptr[index];
    }

private:
    std::size_t _max;
    std::size_t _size;
    T* _ptr;
};


}  // namespace Core


#endif  // Core_SmartBuffer_H
