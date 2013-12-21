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

#ifndef Core_DirectoryIterator_UNIX_H
#define Core_DirectoryIterator_UNIX_H


#include "ECore/Core/Core.h"
#include <dirent.h>


namespace Core {


class Core_API DirectoryIteratorImpl
{
public:
    DirectoryIteratorImpl(const std::string& path);
    ~DirectoryIteratorImpl();

    void duplicate();
    void release();

    const std::string& get() const;
    const std::string& next();

private:
    DIR*        _pDir;
    std::string _current;
    int _rc;
};


//
// inlines
//
const std::string& DirectoryIteratorImpl::get() const
{
    return _current;
}


inline void DirectoryIteratorImpl::duplicate()
{
    ++_rc;
}


inline void DirectoryIteratorImpl::release()
{
    if (--_rc == 0)
        delete this;
}


} // namespace Core


#endif // Core_DirectoryIterator_UNIX_H
