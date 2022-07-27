#include "Server.h"
#include "Log.h"
#include "Client.h"
#include "Param1.h"

using namespace RS;

void Server::Destroy()
{
	closesocket(serverSock);
	//for (Client* client : clients) {
	//	client->Destroy();
	//}
	WSACleanup();
}

Server::~Server()
{
	Destroy();
}

// Add Client
bool Server::Run()
{
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	SOCKET sclient = accept(serverSock, (sockaddr*)&remoteAddr, &nAddrlen);
	LOGI("Accept a new client");
	if (sclient == INVALID_SOCKET) {
		LOGI("accept error !");
	}
	char* ip = inet_ntoa(remoteAddr.sin_addr);
	LOGI("Accept from %s", ip);

	Client* client = new Client(sclient, ip);
	CreateThread(NULL, 0, acceptCallback, client, 0, NULL);
	return true;

}

DWORD Server::acceptCallback(LPVOID lpParam)
{
	Client* client=(Client*)lpParam;
	
	
	LOGI("Hello New Clinet %s ", client->ip);

	Param1 p1;
	while (1) {
		int len = client->Recv<Param1>(&p1);

		if (len == 0) {
			LOGI("client ip [%s] recv len is 0", client->ip);
			break;
		}
		else if (len == -1) {
			LOGI("client ip [%s] disconnected", client->ip);

			break;
		}
		else {
			LOGI("client ip [%s] receive message ", client->ip);

			LOGI("recv %d", p1.no);
			Param1 p2 = { 10, "helo" };
			client->Send<Param1>(&p2);


		}

	}
	return 0;
}

Server::Server(unsigned int port) :port(port)
{
	Init();
}

bool Server::svShouldClose()
{
	return shouldClose;
}


void Server::Init()
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

	LOGI("Bind %s:%d Successfully \n", "127.0.0.1", port);
	if (listen(serverSock, SOMAXCONN) < 0) {
		//Log::Info("trying to Listen and then failed");
		LOGI("trying to listen and then failed");
		return;
	}
}




//void Server::Run()
//{
//	Client *client;
//	while (client = new Client(this)) {
//		Log::Info("Server Get a new Client");
//
//		client->CreateListenFunc(new std::thread(
//			[client]() {
//			while (client->IsExist()) {
//				Param1 *param = new Param1();
//				int recvLen = client->Recv<Param1>(param);
//				if (recvLen == -1) {
//					client->Destroy();
//					break;
//				}
//				if (recvLen == 0) {
//					Log::Info("Recv Len is 0");
//					//break;
//				}
//
//				LOGI("len %d ,recv %s \n", recvLen, param->str);
//				Param1 *param2 = new Param1();
//				param2->no = 20;
//
//
//				client->Send<Param1>(param2);
//			}
//		}
//		));
//
//		clients.push_back(client);
//	}
//}
//
//void Server::Destroy()
//{
//	closesocket(serverSock);
//	for (Client* client : clients) {
//		client->Destroy();
//	}
//	WSACleanup();
//}
