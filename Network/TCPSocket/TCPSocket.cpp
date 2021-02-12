#include"TCPSocket.h"
#include<unistd.h>
#include<sys/types.h> 
TCPSocket::TCPSocket(SOCKET inSocket)
{
    mSocket = inSocket;
}
TCPSocket::~TCPSocket() {
    close(mSocket);
}
int TCPSocket::Bind(const SocketAddress& inBindAddress)
{
    //forcely attaching soket to the port
    int option = 1;
    int err = bind(mSocket,
            &inBindAddress.mSockAddr, 
            inBindAddress.GetSize()
            );
    if(setsockopt(mSocket,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT, (char*)&option,sizeof(option))<0)
    {
        perror("Setsockopt");
        exit(EXIT_FAILURE);
    }
    return err; 
}
int TCPSocket::Listen(int inBackLog)
{
    int err = listen(mSocket,inBackLog);
    if(err < 0 )
    {
        std::cout<<"Cannot created listen socket"<<std::endl;
    }
    return err;
}
int TCPSocket::Connect(const SocketAddress& inAddress)
{
    int err = connect(mSocket, 
            &inAddress.mSockAddr,
            inAddress.GetSize()); 
    if(err<0)
    {
        std::cout<<"Cannot create connect socket"<<std::endl; 
    }
    return err;
}
TCPSocketPtr TCPSocket::Accept(SocketAddress& inFromAddress)
{
    socklen_t length = inFromAddress.GetSize();
    int newSocket = accept(mSocket,
            &inFromAddress.mSockAddr, 
            &length);
    if(newSocket != -1)
    {
        return TCPSocketPtr(new TCPSocket(newSocket));
    }
    else
    {
        return nullptr;
    }
}
int TCPSocket::AcceptNewSocket(SocketAddress& inFromAddress)
{
    socklen_t length = inFromAddress.GetSize();
    int newSocket = accept(mSocket,
            &inFromAddress.mSockAddr, 
            &length);
    if(newSocket != -1)
    {
        return newSocket;
    }
    else
    {
        std::cout<<"Cannot accept new Socket"<<std::endl;
    }
    return newSocket;
}
int TCPSocket::Send(const void* inData, int inLen)
{
    int countSentBytes = send(mSocket, 
            static_cast<const char*>(inData),
            inLen, 0); 
    if(countSentBytes <0)
    {
        std::cout<<"Cannot send "<<std::endl;
        return -1;
    }
    return countSentBytes;
}
int TCPSocket::Receive(void* inData, int inLen)
{
    int countReceivedData = recv(mSocket, static_cast<char*>(inData),inLen,0);
    if(countReceivedData <0)
    {
        std::cout<<"Cannot read"<<std::endl;
        return -1;
    }
    return countReceivedData;
}
