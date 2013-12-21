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

#ifndef Net_NetException_H
#define Net_NetException_H

#include "ECore/Net/Net.h"
#include "ECore/Core/Exception.h"


namespace Core {
namespace Net {


CORE_DECLARE_EXCEPTION(Net_API, NetException, Core::IOException)
CORE_DECLARE_EXCEPTION(Net_API, InvalidAddressException, NetException)
CORE_DECLARE_EXCEPTION(Net_API, InvalidSocketException, NetException)
CORE_DECLARE_EXCEPTION(Net_API, ServiceNotFoundException, NetException)
CORE_DECLARE_EXCEPTION(Net_API, ConnectionAbortedException, NetException)
CORE_DECLARE_EXCEPTION(Net_API, ConnectionResetException, NetException)
CORE_DECLARE_EXCEPTION(Net_API, ConnectionRefusedException, NetException)
CORE_DECLARE_EXCEPTION(Net_API, DNSException, NetException)
CORE_DECLARE_EXCEPTION(Net_API, HostNotFoundException, DNSException)
CORE_DECLARE_EXCEPTION(Net_API, NoAddressFoundException, DNSException)
CORE_DECLARE_EXCEPTION(Net_API, InterfaceNotFoundException, NetException)
CORE_DECLARE_EXCEPTION(Net_API, NoMessageException, NetException)
CORE_DECLARE_EXCEPTION(Net_API, MessageException, NetException)
CORE_DECLARE_EXCEPTION(Net_API, MultipartException, MessageException)
CORE_DECLARE_EXCEPTION(Net_API, HTTPException, NetException)
CORE_DECLARE_EXCEPTION(Net_API, NotAuthenticatedException, HTTPException)
CORE_DECLARE_EXCEPTION(Net_API, UnsupportedRedirectException, HTTPException)
CORE_DECLARE_EXCEPTION(Net_API, FTPException, NetException)
CORE_DECLARE_EXCEPTION(Net_API, SMTPException, NetException)
CORE_DECLARE_EXCEPTION(Net_API, POP3Exception, NetException)
CORE_DECLARE_EXCEPTION(Net_API, ICMPException, NetException)
CORE_DECLARE_EXCEPTION(Net_API, HTMLFormException, NetException)
CORE_DECLARE_EXCEPTION(Net_API, WebSocketException, NetException)


} }   // namespace Core::Net


#endif  // Net_NetException_H
