#pragma once
#include <vector>
#include <unordered_map>
#include "Item.h"

using namespace std;

template<typename T1, typename T2, typename T3, typename T4>
class droplist {
public:
	droplist() {};
	~droplist() = default;

	void addItem(T1 id, T2 classID, T3 preb, T4& Data ) {
		auto dropList = mHsDropList.find(id);
		if (dropList != mHsDropList.end()) {
			auto classType = lower_bound(dropList->second.begin(), dropList->second.end(), classID, [](pair<T2, vector<pair<T3, T4&>>> a, int b) {
				return a.first < b;
				});
			if (classType != dropList->second.end()) {
				if (classID == (*classType).first) {
					int key = (*classType).second.back().first;
					(*classType).second.push_back({ preb + key, Data });
				}
				else {
					vector<pair<T3, T4&>> vec;
					vec.push_back({ preb, Data });
					dropList->second.push_back({ classID, vec });
				}
			}
			else {
				vector<pair<T3, T4&>> vec;
				vec.push_back({ preb, Data });
				dropList->second.push_back({ classID, vec });
			}
		}
		else {
			vector<pair<T3, T4&>> vec;
			vec.push_back({ preb, Data });

			vector<pair<T2, vector<pair<T3, T4&>>>> vec1;
			vec1.push_back({classID, vec });

			mHsDropList.insert({ id, vec1 });
		}
	}

private:
	//unordered_map<드롭ID, vector<pair<클래스Type, vector< 등장확율,드롭Item >>> > mHsDropList
	unordered_map<T1, vector<pair<T2, vector<pair<T3, T4&>>>>> mHsDropList;
	//unordered_map<T1, vector<vector<pair<T2, T3&>>>> mHsDropList;
};