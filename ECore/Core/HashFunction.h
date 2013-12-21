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

#ifndef Core_HashFunction_H
#define Core_HashFunction_H


#include "ECore/Core/Core.h"
#include "ECore/Core/Hash.h"


namespace Core {


template <class T>
struct HashFunction
{
    UInt32 operator () (T key, UInt32 maxValue) const
    {
        return static_cast<UInt32>(Core::hash(key)) % maxValue;
    }
};


template <>
struct HashFunction<std::string>
{
    UInt32 operator () (const std::string& key, UInt32 maxValue) const
    {
        return static_cast<UInt32>(Core::hash(key)) % maxValue;
    }
};


}   // namespace Core


#endif  // Core_HashFunction_H
