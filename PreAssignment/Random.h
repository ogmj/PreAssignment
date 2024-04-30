#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

template <typename T1>
class random {
public:
	random() : mSeed(std::chrono::system_clock::now().time_since_epoch().count()){
		mVecData.reserve(16);
	};
	random(int size) : mSeed(std::chrono::system_clock::now().time_since_epoch().count()){
		mVecData.reserve(size);
	};
	~random() = default;

	void AddRandom(int Preb, const T1& Data) {
		if (mVecData.empty()) {
			mVecData.push_back({ Preb, Data });
		}
		else {
			int key = mVecData.back().first;
			mVecData.push_back({ key + Preb, Data });
		}
	}

	//bool GetRandom(T1& Data) const {
	bool GetRandom(T1& Data) {
		auto key = GetRand<int>(1, mVecData.back().first);
		auto elem = lower_bound(mVecData.begin(), mVecData.end(), key, [](pair<int, const T1&> a, int b) {
			return a.first < b;
			});
		if (elem != mVecData.end()) {
			Data = elem->second;
			return true;
		}
		return false;
	}

	template <typename T2>
	T2 GetRand(T2 begin, T2 end) {
		std::uniform_int_distribution<T2> r(begin, end);
		T2 randValue = r(mSeed);
		return randValue;
	}

	void Enum() {
		for (auto& e : mVecData) {
			cout << "발동확율:" << e.first/ mVecData.size() << "(value:" << e.second << ") ";
		}
		cout << "\n";
	}

	void Enum(vector<pair<int, const T1&>>& vecData){
		for (auto& e : mVecData) {
			vecData.push_back({ e.first, e.second });
		}
	}

	void Clear() {
		mVecData.clear();
	}

private:
	std::mt19937_64 mSeed;
	vector<pair<int, const T1&>> mVecData;
};
