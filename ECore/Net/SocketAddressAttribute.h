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

#ifndef Net_SocketAddressAttribute_H
#define Net_SocketAddressAttribute_H


#include "ECore/Net/Net.h"
#include "ECore/Net/SocketDefs.h"


namespace Core {
namespace Net {
 

class Net_API SocketAddressAttribute
{
public:
    SocketAddressAttribute();
    SocketAddressAttribute(unsigned int ip, unsigned short port);
    ~SocketAddressAttribute();

    Core::UInt32 ip() const;
    Core::UInt16 port() const;

    std::string host() const;
    std::string toString() const;

    struct sockaddr addr();
    void addr(struct sockaddr& sa);

    bool valid();

    void reset();

    bool operator == (const SocketAddressAttribute& attr) const;
    bool operator != (const SocketAddressAttribute& attr) const;

    SocketAddressAttribute& operator = (const SocketAddressAttribute& other);
    SocketAddressAttribute& operator = (const struct sockaddr& sa);

private:
    volatile Core::UInt32 _ip;
    volatile Core::UInt16 _port;
};


//
// inlines
//
inline Core::UInt32 SocketAddressAttribute::ip() const
{
    return _ip;
}

inline Core::UInt16 SocketAddressAttribute::port() const
{
    return ntohs(_port);
}


}}  // namespace Core::Net


#endif  // Net_SocketAddressAttribute_H
