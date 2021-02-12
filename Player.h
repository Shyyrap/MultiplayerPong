#pragma once
#include"Game.h"
#include"Actor.h"
#include"Shape.h"
#include"Network/SocketUtil/SocketUtil.h"
class Player:public Actor 
{
    public:
        Player(class Game* game);
        void Update(float deltaTime)override; 
        int32_t GetX(){return mShape->GetX();}
        int32_t GetY(){return mShape->GetY();}
        int32_t GetW(){return mShape->GetW();}
        int32_t GetH(){return mShape->GetH();}
        Shape* GetShape(){return mShape;}
        void Render()override;
        void Console();
        void Console1();
        void Move(int32_t moveCommand);
        void NewPos();
        void ReadPosition();
        void ReadBallPosition();
        void WritePosition();
        Game* GetGame();
        void ReadEnemyPosition();
        void InitShape();
        void ReBuildPosition()override;
    private:
        bool mIsLose;
        Shape* mShape;
        Game* mGame;
};
