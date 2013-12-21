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

#ifndef Core_InifileEx_H
#define Core_InifileEx_H


#include "ECore/Core/Core.h"
#include <stdlib.h>


namespace Core {


class Core_API InifileEx
{
public:
    enum {
        MAX_FILE_SIZE = 4096,

        COMMENT_SYMBOL = '#'    // skip over comment
    };

    InifileEx(const char* file);
    virtual ~InifileEx();

    double readFloat(const char* section, const char* key, double default_v);
    bool writeFloat(const char* section, const char* key, double value);

    int readInteger(const char* section, const char* key, int default_v);
    bool writeInteger(const char* section, const char* key, int value);

    bool readBool(const char* section, const char* key, bool default_v);
    bool writeBool(const char* section, const char* key, bool value);

    std::string readString(const char* section, const char* key, const char* default_v);
    bool writeString(const char* section, const char* key, const char* value);
  
protected:
    bool parse(const char *section, const char *key, int &section_s, int &section_e, 
            int &key_s, int &key_e, int &value_s, int &value_e, const char *buf);

    virtual int readRaw(const char* file, char* rbuf); // return length, not contain '\0'.
    virtual int writeRaw(const char* file, char* wbuf);

    int readValue(const char* section, const char* key, std::string& value);
    int writeValue(const char* section, const char* key, std::string& value);

    bool isNewLine(const char& c);
    bool isEnd(const char& c);
    bool isLeftBrace(const char& c);
    bool isRightBrace(const char& c);

private:
    char m_buf[MAX_FILE_SIZE];
    std::string m_file;
};


//
// inlines
//
inline bool InifileEx::isNewLine(const char& c)
{
    return ('\n' == c || '\r' == c) ? 1 : 0;
}

inline bool InifileEx::isEnd(const char& c)
{
    return '\0' == c ? 1 : 0;
}

inline bool InifileEx::isLeftBrace(const char& c)
{
    return '[' == c ? 1 : 0;
}

inline bool InifileEx::isRightBrace(const char& c)
{
    return ']' == c ? 1 : 0;
}

inline double InifileEx::readFloat(const char* section, const char* key, double default_v)
{
    std::string value;
    if (0 == readValue(section, key, value))
    {
        char* endPtr = 0;
        double res = strtod(value.c_str(), &endPtr);
        return 0 != endPtr ? res : default_v;
    }
    else
    {
        return default_v;
    }
}

inline bool InifileEx::writeFloat(const char* section, const char* key, double value)
{
    char buf[32] = {0};
    snprintf(buf, sizeof(buf), "%0.8f", value);
    std::string tmp(buf);
    return 0 == writeValue(section, key, tmp);
}

inline int InifileEx::readInteger(const char* section, const char* key, int default_v)
{
    std::string value;
    if (0 == readValue(section, key, value))
    {
        char* endPtr = 0;
        int res = strtol(value.c_str(), &endPtr, 10);
        return 0 != endPtr ? res : default_v;
    }
    else
    {
        return default_v;
    }
}

inline bool InifileEx::writeInteger(const char* section, const char* key, int value)
{
    char buf[32] = {0};
    snprintf(buf, sizeof(buf), "%d", value);
    std::string tmp(buf);
    return 0 == writeValue(section, key, tmp);
}

inline bool InifileEx::readBool(const char* section, const char* key, bool default_v)
{
    std::string value;
    if (0 == readValue(section, key, value))
    {
        char* endPtr = 0;
        bool res = strtol(value.c_str(), &endPtr, 10) == 0 ? false : true;
        return 0 != endPtr ? res : default_v;
    }
    else
    {
        return default_v;
    }
}

inline bool InifileEx::writeBool(const char* section, const char* key, bool value)
{
    char buf[32] = {0};
    snprintf(buf, sizeof(buf), "%d", value ? 1 : 0);
    std::string tmp(buf);
    return 0 == writeValue(section, key, tmp);
}

inline std::string InifileEx::readString(const char* section, const char* key, const char* default_v)
{
    std::string value = default_v;
    readValue(section, key, value);
    return value;
}

inline bool InifileEx::writeString(const char* section, const char* key, const char* value)
{
    std::string tmp(value);
    return 0 == writeValue(section, key, tmp);
}


}   // namespace Core

#endif  // Core_InifileEx_H
