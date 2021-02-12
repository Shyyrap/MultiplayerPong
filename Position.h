#pragma once
#include"Network/Stream/InputMemoryStream.h"
#include"Network/Stream/OutputMemoryStream.h"

const uint32_t kMaxPacketSize = 1470;
class Position
{
    public:
        Position();
        Position(int32_t x,int32_t y);
        void Print();
        void PrintDirection();
        void WritePosition(OutputMemoryStream& inStream);
        void ReadPosition(InputMemoryStream& inStream);
        int32_t GetX();
        int32_t GetY();
        int32_t& GetYR(){return y;}
        int32_t& GetXR(){return x;}
        int32_t GetDirection(){return mDirection;}
        void SetDirection(int32_t direction){mDirection = direction;}
        void SetX(int32_t aX){x = aX;}
        void SetY(int32_t aY){y = aY;}
    private:
        int32_t x;
        int32_t y;
        int32_t mDirection;
};


