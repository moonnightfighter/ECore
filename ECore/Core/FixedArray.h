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

#ifndef Core_FixedArray_H
#define Core_FixedArray_H

#include "ECore/Core/Core.h"
#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <assert.h>

#if defined(CORE_OS_FAMILY_WINDOWS)  
//# pragma warning(push)  
# pragma warning(disable:4996) // std::fill_n, 'std::equal': Function call with parameters that may be unsafe
//# pragma warning(disable:4510) // Core::array<T,N>' : default constructor could not be generated 
//# pragma warning(disable:4610) // warning C4610: class 'Core::array<T,N>' can never be instantiated - user defined constructor required 
#endif


namespace Core {


#define TMEPLATE_FIXEDARRAY  template<class T, std::size_t N>
#define FixedArrayT          FixedArray<T, N>


template<class T, std::size_t N>
class FixedArray
    /// template array class.
{
public:
    T elems[N];    // fixed-size array of elements of type T

public:
    // type definitions
    typedef T              value_type;
    typedef T*             iterator;
    typedef const T*       const_iterator;
    typedef T&             reference;
    typedef const T&       const_reference;
    typedef std::size_t    size_type;
    typedef std::ptrdiff_t difference_type;

    FixedArray();
    FixedArray(const_reference init_value);

    // iterator support
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;

    // operator[]
    reference operator[](size_type i);
    const_reference operator[](size_type i) const;
    
    // at() with range check
    reference at(size_type i);
    const_reference at(size_type i) const;

    // front() and back()
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;

    // size is constant
    static size_type size();
    static bool empty();
    static size_type max_size();
    enum { static_size = N };

    // swap (note: linear complexity)
    void swap(FixedArray<T,N>& y);

    // direct access to data (read-only)
    const_iterator data() const;
    iterator data();

    // use array as C array (direct read/write access to data)
    iterator c_array();

    // assignment with type conversion
    template <typename T2>
    FixedArrayT& operator= (const FixedArray<T2,N>& rhs);

    void fill(const_reference value);
    void fill_n(iterator begin, const_reference value, size_type n);

    // assign one value to all elements
    void assign(const_reference value);    // A synonym for fill
    void assign(const_iterator addr, size_type len);

    // check range (may be private because it is static)
    static void rangecheck(size_type i);

    void dump();    // print the HEX informations of package memory for a new line.
    void dump(std::string& info);
};


//
// inines
//
TMEPLATE_FIXEDARRAY
inline FixedArrayT::FixedArray()
{
}

TMEPLATE_FIXEDARRAY
inline FixedArrayT::FixedArray(typename FixedArrayT::const_reference init_value)
{
    fill(init_value);
}

TMEPLATE_FIXEDARRAY
inline typename FixedArrayT::iterator FixedArrayT::begin()
{
    return elems;
}

TMEPLATE_FIXEDARRAY
inline typename FixedArrayT::const_iterator FixedArrayT::begin() const
{
    return elems;
}

TMEPLATE_FIXEDARRAY
inline typename FixedArrayT::iterator FixedArrayT::end()
{
    return elems+N;
}

TMEPLATE_FIXEDARRAY
inline typename FixedArrayT::const_iterator FixedArrayT::end() const
{
    return elems+N;
}

TMEPLATE_FIXEDARRAY
inline typename FixedArrayT::reverse_iterator FixedArrayT::rbegin()
{
    return reverse_iterator(end());
}

TMEPLATE_FIXEDARRAY
inline typename FixedArrayT::const_reverse_iterator FixedArrayT::rbegin() const
{
    return const_reverse_iterator(end());
}

TMEPLATE_FIXEDARRAY
inline typename FixedArrayT::reverse_iterator FixedArrayT::rend()
{
    return reverse_iterator(begin());
}

TMEPLATE_FIXEDARRAY
inline typename FixedArrayT::const_reverse_iterator FixedArrayT::rend() const
{
    return const_reverse_iterator(begin());
}

TMEPLATE_FIXEDARRAY
inline typename FixedArrayT::reference FixedArrayT::operator[](typename FixedArrayT::size_type i) 
{ 
    core_assert_printf( i < N, "out of range"); 
    return elems[i];
}

TMEPLATE_FIXEDARRAY
inline typename FixedArrayT::const_reference FixedArrayT::operator[](typename FixedArrayT::size_type i) const 
{     
    core_assert_printf( i < N, "out of range"); 
    return elems[i]; 
}

TMEPLATE_FIXEDARRAY
inline typename FixedArrayT::reference FixedArrayT::at(typename FixedArrayT::size_type i)
{
    rangecheck(i);
    return elems[i];
}

TMEPLATE_FIXEDARRAY
inline typename FixedArrayT::const_reference FixedArrayT::at(typename FixedArrayT::size_type i) const
{
    rangecheck(i);
    return elems[i];
}

TMEPLATE_FIXEDARRAY
inline typename FixedArrayT::reference FixedArrayT::front() 
{ 
    return elems[0];
}

TMEPLATE_FIXEDARRAY
inline typename FixedArrayT::const_reference FixedArrayT::front() const 
{
    return elems[0];
}

TMEPLATE_FIXEDARRAY
inline typename FixedArrayT::reference FixedArrayT::back() 
{ 
    return elems[N-1]; 
}

TMEPLATE_FIXEDARRAY
inline typename FixedArrayT::const_reference FixedArrayT::back() const 
{ 
    return elems[N-1]; 
}

TMEPLATE_FIXEDARRAY
inline typename FixedArrayT::size_type FixedArrayT::size() { return N; }

TMEPLATE_FIXEDARRAY
inline bool FixedArrayT::empty() { return false; }

TMEPLATE_FIXEDARRAY
inline typename FixedArrayT::size_type FixedArrayT::max_size() { return N; }


TMEPLATE_FIXEDARRAY
inline void FixedArrayT::swap (FixedArrayT& y)
{
    for (size_type i = 0; i < N; ++i)
    {
        std::swap(elems[i], y.elems[i]);
    }
}

TMEPLATE_FIXEDARRAY
inline typename FixedArrayT::const_iterator FixedArrayT::data() const
{
    return elems;
}

TMEPLATE_FIXEDARRAY
inline typename FixedArrayT::iterator FixedArrayT::data()
{
    return elems;
}

TMEPLATE_FIXEDARRAY
inline typename FixedArrayT::iterator FixedArrayT::c_array()
{
    return elems;
}

// assignment with type conversion

TMEPLATE_FIXEDARRAY template <typename T2>
inline FixedArrayT& FixedArrayT::operator = (const FixedArray<T2,N>& rhs)
{
    std::copy(rhs.begin(), rhs.end(), begin());
    return *this;
}

TMEPLATE_FIXEDARRAY
inline void FixedArrayT::fill(typename FixedArrayT::const_reference value)
{
    std::fill_n(begin(), size(), value);
}

TMEPLATE_FIXEDARRAY
inline void FixedArrayT::fill_n(typename FixedArrayT::iterator begin, typename FixedArrayT::const_reference value, typename FixedArrayT::size_type n)
{
    core_assert_printf(begin != 0, "begin != 0");
    core_assert_printf(begin+n < end(), "array<>: overflow"); 
    std::fill_n(begin, n, value);
}

// assign one value to all elements
TMEPLATE_FIXEDARRAY
inline void FixedArrayT::assign(typename FixedArrayT::const_reference value)
{
    fill(value);    // A synonym for fill
}

TMEPLATE_FIXEDARRAY
inline void FixedArrayT::assign(const_iterator addr, size_type len)
{
    core_assert_printf(addr != 0, "addr != 0");
    if (len > 0)
    {
        rangecheck(len-1);
        memcpy(begin(), addr, len);
    }
}

// check range (may be private because it is static)
TMEPLATE_FIXEDARRAY
inline void FixedArrayT::rangecheck(size_type i)
{
    if (i >= size())
    {
        char msg[128];
        snprintf(msg, sizeof(msg), "FixedArray rangecheck index[%d] >= size[%d]", i, size());

        std::out_of_range e(msg);
        throw e;
    }
}

TMEPLATE_FIXEDARRAY
inline void FixedArrayT::dump()
{
    std::string info;

    FixedArrayT::dump(info);
    printf("%s\n", info.c_str());
}

TMEPLATE_FIXEDARRAY
inline void FixedArrayT::dump(std::string& info)
{
    info.clear();
    char dst[32];

    snprintf(dst, sizeof(dst), "L%d[ ", size());
    info.append(dst);

    char fmt[32];
    snprintf(fmt, sizeof(fmt), "%%0%0dX ", sizeof(T)*2);

    for (int i=0; i<size(); ++i)
    {
        snprintf(dst, sizeof(dst), fmt, FixedArrayT::at(i));
        info.append(dst);
    }
    info.append("]");
}



//
// comparisons
//
TMEPLATE_FIXEDARRAY
inline bool operator == (const FixedArrayT& x, const FixedArrayT& y)
{
    return std::equal(x.begin(), x.end(), y.begin());
}

TMEPLATE_FIXEDARRAY
inline bool operator < (const FixedArrayT& x, const FixedArrayT& y)
{
    return std::lexicographical_compare(x.begin(),x.end(),y.begin(),y.end());
}

TMEPLATE_FIXEDARRAY
inline bool operator != (const FixedArrayT& x, const FixedArrayT& y)
{
    return !(x==y);
}

TMEPLATE_FIXEDARRAY
inline bool operator > (const FixedArrayT& x, const FixedArrayT& y)
{
    return y<x;
}

TMEPLATE_FIXEDARRAY
inline bool operator <= (const FixedArrayT& x, const FixedArrayT& y)
{
    return !(y<x);
}

TMEPLATE_FIXEDARRAY
inline bool operator >= (const FixedArrayT& x, const FixedArrayT& y)
{
    return !(x<y);
}

// global swap()
TMEPLATE_FIXEDARRAY
inline void swap(FixedArrayT& x, FixedArrayT& y)
{
    x.swap(y);
}

// Specific for Core::array: simply returns its elems data member.
TMEPLATE_FIXEDARRAY
inline T(&get_c_array(Core::FixedArrayT& arg))[N]
{
    return arg.elems;
}

// Const version.
TMEPLATE_FIXEDARRAY
inline const T(&get_c_array(const Core::FixedArrayT& arg))[N]
{
    return arg.elems;
}

#if 0
// Overload for std::array, assuming that std::array will have
// explicit conversion functions as discussed at the WG21 meeting
// in Summit, March 2009.
TMEPLATE_FIXEDARRAY
T(&get_c_array(std::array<T,N>& arg))[N]
{
    return static_cast<T(&)[N]>(arg);
}

// Const version.
TMEPLATE_FIXEDARRAY
const T(&get_c_array(const std::array<T,N>& arg))[N]
{
    return static_cast<T(&)[N]>(arg);
}
#endif


}   // namespace Core


#if defined(CORE_OS_FAMILY_WINDOWS)  
//# pragma warning(pop)  
#endif 


#endif  // Core_FixedArray_H
