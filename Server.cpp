#include"Server.h"
#include"Network/SocketUtil/SocketUtil.h"
#include"Logic.h" 
Server::Server() 
{   
    CreateServer();
    readyPlayers = 0; 
    mBallPos = new Position(); 
    mBallVel = 2;
    mBallXDir = 1;
    mBallYDir = 1;
    mIsFirstConnected = false;
    mIsSecondConnected = false;
    pos_1 = new Position(10,height_screen/2);
    pos_2 = new Position(width_screen-40,height_screen/2);
}
void Server::Restart()
{
    pos_1->SetX(10);
    pos_1->SetY(height_screen/2);
    pos_2->SetX(width_screen-40);
    pos_2->SetY(height_screen/2);
    mBallPos->SetY(height_screen/2);
    mBallPos->SetX(width_screen/2);
    mBallXDir = 1;
    mBallYDir = 1;
}
void Server::CreateServer()
{
    listenSocket = SocketUtil::CreateTCPSocket(INET);
    SocketAddress receivingAddress(INADDR_ANY, 12345);
    if(listenSocket->Bind(receivingAddress)!=NO_ERROR) 
    {
        std::cout<<"Created server in port = 12345"<<std::endl;
    }
    listenSocket->Listen(SOMAXCONN);
    readBlockSockets.push_back(listenSocket);
    vector<TCPSocketPtr>readableSockets;
}
void Server::ReadNumber(TCPSocketPtr socket)
{
    char* temporaryBuffer = 
        static_cast<char*>(std::malloc(kMaxPacketSize));
    size_t receivedByteCount = 
        socket->Receive(temporaryBuffer,
                static_cast<int32_t>(receivedByteCount));
    if(receivedByteCount>0)
    {
        InputMemoryStream stream(temporaryBuffer,
                static_cast<int32_t>(receivedByteCount));
        stream.Read(number);
    }
    else
    {
        std::free(temporaryBuffer);
    }
}

void Server::WriteNumberOfSocket(TCPSocketPtr socket, int32_t number)
{
    OutputMemoryStream stream;
    stream.Write(number);
    auto Nbytes = socket->Send(stream.GetBufferPtr(), stream.GetLength());
}
void Server::PollClients()
{
    while(true)
    {
        if(SocketUtil::Select(&readBlockSockets,
                    &readableSockets,
                    nullptr,nullptr,nullptr,nullptr))
        {
            for( const TCPSocketPtr& socket:readableSockets)
            {
                if(socket == listenSocket)
                {
                    SocketAddress newClientAddress;
                    auto newSocket = listenSocket->Accept(newClientAddress);
                    readBlockSockets.push_back(newSocket);
                    readyPlayers++;
                    newSocket->SetNumber(readyPlayers); 
                }//if(socket == listenSocket)
                else
                {
                    if(socket->GetNumber() == 1)
                    {
                        if(mIsFirstConnected == false)
                        {
                            ReadNumber(socket);
                            WriteNumberOfSocket(socket,socket->GetNumber());
                            mIsFirstConnected = true;
                            ReadPosition(socket, pos_1);
                            HandlingPosition(pos_1);
                            MoveBall();
                            WritePosition(socket,pos_1);
                            WritePosition(socket,pos_2);
                            WritePosition(socket, mBallPos);
                        }
                        else
                        {
                            ReadPosition(socket, pos_1);
                            HandlingPosition(pos_1);
                            MoveBall();
                            WritePosition(socket,pos_1);
                            WritePosition(socket,pos_2);
                            WritePosition(socket, mBallPos);
                        }
                    }
                    else
                    {
                        if(socket->GetNumber() == 2)
                        {
                            if(mIsSecondConnected == false)
                            {
                                ReadNumber(socket);
                                WriteNumberOfSocket(socket,socket->GetNumber());
                                mIsSecondConnected = true;
                                ReadPosition(socket, pos_2);
                                HandlingPosition(pos_2);
                                MoveBall();
                                WritePosition(socket,pos_2);
                                WritePosition(socket,pos_1);
                                WritePosition(socket, mBallPos);
                            }
                            else
                            {
                                ReadPosition(socket, pos_2);
                                HandlingPosition(pos_2);
                                MoveBall();
                                WritePosition(socket,pos_2);
                                WritePosition(socket,pos_1);
                                WritePosition(socket, mBallPos);
                            }
                        }
                    }
                }
            }//for(socket: readableSockets)
        }//if(Select(...)
    }//while(true)
}//void PollClients()
void Server::CheckLimits()
{
    if(mBallPos->GetY() == UpLimit)
    {
        mBallYDir = 1;
    }
    else
    {
        if(mBallPos->GetY() == DownLimit)
        {
            mBallYDir = -1;
        }
    }
    if(mBallPos->GetX() > RightLimit || mBallPos->GetX() < LeftLimit)
    {
        Restart();
    }
}
void Server::CheckReflection()
{
    if(mBallPos->GetX()+thickness == pos_2->GetX())
    {
        if(mBallPos->GetY()+thickness > pos_2->GetY())
        {
           if(mBallPos->GetY()+thickness < pos_2->GetY()+50)
            {
                mBallXDir = -1;
            }
        }
        else
        {
            

        }
    }
    else
    {
        if(mBallPos->GetX() == pos_1->GetX()+2*thickness)
        {
            if(mBallPos->GetY() > pos_1->GetY())
            {
               if(mBallPos->GetY() < pos_1->GetY()+50)
                {
                    mBallXDir = 1;
                }
            }
            else
            {

            }
         }
    }
}
void Server::MoveBall()
{
    CheckLimits();
    CheckReflection();
    mBallPos->GetXR() += mBallVel*mBallXDir; 
    mBallPos->GetYR() += mBallVel*mBallYDir; 
}
void Server::HandlingPosition(Position* pos)
{
    int32_t direction = pos->GetDirection();
    int32_t currX= pos->GetX();
    int32_t currY = pos->GetY();
    switch(direction)
    {
        case 0:
            currY-=10;
            pos->SetY(currY);
            break;
        case 1:
            currY+=10;
            pos->SetY(currY);
            break;
        case 2: 
            currX += 10;
            pos->SetX(currX);
            break;
        case 3:
            currX -= 10;
            pos->SetX(currX);
            break;
        case 5:
            //currX += 10;
            //currY += 1;
            pos->SetX(currX);
            pos->SetY(currY);
            break;
    };
}
void Server::WritePosition(TCPSocketPtr socket, Position* pos)
{
    OutputMemoryStream stream;
    pos->WritePosition(stream);
    auto Nbytes = socket->Send(stream.GetBufferPtr(), stream.GetLength());
}
void Server::ReadPosition(TCPSocketPtr socket, Position* pos)
{
    char* temporaryBuffer = 
        static_cast<char*>(std::malloc(kMaxPacketSize));
    size_t receivedByteCount = 
        socket->Receive(temporaryBuffer,
                static_cast<int32_t>(receivedByteCount));
    if(receivedByteCount>0)
    {
        InputMemoryStream stream(temporaryBuffer,
                static_cast<int32_t>(receivedByteCount));
        pos->ReadPosition(stream);
    }
    else
    {
        std::free(temporaryBuffer);
    }
}
