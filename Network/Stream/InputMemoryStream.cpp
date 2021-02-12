#include"InputMemoryStream.h"
void InputMemoryStream::Read(void* outData,
        uint32_t inByteCount)
{
	uint32_t resultHead = mHead + inByteCount;
	if( resultHead > mCapacity )
	{
		//handle error, no data to read!
        std::cout<<"No data to read"<<std::endl;
	}
	std::memcpy(outData, mBuffer + mHead, inByteCount );
	mHead = resultHead;
}

