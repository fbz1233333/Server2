
#include "Server.h"
#include "Client.h"
#include "Param1.h"
#include "Log.h"

int main() {
	Server<Param1, Param1> *server = new Server<Param1 ,Param1>(6666);

	std::function<void(Param1*,Param1*)> servlet= [](Param1* p, Param1 * p2) {
		p2->no = 200;
		strcpy(p2->str, "Hello2");
	};
	//server->RunWithServlet(servlet);

	//
	std::function<void(Client*)> clientHandle = [](Client* client) {

		client->CreateListenFunc(new std::thread(
			[&, client]() {
			while (client->IsExist()) {
				Param1 *param = new Param1();
				int recvLen = client->Recv<Param1>(param);
				if (recvLen == -1) {
					LOGI("Recv len is -1, Link disconnect");
					client->Destroy();
					break;
				}
				if (recvLen == 0) {
					LOGI("Recv Len is Zero");
					continue;
				}

				Param1 *param2 = new Param1();
				client->Send<Param1>(param2);
			}
		}
		
		
		));

	};
	server->RunWithClientHandle(clientHandle);

	server->Destroy();

}