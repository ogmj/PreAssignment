#pragma once
#include "CLock.h"
#include <mutex>

using namespace std;

class CMutex : public CLock {
public:
	CMutex() = default;
	virtual ~CMutex() = default;

	void lock() override
	{
		mMutexLock.lock();
	};
	bool try_lock() override
	{
		return mMutexLock.try_lock();
	};
	void unlock() override
	{
		mMutexLock.unlock();
	};

private:
	recursive_mutex      mMutexLock;
};