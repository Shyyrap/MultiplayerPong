#include"Game.h"
#include"Network/SharedHeaders.h" 
#include"Network/SocketUtil/SocketUtil.h"
int main(int argc, char** argv)
{
    TCPSocketPtr game_socket = SocketUtil::CreateTCPSocket(INET);
    Game game(game_socket);
    //Game game;
    bool success = game.Initialize();
    while(game.IsRunning())
    {
        game.RunLoop();
    }
    game.Shutdown();
    return 0;
}
