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

#ifndef Core_File_H
#define Core_File_H


#include "ECore/Core/Core.h"
#include "ECore/Core/Timestamp.h"
#include <vector>
#include "ECore/Core/File_UNIX.h"


namespace Core {


class Path;


class Core_API File: private FileImpl
{
public:
    typedef FileSizeImpl FileSize;

    File();
    File(const std::string& path);
    File(const char* path);
    File(const Path& path);
    File(const File& file);
    virtual ~File();

    File& operator = (const File& file);
    File& operator = (const std::string& path);
    File& operator = (const char* path);
    File& operator = (const Path& path);

    void swap(File& file);

    const std::string& path() const;

    bool exists() const;
    bool canRead() const;
    bool canWrite() const;
    bool canExecute() const;

    bool isFile() const;
    bool isLink() const;
    bool isDirectory() const;
    bool isDevice() const;

    bool isHidden() const;

    Timestamp created() const;

    Timestamp getLastModified() const;

    File& setLastModified(const Timestamp& ts);

    FileSize getSize() const;

    File& setSize(FileSize size);

    File& setWriteable(bool flag = true);

    File& setReadOnly(bool flag = true);

    File& setExecutable(bool flag = true);

    void copyTo(const std::string& path) const;
    void moveTo(const std::string& path);
    void renameTo(const std::string& path);
    void remove(bool recursive = false);
    bool createFile();
    bool createDirectory();
    void createDirectories();

    void list(std::vector<std::string>& files) const;
    void list(std::vector<File>& files) const;

    bool operator == (const File& file) const;
    bool operator != (const File& file) const;
    bool operator <  (const File& file) const;
    bool operator <= (const File& file) const;
    bool operator >  (const File& file) const;
    bool operator >= (const File& file) const;

    static void handleLastError(const std::string& path);

protected:
    void copyDirectory(const std::string& path) const;
};


//
// inlines
//
inline const std::string& File::path() const
{
    return getPathImpl();
}


inline bool File::operator == (const File& file) const
{
    return getPathImpl() == file.getPathImpl();
}


inline bool File::operator != (const File& file) const
{
    return getPathImpl() != file.getPathImpl();
}


inline bool File::operator < (const File& file) const
{
    return getPathImpl() < file.getPathImpl();
}


inline bool File::operator <= (const File& file) const
{
    return getPathImpl() <= file.getPathImpl();
}


inline bool File::operator > (const File& file) const
{
    return getPathImpl() > file.getPathImpl();
}


inline bool File::operator >= (const File& file) const
{
    return getPathImpl() >= file.getPathImpl();
}


inline void swap(File& f1, File& f2)
{
    f1.swap(f2);
}


} // namespace Core


#endif  // Core_File_H
