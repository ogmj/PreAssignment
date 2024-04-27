#include <iostream>
#include <vector>
#include <string>
#include <cassert>

#include <random>
#include <map>
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
            else if (command[0] == "/s") {

            }
            else if (command[0] == "/i") {

            }
            else if (command[0] == "/pt1") {
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
                std::uniform_int_distribution<int> dist(1, vecInput.back().first);
                key = dist(gen);
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

