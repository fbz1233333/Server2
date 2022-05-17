#include "Client.h"
#include "Log.h"
#include <thread>
#include "Param1.h"
#include "Server.h"

Client::Client(unsigned int serverSock):serverSock(serverSock),exist(true)
{
	// Length
	int len = sizeof(SOCKADDR_IN);
	clientSock = accept(serverSock, (SOCKADDR*)&clientAddr, &len);
	strcpy(ip, inet_ntoa(clientAddr.sin_addr));

}

void Client::Destroy()
{
	LOGI("Client Destroy");
	this->exist = false;
	closesocket(clientSock);
}


bool Client::IsExist()
{
	return this->exist;
}

Client::~Client()
{
	Destroy();
}

bool Client::IsError()
{
	return clientSock == SOCKET_ERROR;
}

void Client::CreateListenFunc(std::thread* thread)
{
	
	this->listenFunc = thread;
	this->listenFunc->join();

}

void Client::StopListen()
{
	Log::Info("Current Client Stop Listening ");
	this->exist = false;
}
