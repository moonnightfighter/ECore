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

#ifndef Net_SocketAddress_H
#define Net_SocketAddress_H


#include "ECore/Net/Net.h"
#include "ECore/Net/SocketDefs.h"
#include "ECore/Net/SocketAddressAttribute.h"


namespace Core {
namespace Net {


class SocketAddressImpl;


class Net_API SocketAddress
{
public:
	SocketAddress();
	SocketAddress(const std::string& host, Core::UInt16 port);
	SocketAddress(const std::string& host, const std::string& port);
	explicit SocketAddress(const std::string& hostAndPort);
	SocketAddress(const SocketAddress& addr);
	SocketAddress(const struct sockaddr* addr, core_socklen_t length);
	~SocketAddress();
		
	SocketAddress& operator = (const SocketAddress& addr);
		
	void swap(SocketAddress& addr);
		
    std::string host() const;
		
	Core::UInt16 port() const;
		
	core_socklen_t length() const;
	const struct sockaddr* addr() const;

    SocketAddressAttribute attribute();

	int af() const;
		
	std::string toString() const;
		
	bool operator < (const SocketAddress& addr) const;
	bool operator == (const SocketAddress& addr) const;
	bool operator != (const SocketAddress& addr) const;
			
	enum
	{
		MAX_ADDRESS_LENGTH = 
#if defined(CORE_HAVE_IPv6)
			sizeof(struct sockaddr_in6)
#else
			sizeof(struct sockaddr_in)
#endif
			/// Maximum length in bytes of a socket address.
	};

protected:
	void init(const std::string& host, Core::UInt16 port);
	Core::UInt16 resolveService(const std::string& service);

private:
	SocketAddressImpl* _pImpl;
};


//
// inlines
//
inline void swap(SocketAddress& a1, SocketAddress& a2)
{
	a1.swap(a2);
}



inline 	bool SocketAddress::operator == (const SocketAddress& addr) const
{
	return host() == addr.host() && port() == addr.port();
}


inline bool SocketAddress::operator != (const SocketAddress& addr) const
{
	return host() != addr.host() || port() != addr.port();
}


} }   // namespace Core::Net


#endif  // Net_SocketAddress_H


