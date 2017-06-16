
#include <vector>
#include <map>
#include <string>
#include <utility>

#ifndef INTERPRET_TABLE_H
#define INTERPRET_TABLE_H

map<std::string, int> registers
{
    //the zero register!
    make_pair("$zero", 0),

    //Assembler temporary
    make_pair("$at", 0),

    //function results and expression evaluation
    make_pair("$v0", 0),
    make_pair("$v1", 0),

    //arguments
    make_pair("$a0", 0),
    make_pair("$a1", 0),
    make_pair("$a2", 0),
    make_pair("$a3", 0),

    //convert temporary registers
    make_pair("$t0", 0),
    make_pair("$t1", 0),
    make_pair("$t2", 0),
    make_pair("$t3", 0),
    make_pair("$t4", 0),
    make_pair("$t5", 0),
    make_pair("$t6", 0),
    make_pair("$t7", 0),

    //convert saved registers
    make_pair("$s0", 0),
    make_pair("$s1", 0),
    make_pair("$s2", 0),
    make_pair("$s3", 0),
    make_pair("$s4", 0),
    make_pair("$s5", 0),
    make_pair("$s6", 0),
    make_pair("$s7", 0),

    //more temporary!
    make_pair("$t8", 0),
    make_pair("$t9", 0),

    //registers used by os kernel :o wo
    make_pair("$k0", 0),
    make_pair("$k1", 0),

    make_pair("$gp", 0), //global pointer
    make_pair("$sp", 0), //stack pointer
    make_pair("$fp", 0), //frame-pointer
    make_pair("$ra", 0)  //return address :o
};

#endif
