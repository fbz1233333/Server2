//#include "Server.h"
//#include "Log.h"
//#include "Client.h"
//#include "Param1.h"
//
//#include <thread>
//
//namespace ServerData {
//
//};
//
//using namespace ServerData;
//Server::~Server()
//{
//}
//Server::Server(unsigned int port) :
//	port(port)
//{
//
//	Init();
//}
//
//void Server::Init()
//{
//	WSADATA wsaData;
//	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
//		return;
//	}
//	serverSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
//	SOCKADDR_IN serverAddr;
//	memset(&serverAddr, 0, sizeof(serverAddr));
//	serverAddr.sin_family = AF_INET;
//	serverAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
//	serverAddr.sin_port = htons(port);
//	if (bind(serverSock, (SOCKADDR*)&serverAddr, sizeof(SOCKADDR)) == SOCKET_ERROR)
//	{
//		return;
//	}
//
//	printf("Bind %s:%d Successfully \n", "127.0.0.1", port);
//	if (listen(serverSock, SOMAXCONN) < 0) {
//		Log::Info("Listnen failed");
//		return;
//	}
//
//}
//
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
