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

#ifndef Core_File_UNIX_H
#define Core_File_UNIX_H


#include "ECore/Core/Core.h"


namespace Core {


class FileImpl
{
protected:
    typedef UInt64 FileSizeImpl;

    FileImpl();
    FileImpl(const std::string& path);
    virtual ~FileImpl();
    void swapImpl(FileImpl& file);
    void setPathImpl(const std::string& path);
    const std::string& getPathImpl() const;
    bool existsImpl() const;
    bool canReadImpl() const;
    bool canWriteImpl() const;
    bool canExecuteImpl() const;
    bool isFileImpl() const;
    bool isDirectoryImpl() const;
    bool isLinkImpl() const;
    bool isDeviceImpl() const;
    bool isHiddenImpl() const;
    Timestamp createdImpl() const;
    Timestamp getLastModifiedImpl() const;
    void setLastModifiedImpl(const Timestamp& ts);
    FileSizeImpl getSizeImpl() const;
    void setSizeImpl(FileSizeImpl size);
    void setWriteableImpl(bool flag = true);		
    void setExecutableImpl(bool flag = true);		
    void copyToImpl(const std::string& path) const;
    void renameToImpl(const std::string& path);
    void removeImpl();
    bool createFileImpl();
    bool createDirectoryImpl();
    static void handleLastErrorImpl(const std::string& path);

private:
    std::string _path;

    friend class DirectoryIteratorImpl;
};


//
// inlines
//
inline const std::string& FileImpl::getPathImpl() const
{
    return _path;
}


} // namespace Core


#endif // Core_File_UNIX_H
