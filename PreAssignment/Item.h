#pragma once
#include <string>

using namespace std;

class item {
public:
	item() : mID(0), mName("item"), mClassType(0), mType(0) {};
	item(__int64 id, const char* name, char ct, char t) : mID(id), mName(name), mClassType(ct), mType(t) {};
	~item() = default;

	const char* getName()
	{
		return mName.c_str();
	}
	char getClassType()
	{
		return mClassType;
	}

private:
	__int64 mID;
	string	mName;
	char	mClassType;
	char	mType;

};