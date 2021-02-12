#include"Actor.h"
#include"Logic.h"
#include"Game.h"
Actor::Actor(Game* game)
{
    mState = EACTIVE;
    mPos = new Position;
}
void Actor::Update(float deltaTime)
{
}
void Actor::Render()
{
}
void Actor::ReBuildPosition()
{
}

