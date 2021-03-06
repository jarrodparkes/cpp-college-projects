//-----------------------------------------------------------------------------
//	Author: Jarrod Parkes
//	Date: September 10, 2013
//
//	File: Main.cpp
//
//	Entry point to program, help menu, and command line parsing.
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

#include <iostream>		//	used for standard i/o
#include "JPServer.h"	//	used for JPServer class

using namespace std;	//	namespace for standard i/o
using namespace JPNet;	//	namespace for JPServer, JPSocket, etc.

#define DEFAULT_IP "127.0.0.1"	//	unless specified, bind to interface 127.0.0.1
#define DEFAULT_PORT 11865		//	unless specified, bind to port 5150

//	command line struct
struct cl_struct {
	int port;
	bool customIP;
	char ipAddress[128];
};

//	function prototypes
void HelpMenu(void);
void ParseArguments(int argc, char **argv, cl_struct *args);

//-----------------------------------------------------------------------------
//	int main(int argc, char **argv)
//
//	Entry point of program.
//
//	argc - number of arugments
//  argv - array of argument values
//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	//	parse command line options
	cl_struct clArgs;
	ParseArguments(argc, argv, &clArgs);

	//	create server
	JPServer *myServer = JPServer::CreateServer(clArgs.ipAddress, clArgs.port);

	//	start server
	if(myServer != NULL) {
		if(myServer->IsSocketBound()) {
			myServer->StartListening();
		}
	}

	//	server init failed
	else {
		cout << "Server could not be started!\n";
	}

	return 0;
}

//-----------------------------------------------------------------------------
//	void HelpMenu(void)
//
//	Displays help menu.
//-----------------------------------------------------------------------------
void HelpMenu(void)
{
	// name of program
	cout << endl << "NAME" << endl;
	cout << "\tJPServer.exe - runs a TCP/IP \"echo\" server" << endl << endl;

	// synopsis of program
	cout << "SYNOPSIS" << endl;
	cout << "\tJPServer.exe [/p:port] [/i:IP] [/?]" << endl << endl;

	// description and "how-to-use" section
	cout << "DESCRIPTION" << endl;
	cout << "\tRuns a TCP/IP \"EchoServer\" using the WinSock API." << endl;
	cout << "\tBy default, JPServer runs on 127.0.0.1:11865." << endl << endl;
	cout << "\t/?\t\tdisplay help menu" << endl;
	cout << "\t/p:port\t\tport number to listen on" << endl;
	cout << "\t/i:IP\t\tip address of interface to listen on" << endl;	
	ExitProcess(1);
}

//-----------------------------------------------------------------------------
//	void ParseArguments(int argc, char **argv, cl_struct args);
//
//	Parses command line arguments.
//
//	argc - number of arugments
//  argv - array of argument values
//	args - struct to store any specified values
//-----------------------------------------------------------------------------
void ParseArguments(int argc, char **argv, cl_struct *args)
{
	args->port = 0;
	args->customIP = false;

	for(int i = 1; i < argc; i++)
	{
		if(argv[i][0] == '/')
		{
			switch (tolower(argv[i][1]))
			{
				case 'p':					
					args->port = atoi(&argv[i][3]);
					break;
				case 'i':				
					args->customIP = true;
					if (strlen(argv[i]) > 3) {
						strcpy_s(args->ipAddress, &argv[i][3]);
					}
					break;
				default:
					HelpMenu();
					break;
			}
		}
	}

	//	if no port specified, use default port
	if(args->port == 0) {
		args->port = DEFAULT_PORT;
	}

	//	if no IP specified, use default IP
	if(!args->customIP) {
		strcpy_s(args->ipAddress, DEFAULT_IP);
	}
}