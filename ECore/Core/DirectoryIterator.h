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

#ifndef Core_DirectoryIterator_H
#define Core_DirectoryIterator_H


#include "ECore/Core/Core.h"
#include "ECore/Core/File.h"
#include "ECore/Core/Path.h"


namespace Core {


class DirectoryIteratorImpl;


class Core_API DirectoryIterator
{
public:
    DirectoryIterator();
    DirectoryIterator(const std::string& path);
    DirectoryIterator(const DirectoryIterator& iterator);
    DirectoryIterator(const File& file);
    DirectoryIterator(const Path& path);
    ~DirectoryIterator();

    const std::string& name() const;

    const Path& path() const;

    DirectoryIterator& operator = (const DirectoryIterator& it);
    DirectoryIterator& operator = (const File& file);
    DirectoryIterator& operator = (const Path& path);
    DirectoryIterator& operator = (const std::string& path);

    DirectoryIterator& operator ++ ();   // prefix
    DirectoryIterator operator ++ (int); // postfix

    const File& operator * () const;
    File& operator * ();
    const File* operator -> () const;
    File* operator -> ();

    bool operator == (const DirectoryIterator& iterator) const;
    bool operator != (const DirectoryIterator& iterator) const;

private:
    Path _path;
    File _file;
    DirectoryIteratorImpl* _pImpl;
};


//
// inlines
//
inline const std::string& DirectoryIterator::name() const
{
    return _path.getFileName();
}


inline const Path& DirectoryIterator::path() const
{
    return _path;
}


inline const File& DirectoryIterator::operator * () const
{
    return _file;
}


inline File& DirectoryIterator::operator * ()
{
    return _file;
}


inline const File* DirectoryIterator::operator -> () const
{
    return &_file;
}


inline File* DirectoryIterator::operator -> ()
{
    return &_file;
}


inline bool DirectoryIterator::operator == (const DirectoryIterator& iterator) const
{
    return name() == iterator.name();
}


inline bool DirectoryIterator::operator != (const DirectoryIterator& iterator) const
{
    return name() != iterator.name();
}


} // namespace Core


#endif  // Core_DirectoryIterator_H
