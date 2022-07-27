#pragma once
#include <iostream>
#include <winsock.h>
#include <vector>
#include <thread>
#include <functional>

#pragma comment(lib, "ws2_32.lib")

#include "Client.h"
#include <map>

using namespace RS;

class Server
{
public:
	bool shouldClose = false;

	unsigned int port;
	SOCKET serverSock;
	bool svShouldClose();

	std::map<Client*, Client*> clientMap;
public:
	void Init();
	void Destroy();
	bool Run();

	static DWORD WINAPI acceptCallback(LPVOID lpParam);

	Server(unsigned int port);
	~Server();

};



