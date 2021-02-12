#include"Player.h"
#include"Shape.h"
#include"Server.h"

int main(int argc, char** argv)
{
    Server* mServer = new Server;
    mServer->PollClients();
    return 0;
}

