#pragma once
#include <winsock.h>
#include <thread>

namespace RS {

	class Client {
	public:
		unsigned int clientfd;
		char ip[64];
		Client(unsigned int fd, char* ip);
		template<typename T>
		int Recv(T* t) {
			return recv(clientfd, (char*)t, sizeof(T), 0);
		}

		template<typename T>
		int Send(T* t) {

			return send(clientfd,(const char*) t, sizeof(T), 0);
		}

	};
}
