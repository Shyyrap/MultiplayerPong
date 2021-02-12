#include"../SocketUtil.h"

int main(int argc, char**  argv)
{
    char buffer[1024];
    int master_fd;
    TCPSocketPtr master = SocketUtil::CreateTCPSocket(INET);
    SocketAddress masterAddress(INADDR_ANY, 12345);
    master->Bind(masterAddress);
    master->Listen(SOMAXCONN);
    SocketAddress cliAddr;
    auto acceptSocket = master->Accept(cliAddr);
   // while(true)
    {
        if(acceptSocket != nullptr )
        {
            std::cout<<"Someone connected "<<std::endl;
            int receive = acceptSocket->Receive(buffer,1024);
            std::cout<<"Server receive "<<receive<<" bytes "<<std::endl; 
            for(int i=0; i<receive;i++)
            {
                std::cout<<buffer[i];
            }
            std::cout<<std::endl;
        }
        else
        {
        }
    }
    return 0;
}
