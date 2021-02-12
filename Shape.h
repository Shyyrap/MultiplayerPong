#pragma once
#include<SDL2/SDL.h>
#include"Actor.h"
class Shape
{
    public:
        Shape(Actor* owner);
        ~Shape(); int32_t GetX(){return x;}
        int32_t GetY(){return y;}
        int32_t GetW(){return w;}
        int32_t GetH(){return h;}
        SDL_Rect* GetRect(){return mShapeRect;}
        void NewPos(int32_t x, int32_t y);
        void SetW(int32_t aW){w = aW;}
        void SetH(int32_t aH){h = aH;}
        void SetY(int32_t aY){y = aY;}
        void SetX(int32_t aX){x = aX;}
    private:
        SDL_Rect* mShapeRect;
        Actor* mOwner;
        int32_t x;
        int32_t y;
        int32_t w; 
        int32_t h;
};
