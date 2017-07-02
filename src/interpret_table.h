
#include <vector>
#include <map>
#include <string>
#include <utility>
#include <boost/any.hpp>

#include "register.h"

using std::make_pair;

#ifndef INTERPRET_TABLE_H
#define INTERPRET_TABLE_H

static Register<int> def;


std::map<std::string, Register<reg_type>> registers
{ };
/*
    //the zero register!
    make_pair("$zero", Register<int>(def)),

    //Assembler temporary
    make_pair("$at", Register<int>(def)),

    //function results and expression evaluation
    make_pair("$v0", Register<int>(def)),
    make_pair("$v1", Register<int>(def)),

    //arguments
    make_pair("$a0", Register<int>(def)),
    make_pair("$a1", Register<int>(def)),
    make_pair("$a2", Register<int>(def)),
    make_pair("$a3", Register<int>(def)),

    //convert temporary registers
    make_pair("$t0", Register<int>(def)),
    make_pair("$t1", Register<int>(def)),
    make_pair("$t2", Register<int>(def)),
    make_pair("$t3", Register<int>(def)),
    make_pair("$t4", Register<int>(def)),
    make_pair("$t5", Register<int>(def)),
    make_pair("$t6", Register<int>(def)),
    make_pair("$t7", Register<int>(def)),

    //convert saved registers
    make_pair("$s0", Register<int>(def)),
    make_pair("$s1", Register<int>(def)),
    make_pair("$s2", Register<int>(def)),
    make_pair("$s3", Register<int>(def)),
    make_pair("$s4", Register<int>(def)),
    make_pair("$s5", Register<int>(def)),
    make_pair("$s6", Register<int>(def)),
    make_pair("$s7", Register<int>(def)),

    //more temporary!
    make_pair("$t8", Register<int>(def)),
    make_pair("$t9", Register<int>(def)),

    //registers used by os kernel :o wo
    make_pair("$k0", Register<int>(def)),
    make_pair("$k1", Register<int>(def)),

    make_pair("$gp", Register<int>(def)), //global pointer
    make_pair("$sp", Register<int>(def)), //stack pointer
    make_pair("$fp", Register<int>(def)), //frame-pointer
    make_pair("$ra", Register<int>(def))  //return address :o
};
*/
#endif
