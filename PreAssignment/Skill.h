#pragma once
#include <string>

using namespace std;

class skill {
public:
	skill() : mID(0), mName("skill"), mPreb(0) {};
	skill(int id, const char * name, int preb) : mID(id), mName(name), mPreb(preb) {};
	~skill() = default;

	int getPreb()
	{
		return mPreb;
	}

	const char* getName() {
		return mName.c_str();
	}

private:
	int		mID;
	string	mName;
	int		mPreb;
};