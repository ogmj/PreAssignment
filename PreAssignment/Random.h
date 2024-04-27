#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>


using namespace std;

template <typename T>
class random {
public:
	random(){};
	~random() = default;

	void AddRandom(int Preb, const T& Data) {
		if (m_vecData.empty()) {
			m_vecData.push_back({ Preb, Data });
		}
		else {
			m_vecData.push_back({ m_vecData.back().first + Preb, Data });
		}
	}

	bool GetRandom(T& Data) const {

		std::mt19937_64 gen(std::chrono::system_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<int> r(1, m_vecData.back().first);
		int key = r(gen);
		cout << "random value :" << key << "\n";
		auto elem = lower_bound(m_vecData.begin(), m_vecData.end(), key, [](pair<int, const T&> a, int b) {
			return a.first < b;
			});
		if (elem != m_vecData.end()) {
			Data = elem->second;
			return true;
		}
		return false;
	}

	void Enum() {
		for (auto& e : m_vecData) {
			cout << "key:" << e.first << "(value:" << e.second << ") ";
		}
		cout << "\n";
	}

private:
	vector<pair<int, const T&>> m_vecData;
};
