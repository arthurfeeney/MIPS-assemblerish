
#include <vector>
#include <map>
#include <string>
#include <utility>
#include <algorithm>
#include <memory>
#include <array>

using std::make_pair;

#ifndef REGISTERS_H
#define REGISTERS_H

namespace special_registers {
    extern int hi;
    extern int lo;
};

extern std::vector<int> reg_save;


extern std::map<std::string, int*> registers;
#endif
