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

#ifndef Core_DynamicFixedArray_H
#define Core_DynamicFixedArray_H

#include "ECore/Core/Core.h"
#include <stdio.h>
#include "ECore/Core/FixedArray.h"

namespace Core {


#define TMEPLATE_DYNAMICFIXEDARRAY   template <class _T, std::size_t _MAX>
#define DynamicFixedArrayT       DynamicFixedArray<_T, _MAX>
#define DynamicFixedArrayBaseT   FixedArray<_T, _MAX>
#define DYNAMICFIXEDARRAY_BLOCK_SIZE  512


template <class _T, std::size_t _MAX = DYNAMICFIXEDARRAY_BLOCK_SIZE>
class DynamicFixedArray : protected DynamicFixedArrayBaseT
    /// dynamic array template class.
{
public:
    enum {
        MAX_SIZE = DYNAMICFIXEDARRAY_BLOCK_SIZE
    };

    typedef typename DynamicFixedArrayBaseT::value_type      value_type;
    typedef typename DynamicFixedArrayBaseT::iterator        iterator;
    typedef typename DynamicFixedArrayBaseT::const_iterator  const_iterator;
    typedef typename DynamicFixedArrayBaseT::reference       reference;
    typedef typename DynamicFixedArrayBaseT::const_reference const_reference;
    typedef typename DynamicFixedArrayBaseT::size_type       size_type;
    
    DynamicFixedArray();
    DynamicFixedArray(const_reference init_value);
    DynamicFixedArray(const DynamicFixedArrayT& other);

    // assignment with type conversion
    template <typename _T2>
    DynamicFixedArrayT& operator = (const DynamicFixedArray<_T2,_MAX>& other);

    bool operator == (const DynamicFixedArrayT& other) const;

    reference operator[](size_type i);
    const_reference operator[](size_type i) const;

    reference at(size_type i);
    const_reference at(size_type i) const;

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;

    bool empty() const;
    void clear();

    void fill(const_reference value);
    void fill_n(iterator begin, const_reference value, size_type n);

    DynamicFixedArrayT& assign(const_reference value);
    DynamicFixedArrayT& assign(const_iterator addr, size_type len);

    DynamicFixedArrayT& append(const_reference value);
    DynamicFixedArrayT& append(const_iterator addr, size_type len);

    size_type& size();
    size_type size() const;
    void resize(size_type size);   // not erase data.

    size_type max_size() const;

    void rangecheck(size_type i) const;

    void dump();    // print the HEX informations of package memory for a new line.
    void dump(std::string& info);
    
private:
    size_type _length;
};


// DynamicFixedArray
// inlines
//
TMEPLATE_DYNAMICFIXEDARRAY
inline DynamicFixedArrayT::DynamicFixedArray():
    DynamicFixedArrayBaseT(),
    _length(0)
{
}

TMEPLATE_DYNAMICFIXEDARRAY
inline DynamicFixedArrayT::DynamicFixedArray(const_reference init_value) :
    DynamicFixedArrayBaseT(init_value),
    _length(0)
{

}

TMEPLATE_DYNAMICFIXEDARRAY
inline DynamicFixedArrayT::DynamicFixedArray(const DynamicFixedArrayT& other)
{
    *this = other;
}

TMEPLATE_DYNAMICFIXEDARRAY template <typename _T2>
DynamicFixedArrayT& DynamicFixedArrayT::operator = (const DynamicFixedArray<_T2,_MAX>& other)
{
    if (&other != this)
    {
        this->assign(other.begin(), other.size());
        _length = other._length;
    }

    return *this;
}

TMEPLATE_DYNAMICFIXEDARRAY
inline bool DynamicFixedArrayT::operator == (const DynamicFixedArray& other) const
{
    return (max_size() == other.max_size()
            && size() == other.size()
            && 0 == memcmp(begin(), other.begin(), other.size())); 
}

TMEPLATE_DYNAMICFIXEDARRAY
inline typename DynamicFixedArrayT::reference DynamicFixedArrayT::operator[](typename DynamicFixedArrayT::size_type i)
{
    return DynamicFixedArrayBaseT::at(i);
}

TMEPLATE_DYNAMICFIXEDARRAY
inline typename DynamicFixedArrayT::const_reference DynamicFixedArrayT::operator[](typename DynamicFixedArrayT::size_type i) const
{
    return DynamicFixedArrayBaseT::at(i);
}

TMEPLATE_DYNAMICFIXEDARRAY
inline typename DynamicFixedArrayT::reference DynamicFixedArrayT::at(typename DynamicFixedArrayT::size_type i)
{
    DynamicFixedArrayT::rangecheck(i);
    return DynamicFixedArrayBaseT::at(i);
}

TMEPLATE_DYNAMICFIXEDARRAY
inline typename DynamicFixedArrayT::const_reference DynamicFixedArrayT::at(typename DynamicFixedArrayT::size_type i) const
{
    DynamicFixedArrayT::rangecheck(i);
    return DynamicFixedArrayBaseT::at(i);
}

TMEPLATE_DYNAMICFIXEDARRAY
inline typename DynamicFixedArrayT::iterator DynamicFixedArrayT::begin()
{
    return DynamicFixedArrayBaseT::begin();
}

TMEPLATE_DYNAMICFIXEDARRAY
inline typename DynamicFixedArrayT::const_iterator DynamicFixedArrayT::begin() const
{
    return DynamicFixedArrayBaseT::begin();
}

TMEPLATE_DYNAMICFIXEDARRAY
inline typename DynamicFixedArrayT::iterator DynamicFixedArrayT::end()
{
    return DynamicFixedArrayBaseT::begin()+_length;
}

TMEPLATE_DYNAMICFIXEDARRAY
inline typename DynamicFixedArrayT::const_iterator DynamicFixedArrayT::end() const
{
    return DynamicFixedArrayBaseT::begin()+_length;
}

TMEPLATE_DYNAMICFIXEDARRAY
inline typename DynamicFixedArrayT::reference DynamicFixedArrayT::front()
{
    return DynamicFixedArrayBaseT::front();
}

TMEPLATE_DYNAMICFIXEDARRAY
inline typename DynamicFixedArrayT::const_reference DynamicFixedArrayT::front() const
{
    return DynamicFixedArrayBaseT::front();
}

TMEPLATE_DYNAMICFIXEDARRAY
inline typename DynamicFixedArrayT::reference DynamicFixedArrayT::back()
{
    return DynamicFixedArrayBaseT::at(_length-1);
}

TMEPLATE_DYNAMICFIXEDARRAY
inline typename DynamicFixedArrayT::const_reference DynamicFixedArrayT::back() const
{
    return DynamicFixedArrayBaseT::at(_length-1);
}

TMEPLATE_DYNAMICFIXEDARRAY
inline bool DynamicFixedArrayT::empty() const
{
    return 0 == _length;
}

TMEPLATE_DYNAMICFIXEDARRAY
inline void DynamicFixedArrayT::clear()
{
    _length = 0;
}

TMEPLATE_DYNAMICFIXEDARRAY
inline void DynamicFixedArrayT::fill(typename DynamicFixedArrayT::const_reference value)
{
    DynamicFixedArrayBaseT::fill(value);
}

TMEPLATE_DYNAMICFIXEDARRAY
inline void DynamicFixedArrayT::fill_n(typename DynamicFixedArrayT::iterator begin, typename DynamicFixedArrayT::const_reference value, typename DynamicFixedArrayT::size_type n)
{
    DynamicFixedArrayBaseT::fill_n(begin, value, n);
}

TMEPLATE_DYNAMICFIXEDARRAY
inline DynamicFixedArrayT& DynamicFixedArrayT::assign(typename DynamicFixedArrayT::const_reference value)
{
    DynamicFixedArrayBaseT::assign(value);
    return *this;
}

TMEPLATE_DYNAMICFIXEDARRAY
inline DynamicFixedArrayT& DynamicFixedArrayT::assign(typename DynamicFixedArrayT::const_iterator addr, typename DynamicFixedArrayT::size_type len)
{
    core_assert_printf(addr != 0, "addr != 0");
    if (len > 0)
    {
        //DynamicFixedArrayBaseT::rangecheck(len-1);
        resize(len);
        memcpy(begin(), addr, len);
    }
    //_length = len;
    return *this;
}

TMEPLATE_DYNAMICFIXEDARRAY
inline DynamicFixedArrayT& DynamicFixedArrayT::append(typename DynamicFixedArrayT::const_reference value)
{
    /*if (_length > 0)
    {
        DynamicFixedArrayBaseT::rangecheck(_length-1);
    }*/

    resize(DynamicFixedArrayT::size()+1);
    DynamicFixedArrayBaseT::at(DynamicFixedArrayT::size()-1) = value;
    //++_length;
    return *this;
}

TMEPLATE_DYNAMICFIXEDARRAY
inline DynamicFixedArrayT& DynamicFixedArrayT::append(typename DynamicFixedArrayT::const_iterator addr, typename DynamicFixedArrayT::size_type len)
{
    core_assert_printf(addr != 0, "addr != 0");
    /*if (_length+len > 0)
    {
        DynamicFixedArrayBaseT::rangecheck(_length+len-1);
    }*/
    resize(DynamicFixedArrayT::size()+len);
    if (len > 0)
    {
        memcpy(end(), addr, len);
    }
    //_length = _length + len;
    return *this;
}

TMEPLATE_DYNAMICFIXEDARRAY
inline typename DynamicFixedArrayT::size_type& DynamicFixedArrayT::size()
{
    return _length;
}

TMEPLATE_DYNAMICFIXEDARRAY
inline typename DynamicFixedArrayT::size_type DynamicFixedArrayT::size() const
{
    return _length;
}

TMEPLATE_DYNAMICFIXEDARRAY
inline void DynamicFixedArrayT::resize(typename DynamicFixedArrayT::size_type size)
{
    if (size > DynamicFixedArrayT::max_size())
    {
        char msg[128];
        snprintf(msg, sizeof(msg), "DynamicFixedArray resize size[%d] > max_size[%d]", size, DynamicFixedArrayT::max_size());

        std::out_of_range e(msg);
        throw e;
    }
    _length = size;
}

TMEPLATE_DYNAMICFIXEDARRAY
inline typename DynamicFixedArrayT::size_type DynamicFixedArrayT::max_size() const
{
    return DynamicFixedArrayBaseT::max_size();
}

TMEPLATE_DYNAMICFIXEDARRAY
inline void DynamicFixedArrayT::rangecheck(typename DynamicFixedArrayT::size_type i) const
{
    if (i >= _length)
    {
        char msg[128];
        snprintf(msg, sizeof(msg), "DynamicFixedArray rangecheck index[%d] > size[%d]", i, _length);
        std::out_of_range e(msg);
        throw e;
    }
}

TMEPLATE_DYNAMICFIXEDARRAY
inline void DynamicFixedArrayT::dump()
{
    std::string info;

    DynamicFixedArrayT::dump(info);
    printf("%s\n", info.c_str());
}

TMEPLATE_DYNAMICFIXEDARRAY
inline void DynamicFixedArrayT::dump(std::string& info)
{
    info.clear();
    char dst[32];

    if (!empty())
    {
        snprintf(dst, sizeof(dst), "L%d[ ", size());
        info.append(dst);

        char fmt[32];
        snprintf(fmt, sizeof(fmt), "%%0%0dX ", sizeof(_T)*2);

        for (int i=0; i<size(); ++i)
        {
            snprintf(dst, sizeof(dst), fmt, DynamicFixedArrayT::at(i));
            info.append(dst);
        }
        info.append("]");
    }
    else
    {
        info = "L0[ NULL ]";
    }
}


}   // namespace Core


#endif  // Core_DynamicArray_H
