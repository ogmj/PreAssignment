#pragma once
#include "CMap.h"
#include "../PreAssignment/Util/CMutex.h"

class CMapManager {
public:
	CMapManager() {};
	~CMapManager() = default;
	int SelectChannelMap() {

	}
private:
	CMutex mLock;
};