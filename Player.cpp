#include"Player.h"
#include"Actor.h"
#include"Game.h"
Player::Player(Game* game):Actor(game)
{
    mGame = game;
    InitShape();
    ReBuildPosition();
}
Game* Player::GetGame()
{
    return mGame;
}
void Player::ReBuildPosition()
{
    if(GetGame()->GetNumberSocket()== 1)
    {
        int32_t x = 10;
        GetPosition()->SetX(x);
        int32_t y = height_screen/2;
        GetPosition()->SetY(y);
    }
    else
    {
        if(GetGame()->GetNumberSocket()== 2)
        {
            int32_t x = width_screen-40;
            GetPosition()->SetX(x);
            int32_t y = height_screen/2;
            GetPosition()->SetY(y);
        }
    }
}
void Player::InitShape()
{
    mShape = new Shape(this); 
    int32_t x = 10;
    mShape->SetX(x);
    int32_t y = height_screen/2;
    mShape->SetY(y);
    int32_t w = thickness*3;
    mShape->SetW(w);
    int32_t h = thickness*5;
    mShape->SetW(h);
    SDL_Rect* shape = mShape->GetRect();
    shape[0].x = x;
    shape[0].y = y;
    shape[0].w = w;
    shape[0].h = h;
}
void Player::NewPos()
{
    GetShape()->NewPos(GetPosition()->GetX(),GetPosition()->GetY());
}
void Player::ReadBallPosition()
{
    char* temporaryBuffer = 
        static_cast<char*>(std::malloc(kMaxPacketSize));
    size_t receivedByteCount = 
        GetGame()->GetSocket()->Receive(temporaryBuffer,
                static_cast<int32_t>(receivedByteCount));
    if(receivedByteCount>0)
    {
        InputMemoryStream stream(temporaryBuffer,
                static_cast<int32_t>(receivedByteCount));
        //GetPosition()->ReadPosition(stream);
        GetGame()->GetBall()->GetPosition()->ReadPosition(stream);
    }
    else
    {
        std::free(temporaryBuffer);
    }
}
void Player::Update(float deltaTime)
{
    if(GetGame()->GetNumberSocket() == 1){
    Console();
    }
    else
    {
        Console1();
    }
    WritePosition();
    ReadPosition();
    ReadEnemyPosition();
    ReadBallPosition();
    NewPos();
}
void Player::Render()
{
    SDL_RenderFillRect(mGame->GetRenderer(),mShape->GetRect()); 
}
void Player::Move(int32_t moveCommand)
{
    switch(moveCommand)
    {
        case 0:
            GetPosition()->SetDirection(0);
            break;
        case 1:
            GetPosition()->SetDirection(1);
            break;
        case 2:
            GetPosition()->SetDirection(2);
            break;
        case 3:
            GetPosition()->SetDirection(3);
            break;
        case 5:
            GetPosition()->SetDirection(5);
            break;
    };
}
void Player::Console1()
{
    const Uint8* playerKeyBoard;
    int32_t moveNumber;
    playerKeyBoard = mGame->GetKeyboardState();
    if(playerKeyBoard[SDL_SCANCODE_UP])
    {
        Move(0);
    }
    else
    {
        if(playerKeyBoard[SDL_SCANCODE_DOWN])
        {
            Move(1);
        }
        else
        {
            if(playerKeyBoard[SDL_SCANCODE_LEFT])
            {
                Move(2);
            }
            else
            {
                if(playerKeyBoard[SDL_SCANCODE_RIGHT])
                {
                    Move(3);
                }
                else
                {
                    Move(5);
                }
            }
        }
    }
}
void Player::Console()
{
    const Uint8* playerKeyBoard;
    int32_t moveNumber;
    playerKeyBoard = mGame->GetKeyboardState();
    if(playerKeyBoard[SDL_SCANCODE_W])
    {
        Move(0);
    }
    else
    {
        if(playerKeyBoard[SDL_SCANCODE_S])
        {
            Move(1);
        }
        else
        {
            if(playerKeyBoard[SDL_SCANCODE_D])
            {
                Move(2);
            }
            else
            {
                if(playerKeyBoard[SDL_SCANCODE_A])
                {
                    Move(3);
                }
                else
                {
                    Move(5);
                }
            }
        }
    }
}
void Player::WritePosition()
{
    OutputMemoryStream stream;
    GetPosition()->WritePosition(stream);
    GetGame()->GetSocket()->Send(stream.GetBufferPtr(),stream.GetLength()); 
}
void Player::ReadPosition()
{
    char* temporaryBuffer = 
        static_cast<char*>(std::malloc(kMaxPacketSize));
    size_t receivedByteCount = 
        GetGame()->GetSocket()->Receive(temporaryBuffer,
                static_cast<int32_t>(receivedByteCount));
    if(receivedByteCount>0)
    {
        InputMemoryStream stream(temporaryBuffer,
                static_cast<int32_t>(receivedByteCount));
        GetPosition()->ReadPosition(stream);
        //GetGame()->GetEnemy()->GetPosition()->ReadPosition(stream);
    }
    else
    {
        std::free(temporaryBuffer);
    }
}
void Player::ReadEnemyPosition()
{
    char* temporaryBuffer = 
        static_cast<char*>(std::malloc(kMaxPacketSize));
    size_t receivedByteCount = 
        GetGame()->GetSocket()->Receive(temporaryBuffer,
                static_cast<int32_t>(receivedByteCount));
    if(receivedByteCount>0)
    {
        InputMemoryStream stream(temporaryBuffer,
                static_cast<int32_t>(receivedByteCount));
        GetGame()->GetEnemy()->GetPosition()->ReadPosition(stream);
    }
    else
    {
        std::free(temporaryBuffer);
    }
}
