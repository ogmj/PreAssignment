#pragma once
#include <vector>
#include <unordered_map>
#include <atomic>
#include "CMap.h"
#include "Util/CMutex.h"
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
		if (type == static_cast<char>(CMap::MapType::BASE)) {
			mVecBaseMapChannelList.push_back({pMap->GetIndex(), pMap});
			mHsSelectMapChannelList.insert({pMap->GetIndex(), pMap});
		}
		else {
			mHsSubMapChannelList.insert({pMap->GetIndex(), pMap});
			mHsSelectMapChannelList.insert({pMap->GetIndex(), pMap });
		}
	}

	void ClearChannelMap() {
		CLOCK(mLock);
		for (auto& sub: mHsSubMapChannelList) {
			delete sub.second;
		}
		mHsSubMapChannelList.clear();
		for (auto& base : mVecBaseMapChannelList) {
			delete base.second;
		}
		mVecBaseMapChannelList.clear();
		mHsSelectMapChannelList.clear();
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
		return 0;
	}

	void AddPlayer(int index) {
		CLOCK(mLock);
		auto selectMapIt = mHsSelectMapChannelList.find(index);
		if (selectMapIt != mHsSelectMapChannelList.end()) {
			(*selectMapIt).second->AddPlayer();
			if ((*selectMapIt).second->GetSuitablePlayerCnt() <= (*selectMapIt).second->GetPlayerCnt()) {
				mHsSelectMapChannelList.erase(selectMapIt);
			}
		}
		//만약 mHsSelectMapChannelList에 더이상 유효한 맵이 없다면 신규 맵채널 준비
		if (mHsSelectMapChannelList.empty()) {
			CMap * pMap = CMap::MakeMap(GetMapID(), static_cast<char>(CMap::MapType::SUB), static_cast<int>(CMap::PlayerCnt::Suitable));
			AddChannelMap(static_cast<char>(CMap::MapType::SUB), pMap);
		}
	}

	void RemovePlayer(int index) {
		CLOCK(mLock);
		auto subMapIt = mHsSubMapChannelList.find(index);
		if (subMapIt != mHsSubMapChannelList.end()) {
			(*subMapIt).second->RemovePlayer();
			if ((*subMapIt).second->GetSuitablePlayerCnt() * 0.7 >= (*subMapIt).second->GetPlayerCnt()) {
				auto selectMapIt = mHsSelectMapChannelList.find(index);
				if (selectMapIt == mHsSelectMapChannelList.end()) {
					mHsSelectMapChannelList.insert({ index,(*subMapIt).second });
				}
			}
		}
		else {
			auto baseMapIt = lower_bound(mVecBaseMapChannelList.begin(), mVecBaseMapChannelList.end(), index, [](pair<int, CMap*>a, int b) {
				return a.first < b;
				});
			if (baseMapIt != mVecBaseMapChannelList.end()) {
				(*baseMapIt).second->RemovePlayer();
				if ((*baseMapIt).second->GetSuitablePlayerCnt() * 0.7 >= (*baseMapIt).second->GetPlayerCnt()) {
					auto selectMapIt = mHsSelectMapChannelList.find(index);
					if (selectMapIt == mHsSelectMapChannelList.end()) {
						mHsSelectMapChannelList.insert({ index,(*baseMapIt).second });
					}
				}
			}
		}
	}

	void EnumMapState() {
		cout << "선택 가능 채널\n";
		for (auto& selectMap : mHsSelectMapChannelList) {
			cout << "index: " << selectMap.second->GetIndex() << ", PlayerCnt: " << selectMap.second->GetPlayerCnt() << "(" << selectMap.second->GetSuitablePlayerCnt() << ")\n";
		}
		cout << "선택 불가능 채널\n";
		for (auto& map : mVecBaseMapChannelList) {
			if (map.second->GetPlayerCnt() >= 10) {
				cout << "index: " << map.second->GetIndex() << ", PlayerCnt: " << map.second->GetPlayerCnt() << "(" << map.second->GetSuitablePlayerCnt() << ")\n";
			}
		}
		for (auto& map : mHsSubMapChannelList) {
			if (map.second->GetPlayerCnt() >= 10) {
				cout << "index: " << map.second->GetIndex() << ", PlayerCnt: " << map.second->GetPlayerCnt() << "(" << map.second->GetSuitablePlayerCnt() << ")\n";
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