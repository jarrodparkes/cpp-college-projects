//-----------------------------------------------------------------------------
//	Author: Jarrod Parkes
//	Date: September 15, 2013
//
//	File: JPClient.h
//
//	Header/definition for the JPClient class.
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

#ifndef JPCLIENT_H
#define JPCLIENT_H

#include "JPDefines.h"

namespace JPNet {
	//-----------------------------------------------------------------------------
	//	JPClient
	//
	//	JPClient is a simple TCP/IP client built on top of the WinSock API.
	//
	//	JPClient is implemented as a singleton.
	//-----------------------------------------------------------------------------
	class JPClient
	{
		public:
			static JPClient* CreateClient(void);
			bool Connect(char *ipAddr, char *port, NetworkProtocol procFam = NetworkProtocol::IPv4, 
				TransportProtocol transProt = TransportProtocol::TCP);
			void EchoService(void);

		private:
			JPSocket m_clientSocket;

			JPClient(void);
			~JPClient(void);

			static bool TestSocketAPI(void);
	};
};

#endif