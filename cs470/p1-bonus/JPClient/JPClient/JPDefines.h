//-----------------------------------------------------------------------------
//	Author: Jarrod Parkes
//	Date: September 15, 2013
//
//	File: JPDefines.h
//
//	Headers and definitions for the JPNet namespace.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//	CREDITS/REFERENCES
//
//	1. Simple WinSock Client Code (C++)
//	http://msdn.microsoft.com/en-us/library/windows/desktop/ms737591(v=vs.85).aspx
//	I used this source code as a reference when getting started. I had to make
//	several changes for command parsing, etc., but this was very useful
//	for getting started with the WinSock API.
//
//	2. WinSock Overview
//	http://en.wikipedia.org/wiki/Winsock
//	After seeing the above example used WinSock, I did a quick Wiki read to get 
//	a high-level understanding of the API.
//
//	3. WinSock MSDN Reference
//	http://msdn.microsoft.com/en-us/library/windows/desktop/ms741416(v=vs.85).aspx
//	Finally, when I began writing my code, I used this as a reference to ensure
//	I was correctly calling/using the functions in the WinSock API.
//-----------------------------------------------------------------------------

#ifndef JPDEFINES_H
#define JPDEFINES_H

#include <WinSock2.h>				// header for WinSock

#pragma comment(lib, "Ws2_32.lib")	// link against WinSock library

namespace JPNet {

	// a mapping of network protocols to WinSock arguments
	enum NetworkProtocol {
		IPv4 = 2,		//	AF_INET
		IPv6 = 23		//	AF_INET6
	};

	// a mapping of transport protocols to WinSock arguments
	enum TransportProtocol {
		TCP = 1,		//	SOCK_STREAM
		UDP = 2			//	SOCK_DGRAM
	};

	// struct to encapsulate WinSock socket and its associated address
	struct JPSocket {
		SOCKET socket;
		SOCKADDR_IN addr;
	};
}

#endif