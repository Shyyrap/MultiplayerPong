#pragma once
#include"Actor.h"
#include"Game.h"
#include"Shape.h"
#include"Network/SocketUtil/SocketUtil.h"
class Ball:public Actor 
{
    public:
        Ball(class Game* game);
        void Update(float deltaTime)override; 
        int32_t GetX(){return mShape->GetX();}
        int32_t GetY(){return mShape->GetY();}
        int32_t GetW(){return mShape->GetW();}
        int32_t GetH(){return mShape->GetH();}
        Shape* GetShape(){return mShape;}
        void Render()override;
        void NewPos();
        Game* GetGame();
        void InitShape();
        void ReBuildPosition()override;
    private:
        Shape* mShape;
        Game* mGame;
};
