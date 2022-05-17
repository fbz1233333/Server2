#pragma once
#include <winsock.h>
#include <thread>

class Client
{
private:
	unsigned int clientSock;
	SOCKADDR_IN clientAddr;
	//void* serverArgs;
	std::thread* listenFunc;
	char ip[64];
	bool exist;
	unsigned int serverSock;
public:

	Client(unsigned int serverSock);
	~Client();

	void Destroy();
	bool IsExist();
	bool IsError();

	virtual void CreateListenFunc(std::thread* thread);
	template<typename T>
	int Recv(T* t);

	template<typename T>
	void Send(T* t);

	void StopListen();
};

template<typename T>
inline int Client::Recv(T * t)
{
	return recv(clientSock, (char*)t, sizeof(T), NULL);
}

template<typename T>
inline void Client::Send(T * t)
{
	send(clientSock, (const char*)t, sizeof(T), NULL);
}
