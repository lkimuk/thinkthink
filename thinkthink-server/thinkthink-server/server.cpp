#include <iostream>
#include "ThinkThinkServer.h"


int main()
{
    ThinkThinkServer server(3007);
    server.Accept();
    server.Run();

    return 0;
}
