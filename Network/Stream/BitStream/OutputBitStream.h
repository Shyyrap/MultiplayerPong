#pragma once
class OutputBitStream
{
    public:
        OutputBitStream();
        ~OutputBitStream();
        void WriteBits(uint8_t inData, size_t inBitCount);
        void WriteBits(const void* inData, size_t inBitCount);
        const char* GetBufferPtr()const {return mBufferPtr;}
        uint32_t GetBitLength()const{return mBitHead;}
        uint32_t GetByteLength()const{return (mBitHead+7)>>3;}
        void WriteBytes(const void* inData,size_t inByteCount);
    private:
        void ReallocBuffer(uin32_t inNewBitCapacity);
        char* mBufferPtr;
        uint32_t mBitHead;
        uint32_t mBitCapacity;
};
