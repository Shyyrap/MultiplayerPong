#pragma once
#include"Game.h"
#include"Actor.h"
#include"Shape.h"
#include"Network/SocketUtil/SocketUtil.h"
class Enemy:public Actor 
{
    public:
        Enemy(class Game* game);
        void Update(float deltaTime)override; 
        int32_t GetX(){return mShape->GetX();}
        int32_t GetY(){return mShape->GetY();}
        int32_t GetW(){return mShape->GetW();}
        int32_t GetH(){return mShape->GetH();}
        Shape* GetShape(){return mShape;}
        void Render()override;
        void NewPos();
        void ReadPosition();
        Game* GetGame();
        void InitShape();
        void ReBuildPosition()override;
        //void WritePosition();
    private:
        bool mIsLose;
        Shape* mShape;
        Game* mGame;
};
