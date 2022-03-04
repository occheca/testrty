#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

struct KeyH {
    int x;
    int y;

    bool operator==(const KeyH& param) const {
        return (this->x == param.x && this->y == param.y);
    }
};

struct hashFnKey
{
    size_t operator() (const KeyH& param) const
    {
        return std::hash<int>()(param.x) ^ std::hash<int>()(param.y);
    }
};

void exercise2() {
    std::unordered_map<KeyH, size_t, hashFnKey> ump;
    size_t i, l;

    std::vector<KeyH> arrKeys = {
        { 110,220 },
        { 102,230 },
        { 101,340 },
        { 101,339 },
        { 115,220 },
        { 101,341 },
        { 115,219 }
    };

    for (i = 0, l = arrKeys.size(); i < l; i++) {
        ump[arrKeys[i]] = i;
    }

    std::cout << std::endl << "===== Exercise 2: unordered_map =====\n";
    for (auto x : ump) {
        std::cout << x.first.x << " " << x.first.y << " " << x.second << std::endl;
    }
    std::cout << std::endl;
}; 

