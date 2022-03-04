
#include <iostream>
#include <vector>
#include <map>

struct Key {
    int x;
    int y;

    bool operator<(const Key& param) const
    {
        bool result = false;

        if (this->x != param.x) {
            result = (this->x < param.x);
        }
        else {
            result = (this->y < param.y);
        }
        return result;
    }
};

void exercise1() {

    std::map<Key, size_t> mp;
    size_t i, l;

    std::vector<Key> arrKeys = {
        { 110,220 },
        { 102,230 },
        { 101,340 },
        { 101,339 },
        { 115,220 },
        { 101,341 },
        { 115,219 }
    };
    
    for (i = 0, l=arrKeys.size(); i < l; i++) {
        mp[arrKeys[i]] = i;
    }
        
    std::cout << std::endl << "===== Exercise 1: map =====\n";
    for (auto x : mp) {
        std::cout << x.first.x << " " << x.first.y << " " << x.second << std::endl;
    }
    std::cout << std::endl; 

};

