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

#ifndef Net_SocketDefs_H
#define Net_SocketDefs_H


#if defined(CORE_OS_FAMILY_WINDOWS)
#include "ECore/Core/UnWindows.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#define CORE_INVALID_SOCKET  INVALID_SOCKET
#define core_socket_t        SOCKET
#define core_socklen_t       int
#define core_ioctl_request_t int
#define core_closesocket(s)  closesocket(s)
#define CORE_EINTR           WSAEINTR
#define CORE_EACCES          WSAEACCES
#define CORE_EFAULT          WSAEFAULT
#define CORE_EINVAL          WSAEINVAL
#define CORE_EMFILE          WSAEMFILE
#define CORE_EAGAIN          WSAEWOULDBLOCK
#define CORE_EWOULDBLOCK     WSAEWOULDBLOCK
#define CORE_EINPROGRESS     WSAEINPROGRESS
#define CORE_EALREADY        WSAEALREADY
#define CORE_ENOTSOCK        WSAENOTSOCK
#define CORE_EDESTADDRREQ    WSAEDESTADDRREQ
#define CORE_EMSGSIZE        WSAEMSGSIZE
#define CORE_EPROTOTYPE      WSAEPROTOTYPE
#define CORE_ENOPROTOOPT     WSAENOPROTOOPT
#define CORE_EPROTONOSUPPORT WSAEPROTONOSUPPORT
#define CORE_ESOCKTNOSUPPORT WSAESOCKTNOSUPPORT
#define CORE_ENOTSUP         WSAEOPNOTSUPP
#define CORE_EPFNOSUPPORT    WSAEPFNOSUPPORT
#define CORE_EAFNOSUPPORT    WSAEAFNOSUPPORT
#define CORE_EADDRINUSE      WSAEADDRINUSE
#define CORE_EADDRNOTAVAIL   WSAEADDRNOTAVAIL
#define CORE_ENETDOWN        WSAENETDOWN
#define CORE_ENETUNREACH     WSAENETUNREACH
#define CORE_ENETRESET       WSAENETRESET
#define CORE_ECONNABORTED    WSAECONNABORTED
#define CORE_ECONNRESET      WSAECONNRESET
#define CORE_ENOBUFS         WSAENOBUFS
#define CORE_EISCONN         WSAEISCONN
#define CORE_ENOTCONN        WSAENOTCONN
#define CORE_ESHUTDOWN       WSAESHUTDOWN
#define CORE_ETIMEDOUT       WSAETIMEDOUT
#define CORE_ECONNREFUSED    WSAECONNREFUSED
#define CORE_EHOSTDOWN       WSAEHOSTDOWN
#define CORE_EHOSTUNREACH    WSAEHOSTUNREACH
#define CORE_ESYSNOTREADY    WSASYSNOTREADY
#define CORE_ENOTINIT        WSANOTINITIALISED
#define CORE_HOST_NOT_FOUND  WSAHOST_NOT_FOUND
#define CORE_TRY_AGAIN       WSATRY_AGAIN
#define CORE_NO_RECOVERY     WSANO_RECOVERY
#define CORE_NO_DATA         WSANO_DATA
#elif defined(CORE_VXWORKS)
#include <hostLib.h>
#include <ifLib.h>
#include <inetLib.h>
#include <ioLib.h>
#include <resolvLib.h>
#include <types.h>
#include <socket.h>
#include <netinet/tcp.h>
#define CORE_INVALID_SOCKET  -1
#define core_socket_t        int
#define core_socklen_t       int
#define core_ioctl_request_t int
#define core_closesocket(s)  ::close(s)
#define CORE_EINTR           EINTR
#define CORE_EACCES          EACCES
#define CORE_EFAULT          EFAULT
#define CORE_EINVAL          EINVAL
#define CORE_EMFILE          EMFILE
#define CORE_EAGAIN          EAGAIN
#define CORE_EWOULDBLOCK     EWOULDBLOCK
#define CORE_EINPROGRESS     EINPROGRESS
#define CORE_EALREADY        EALREADY
#define CORE_ENOTSOCK        ENOTSOCK
#define CORE_EDESTADDRREQ    EDESTADDRREQ
#define CORE_EMSGSIZE        EMSGSIZE
#define CORE_EPROTOTYPE      EPROTOTYPE
#define CORE_ENOPROTOOPT     ENOPROTOOPT
#define CORE_EPROTONOSUPPORT EPROTONOSUPPORT
#define CORE_ESOCKTNOSUPPORT ESOCKTNOSUPPORT
#define CORE_ENOTSUP         ENOTSUP
#define CORE_EPFNOSUPPORT    EPFNOSUPPORT
#define CORE_EAFNOSUPPORT    EAFNOSUPPORT
#define CORE_EADDRINUSE      EADDRINUSE
#define CORE_EADDRNOTAVAIL   EADDRNOTAVAIL
#define CORE_ENETDOWN        ENETDOWN
#define CORE_ENETUNREACH     ENETUNREACH
#define CORE_ENETRESET       ENETRESET
#define CORE_ECONNABORTED    ECONNABORTED
#define CORE_ECONNRESET      ECONNRESET
#define CORE_ENOBUFS         ENOBUFS
#define CORE_EISCONN         EISCONN
#define CORE_ENOTCONN        ENOTCONN
#define CORE_ESHUTDOWN       ESHUTDOWN
#define CORE_ETIMEDOUT       ETIMEDOUT
#define CORE_ECONNREFUSED    ECONNREFUSED
#define CORE_EHOSTDOWN       EHOSTDOWN
#define CORE_EHOSTUNREACH    EHOSTUNREACH
#define CORE_ESYSNOTREADY    -4
#define CORE_ENOTINIT        -5
#define CORE_HOST_NOT_FOUND  HOST_NOT_FOUND
#define CORE_TRY_AGAIN       TRY_AGAIN
#define CORE_NO_RECOVERY     NO_RECOVERY
#define CORE_NO_DATA         NO_DATA
#elif defined(CORE_OS_FAMILY_UNIX) || defined(CORE_OS_FAMILY_VMS)
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#if CORE_OS != CORE_OS_HPUX
#include <sys/select.h>
#endif
#include <sys/ioctl.h>
#if defined(CORE_OS_FAMILY_VMS)
#include <inet.h>
#else
#include <arpa/inet.h>
#endif
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#if defined(CORE_OS_FAMILY_UNIX)
#include <net/if.h>
#endif
#if defined(sun) || defined(__APPLE__)
#include <sys/sockio.h>
#include <sys/filio.h>
#endif
#define CORE_INVALID_SOCKET  -1
#define core_socket_t        int
#define core_socklen_t       socklen_t
#if defined(CORE_OS_FAMILY_BSD)
#define core_ioctl_request_t unsigned long
#else
#define core_ioctl_request_t int
#endif
#define core_closesocket(s)  ::close(s)
#define CORE_EINTR           EINTR
#define CORE_EACCES          EACCES
#define CORE_EFAULT          EFAULT
#define CORE_EINVAL          EINVAL
#define CORE_EMFILE          EMFILE
#define CORE_EAGAIN          EAGAIN
#define CORE_EWOULDBLOCK     EWOULDBLOCK
#define CORE_EINPROGRESS     EINPROGRESS
#define CORE_EALREADY        EALREADY
#define CORE_ENOTSOCK        ENOTSOCK
#define CORE_EDESTADDRREQ    EDESTADDRREQ
#define CORE_EMSGSIZE        EMSGSIZE
#define CORE_EPROTOTYPE      EPROTOTYPE
#define CORE_ENOPROTOOPT     ENOPROTOOPT
#define CORE_EPROTONOSUPPORT EPROTONOSUPPORT
#if defined(ESOCKTNOSUPPORT)
#define CORE_ESOCKTNOSUPPORT ESOCKTNOSUPPORT
#else
#define CORE_ESOCKTNOSUPPORT -1
#endif
#define CORE_ENOTSUP         ENOTSUP
#define CORE_EPFNOSUPPORT    EPFNOSUPPORT
#define CORE_EAFNOSUPPORT    EAFNOSUPPORT
#define CORE_EADDRINUSE      EADDRINUSE
#define CORE_EADDRNOTAVAIL   EADDRNOTAVAIL
#define CORE_ENETDOWN        ENETDOWN
#define CORE_ENETUNREACH     ENETUNREACH
#define CORE_ENETRESET       ENETRESET
#define CORE_ECONNABORTED    ECONNABORTED
#define CORE_ECONNRESET      ECONNRESET
#define CORE_ENOBUFS         ENOBUFS
#define CORE_EISCONN         EISCONN
#define CORE_ENOTCONN        ENOTCONN
#if defined(ESHUTDOWN)
#define CORE_ESHUTDOWN       ESHUTDOWN
#else
#define CORE_ESHUTDOWN       -2
#endif
#define CORE_ETIMEDOUT       ETIMEDOUT
#define CORE_ECONNREFUSED    ECONNREFUSED
#if defined(EHOSTDOWN)
#define CORE_EHOSTDOWN       EHOSTDOWN
#else
#define CORE_EHOSTDOWN       -3
#endif
#define CORE_EHOSTUNREACH    EHOSTUNREACH
#define CORE_ESYSNOTREADY    -4
#define CORE_ENOTINIT        -5
#define CORE_HOST_NOT_FOUND  HOST_NOT_FOUND
#define CORE_TRY_AGAIN       TRY_AGAIN
#define CORE_NO_RECOVERY     NO_RECOVERY
#define CORE_NO_DATA         NO_DATA
#endif


#if defined(CORE_OS_FAMILY_BSD) || (CORE_OS == CORE_OS_TRU64) || (CORE_OS == CORE_OS_AIX) || (CORE_OS == CORE_OS_IRIX) || (CORE_OS == CORE_OS_QNX) || (CORE_OS == CORE_OS_VXWORKS)
#define CORE_HAVE_SALEN      1
#endif


#if CORE_OS != CORE_OS_VXWORKS && !defined(CORE_NET_NO_ADDRINFO)
#define CORE_HAVE_ADDRINFO   1
#endif


#if (CORE_OS == CORE_OS_HPUX) || (CORE_OS == CORE_OS_SOLARIS) || (CORE_OS == CORE_OS_WINDOWS_CE)
#define CORE_BROKEN_TIMEOUTS 1
#endif


#if defined(CORE_HAVE_ADDRINFO)
#if !defined(AI_ADDRCONFIG)
#define AI_ADDRCONFIG 0
#endif
#endif


#if defined(CORE_HAVE_SALEN)
#define core_set_sa_len(pSA, len) (pSA)->sa_len   = (len)
#define core_set_sin_len(pSA)     (pSA)->sin_len  = sizeof(struct sockaddr_in)
#if defined(CORE_HAVE_IPv6)
#define core_set_sin6_len(pSA)    (pSA)->sin6_len = sizeof(struct sockaddr_in6)
#endif
#else
#define core_set_sa_len(pSA, len) (void) 0
#define core_set_sin_len(pSA)     (void) 0
#define core_set_sin6_len(pSA)    (void) 0
#endif


#ifndef INADDR_NONE
#define INADDR_NONE 0xFFFFFFFF
#endif


#endif  // Net_SocketDefs_H
