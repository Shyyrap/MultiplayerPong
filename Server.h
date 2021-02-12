#pragma once
#include"Network/SharedHeaders.h"
#include"Network/SocketUtil/SocketUtil.h"
#include"Position.h"
#include"Logic.h"
class Server
{
    public:
        Server();
        void CreateServer();
        void PollClients();
        TCPSocketPtr GetSocket(){return listenSocket;}
        void ReadPosition(TCPSocketPtr socket, Position* pos);
        void WritePosition(TCPSocketPtr socket, Position*pos);
        void HandlingPosition(Position* pos);
        void MoveBall();
        void ReadNumber(TCPSocketPtr socket);
        void WriteNumberOfSocket(TCPSocketPtr socket, int32_t number);
        void CheckLimits();
        void CheckReflection();
        void Restart();
    private:
       TCPSocketPtr listenSocket;
       std::vector<TCPSocketPtr> readableSockets;
       int32_t readyPlayers;
       std::vector<TCPSocketPtr> readBlockSockets;
       Position* mBallPos;
       Position* pos_1;
       Position* pos_2;
       int32_t mBallVel;
       int32_t mBallXDir; 
       int32_t mBallYDir;
       int32_t number;
       bool mIsFirstConnected;
       bool mIsSecondConnected;
       const int32_t UpLimit = 10;
       const int32_t DownLimit = height_screen;
       const int32_t LeftLimit = 0;
       const int32_t RightLimit = width_screen;
};
