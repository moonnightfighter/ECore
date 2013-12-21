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

#ifndef Core_FixBuffer_H
#define Core_FixBuffer_H


#include <cstddef>
#include <assert.h>


namespace Core {


template <class T, std::size_t N>
class FixBuffer
{
public:
    typedef T           value_t;
    typedef T*          iterator_t;
    typedef const T*    const_iterator_t;
    typedef T&          reference_t;
    typedef const T&    const_reference_t;
    typedef std::size_t size_t;

    FixBuffer():
        _size(0)
    {
    }
    
    FixBuffer(value_t init_value):
        _size(0)
    {
        for (int i=0; i<N; ++i)
        {
            _buf[i] = init_value;
        }
    }

    FixBuffer(const FixBuffer& other):
        _size(0)
    {
        if (this != &other)
        {
            assign(other.begin(), other.size());
        }
    }
    
    ~FixBuffer()
    {
    }

    inline FixBuffer& operator = (const FixBuffer& other)
    {
        if (this != &other)
        {
            assign(other.begin(), other.size());
        }
        return *this;
    }

    inline iterator_t begin()
    {
        return _buf;
    }

    inline const_iterator_t begin() const
    {
        return _buf;
    }

    inline iterator_t end()
    {
        return _buf + size();
    }

    inline const_iterator_t end() const
    {
        return _buf + size();
    }

    inline reference_t operator [] (size_t index)
    {
        rangecheck(index);
        return _buf[index];
    }

    inline const_reference_t operator [] (size_t index) const
    {
        rangecheck(index);
        return _buf[index];
    }

    inline void append(const_iterator_t src, size_t size)
    {
        if (size > 0)
        {
            resize(_size + size);
            memcpy(end(), src, size*sizeof(value_t));
        }
    }

    inline void assign(const_iterator_t src, size_t size)
    {
        resize(size);

        if (size > 0)
        {
            memcpy(begin(), src, size*sizeof(value_t));
        }
    }

    inline bool operator == (const FixBuffer& other)
    {
        if (size() != other.size())
        {
            return false;
        }
        
        for (int i=0; i<(int)size(); ++i)
        {
            if (_buf[i] != other._buf[i])
            {
                return false;
            }
        }

        return true;
    }

    inline bool operator != (const FixBuffer& other)
    {
        return !(*this == other);
    }

    inline void clear()
    {
        _size = 0;
    }

    inline size_t size()
    {
        return _size;
    }

    inline const size_t size() const
    {
        return _size;
    }

    inline void resize(size_t size)
    {
        rangecheck((size!=0) ? (size-1) : 0);
        _size = size;
    }

    inline size_t capacity()
    {
        return N;
    }

private:
    inline void rangecheck(size_t idx)
    {
        core_assert_printf(idx < capacity(), "idx < capacity()");
    }

private:
    volatile size_t _size;
    value_t _buf[N];
};


}   // namespace Core


#endif  // Core_FixBuffer_H
