#pragma once
#include"../SharedHeaders.h"
class OutputMemoryStream
{
    public:
        OutputMemoryStream();
        ~OutputMemoryStream(){std::free(mBuffer);}
        const char* GetBufferPtr()const{return mBuffer;}
        uint32_t GetLength()const{return mHead;}
        void Write(const void* inData,size_t inByteCount);
        void Write(uint32_t inData){Write(&inData,sizeof(inData));}
        void Write(int32_t inData)
        {Write(&inData,sizeof(inData));}
        void Write(uint8_t inData){Write(&inData,sizeof(inData));}
    private:
        void ReallocBuffer(uint32_t inNewLength);
        char* mBuffer;
        uint32_t mHead;
        uint32_t mCapacity;
};
