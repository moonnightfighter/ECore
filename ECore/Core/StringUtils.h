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

#ifndef Core_StringUtils_H
#define Core_StringUtils_H


#include <stdlib.h>
#include <errno.h>
#include <string.h>


template <typename T>
inline bool core_string_to_value(char* str_in, T* val_out, int base)
{
    if (0 == str_in || 0 == val_out)
    {
        return false;
    }

    char* end = 0;
    *val_out = strtol(str_in, &end, 10); // room id
    return (str_in != end && errno != ERANGE);
}

inline bool core_string_equal(const char* s1, const char* s2)
{
    if (0 == s1 || 0 == s2)
    {
        return false;
    }

    return (0 == strcmp(s1, s2));
}

inline int core_string_split(const char* separator, char* str_in, char* argv_out[], int argv_max)
{
    int argc = 0;
    char *token = strtok(str_in, separator);
    while(token != 0)
    {
        if (argc >= argv_max)
        {
            break;
        }
        argv_out[argc] = token;
        //printf("split argc:%d, argv:%s\n", argc, argv_out[argc]);
        ++argc;
        token = strtok(0, separator);
    }
    return argc;
}


#endif  // Core_StringUtils_H
