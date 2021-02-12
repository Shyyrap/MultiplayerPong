#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"Logic.h" 
#include"Actor.h"
#include"Network/SharedHeaders.h" 
#include"Position.h"
class Game 
{
    public: 
        Game(TCPSocketPtr socket);
        Game();
        bool Initialize();
        void InitPlayer();
        void InitBall();
        void InitEnemy();
        bool IsRunning(){return isRunning;}
        void RunLoop();
        void Shutdown();
        void SetWalls();
        void ProcessInput();
        void UpdateGame();
        void GenerateOutput();
        const Uint8* GetKeyboardState(){return mKeyBoardState;}
        SDL_Rect* GetWalls(){return mWalls;}
        SDL_Renderer* GetRenderer(){return mRenderer;}
        bool IsConnectedToServer(){return mIsConnected;}
        int ConnectToServer();
        TCPSocketPtr GetSocket(){return mGameSocket;}
        Actor* GetEnemy(){return mEnemy;}
        Actor* GetBall(){return mBall;}
        void RequestNumber();
        void ReadNumber();
        int32_t GetNumberSocket(){return mNumberOfSocket;}
    private:
        SDL_Window* mWindow;
        TCPSocketPtr mGameSocket;
        Actor* mPlayer;
        Actor* mEnemy;
        Actor* mBall;
        bool mIsConnected;
        SDL_Surface* mSurface;
        SDL_Renderer* mRenderer;
        bool isInited;
        bool isRunning;
        Uint32 mTicksCount;
        SDL_Rect* mWalls;
        WALL_SIDES wall_sides;
        const Uint8* mKeyBoardState;
        int32_t mNumberOfSocket;
};
