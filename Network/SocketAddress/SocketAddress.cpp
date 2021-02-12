#include"SocketAddress.h"
#include<string.h> 
#include<sys/types.h>

SocketAddress::SocketAddress(uint32_t inAddress, 
        uint16_t inPort)
{
    GetAsSockAddrIn()->sin_family = AF_INET;
    GetAsSockAddrIn()->sin_addr.s_addr = htonl(
            inAddress);
    GetAsSockAddrIn()->sin_port = htons(inPort);
}
SocketAddress::SocketAddress(const char* IP, uint16_t inPort)
{
    GetAsSockAddrIn()->sin_family = AF_INET;
    GetAsSockAddrIn()->sin_port = htons(inPort);
    inet_pton(AF_INET, IP, &GetAsSockAddrIn()->sin_addr);
}
SocketAddress::SocketAddress(const sockaddr& inSockAddr)
{
    memcpy(&mSockAddr,&inSockAddr, sizeof(sockaddr));
}

SocketAddress::SocketAddress()
{
    GetAsSockAddrIn()->sin_family = AF_INET;
    GetAsSockAddrIn()->sin_addr.s_addr = INADDR_ANY;
    GetAsSockAddrIn()->sin_port =0; 

}
