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

#ifndef Net_Net_H
#define Net_Net_H


#include "ECore/Core/Core.h"


#if defined(_WIN32) && defined(_DLL)
#if !defined(NET_DLL) && !defined(NET_STATIC)
#define NET_DLL
#endif
#endif


#if defined(_WIN32) && defined(NET_DLL)
#ifdef NET_EXPORTS
#define Net_API __declspec(dllexport)
#else
#define Net_API __declspec(dllimport)
#endif
#endif


#if !defined(Net_API)
#define Net_API
#endif


//
// Automatically link Net library.
//
#if defined(_MSC_VER)
    #if !defined(NET_EXPORTS)
        #pragma comment(lib, "Net" CORE_LIB_SUFFIX)
    #endif
#endif


#if defined(_MSC_VER) && defined(NET_DLL)
    #pragma comment(lib, "ws2_32.lib")
    #pragma comment(lib, "iphlpapi.lib")
#endif


namespace Core {
namespace Net {


void Net_API initializeNetwork();
/// Initialize the network subsystem.
/// Calls WSAStartup() on Windows, does nothing
/// on other platforms.


void Net_API uninitializeNetwork();
/// Uninitialize the network subsystem.
/// Calls WSACleanup() on Windows, does nothing
/// on other platforms.


} }   // namespace Core::Net


#endif  // Net_Net_H
