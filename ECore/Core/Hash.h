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

#ifndef Core_Hash_H
#define Core_Hash_H


#include "ECore/Core/Core.h"
#include <cstddef>


namespace Core {


std::size_t Core_API hash(Int8 n);
std::size_t Core_API hash(UInt8 n);
std::size_t Core_API hash(Int16 n);
std::size_t Core_API hash(UInt16 n);
std::size_t Core_API hash(Int32 n);
std::size_t Core_API hash(UInt32 n);
std::size_t Core_API hash(Int64 n);
std::size_t Core_API hash(UInt64 n);
std::size_t Core_API hash(const std::string& str);


template <class T>
struct Hash
{
    std::size_t operator () (T value) const
    {
        return Core::hash(value);
    }
};


//
// inlines
//
inline std::size_t hash(Int8 n)
{
    return static_cast<std::size_t>(n)*2654435761U; 
}


inline std::size_t hash(UInt8 n)
{
    return static_cast<std::size_t>(n)*2654435761U; 
}


inline std::size_t hash(Int16 n)
{
    return static_cast<std::size_t>(n)*2654435761U; 
}


inline std::size_t hash(UInt16 n)
{
    return static_cast<std::size_t>(n)*2654435761U; 
}


inline std::size_t hash(Int32 n)
{
    return static_cast<std::size_t>(n)*2654435761U; 
}


inline std::size_t hash(UInt32 n)
{
    return static_cast<std::size_t>(n)*2654435761U; 
}


inline std::size_t hash(Int64 n)
{
    return static_cast<std::size_t>(n)*2654435761U; 
}


inline std::size_t hash(UInt64 n)
{
    return static_cast<std::size_t>(n)*2654435761U; 
}


}   // namespace Core


#endif  // Core_Hash_H
