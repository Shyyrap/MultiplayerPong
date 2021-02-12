#include"Ball.h"
#include"Actor.h"
#include"Game.h"
Ball::Ball(Game* game):Actor(game)
{
    mGame = game;
    InitShape();
    ReBuildPosition();
}
void Ball::ReBuildPosition()
{
   int32_t x = width_screen/2;
   GetPosition()->SetX(x);
   int32_t y = height_screen/2;
   GetPosition()->SetY(y);
}
void Ball::InitShape()
{
    mShape = new Shape(this); 
    int32_t x = width_screen/2;
    mShape->SetX(x);
    int32_t y = height_screen/2;
    mShape->SetY(y);
    int32_t w = thickness*2;
    mShape->SetW(w);
    int32_t h = thickness*2;
    SDL_Rect* shape = mShape->GetRect();
    shape[0].x = x;
    shape[0].y = y;
    shape[0].w = w;
    shape[0].h = h;
}
Game* Ball::GetGame()
{
    return mGame;
}
void Ball::NewPos()
{
    GetShape()->NewPos(GetPosition()->GetX(),GetPosition()->GetY());
}
void Ball::Update(float deltaTime)
{
    NewPos();
}
void Ball::Render()
{
    SDL_RenderFillRect(mGame->GetRenderer(),mShape->GetRect()); 
}
