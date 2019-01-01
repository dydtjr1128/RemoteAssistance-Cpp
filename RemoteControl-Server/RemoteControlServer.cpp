#include "RemoteControlServer.h"

RemoteControlServer::RemoteControlServer()
{

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
