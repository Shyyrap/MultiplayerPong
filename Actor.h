#pragma once
#include"Position.h"
enum State
{
    EACTIVE,
    EPAUSE,
    EDEAD
};
class Actor
{
    public:
        Actor(class Game* game);
        virtual void Update(float deltaTime);
        virtual void Render();
        Position* GetPosition(){return mPos;};
        State GetState(){return mState;}
        virtual void ReBuildPosition();
    private:
        State mState;
        Position* mPos;
        class Game* mGame;
};
