#include <iostream>
#include <cassert>
#include <memory>
#include "Random.h"
#include "Skill.h"
#include "DropInfo.h"
//#include "CMap.h"
#include "CMapManager.h"
//#include "Util/CSingleton.h"

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

static vector<shared_ptr<int>> gVecValue;
static vector<shared_ptr<skill>> gVecSkill;
static vector<ItemInfo*> gVecItem;

static CMapManager* gMapManager = CSingleton< CMapManager >::GetInstance();
static random<shared_ptr<int>>* gRandomInt =  CSingleton<random<shared_ptr<int>>>::GetInstance();
static random<shared_ptr<skill>>* gRandomSkill = CSingleton<random<shared_ptr<skill>>>::GetInstance();
static DropInfo<int, char, int, ItemInfo>* gDropList = CSingleton<DropInfo<int, char, int, ItemInfo>>::GetInstance();

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
                assert(command.size() == 2 && "/test1 command size error");
                assert(atoi(command[1].c_str()) && "/test1 command value error");

                shared_ptr<int> value;
                int cnt = atoi(command[1].c_str());
                for (auto i = 0; i < cnt; ++i) {
                    value = make_shared<int>(CSingleton<random<shared_ptr<int>> >::GetInstance()->GetRand(1,99));
                    gVecValue.push_back(value);
                }
                for (auto& elem : gVecValue) {
                    CSingleton<random<shared_ptr<int>> >::GetInstance()->AddRandom(*elem, elem);
                }
                shared_ptr<int> result;
                vector<pair<int, const shared_ptr<int>&>> vecEnum;
                CSingleton<random<shared_ptr<int>> >::GetInstance()->Enum(vecEnum);
                int total = 0;
                for (auto e : vecEnum) {
                    total += *e.second.get();
                }
                int f = 1;
                for (auto it = vecEnum.begin(); it != vecEnum.end(); ++it) {
                    cout << "난수구간: " << f << "-" << (*it).first << ", 값: " << *(*it).second.get() << " ,확율:" << *(*it).second.get() * 100 / total << "." << (*(*it).second.get() * 10000 / total) % 100 << "%\n";
                    f = (*it).first;
                }
                CSingleton<random<shared_ptr<int>> >::GetInstance()->GetRandom(result);
                cout << ", 값: " << *result << "\nend\n";
            }
            else if (command[0] == "/retest1") {
                assert(command.size() == 1);
                shared_ptr<int> result;
                vector<pair<int, const shared_ptr<int>&>> vecEnum;
                CSingleton<random<shared_ptr<int>> >::GetInstance()->Enum(vecEnum);
                assert(vecEnum.empty() == false && "/retest1 enum empty.");
                int total = 0;
                for (auto e : vecEnum) {
                    total += *e.second.get();
                }
                int f = 1;
                for (auto it = vecEnum.begin(); it != vecEnum.end(); ++it) {
                    cout << "난수구간: " << f << "-" << (*it).first << ", 값: " << *(*it).second.get() << " ,확율:" << *(*it).second.get() * 100 / total << "." << (*(*it).second.get() * 10000 / total) % 100 << "%\n";
                    f = (*it).first;
                }
                CSingleton<random<shared_ptr<int>> >::GetInstance()->GetRandom(result);
                cout << ", 값: " << *result << "\nend\n";
            }
            else if (command[0] == "/skilltest1") {
                assert(command.size() == 2);
                assert(atoi(command[1].c_str()));

                CSingleton<random<shared_ptr<skill>> >::GetInstance()->Clear();
                gVecSkill.clear();

                shared_ptr<skill> value;
                int cnt = atoi(command[1].c_str());
                for (auto i = 0; i < cnt; ++i) {
                    value = make_shared<skill>(i+1/*스킬ID*/, ("skill" + to_string(i + 1)).c_str()/*스킬명*/, CSingleton<random<shared_ptr<skill>> >::GetInstance()->GetRand(1, 99)/*스킬발동계수*/);
                    gVecSkill.push_back(value);
                }
                for (auto& elem : gVecSkill) {
                    CSingleton<random<shared_ptr<skill>> >::GetInstance()->AddRandom(elem.get()->getPreb(), elem);
                }

                vector<pair<int, const shared_ptr<skill>&>> vecEnumSkill;
                int total = 0;
                shared_ptr<skill> result;
                CSingleton<random<shared_ptr<skill>> >::GetInstance()->Enum(vecEnumSkill);
                for(auto& e : vecEnumSkill) {
                    total += e.second.get()->getPreb();
                }
                int f = 1;
                for(auto& e : vecEnumSkill) {
                    cout << "스킬명: " << e.second.get()->getName() << " ,스킬난수구간: " << f << "-" << e.first << " ,발동확율:" << e.second.get()->getPreb() * 100 / total << "." << (e.second.get()->getPreb() * 10000 / total) % 100 << "%\n";
                    f = e.first;
                }
                CSingleton<random<shared_ptr<skill>> >::GetInstance()->GetRandom(result);
                cout << ", 발동스킬: " << result.get()->getName() << "\nend\n";
            }
            else if (command[0] == "/reskilltest1") {
                assert(command.size() == 1);
                vector<pair<int, const shared_ptr<skill>&>> vecEnumSkill;
                int total = 0;
                shared_ptr<skill> result;
                CSingleton<random<shared_ptr<skill>> >::GetInstance()->Enum(vecEnumSkill);
                for (auto& e : vecEnumSkill) {
                    total += e.second.get()->getPreb();
                }
                int f = 1;
                for (auto& e : vecEnumSkill) {
                    cout << "스킬명: " << e.second.get()->getName() << " ,스킬난수구간: " <<  f << "-" << e.first << " ,발동확율:" << e.second.get()->getPreb() * 100 / total << "." << (e.second.get()->getPreb() * 10000 / total) % 100 << "%\n";
                    f = e.first;
                }
                CSingleton<random<shared_ptr<skill>> >::GetInstance()->GetRandom(result);
                cout << ", 발동스킬: " << result.get()->getName() << "\nend\n";
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
            else if (command[0] == "/test2loaditem") {

                assert(command.size() == 5 && "/test2loaditem command size error");
                assert(atoi(command[1].c_str()) && "/test2loaditem command cnt error");
                assert(atoi(command[2].c_str()) && "/test2loaditem command dropID error");
                assert(atoi(command[3].c_str()) && "/test2loaditem command classType error");
                assert(atoi(command[4].c_str()) && "/test2loaditem command itemType error");

                auto cnt = atoi(command[1].c_str());
                auto dropID = atoi(command[2].c_str());
                auto classType = static_cast<char>(atoi(command[3].c_str()));
                auto itemtype = static_cast<char>(atoi(command[4].c_str()));
                //드롭 리스트에 아이템 등록
                for (auto i = 0; i < cnt; ++i) {
                    ItemInfo* pItemInfo = ItemInfo::MakeItemInfo(gVecItem.size()+1, ("item"+to_string(gVecItem.size() + 1)).c_str(), classType, itemtype);
                    gVecItem.push_back(pItemInfo);
                    CSingleton<DropInfo<int, char, int, ItemInfo>>::GetInstance()->AddDropItem(dropID, classType, CSingleton<random<shared_ptr<int>> >::GetInstance()->GetRand(1, 99), pItemInfo);
                }
                cout << "end\n";
            }
            else if (command[0] == "/test2clearitem") {
                for (auto& item: gVecItem) {
                    delete item;
                }
                gVecItem.clear();
                cout << "end\n";
            }
            else if (command[0] == "/test2dropitem") {
                assert(command.size() == 3 && "/test2dropitem command size error");
                assert(atoi(command[1].c_str()) && "/test2dropitem command dropID error");
                assert(atoi(command[2].c_str()) && "/test2dropitem command classType error");
                auto dropID = atoi(command[1].c_str());
                auto classType = static_cast<char>(atoi(command[2].c_str()));
                ItemInfo* pItemInfo = nullptr;
                if (CSingleton<DropInfo<int, char, int, ItemInfo>>::GetInstance()->GetRandomItem(dropID, classType, pItemInfo)) {
                    if (pItemInfo) {
                        cout << "드롭아이템명: " << pItemInfo->GetName() << "\n";
                    }
                }
                else {
                    cout << "드롭ID 혹은 직업타입으로 드롭아이템을 찾지 못하였습니다.\n";
                }
            }
            else if (command[0] == "/test3addmap") {
                assert(command.size() == 3 && "/test3addmap command size error");
                assert(atoi(command[1].c_str()) && "/test3addmap command[1] value error");
                assert(atoi(command[2].c_str()) && "/test3addmap command[2] value error");

                auto cnt = atoi(command[1].c_str());
                auto type = static_cast<char>(atoi(command[2].c_str()));
                assert(type >= 1 && type <= 2 && "/test3addmap command[2] range error");

                for (auto i = 0; i < cnt; ++i) {
                    CMap* pMap = CMap::MakeMap(CSingleton< CMapManager >::GetInstance()->GetMapID(),
                        type, static_cast<char>(CMap::PlayerCnt::Suitable));
                    CSingleton< CMapManager >::GetInstance()->AddChannelMap(type, pMap);
                }
                CSingleton< CMapManager >::GetInstance()->EnumMapState();
                cout << "end\n";
            }
            else if (command[0] == "/test3clearmap") {
                CSingleton< CMapManager >::GetInstance()->ClearChannelMap();
                CSingleton< CMapManager >::GetInstance()->EnumMapState();
                cout << "end\n";
            }
            else if (command[0] == "/test3addplayer") {
                assert(command.size() == 2 && "/test3addplayer command size error");
                assert(atoi(command[1].c_str()) && "/test3addplayer command[1] value error");
                auto cnt = atoi(command[1].c_str());
                for (auto i = 0; i < cnt; ++i) {
                    auto index = CSingleton< CMapManager >::GetInstance()->SelectChannelMap();
                    CSingleton< CMapManager >::GetInstance()->AddPlayer(index);
                }
                CSingleton< CMapManager >::GetInstance()->EnumMapState();
                cout << "end\n";
            }
            else if (command[0] == "/test3removeplayer") {
                assert(command.size() == 3 && "/test3removeplayer command size error");
                assert(atoi(command[1].c_str()) && "/test3removeplayer command[1] value error");
                assert(atoi(command[2].c_str()) && "/test3removeplayer command[2] value error");
                auto index = atoi(command[1].c_str());
                auto cnt = atoi(command[2].c_str());
                for (auto i = 0; i < cnt; ++i) {
                    CSingleton< CMapManager >::GetInstance()->RemovePlayer(index);
                }
                CSingleton< CMapManager >::GetInstance()->EnumMapState();
                cout << "end\n";
            }
        }
    }

    cout << "Hello World!\n";
}

