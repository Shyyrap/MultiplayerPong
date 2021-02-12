#include"OutputMemoryStream.h"
OutputMemoryStream::OutputMemoryStream()
{
    mBuffer = nullptr;
    mHead = 0;
    mCapacity = 0;
    ReallocBuffer(32);
}
void OutputMemoryStream::ReallocBuffer(uint32_t inNewLength)
{
    mBuffer = static_cast<char*>(std::realloc(mBuffer,inNewLength));
    //обработать ошибку вызова relloc 
    mCapacity = inNewLength;
}
void OutputMemoryStream::Write(const void* inData,
        size_t inByteCount)
{
    uint32_t resultHead = mHead+static_cast<uint32_t>(inByteCount);
    if(resultHead>mCapacity)
    {
        ReallocBuffer(std::max(mCapacity*2, resultHead));
    }
    // скопировать в начало свободной обласит в буфере
    std::memcpy(mBuffer+mHead,inData,inByteCount);
    //подготовить указатель на начало свободной области 
    mHead = resultHead;
}
