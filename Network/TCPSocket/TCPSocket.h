#pragma once
#include"../SocketAddress/SocketAddress.h"
#include"../SharedHeaders.h"

class TCPSocket
{ 
    public:
        ~TCPSocket();
        int Bind(const SocketAddress& inBindAddress);
        int Connect(const SocketAddress& inAddress);
        int Listen(int Backlog);
        std::shared_ptr<TCPSocket> Accept( SocketAddress& inFromAddress); 
        int AcceptNewSocket(SocketAddress& inFromAddress);
        int Send(const void* inData, int inLen);
        int Receive(void* inBuffer,int inLen );
        int SetNumber(int num){mNumber = num;}
        int GetNumber(){return mNumber;}
    private:
        TCPSocket(SOCKET inSocket);
        friend class SocketAddress;
        int mSocket;
        friend class SocketUtil;
        int mNumber;
};
using TCPSocketPtr = std::shared_ptr<TCPSocket>;
