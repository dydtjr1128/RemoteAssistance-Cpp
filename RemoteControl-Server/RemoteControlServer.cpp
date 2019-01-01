#include "RemoteControlServer.h"

RemoteControlServer::RemoteControlServer()
{
	WSADATA wsaData;
	int iResult;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		std::cout << "WSAStartup failed with error: " << iResult << "\n";
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		std::cout << "getaddrinfo failed with error: " << iResult << "\n";
		WSACleanup();
	}

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		std::cout << "socket failed with error: " << WSAGetLastError() << "\n";
		freeaddrinfo(result);
		WSACleanup();
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		std::cout << "bind failed with error: " << WSAGetLastError() << "\n";
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		std::cout << "listen failed with error: " << WSAGetLastError() << "\n";
		closesocket(ListenSocket);
		WSACleanup();
	}

	struct sockaddr_in clientInfo;
	int clientLen = sizeof(clientInfo);
	// Accept a client socket
	ClientSocket = accept(ListenSocket, (SOCKADDR *)&clientInfo, &clientLen);
	if (ClientSocket == INVALID_SOCKET) {
		std::cout << "accept failed with error: " << WSAGetLastError() << "\n";
		closesocket(ListenSocket);
		WSACleanup();
	}

	// No longer need server socket
	closesocket(ListenSocket);

	// Receive until the peer shuts down the connection
	do {

		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			recvbuf[iResult] = NULL;
			
			std::cout << "Bytes received: " << iResult << "  message : " << recvbuf << "\n";
			
			getsockname(ClientSocket, (SOCKADDR *)&clientInfo, &clientLen);// 서버의 소켓의 정보 가져온다.
			std::cout << "Sock Info: " << inet_ntoa(clientInfo.sin_addr) << " " << ntohs(clientInfo.sin_port) << "\n";//포트의경우 상대측이 사용하는 포트(접속한 포트가 아니라)
			getpeername(ClientSocket, (SOCKADDR *)&clientInfo, &clientLen);// peer, client, 상대측의 소켓 정보 가져온다.
			std::cout << "Peer Info: " << inet_ntoa(clientInfo.sin_addr) << " " << ntohs(clientInfo.sin_port) << "\n";//포트의경우 상대측이 사용하는 포트(접속한 포트가 아니라)

			// Echo the buffer back to the sender
			iSendResult = send(ClientSocket, recvbuf, iResult, 0);
			if (iSendResult == SOCKET_ERROR) {
				std::cout << "send failed with error: " << WSAGetLastError() << "\n";
				closesocket(ClientSocket);
				WSACleanup();
			}
			std::cout << "Bytes sent: " << iSendResult << "\n";
		}
		else if (iResult == 0)
			std::cout << "Connection closing...\n";
		else {
			std::cout << "recv failed with error: " << WSAGetLastError() << "\n";
			closesocket(ClientSocket);
			WSACleanup();
		}

	} while (iResult > 0);

	// shutdown the connection since we're done
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		std::cout << "shutdown failed with error: "<< WSAGetLastError() << "\n";
		closesocket(ClientSocket);
		WSACleanup();
	}

	// cleanup
	closesocket(ClientSocket);
	WSACleanup();

	//return 0;
}

RemoteControlServer::~RemoteControlServer()
{
}

int RemoteControlServer::sendMessage(SOCKET curSocket, char * message, int messageSize)
{
	return send(curSocket, message, messageSize, 0);
}

int RemoteControlServer::receiveMessage(SOCKET curSocket, char * buffer, int bufSize)
{
	return recv(curSocket, buffer, bufSize, 0);
}
