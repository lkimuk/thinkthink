#include <iostream>
#include "ThinkThinkServer.h"
#include "FileReceiver.h"


int main()
{
	/*FileReceiver file_server(3006);
	file_server.Start();*/

	ThinkThinkServer server(3007);
	server.Accept();
	server.Run();

    return 0;
}
