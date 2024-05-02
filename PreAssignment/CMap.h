#pragma once
#include "../PreAssignment/Util/CMemoryPool.h"

class CMap: public MemoryPool<CMap> {
public:
	CMap() = delete;
	explicit CMap( int id, char type, int max ): mIndex(id), mType(type), mMaxPlayerCnt(max), mPlayerCnt(0) {};
	virtual ~CMap() = default;

	CMap* MakeMap(int id, char type, int max) {
		return new CMap(id, type, max);
	}

	void AddPlayer() {
		++mPlayerCnt;
	}
	void RemovePlayer(){
		--mPlayerCnt;
	}
	int GetMaxPlayerCnt() {
		return mMaxPlayerCnt;
	}
	int GetPlayerCnt() {
		return mPlayerCnt;
	}
	char GetType() {
		return mType;
	}
	int GetIndex() {
		return mIndex;
	}

private:
	int mIndex;			//유니크 아이디
	int mPlayerCnt;
	int mMaxPlayerCnt;
	char mType;			//0:기본 1;추가
};