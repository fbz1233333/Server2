
#include "Client.h"
#include "Param1.h"
#include "Log.h"
#include "Server.h"

int main() {
	Server *server = new Server(6666);

	while (1) {
		server->Run();
	}

	server->Destroy();

}