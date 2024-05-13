#pragma once
#include <string>
#include "../PreAssignment/Util/CMemoryPool.h"

using namespace std;

class ItemInfo : public MemoryPool<ItemInfo> {
public:
	ItemInfo() = delete;
	virtual ~ItemInfo() = default;

	static ItemInfo* MakeItemInfo(__int64 id, const char* name, char ct, char t) {
		return new ItemInfo(id, name, ct, t);
	}

	const char* GetName()
	{
		return mName.c_str();
	}
	const char* GetClassType()
	{
		return EnumNameClassType()[mClassType];
	}

	const char* const* EnumNameClassType() {
		static const char* const names[5] = {
		  nullptr,
		  "Warrior",
		  "Sorceress",
		  "Rogue",
		};
		return names;
	}

	enum class ItemType : char {
		Weapon = 1,
		Armor = 2,
	};

private:
	explicit ItemInfo(__int64 id, const char* name, char ct, char t) : mID(id), mName(name), mClassType(ct), mType(t) {};

private:
	__int64 mID;
	string	mName;
	char	mClassType;
	char	mType;

};