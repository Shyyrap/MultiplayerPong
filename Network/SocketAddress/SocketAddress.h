#pragma once
#include<sys/socket.h>
#include<netinet/in.h> 
#include<arpa/inet.h>
#include<iostream>
#include<memory>

class SocketAddress
{
    public:
        SocketAddress(uint32_t inAddress, 
                uint16_t inPort);
        SocketAddress(const sockaddr& inSockAddr);
        SocketAddress(const char* IP, uint16_t inPort);
        SocketAddress();
        size_t GetSize()const{return sizeof(mSockAddr);}
    private:
        friend class TCPSocket;
        sockaddr mSockAddr;
        sockaddr_in* GetAsSockAddrIn()
        {
            return reinterpret_cast<sockaddr_in*>(&mSockAddr);
        }
};
using SocketAddressPtr = std::shared_ptr<SocketAddress>;
