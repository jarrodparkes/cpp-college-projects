//-----------------------------------------------------------------------------
//	Author: Jarrod Parkes
//	Date: September 10, 2013
//
//	File: JPServer.cpp
//
//	Implementation for the JPServer class.
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

#include <string>			//	for std::string object
#include <cctype>			//	used for toUpper() function
#include <iostream>			//	used for standard i/o
#include "JPServer.h"		//	include for JPServer header

using namespace std;		//	namespace for standard i/o
using namespace JPNet;		//	namespace for JPServer, JPSocket, etc.

#define DEFAULT_BUFFER 4096													// buffer size
#define WELCOME_MSG "Welcome to the JPServer. Type 'bye' to close.\r\n"		// welcome msg for client

//-----------------------------------------------------------------------------
//	JPServer* JPServer::CreateServer(char *ipAddr, u_short port, 
//			NetworkProtocol netProt, TransportProtocol transProt)
//
//	Invokes the creation of a JPServer singleton, and returns it.
//
//	ipAddr - IP address of the interface the server will attempt to bind to
//	port - port number the server process will attempt to use
//	netPort	- the network protocol the server will use (only IPv4 for now)
//	transPort - the transport protocol the server will use (only TCP for now)
//-----------------------------------------------------------------------------
JPServer* JPServer::CreateServer(char *ipAddr, u_short port, NetworkProtocol netProt, TransportProtocol transProt) {
	
	static JPServer *m_server = 0;

	//  if JPServer already exists, return it
	if(m_server != NULL) {
		return m_server;		
	}
	//	otherwise, create JPServer and return new it
	else {

		if(TestSocketAPI()) {
			m_server = new JPServer(ipAddr, port, netProt, transProt);
			return m_server;
		}

		else {
			return NULL;
		}
	}
}

//-----------------------------------------------------------------------------
//	bool JPServer::TestSocketAPI(void)
//
//	Tests if the Winsock v2.2 API will initialize.
//
//	Note: This function could be done outside of the class; however, this
//	server is dependent on WinSock, so I left it here.
//-----------------------------------------------------------------------------
bool JPServer::TestSocketAPI(void) {
	
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
//	JPServer::JPServer(char *ipAddr, u_short port, 
//			NetworkProtocol netProt, TransportProtocol transProt)
//
//	Constructs a JPServer singleton and binds it to an interface.
//
//	ipAddr - IP address of the interface the server will attempt to bind to
//	port - port number the server process will attempt to use
//	netPort	- the network protocol the server will use (only IPv4 for now)
//	transPort - the transport protocol the server will use (only TCP for now)
//-----------------------------------------------------------------------------
JPServer::JPServer(char *ipAddr, u_short port, NetworkProtocol netProt, TransportProtocol transProt) {

	// create a WinSock socket
	m_serverSocket.socket = CreateSocket(netProt, transProt);

	if(m_serverSocket.socket != NULL) {

		// set the socket's network protocol, ip address, and port
		m_serverSocket.addr.sin_family = netProt;
		m_serverSocket.addr.sin_addr.s_addr = inet_addr(ipAddr);
		m_serverSocket.addr.sin_port = htons(port);

		// socket fails to bind
		if(!BindSocket()) {
			m_socketBound = false;
			cout << endl << "Socket Cannot Bind to " << inet_ntoa(m_serverSocket.addr.sin_addr) << ":" 
			<< ntohs(m_serverSocket.addr.sin_port) << endl;
			cout << "Try Running JPServer on Different Port!" << endl;
			cout << endl << "[Type \"JPServer.exe /?\" for Help]" << endl;
		}
		// socket binds successfully
		else {
			m_socketBound = true;
		}
	}

	else {
		cout << "Socket could not be created!" << endl;
	}
}

//-----------------------------------------------------------------------------
//	SOCKET JPServer::CreateSocket(NetworkProtocol netProt, 
//			TransportProtocol transProt)
//
//	Creates a WinSock socket and returns it.
//
//	netPort	- the network protocol the socket will use (only IPv4 for now)
//	transPort - the transport protocol the socket will use (only TCP for now)
//-----------------------------------------------------------------------------
SOCKET JPServer::CreateSocket(NetworkProtocol netProt, TransportProtocol transProt) {

	SOCKET tempSocket = socket(netProt, transProt, 0);
	
	// socket creation failed
	if(tempSocket == SOCKET_ERROR) {
		return NULL;
	}

	// socket was created, return it
	return tempSocket;
}

//-----------------------------------------------------------------------------
//	bool JPServer::BindSocket(void)
//
//	Binds the server Winsock socket to an interface.
//-----------------------------------------------------------------------------
bool JPServer::BindSocket(void) {

	// bind failed, print to screen
	if(bind(m_serverSocket.socket, (struct sockaddr *)&m_serverSocket.addr, sizeof(m_serverSocket.addr)) == SOCKET_ERROR) {
		return false;
	}
	// bind success, print to screen the IP and port
	else {
		cout << endl << "Server Started at " << inet_ntoa(m_serverSocket.addr.sin_addr) << ":" 
			<< ntohs(m_serverSocket.addr.sin_port) << endl;
	}

	return true;
}

//-----------------------------------------------------------------------------
//	bool JPServer::IsSocketBound(void)
//
//	Return whether the created socket was bound to an interface.
//-----------------------------------------------------------------------------
bool JPServer::IsSocketBound(void) {
	return m_socketBound;
}

//-----------------------------------------------------------------------------
//	JPServer::~JPServer(void)
//
//	Destructor for JPServer.
//-----------------------------------------------------------------------------
JPServer::~JPServer(void)
{}

//-----------------------------------------------------------------------------
//	void JPServer::StartListening(void)
//
//	Sets JPServer into "listen" mode (passive open) to accept connections. If a
//	client connects, JPServer spawns a thread to handle the "echo" service.	
//-----------------------------------------------------------------------------
void JPServer::StartListening(void) {

	JPSocket tempSocket;	//	struct to hold the values of incoming connections
	
	int ipAddrSize;			//	length of address structure (IPv4 in this case)
	HANDLE hThread;			//	handle for threads
	DWORD dwThreadId;		//	thread identifier

	//	check if socket exists
	if(m_serverSocket.socket == NULL) {
		cout << "Socket Not Initialized, Cannot Start Listening\n";
	}

	//	set socket to "passive open"
	listen(m_serverSocket.socket, 8);

	//	loop continuously waiting for clients
	while(1) {

		//	continually accept incoming connections
		ipAddrSize = sizeof(tempSocket.addr);
		tempSocket.socket = accept(m_serverSocket.socket, (struct sockaddr *)&tempSocket.addr, &ipAddrSize);

		//	found an incoming connection, a new client!
		if (tempSocket.socket != INVALID_SOCKET) {

			//	create a client socket for the server to interact with
			JPSocket *clientSocket = new JPSocket;
			clientSocket->socket = tempSocket.socket;
			clientSocket->addr = tempSocket.addr;

			//	print client's IP and port number
			cout << "Client " << inet_ntoa(clientSocket->addr.sin_addr) << ":" 
				<< ntohs(clientSocket->addr.sin_port) << " Connected" << endl;
 
			//	spawn the EchoService thread to handle the client
			hThread = CreateThread(NULL, 0, EchoService, (LPVOID)clientSocket, 0, &dwThreadId);

			//	thread creation failed
			if (hThread == NULL) {
				cout << "CreateThread() failed: " << GetLastError() << endl;
				break;
			}

			CloseHandle(hThread);
		}
		//	found an incoming connection, but failed to accept it
		else {
			cout << "accept() failed: " << WSAGetLastError() << endl;
			break;
		}
	}

	// server is done waiting, let's close the socket
	closesocket(m_serverSocket.socket);
	WSACleanup();
}

//-----------------------------------------------------------------------------
//	DWORD JPServer::EchoService(LPVOID lpParam)
//
//	Implements an "echo" service for a connection client. At a high level, the 
//	echo service works as follows:
//
//	1.	Receive Client Data
//	a)	send a welcome message to the client
//	b)	receive data from client
//	c)	if newline character is encountered, process data as "command"
//	d)	otherwise, concat data into a buffer
//
//	2.	Parse Received Data
//	a)	check buffer to see if the command is "bye"
//	b)	if command is "bye", then exit
//	c)	otherwise, issue the command by printing it to the server
//	d)	then, format the output and increase command count by one
//	e)	finally, send a response back to the client
//-----------------------------------------------------------------------------
DWORD JPServer::EchoService(LPVOID lpParam) {

	//	convert void pointer back into socket structure
	JPSocket *clientSocket = (JPSocket*)lpParam;

	string recvString; 
	string tempString;

	char receiveBuffer[DEFAULT_BUFFER];
	char responseBuffer[DEFAULT_BUFFER];
	
	int bytesReturned;

	char *tempChar;

	int commandCount = 0;

	//	1a)	send a welcome message to the client
	bytesReturned = send(clientSocket->socket, WELCOME_MSG, (int)strlen(WELCOME_MSG), 0);
		
	if(bytesReturned == SOCKET_ERROR) {
		cout << "Welcome Msg Failed: " << WSAGetLastError() << endl;
		return 0;
	}

	while(1) {

		//	1b)	receive data from client
		bytesReturned = recv(clientSocket->socket, receiveBuffer, DEFAULT_BUFFER, 0);

		// nothing sent
		if (bytesReturned == 0) {
			break;
		}

		else if (bytesReturned == SOCKET_ERROR) {
			cout << "Client " << inet_ntoa(clientSocket->addr.sin_addr) << ":" 
				<< ntohs(clientSocket->addr.sin_port) << " Disconnected" << endl;
			break;
		}

		//	terminate received data with null character
		receiveBuffer[bytesReturned] = '\0';

		//	check for newline character	
		tempChar = strchr(receiveBuffer, '\n');
		
		//	1c)	if newline character is encountered, process data as "command"
		if(tempChar != NULL) {

			// concat received "command" into a buffer (remove \r\n)
			recvString.append(receiveBuffer, 0, tempChar-receiveBuffer-1);

			//	convert command to uppercase for comparison
			for(unsigned int i = 0; i < recvString.length(); i++) {
				tempString += toupper(recvString[i]);
			}

			//	2a)	check buffer to see if the command is "bye"
			if(tempString.compare("BYE") == 0) {

				// send a goodbye message
				send(clientSocket->socket, "Disconnecting from JPServer...", 32, 0);

				// print the client is disconnecting...
				cout << "Client " << inet_ntoa(clientSocket->addr.sin_addr) << ":" 
				<< ntohs(clientSocket->addr.sin_port) << " Disconnected" << endl;

				//	2b)	if command is "bye", then exit
				break;
			}
			else if(recvString.compare("") == 0) {
				// empty command, do nothing
			}
			else {
				//	2c)	otherwise, issue the command by printing it to the server
				cout << "[" << inet_ntoa(clientSocket->addr.sin_addr) << ":" << 
					ntohs(clientSocket->addr.sin_port) << "] " << recvString << endl;

				//	2d)	then, format the output and increase command count by one
				recvString.insert(0, ": ");
				recvString.insert(0, to_string(++commandCount));
				recvString.insert(0, "[Server] Command #");
				recvString.append("\r\n");

				//	copy formatted response into buffer
				strcpy_s(responseBuffer, recvString.c_str());

				//	2e)	finally, send a response back to the client
				bytesReturned = send(clientSocket->socket, responseBuffer, recvString.length(), 0);
				if (bytesReturned == 0) {
					break;
				}
				else if (bytesReturned == SOCKET_ERROR) {
					cout << "Client " << inet_ntoa(clientSocket->addr.sin_addr) << ":" 
					<< ntohs(clientSocket->addr.sin_port) << " Disconnected" << endl;
					break;
				}
			}

			//	clear temporary string "buffers"
			recvString.clear();
			tempString.clear();
		}

		//	1d)	otherwise, concat data into a buffer
		else {
			recvString.append(receiveBuffer);
		}
	}

	//	client disconnected, clean-up
	closesocket(clientSocket->socket);
	delete clientSocket;
	clientSocket = NULL;
	return 0;
}