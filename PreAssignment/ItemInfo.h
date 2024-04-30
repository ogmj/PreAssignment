#pragma once
#include <string>

using namespace std;

class ItemInfo {
public:
	ItemInfo() : mID(0), mName("item"), mClassType(0), mType(0) {};
	ItemInfo(__int64 id, const char* name, char ct, char t) : mID(id), mName(name), mClassType(ct), mType(t) {};
	~ItemInfo() = default;

	const char* GetName()
	{
		return mName.c_str();
	}
	char GetClassType()
	{
		return mClassType;
	}

private:
	__int64 mID;
	string	mName;
	char	mClassType;
	char	mType;

};