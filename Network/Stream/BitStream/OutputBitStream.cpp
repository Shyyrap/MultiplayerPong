#include"InputBitStream.h"
#include<memory>

OutputBitStream::OutputBitStream(){
    ReallocBuffer(256);
}
~OutputBitStream::OutputBitStream()
{
    std::free(mBufferPtr);
}
void OutputBitStream::WriteBits(uint8_t inData, size_t inBitCount)
{
    uint32_t nextBitHead = mBitHead+static_cast<uint32_t>(inBitCount);
    if(nextBitHead > mBitCapacity)
    {
        ReallocBuffer(std::max(mBitCapacity*2,nextBitHead));
    }

    //вычислить смещение байта byteOffset в буфере
    //разделив номер первого бита на 8,
    //и смещение бита bitOffset - в 3 младших битах номера
    uint32_t byteOffset = mBitHead>>3;
    uint32_t bitOffset = mBitHead&0x7;

    //вычислить маску для сохранения нужных битов в текущем байте 
    uint8_t currentMask = ~(0xff<<bitOffset);
    mBuffer[byteOffset] = (mBuffer[byteOffset]&currentMask)|(inData<<bitOffset);
    //вычислить число неиспольжзованных битов
    //в целевом байте в буфере
    uint32_t bitsFreeThisByte = 8 - bitOffset;
    //если необходимо, перенести в следующий байт
    if(bitsFreeThisByte < inBitCount)
    {
        mBuffer[byteOffset+1] = inData>>bitsFreeThisByte;

    }
    mBitHead = nextBitHead;
}

void OutputBitStream::WriteBits(const void* inData, size_t inBitCount)
{
    const char* srcByte = static_cast<const char*>(inData);
    //записать все байты 
    while(inBitCount>8)
    {
        WriteBits(*scrByte,8);
        ++scrByte;
        inBitCount -= 8;
    }
    //записать все что осталось 
    if(inBitCount>0)
    {

        WriteBits(*scrByte,inBitCount);
    }

}
void OutputBitStream::WriteBytes(const void* inData, size_t inByteCount)
{
    WriteBits(inData, inByteCount<<3);
}

