#pragma once
#include <iostream>
#include <winsock.h>
#include <vector>
#include <thread>
#include <functional>

#pragma comment(lib, "ws2_32.lib")

#include "Client.h"
#include "Param1.h"
#include "Log.h"

template<typename T, typename S>
class Server
{
private:
	unsigned int port;
	unsigned int serverSock;
	std::vector<Client*> clients;
	
public:
	void Init();
	// everytime we find a new Client what should you do
	void RunWithClientHandle(std::function<void(Client*)> clientHandle) {
		while (Client* client = new Client(this->serverSock)) {
			LOGI("Server Get a new Client");
			clientHandle(client);
		}
	};
	void RunWithServlet(std::function<void(T* t , S* s )> servlet) {
	
		while (Client *client = new Client(this->serverSock)) {
			LOGI("Server Get a new Client");
			clients.push_back(client);
			client->CreateListenFunc(new std::thread(

				// 原来是& 没写
				[&, client]() {
				while (client->IsExist()) {
					T *param = new T();
					int recvLen = client->Recv<T>(param);
					if (recvLen == -1) {
						client->Destroy();
						break;
					}
					if (recvLen == 0) {
						LOGI("Recv Len is Zero");
					}

					S *param2 = new S();
					servlet(param, param2);
					client->Send<S>(param2);
				}
			}
			));
		}
	};
	void Destroy();
	Server(unsigned int port);
	~Server();

};



template<typename T, typename S>
inline Server<T, S>::Server(unsigned int port):port(port)
{
	Init();
}

template<typename T, typename S>
inline void Server<T, S>::Init()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		return;
	}
	serverSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	serverAddr.sin_port = htons(port);
	if (bind(serverSock, (SOCKADDR*)&serverAddr, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		return;
	}

	printf("Bind %s:%d Successfully \n", "127.0.0.1", port);
	if (listen(serverSock, SOMAXCONN) < 0) {
		Log::Info("trying to Listen and then failed");
		return;
	}
}



template<typename T, typename S>
inline void Server<T, S>::Destroy()
{
	closesocket(serverSock);
	for (Client* client : clients) {
		client->Destroy();
	}
	WSACleanup();
}

template<typename T, typename S>
inline Server<T, S>::~Server()
{
	Destroy();
}
