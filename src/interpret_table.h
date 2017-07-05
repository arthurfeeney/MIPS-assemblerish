
#include <vector>
#include <map>
#include <string>
#include <utility>
#include <algorithm>
#include <memory>
#include <array>

//#include "register.h"

using std::make_pair;

#ifndef INTERPRET_TABLE_H
#define INTERPRET_TABLE_H

static std::vector<int> reg_save(32, 0);

std::map<std::string, int*> registers
{
    //the zero register!
    make_pair("$zero", &reg_save[0]),

    //Assembler temporary
    make_pair("$at", &reg_save[1]),

    //function results and expression evaluation
    make_pair("$v0", &reg_save[2]),
    make_pair("$v1", &reg_save[3]),

    //arguments
    make_pair("$a0", &reg_save[4]),
    make_pair("$a1", &reg_save[5]),
    make_pair("$a2", &reg_save[6]),
    make_pair("$a3", &reg_save[7]),

    //convert temporary registers
    make_pair("$t0", &reg_save[8]),
    make_pair("$t1", &reg_save[9]),
    make_pair("$t2", &reg_save[10]),
    make_pair("$t3", &reg_save[11]),
    make_pair("$t4", &reg_save[12]),
    make_pair("$t5", &reg_save[13]),
    make_pair("$t6", &reg_save[14]),
    make_pair("$t7", &reg_save[15]),

    //convert saved registers
    make_pair("$s0", &reg_save[16]),
    make_pair("$s1", &reg_save[17]),
    make_pair("$s2", &reg_save[18]),
    make_pair("$s3", &reg_save[19]),
    make_pair("$s4", &reg_save[20]),
    make_pair("$s5", &reg_save[21]),
    make_pair("$s6", &reg_save[22]),
    make_pair("$s7", &reg_save[23]),

    //more temporary!
    make_pair("$t8", &reg_save[24]),
    make_pair("$t9", &reg_save[25]),

    //registers used by os kernel :o wo
    make_pair("$k0", &reg_save[26]),
    make_pair("$k1", &reg_save[27]),

    make_pair("$gp", &reg_save[28]), //global pointer
    make_pair("$sp", &reg_save[29]), //stack pointer
    make_pair("$fp", &reg_save[30]), //frame-pointer
    make_pair("$ra", &reg_save[31])  //return address :o
};
#endif
