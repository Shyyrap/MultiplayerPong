#include"Game.h"
#include"Network/SocketUtil/SocketUtil.h"
#include"Network/SharedHeaders.h"
#include"Shape.h"
#include"Player.h"
#include"Enemy.h"
#include"Ball.h"

int Game::ConnectToServer()
{
    SocketAddress servAddr(INADDR_ANY, 12345);
    int connecting = mGameSocket->Connect(servAddr); 
    if(connecting < 0) 
    {
        std::cout<<"Cannot connect to server"<<std::endl;
        mIsConnected = false;
        isRunning = false;
    }
    else
    {
        mIsConnected = true;
        isRunning = true;
        std::cout<<"Connect to server"<<std::endl;
    }
    return connecting;
}
void Game::RequestNumber()
{
    mNumberOfSocket = 0;
    OutputMemoryStream stream;
    stream.Write(mNumberOfSocket);
    GetSocket()->Send(stream.GetBufferPtr(), stream.GetLength());
}
void Game::ReadNumber()
{
    char* temporaryBuffer = 
        static_cast<char*>(std::malloc(kMaxPacketSize));
    size_t receivedByteCount = 
        GetSocket()->Receive(temporaryBuffer,
                static_cast<int32_t>(receivedByteCount));
    if(receivedByteCount>0)
    {
        InputMemoryStream stream(temporaryBuffer,
                static_cast<int32_t>(receivedByteCount));
        stream.Read(mNumberOfSocket);
    }
    else
    {
        std::free(temporaryBuffer);
    }
    std::cout<<"Player number = "<<GetNumberSocket()<<std::endl;
}
void Game::InitPlayer()
{
    mPlayer = new Player(this);
}
void Game::InitEnemy()
{
    mEnemy = new Enemy(this);
}
void Game::InitBall()
{
    mBall = new Ball(this);
}
Game::Game()
{
    mWalls = new SDL_Rect[4];
    SetWalls();
    mWindow = nullptr;
    mTicksCount = 0;
    mRenderer = nullptr;
    mKeyBoardState = nullptr;
    isRunning = true;
    InitPlayer();
}
Game::Game(TCPSocketPtr socket)
{
    mWindow = nullptr;
    mTicksCount = 0;
    mRenderer = nullptr;
    mKeyBoardState = nullptr;
    mWalls = new SDL_Rect[4];
    SetWalls();
    mGameSocket = socket;
    ConnectToServer();
    RequestNumber();
    ReadNumber();
    InitPlayer();
    InitEnemy();
    InitBall();
}
void Game::SetWalls()
{
    mSurface = IMG_Load("Some.png");
    mWalls[NORTH_WALL].y = 0; 
    mWalls[NORTH_WALL].x = 0;
    mWalls[NORTH_WALL].h = thickness*5;
    mWalls[NORTH_WALL].w = width_screen;

    mWalls[WEST_WALL].y = 0; 
    mWalls[WEST_WALL].x = 0; 
    mWalls[WEST_WALL].h = height_screen;
    mWalls[WEST_WALL].w = thickness*5; 
    mWalls[SOUTH_WALL].y = height_screen-thickness*5;
    mWalls[SOUTH_WALL].x = 0;
    mWalls[SOUTH_WALL].h = thickness*5; mWalls[SOUTH_WALL].w = width_screen;

    mWalls[EAST_WALL].y = 0;
    mWalls[EAST_WALL].x = width_screen - 5*thickness;
    mWalls[EAST_WALL].h = height_screen;
    mWalls[EAST_WALL].w = thickness*5;
}
bool Game::Initialize() 
{
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if(sdlResult<0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        isInited = false;
        return isInited;
    }
    else
    {
        mWindow = SDL_CreateWindow(
                "First Game", 
                100,//top xleft
                100,// top y-coordinate
                width_screen,//width
                height_screen, //height
                0//flags to 
                );
        if(!mWindow)
        {
            SDL_Log("Failed to create window %s", SDL_GetError());
            isInited = false;
            return isInited;
        }

    }
    //here renderer code
    mRenderer = SDL_CreateRenderer(
            mWindow,
            -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(mRenderer == nullptr)
    {
        SDL_Log("Coudln't create Renderer %s", SDL_GetError());
        isInited = false;
    }
    return  isInited;
}
void Game::Shutdown()
{
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    SDL_Quit();
}
void Game::ProcessInput()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        mKeyBoardState = SDL_GetKeyboardState(NULL);
        switch(event.type)
        {
            case SDL_QUIT:
                isRunning =false;
                break;
        };
    }
}

void Game::UpdateGame()
{
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount+16));
    float deltaTime = (SDL_GetTicks() - mTicksCount)/1000.0f;
    if(deltaTime >0.05f)
    {
        deltaTime = 0.05f;
    }
    mPlayer->Update(deltaTime);
    mEnemy->Update(deltaTime);
    mBall->Update(deltaTime);
}
void Game::RunLoop()
{
    ProcessInput();
    UpdateGame();
    GenerateOutput();
}
void Game::GenerateOutput()
{
    //Set background
    SDL_SetRenderDrawColor(mRenderer,
            0,
            0,
            255,
            255);
    SDL_RenderClear(mRenderer);
    //Render wall
    for(int i =0; i<4; i++) 
    {
        SDL_SetRenderDrawColor(mRenderer, 0,255,0,255);
        SDL_RenderFillRect(mRenderer, GetWalls()+i);
    }
    SDL_SetRenderDrawColor(mRenderer, 255,0,
            0,255);
    mPlayer->Render();
    SDL_SetRenderDrawColor(mRenderer, 0,0,
            0,255);
    mEnemy->Render();
    SDL_SetRenderDrawColor(mRenderer, 255,255,
            255,255);
    mBall->Render();
    SDL_RenderPresent(mRenderer);
}

