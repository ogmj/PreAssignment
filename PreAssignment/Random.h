#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>


using namespace std;

template <typename T1>
class random {
public:
	random()
	{
		m_vecData.reserve(16);
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

	bool GetRandom(T1& Data) const {
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
	T2 GetRand(T2 begin, T2 end) const {
		std::mt19937_64 gen(std::chrono::system_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<T2> r(begin, end);
		T2 key = r(gen);
		cout << "random value :" << key << "\n";
		return key;
	}

	void Enum() {
		for (auto& e : m_vecData) {
			cout << "key:" << e.first << "(value:" << e.second << ") ";
		}
		cout << "\n";
	}

private:
	vector<pair<int, const T1&>> m_vecData;
};
