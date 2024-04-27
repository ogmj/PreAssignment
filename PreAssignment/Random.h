#pragma once
#include <vector>
#include <algorithm>
#include <random>


using namespace std;

template <typename T>
class random {
public:
	random() : m_seed(std::chrono::system_clock::now().time_since_epoch().count()) {};
	~random() = default;

	void AddRandom(int Preb, const T& Data) {
		if (m_vecData.empty()) {
			m_vecData.push_back(Preb, Data);
		}
		else {
			m_vecData.push_back(m_vecData.back()->first+Preb, Data);
		}
	}

	bool GetRandom(T& Data) const {
		std::uniform_int_distribution<int> r(1, m_vecData.back().first);

		auto key = r(m_seed);
		auto elem = lower_bound(m_vecData.begin(), m_vecData.end(), key, [](pair<int, int> a, int b) {
			return a.first < b;
			});
		if (e != m_vecData.end()) {
			Data = e.second;
			return true;
		}
		return false;
	}

private:
	mt19937_64	m_seed;
	vector<int, T&> m_vecData;
};