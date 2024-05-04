#pragma once
#include "../PreAssignment/Util/CMemoryPool.h"

class CMap: public MemoryPool<CMap> {
public:
	CMap() = delete;
	virtual ~CMap() = default;

	static CMap* MakeMap(int id, char type, int suitable) {
		return new CMap(id, type, suitable);
	}

	enum class MapType : char {
		BASE = 1,	//불변 맵타입으로 플레이어 수가 0이 되더라도 제거되지 않는다.
		SUB = 2		//가변 맵타입으로 플레이어 수에 따라 제거된다. 
	};
	enum class PlayerCnt : int {
		Suitable = 10,	//맵에서 플레이 가능한 적정인원수. 적정 플레이어수의 120%정도까지는 성능상 커버가 되어야 합니다.
	};

	void AddPlayer() {
		++mPlayerCnt;
	}
	void RemovePlayer(){
		--mPlayerCnt;
	}
	int GetSuitablePlayerCnt() {
		return mSuitablePlayerCnt;
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
	explicit CMap(int id, char type, int suitable) : mIndex(id), mType(type), mSuitablePlayerCnt(suitable), mPlayerCnt(0) {};

private:
	int mIndex;				//유니크 아이디
	int mPlayerCnt;			//현재 플레이어 수
	int mSuitablePlayerCnt;	//적정 플레이어수
	char mType;				//1:불변맵타입 2;가변맵타입
};