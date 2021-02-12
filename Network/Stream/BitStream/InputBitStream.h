#pragma once
class OutputBitStream
{
    public:
        OutputBitStream();
        ~OutputBitStream();
        void WriteBits();
        void WriteBits();
        const char* GetBufferPtr(){
            return mBufferPtr;
        }
    private:
        void ReallocBuffer(uint32_t inNewBitCapacity);
        char* mBufferPtr;
        uint32_t mBitHead;
        uint32_t mBitCapacity;

};
