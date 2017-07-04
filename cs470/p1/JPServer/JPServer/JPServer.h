//-----------------------------------------------------------------------------
//	Author: Jarrod Parkes
//	Date: September 10, 2013
//
//	File: JPServer.h
//
//	Header/definition for the JPServer class.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//	CREDITS/REFERENCES
//
//	1. TCP/IP Server Example (in C)
//	http://www.mycplus.com/source-code/c-source-code/tcp-client-and-server/
//	I used this source code as a reference when getting started. Since this code
//	is largely procedural, I created my own OO-design around it in C++. I also did 
//	my best to make the code extensible for re-use.
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

#ifndef JPSERVER_H
#define JPSERVER_H

#include "JPDefines.h"

namespace JPNet {
	//-----------------------------------------------------------------------------
	//	JPServer
	//
	//	JPServer is a simple TCP/IP server built on top of the WinSock API.
	//
	//	This server is capable of handling multiple clients by spawning a separate
	//	thread for each connection to handle a simple "echo" service.
	//
	//	JPServer is implemented as a singleton.
	//-----------------------------------------------------------------------------
	class JPServer
	{
		public:
			static JPServer* CreateServer(char *ipAddr, u_short port, NetworkProtocol procFam = NetworkProtocol::IPv4, TransportProtocol transProt = TransportProtocol::TCP);
			void StartListening(void);
			bool IsSocketBound(void);

		private:
			JPSocket m_serverSocket;
			bool m_socketBound;

			JPServer(char *ipAddr, u_short port, NetworkProtocol netProt, TransportProtocol transProt);
			~JPServer(void);

			static bool TestSocketAPI(void);
			
			SOCKET CreateSocket(NetworkProtocol netProt, TransportProtocol transProt);
			bool BindSocket(void);	

			static DWORD WINAPI EchoService(LPVOID lpParam);
	};
};

#endif