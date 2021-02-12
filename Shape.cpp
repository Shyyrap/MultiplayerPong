#include"Shape.h"
#include"Logic.h" 
#include"Actor.h"
#include"Position.h"
Shape::Shape(Actor* owner)
{
    mOwner = owner;
    mShapeRect = new SDL_Rect[0];
}
void Shape::NewPos(int32_t x, int32_t y)
{
    mShapeRect[0].x = x;
    mShapeRect[0].y = y;
}

