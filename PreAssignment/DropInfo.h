#pragma once
#include <vector>
#include <unordered_map>
#include "ItemInfo.h"
#include "Util/CMutex.h"
#include "Util/CSingleton.h"

using namespace std;

template<typename T1, typename T2, typename T3, typename T4>
class DropInfo {
public:
	DropInfo() {};
	~DropInfo() = default;

	void AddDropItem(T1 id, T2 classID, T3 preb, T4* Data ) {
		CLOCK(mLock);
		auto dropList = mHsDropList.find(id);
		if (dropList != mHsDropList.end()) {
			auto classType = lower_bound(dropList->second.begin(), dropList->second.end(), classID, [](pair<T2, vector<pair<T3, T4*>>> a, int b) {
				return a.first < b;
				});
			if (classType != dropList->second.end()) {
				if (classID == (*classType).first) {
					int key = (*classType).second.back().first;
					(*classType).second.push_back({ preb + key, Data });
				}
				else {
					vector<pair<T3, T4*>> vec;
					vec.push_back({ preb, Data });
					dropList->second.push_back({ classID, vec });
				}
			}
			else {
				vector<pair<T3, T4*>> vec;
				vec.push_back({ preb, Data });
				dropList->second.push_back({ classID, vec });
			}
		}
		else {
			vector<pair<T3, T4*>> vec;
			vec.push_back({ preb, Data });

			vector<pair<T2, vector<pair<T3, T4*>>>> vec1;
			vec1.push_back({classID, vec });

			mHsDropList.insert({ id, vec1 });
		}
	}

	bool GetRandomItem(T1 id, T2 classID, T4*& Data) {
		CLOCK(mLock);
		auto dropList = mHsDropList.find(id);
		if (dropList != mHsDropList.end()) {
			auto classType = lower_bound(dropList->second.begin(), dropList->second.end(), classID, [](pair<T2, vector<pair<T3, T4*>>> a, int b) {
				return a.first < b;
				});
			if (classType != dropList->second.end()) {
				if (classID == (*classType).first) {
					int dropRand = CSingleton<random<shared_ptr<int>> >::GetInstance()->GetRand(1, (*classType).second.back().first);
					cout << "드롭난수: " << dropRand << "\n";
					auto itemIt = lower_bound((*classType).second.begin(), (*classType).second.end(), dropRand, [](pair<T3, T4*> a, T3 b) {
						return a.first < b;
						});
					cout << "아이템 리스트\n";
					int f = 1;
					for (auto& item : (*classType).second) {
						cout << "아이템명: " << item.second->GetName() << ", 드롭난수구간: " << f << "-" << item.first << ", 클래스: " << item.second->GetClassType() << "\n";
						f = item.first;
					}
					Data = (*itemIt).second;
					return true;
				}
			}
		}
		return false;
	}

private:
	//unordered_map<드롭아이디, vector<pair<클래스타입, vector<드롭난수구간,드롭아이템 >>> > mHsDropList
	unordered_map<T1, vector<pair<T2, vector<pair<T3, T4*>>>>> mHsDropList;
	CMutex mLock;
};