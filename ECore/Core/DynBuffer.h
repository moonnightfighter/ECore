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

#ifndef Core_DynBuffer_H
#define Core_DynBuffer_H


#include <cstring>
#include <cstddef>
#include <assert.h>


namespace Core {


template <class T>
class DynBuffer
{
public:
    typedef T           value_t;
    typedef T*          iterator_t;
    typedef const T*    const_iterator_t;
    typedef T&          reference_t;
    typedef const T&    const_reference_t;
    typedef std::size_t size_t;

    inline DynBuffer(size_t capacity):
        _capacity(capacity),
        _size(0),
        _ptr(new value_t[capacity])
    {
    }

    inline DynBuffer(const DynBuffer& other):
        _capacity(0),
        _size(0),
        _ptr(0)
    {
        if (this != &other)
        {
            realloc(other._capacity);
            assign((iterator_t)other.begin(), other.size());
        }
    }

    inline ~DynBuffer()
    {
        delete [] _ptr;
    }

    
    inline DynBuffer& operator = (const DynBuffer& other)
    {
        if (this != &other)
        {
            realloc(other._capacity);
            assign((iterator_t)other.begin(), other.size());
        }

        return *this;
    }

    inline void realloc(std::size_t newCapacity, bool preserveContent = true)
    {
        iterator_t ptr = 0;

        if (newCapacity != 0 && newCapacity != _capacity)
        {
            ptr = new value_t[newCapacity];
            if (preserveContent)
            {
                size_t n = newCapacity > _capacity ? _capacity : newCapacity;
                _size = _size > n ? n : _size;
                std::memcpy(ptr, _ptr, n);
            }
            else
            {
                _size = 0;
            }
        }
        else
        {
             _size = 0;
        }
        
        if (_ptr)
        {
            delete [] _ptr;
        }
        
        _ptr  = ptr;
        _capacity = newCapacity;
    }

    inline void resize(size_t size)
    {
        rangecheck((size!=0) ? (size-1) : 0);
        _size = size;
    }

    inline size_t size() const
    {
        return _size;
    }

    inline iterator_t begin()
    {
        return _ptr;
    }

    inline const_iterator_t begin() const
    {
        return _ptr;
    }

    inline iterator_t end()
    {
        return _ptr + _size;
    }

    inline const_iterator_t end() const
    {
        return _ptr + _size;
    }

    inline reference_t operator [] (size_t index)
    {
        rangecheck(index);
        return _ptr[index];
    }

    inline const_reference_t operator [] (size_t index) const
    {
        rangecheck(index);
        return _ptr[index];
    }

    inline void append(iterator_t src, size_t size)
    {
        if (size > 0)
        {
            rangecheck(_size + size - 1);
            memcpy(end(), src, size*sizeof(value_t));
            _size += size;
        }
    }

    inline void assign(iterator_t src, size_t size)
    {
        if (size > 0)
        {
            rangecheck(size - 1);
            memcpy(begin(), src, size*sizeof(value_t));
            _size = size;
        }
    }

    inline size_t capacity()
    {
        return _capacity;
    }

    inline size_t capacity() const
    {
        return _capacity;
    }

    inline void clear()
    {
        _size = 0;
    }

protected:
    inline void rangecheck(size_t idx)
    {
        core_assert_printf(idx < capacity(), "idx < capacity()");
    }

private:
    DynBuffer();

    size_t _capacity;
    size_t _size;
    iterator_t _ptr;
};


} // namespace Core


#endif // Core_DynBuffer_H
