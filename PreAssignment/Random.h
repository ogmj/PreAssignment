#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

template <typename T1>
class random {
public:
	random() : m_Seed(std::chrono::system_clock::now().time_since_epoch().count())
	{
		m_vecData.reserve(16);
	};
	random(int size) : m_Seed(std::chrono::system_clock::now().time_since_epoch().count())
	{
		m_vecData.reserve(size);
	};
	~random() = default;

	void AddRandom(int Preb, const T1& Data) {
		if (m_vecData.empty()) {
			m_vecData.push_back({ Preb, Data });
		}
		else {
			int key = m_vecData.back().first;
			m_vecData.push_back({ key + Preb, Data });
		}
	}

	//bool GetRandom(T1& Data) const {
	bool GetRandom(T1& Data) {
		auto key = GetRand<int>(1, m_vecData.back().first);
		auto elem = lower_bound(m_vecData.begin(), m_vecData.end(), key, [](pair<int, const T1&> a, int b) {
			return a.first < b;
			});
		if (elem != m_vecData.end()) {
			Data = elem->second;
			return true;
		}
		return false;
	}

	template <typename T2>
	T2 GetRand(T2 begin, T2 end) {
		std::uniform_int_distribution<T2> r(begin, end);
		T2 key = r(m_Seed);
		cout << "렌덤값 :" << key << "\n";
		return key;
	}

	void Enum() {
		for (auto& e : m_vecData) {
			cout << "발동확율:" << e.first/ m_vecData.size() << "(value:" << e.second << ") ";
		}
		cout << "\n";
	}

	void Enum(vector<pair<int, const T1&>>& vecData){
		for (auto& e : m_vecData) {
			vecData.push_back({ e.first, e.second });
		}
	}

	void Clear() {
		m_vecData.clear();
	}

private:
	std::mt19937_64 m_Seed;
	vector<pair<int, const T1&>> m_vecData;
};
