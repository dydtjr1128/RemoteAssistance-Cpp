#ifndef REMOTE_CONTROL_CLIENT
#define REMOTE_CONTROL_CLIENT

#include <WinSock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <iostream>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

// size of our buffer
#define DEFAULT_BUFLEN 512
// port to connect sockets through 
#define DEFAULT_PORT "10004"

class RemoteControlClient {
public:
	RemoteControlClient();
	RemoteControlClient(const char* serverIP);
	~RemoteControlClient();
	//for error checking function calls in Winsock library
	int iResult;

	//socket for client to connect to server
	SOCKET ConnectSocket;
};

#endif