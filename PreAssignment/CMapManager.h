#pragma once
#include <vector>
#include <unordered_map>
#include <atomic>
#include "CMap.h"
#include "../PreAssignment/Util/CMutex.h"
using namespace std;

class CMapManager {
public:
	CMapManager() : mMapID(0) {};
	~CMapManager() = default;

	int GetMapID() {
		return ++mMapID;
	}

	void AddChannelMap(char type, CMap* pMap) {
		CLOCK(mLock);
		if (type == 0) {
			mVecBaseMapChannelList.push_back({GetMapID(), pMap});
			mHsSelectMapChannelList.insert({ GetMapID(), pMap });
		}
		else {
			mHsSubMapChannelList.insert({GetMapID(), pMap});
			mHsSelectMapChannelList.insert({ GetMapID(), pMap });
		}
	}

	void DeleteChannelMap(int index) {
		CLOCK(mLock);
		auto subMapIt = mHsSubMapChannelList.find(index);
		if (subMapIt != mHsSubMapChannelList.end()) {
			delete (*subMapIt).second;
			mHsSubMapChannelList.erase(subMapIt);

			auto selectMapIt = mHsSelectMapChannelList.find(index);
			if (selectMapIt != mHsSelectMapChannelList.end()) {
				mHsSelectMapChannelList.erase(selectMapIt);
			}
		}
		else {
			auto baseMapIt = lower_bound(mVecBaseMapChannelList.begin(), mVecBaseMapChannelList.end(), index, [](pair<int,CMap*> a, int b) {
				return a.first < b;
				});
			if (baseMapIt != mVecBaseMapChannelList.end()) {
				delete (*baseMapIt).second;
				mVecBaseMapChannelList.erase(baseMapIt);

				auto selectMapIt = mHsSelectMapChannelList.find(index);
				if (selectMapIt != mHsSelectMapChannelList.end()) {
					mHsSelectMapChannelList.erase(selectMapIt);
				}
			}
		}
	}

	int SelectChannelMap() {
		CLOCK(mLock);
		auto selectMapIt = mHsSelectMapChannelList.begin();
		if (selectMapIt != mHsSelectMapChannelList.end()) {
			return (*selectMapIt).first;
		}
	}

	void AddPlayer(int index) {
		CLOCK(mLock);
		auto selectMapIt = mHsSelectMapChannelList.find(index);
		if (selectMapIt != mHsSelectMapChannelList.end()) {
			(*selectMapIt).second->AddPlayer();
			if ((*selectMapIt).second->GetMaxPlayerCnt() >= (*selectMapIt).second->GetPlayerCnt()) {
				mHsSelectMapChannelList.erase(selectMapIt);
			}
		}
	}

	void RemovePlayer(int index) {
		CLOCK(mLock);
		auto subMapIt = mHsSubMapChannelList.find(index);
		if (subMapIt != mHsSubMapChannelList.end()) {
			(*subMapIt).second->RemovePlayer();
			if ((*subMapIt).second->GetMaxPlayerCnt() * 0.8 >= (*subMapIt).second->GetPlayerCnt()) {
				mHsSelectMapChannelList.insert({index,(*subMapIt).second});
			}
		}
		else {
			auto baseMapIt = lower_bound(mVecBaseMapChannelList.begin(), mVecBaseMapChannelList.end(), index, [](pair<int, CMap*>a, int b) {
				return a.first < b;
				});
			if (baseMapIt != mVecBaseMapChannelList.end()) {
				(*baseMapIt).second->RemovePlayer();
				if ((*baseMapIt).second->GetMaxPlayerCnt() * 0.8 >= (*baseMapIt).second->GetPlayerCnt()) {
					mHsSelectMapChannelList.insert({index,(*baseMapIt).second});
				}
			}
		}
	}

private:
	CMutex mLock;
	atomic<int> mMapID;
	vector<pair<int, CMap*>> mVecBaseMapChannelList;
	unordered_map<int, CMap*> mHsSubMapChannelList;
	unordered_map<int, CMap*> mHsSelectMapChannelList;
};