#pragma once
#include <iostream>

using namespace std;

template<typename T, int ALLOC_BLOCK_SIZE = 50>
class MemoryPool
{
public:
	static void* operator new(size_t allocLength)
	{
		//만약 더 이상 할당할 수 있는 공간이 없을 경우 새로 할당합니다.
		if (!mFreePointer)
		{
			alloc_block(get_size(allocLength));
		}
		unsigned char* ReturnPointer = mFreePointer;
		mFreePointer = *reinterpret_cast<unsigned char**>(ReturnPointer);

		return ReturnPointer;
	}

	static void operator delete(void* deletePointer)
	{
		*reinterpret_cast<unsigned char**>(deletePointer) = mFreePointer;
		//delete된 블록의 next에 현재 m_free_pointer의 주소를 넣어줍니다.
		mFreePointer = static_cast<unsigned char*>(deletePointer);
	}

private:
	static size_t get_size(size_t allocLength)
	{
		if (allocLength > 8)
		{
			return allocLength;
		}
		else
		{
			T* p = nullptr;
			return sizeof(p);
		}
	}
	static void alloc_block(size_t allocLength)
	{
		mFreePointer = new unsigned char[allocLength * ALLOC_BLOCK_SIZE];
		//m_free_pointer에 사용할 크기의 메모리를 할당합니다.

		unsigned char** current = reinterpret_cast<unsigned char**>(mFreePointer);
		//할당한 메모리의 첫 블록의 포인터를 current에 넣습니다.

		unsigned char* next = mFreePointer; //할당된 메모리 첫 블록입니다.
		for (int i = 0; i < ALLOC_BLOCK_SIZE - 1; ++i)
		{
			next += allocLength;	//다음 블록을 계산합니다.
			*current = next;
			current = reinterpret_cast<unsigned char**>(next);
		}
		*current = nullptr;	//마지막일 경우 앞에 주소는 nullptr입니다.

	}

private:
	static unsigned char* mFreePointer;

protected:
	~MemoryPool(){}
};

template<typename T, int ALLOC_BLOCK_SIZE>
unsigned char* MemoryPool<T, ALLOC_BLOCK_SIZE>::mFreePointer = nullptr;
