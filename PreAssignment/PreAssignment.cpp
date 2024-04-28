#include <iostream>
#include <cassert>
#include <memory>
#include "Random.h"

using namespace std;

void spilt(vector<string>& command, string input) {
    string elem;
    elem.clear();
    for (auto& i : input) {
        if (i == ' ') {
            command.push_back(elem);
            elem.clear();
        }
        else {
            elem += i;
        }
    }
    command.push_back(elem);
}

static random<shared_ptr<int>> g_randomTest;
static vector<shared_ptr<int>> vecValue;

int main()
{
    char input[512];
    vector<string> command;

    while (1) {
        command.clear();
        cin.getline(input, sizeof(input));
        spilt(command, input);
        if (!command.empty()) {
            if (command[0] == "/quit") {
                break;
            }
            else if (command[0] == "/test1") {
                assert(command.size() == 2);
                assert(atoi(command[1].c_str()));

                shared_ptr<int> value;
                int cnt = atoi(command[1].c_str());
                for (auto i = 0; i < cnt; ++i) {
                    value = make_shared<int>(g_randomTest.GetRand(1,99));
                    vecValue.push_back(value);
                }
                for (auto& elem : vecValue) {
                    g_randomTest.AddRandom(*elem, elem);
                }
                shared_ptr<int> result;
                g_randomTest.Enum();
                g_randomTest.GetRandom(result);
                cout << "result value: " << *result << "\nend\n";

            }
            else if (command[0] == "/retest1") {
                assert(command.size() == 1);
                shared_ptr<int> result;
                g_randomTest.Enum();
                g_randomTest.GetRandom(result);
                cout << "result value: " << result << "\nend\n";
            }
            else if (command[0] == "/i") {

            }
            else if (command[0] == "/prototype1") {
                assert(command.size() > 1);
                assert(atoi(command[1].c_str()));
                vector<pair<int, int>> vecInput;
                int key = 0;

                for (int i = 1; i < command.size(); ++i) {
                    if (vecInput.empty()) {
                        vecInput.push_back({ atoi(command[i].c_str()), i });
                    }
                    else {
                        auto v = vecInput.back();
                        key = v.first;
                        key += atoi(command[i].c_str());
                        vecInput.push_back({ key, i });

                    }
                }

                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<int> r(1, vecInput.back().first);
                key = r(gen);
                cout << "key: "<< key << "\n";

                auto e = lower_bound(vecInput.begin(), vecInput.end(), key, [](pair<int, int> a, int b) {
                    return a.first < b;
                    });
                if (e != vecInput.end()) {
                    cout << "find:" << e->first << ", " << e->second << "\n";
                }
                else {
                    cout << "Not Found\n";
                }

                cout << "end\n";
            }
        }
    }

    cout << "Hello World!\n";
}

