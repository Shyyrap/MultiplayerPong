#include"Position.h"
#include<iostream>
#include"Logic.h"
Position::Position()
{
    x = width_screen/2;
    y = height_screen/2;
    mDirection = 5;
}
Position::Position(int32_t x, int32_t y)
{
    this->x = x;
    this->y = y;
    mDirection = 5;
}
void Position::PrintDirection()
{
    std::cout<<"Direction is = "<<mDirection<<std::endl;
}

void Position::Print()
{
    std::cout<<"X = "<<x<<std::endl;
    std::cout<<"Y = "<<y<<std::endl;
}

void Position::ReadPosition(InputMemoryStream& inStream)
{
    inStream.Read(x);
    inStream.Read(y);
    inStream.Read(mDirection);
}
void Position::WritePosition(OutputMemoryStream& inStream)
{
    inStream.Write(x);
    inStream.Write(y);
    inStream.Write(mDirection);
}

int32_t Position::GetX()
{
    return x;
}
int32_t Position::GetY()
{
    return y;
}

