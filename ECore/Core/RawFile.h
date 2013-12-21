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

#ifndef Core_RawFile_H
#define Core_RawFile_H


#include "ECore/Core/Core.h"


namespace Core {


class Core_API RawFile
{
public:
    RawFile();
    RawFile(const char* file, bool autoCreate = false);
    ~RawFile();

    bool open(const char* file, bool autoCreate = false);
    void close();

    bool opened();

    int get(char* buf_out, int len);    // return gets length.
    int put(const char* buf_in, int len);   // return puts length.
    void flush();

    int eof();  // return end pos of file.
    bool offset(int pos);

    void setFile(std::string file);
    std::string name();

private:
    std::string _name;
    FILE* _fd;
};


//
// inlines
//
inline void RawFile::setFile(std::string file)
{
    _name = file;
}

inline std::string RawFile::name()
{
    return _name;
}

inline bool RawFile::opened()
{
    return 0 != _fd;
}


}  // namespace Core


#endif  // Core_RawFile_H
