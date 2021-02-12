#include"Actor.h"
#include"Game.h"
#include"Enemy.h"
Enemy::Enemy(Game* game):Actor(game)
{
    mGame = game;
    InitShape();
    ReBuildPosition();
}
Game* Enemy::GetGame()
{
    return mGame;
}
void Enemy::ReBuildPosition()
{
    if(GetGame()->GetNumberSocket()== 1)
    {
        int32_t x = width_screen-40;
        GetPosition()->SetX(x);
        int32_t y = height_screen/2;
        GetPosition()->SetY(y);
    }
    else
    {
        if(GetGame()->GetNumberSocket()== 2)
        {
            int32_t x = 10;
            GetPosition()->SetX(x);
            int32_t y = height_screen/2;
            GetPosition()->SetY(y);
        }
    }
}
void Enemy::InitShape()
{
    mShape = new Shape(this); 
    int32_t x = width_screen-40;
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
void Enemy::NewPos()
{
    GetShape()->NewPos(GetPosition()->GetX(),GetPosition()->GetY());
}
void Enemy::Update(float deltaTime)
{
    NewPos();
}
void Enemy::Render()
{
    SDL_RenderFillRect(mGame->GetRenderer(),mShape->GetRect()); 
}
