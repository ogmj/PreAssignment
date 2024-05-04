#pragma once
#include <string>
#include "../PreAssignment/Util/CMemoryPool.h"

using namespace std;

class ItemInfo : public MemoryPool<ItemInfo> {
public:
	ItemInfo() = delete;
	~ItemInfo() = default;

	static ItemInfo* MakeItemInfo(__int64 id, const char* name, char ct, char t) {
		return new ItemInfo(id, name, ct, t);
	}

	const char* GetName()
	{
		return mName.c_str();
	}
	char GetClassType()
	{
		return mClassType;
	}
private:
	explicit ItemInfo(__int64 id, const char* name, char ct, char t) : mID(id), mName(name), mClassType(ct), mType(t) {};

private:
	__int64 mID;
	string	mName;
	char	mClassType;
	char	mType;

};