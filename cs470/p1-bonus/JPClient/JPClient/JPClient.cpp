//-----------------------------------------------------------------------------
//	Author: Jarrod Parkes
//	Date: September 15, 2013
//
//	File: JPClient.cpp
//
//	Implementation for the JPClient class.
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

#include <string>				//	used for std::string
#include <iostream>				//	used for standard i/o
#include <WinSock2.h>			//	header for WinSock
#include <ws2tcpip.h>			//	header for getaddrinfo 
#include "JPClient.h"			//	include for JPServer header

using namespace std;			//	namespace for standard i/o
using namespace JPNet;			//	namespace for JPServer, JPSocket, etc.

#define DEFAULT_BUFFER 4096		// buffer size

//-----------------------------------------------------------------------------
//	JPClient* JPClient::CreateClient(void)
//
//	Invokes the creation of a JPClient singleton, and returns it.
//-----------------------------------------------------------------------------
JPClient* JPClient::CreateClient(void) {
	
	static JPClient *m_client = 0;

	//  if JPClient already exists, return it
	if(m_client != NULL) {
		return m_client;		
	}
	//	otherwise, create JPClient and return new it
	else {

		if(TestSocketAPI()) {
			m_client = new JPClient();
			m_client->m_clientSocket.socket = INVALID_SOCKET;
			return m_client;
		}

		else {
			return NULL;
		}
	}
}

//-----------------------------------------------------------------------------
//	bool JPClient::TestSocketAPI(void)
//
//	Tests if the Winsock v2.2 API will initialize.
//-----------------------------------------------------------------------------
bool JPClient::TestSocketAPI(void) {
	
	// struct to store Winsock data
	WSADATA wsd;

	// intialize Winsock v2.2
	if(WSAStartup(MAKEWORD(2,2), &wsd) != 0) {
		cout << "Failed to load Winsock v2.2!" << endl;
		return false;
	}

	// WinSock started normally
	return true;
}

//-----------------------------------------------------------------------------
//	JPClient::JPClient(void)
//
//	Constructs a JPClient singleton.
//-----------------------------------------------------------------------------
JPClient::JPClient(void)
{}

//-----------------------------------------------------------------------------
//	JPClient::~JPClient(void)
//
//	Destructor for JPClient.
//-----------------------------------------------------------------------------
JPClient::~JPClient(void)
{}

//-----------------------------------------------------------------------------
//	bool JPClient::Connect(char *ipAddr, char *port, 
//					NetworkProtocol netProt, TransportProtocol transProt)
//
//	Attempts to connect a JPClient to a JPServer.
//	http://msdn.microsoft.com/en-us/library/windows/desktop/ms737591(v=vs.85).aspx
//
//	ipAddr - IP address of the interface the server will attempt to bind to
//	port - port number the server process will attempt to use
//	netPort	- the network protocol the server will use (only IPv4 for now)
//	transPort - the transport protocol the server will use (only TCP for now)
//-----------------------------------------------------------------------------
bool JPClient::Connect(char *ipAddr, char *port, 
	NetworkProtocol netProt, TransportProtocol transProt) {

	struct addrinfo *result = NULL;
	struct addrinfo *ptr = NULL;
	struct addrinfo hint;

    int bytesReturned;

	//	initialize a "hint" address (used to search for JPServer)
    ZeroMemory(&hint, sizeof(hint));		//	clear "hint" address
	hint.ai_family = netProt;				//	use IPv4
    hint.ai_socktype = transProt;			//	use TCP
    hint.ai_protocol = IPPROTO_TCP;			//	use IPv4 w/TCP

    //	store JPServer address into result
    bytesReturned = getaddrinfo(ipAddr, port, &hint, &result);
    if (bytesReturned != 0) {
        cout << "getaddrinfo failed with error: " << bytesReturned << endl;
        WSACleanup();
        return false;
    }

    //	attempt to connect to JPServer
    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {

        //	set client socket to correct type
		m_clientSocket.socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (m_clientSocket.socket == INVALID_SOCKET) {
            cout << "socket failed with error: " << WSAGetLastError() << endl;
            WSACleanup();
            return false;
        }

        // connect to a JPServer
        bytesReturned = connect(m_clientSocket.socket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (bytesReturned == SOCKET_ERROR) {
            closesocket(m_clientSocket.socket);
            m_clientSocket.socket = INVALID_SOCKET;
            continue;
        }
        break;
    }

	// cannot connect to the JPServer
    if (m_clientSocket.socket == INVALID_SOCKET) {
        cout << endl << "Unable to Connect to JPServer!" << endl;
		cout << "Are You Running JPClient with the Correct IP and Port?" << endl;
		cout << endl << "[Type \"JPClient.exe /?\" for Help]" << endl;
        WSACleanup();
        return false;
    }

	return true;
}

//-----------------------------------------------------------------------------
//	void JPClient::EchoService(void)
//
//	Implements the "echo" service for a JPClient. At a high level, the 
//	echo service works as follows:
//
//	1.	Poll/Send Client Input
//	a)	prompt client for input
//	b)	parse input, send to JPServer
//	c)	clear input string for future use
//
//	2.	Parse Any Received Data
//	a)	receive data from server
//	b)	if data is received, parse it 
//	c)	if data is "Disconnecting from JPServer...", then exit
//	d)	otherwise, print received data
//-----------------------------------------------------------------------------
void JPClient::EchoService(void) {

	string recvString; 
	string sendString;

	char responseBuffer[DEFAULT_BUFFER];
    char receiveBuffer[DEFAULT_BUFFER];
    int bytesReturned;
    int recvbuflen = DEFAULT_BUFFER;

	//	receive welcome message for JPServer
	system("cls");
	bytesReturned = recv(m_clientSocket.socket, receiveBuffer, 4096, 0);
	if (bytesReturned == SOCKET_ERROR) {
        cout << "Welcome Msg Failed" << endl;
        WSACleanup();
		return;
	}
	//	null-terminate messsage, and print
	else {
		receiveBuffer[bytesReturned] = '\0';
		cout << receiveBuffer;
	}

	// EchoService loop
	while(1) {

		//	1a)	prompt client for input
		getline(cin, sendString);

		//	1b) parse input, send to JPServer
		if(sendString.length() != 0) {
			sendString.append("\r\n");

			//	copy formatted response into buffer
			strcpy_s(responseBuffer, sendString.c_str());

			bytesReturned = send(m_clientSocket.socket, responseBuffer, sendString.length(), 0 );
			if (bytesReturned == SOCKET_ERROR) {
				cout << endl << "Send failed!" << endl << "Server has closed connection..." << endl;
				closesocket(m_clientSocket.socket);
				WSACleanup();
				return;
			}
		}
		//	nothing was entered, continue through
		else {
			continue;
		}

		//	1c)	clear input string for future use
		sendString.clear();
	
		//	2a)	receive data from server
		bytesReturned = recv(m_clientSocket.socket, receiveBuffer, 4096, 0);
		if (bytesReturned == 0) {
			continue;
		}
		else if (bytesReturned == SOCKET_ERROR) {
			cout << "Disconnected" << endl;
			break;
		}
		//	2b)	if data is received, parse it 
		else {
			receiveBuffer[bytesReturned] = '\0';
			recvString.append(receiveBuffer);

			//	2c)	if data is "Disconnecting from JPServer...", then exit
			if(recvString.compare("Disconnecting from JPServer...") == 0) {
				cout << "Disconnecting from JPServer..." << endl;
				break;
			}
			//	2d)	otherwise, print received data
			else {
				cout << receiveBuffer;
			}
		}

		recvString.clear();
	}

	// close socket and return
	closesocket(m_clientSocket.socket);
    WSACleanup();
	return;
}