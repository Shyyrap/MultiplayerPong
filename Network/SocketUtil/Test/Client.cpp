#include"../SocketUtil.h"
#include<stdio.h>
#include<cstring>

int main(int argc, char** argv)
{
    TCPSocketPtr slave_socket = SocketUtil::CreateTCPSocket(INET);
    SocketAddress servAddr(INADDR_ANY, 12345);
    std::string buffer;
    slave_socket->Connect(servAddr);
    std::cout<<"Client connected to server "<<std::endl;
    std::cout<<"Say something to server"<<std::endl;
    std::cin>>buffer;
    int sent = slave_socket->Send(buffer.c_str(),buffer.size());
    std::cout<<"Client sent "<<sent<<" data"<<std::endl;
    return 0;
}

