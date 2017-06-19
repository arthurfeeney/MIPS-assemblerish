
#include <map>
#include <utility>
#include <string>
#include <vector>
#include <algorithm>

#include "table.h"

using std::vector;
using std::string;
using std::map;
using std::make_pair;

//this file just stores maps to convert things (instructions, registers, etc)

map<string, int> label_indices; // stores the locations of labels.

bool is_num(const string& word) {
    const vector<char> digits = {'-','0','1','2','3','4','5','6','7','8','9'};
    if(std::find(word.begin() + 1, word.end(), '-') != word.end())
        return false;
    for(const char& c : word)
        if(find(digits.begin(), digits.end(), c) == digits.end())
            return false;
    return true;
}

map<string, char> instr_type {
    make_pair("addi", 'i'),
    make_pair("addiu", 'i'),
    make_pair("sw", 'i'),
    make_pair("lw", 'i'),
    make_pair("beq", 'i'),
    make_pair("bne", 'i'),
    make_pair("andi", 'i'),
    make_pair("lbu", 'i'),
    make_pair("lhu", 'i'),
    make_pair("lui", 'i'),
    make_pair("ori", 'i'),
    make_pair("xori", 'i'),
    make_pair("slti", 'i'),
    make_pair("sltiu", 'i'),
    make_pair("bgtz", 'i'),
    make_pair("blez", 'i'),
    make_pair("lb", 'i'),
    make_pair("lh", 'i'),
    make_pair("sb", 'i'),
    make_pair("sh", 'i'),
    make_pair("add", 'r'),
    make_pair("sub", 'r'),
    make_pair("addu", 'r'),
    make_pair("and", 'r'),
    make_pair("mult", 'r'),
    make_pair("jr", 'r'),
    make_pair("sll", 'r'),
    make_pair("srl", 'r'),
    make_pair("sra", 'r'),
    make_pair("subu", 'r'),
    make_pair("or", 'r'),
    make_pair("xor", 'r'),
    make_pair("nor", 'r'),
    make_pair("div", 'r'),
    make_pair("divu", 'r'),
    make_pair("multu", 'r'),
    make_pair("sllv", 'r'),
    make_pair("srav", 'r'),
    make_pair("slt", 'r'),
    make_pair("sltu", 'r'),
    make_pair("jalr", 'r'),
    make_pair("mfhi", 'r'),
    make_pair("mflo", 'r'),
    make_pair("mthi", 'r'),
    make_pair("mtlo", 'r'),
    make_pair("j", 'j'),
    make_pair("jal", 'j'),
    make_pair("la", 'p') // a Pseudo-instruction.
};


map<string, vector<string> > convert_pseudo {
    make_pair("la", vector<string> {"lui", "ori"})
};

map<string, string> convert_instr {
    make_pair("addi", "001000"),
    make_pair("addiu", "001001"),
    make_pair("sw", "101011"),
    make_pair("lw", "100011"),
    make_pair("add", "100000"),
    make_pair("addu", "100001"),
    make_pair("sub", "100010"),
    make_pair("j", "000010"),
    make_pair("jal", "000011"),
    make_pair("beq", "000100"),
    make_pair("bne", "000101"),
    make_pair("and", "100100"),
    make_pair("andi", "001100"),
    make_pair("lbu", "100100"),
    make_pair("lhu", "100101"),
    make_pair("mult", "011000"),
    make_pair("lui", "001111"),
    make_pair("ori", "001101"),
    make_pair("jr", "001000"),
    make_pair("sll", "000000"),
    make_pair("srl", "000010"),
    make_pair("sra", "000011"),
    make_pair("subu", "100011"),
    make_pair("or", "100101"),
    make_pair("xor", "100110"),
    make_pair("nor", "100111"),
    make_pair("div", "011010"),
    make_pair("divu", "011011"),
    make_pair("multu", "011001"),
    make_pair("sllv", "000100"),
    make_pair("srav", "000111"),
    make_pair("xori", "001110"),
    make_pair("slt", "101010"),
    make_pair("sltu", "101011"),
    make_pair("slti", "001010"),
    make_pair("sltiu", "001011"),
    make_pair("bgtz", "000111"),
    make_pair("blez", "000110"),
    make_pair("jalr", "001001"),
    make_pair("lb", "100000"),
    make_pair("lh", "100001"),
    make_pair("sb", "101000"),
    make_pair("sh", "101001"),
    make_pair("mfhi", "010000"),
    make_pair("mflo", "010010"),
    make_pair("mthi", "010001"),
    make_pair("mtlo", "010011")
};

map<string, string> instr_opcode {
    make_pair("add", "000000"),
    make_pair("sub", "000000"),
    make_pair("addu", "000000"),
    make_pair("and", "000000"),
    make_pair("mult", "000000"),
    make_pair("jr", "000000"),
    make_pair("sll", "000000"),
    make_pair("srl", "000000"),
    make_pair("sra", "000000"),
    make_pair("subu", "000000"),
    make_pair("or", "000000"),
    make_pair("xor", "000000"),
    make_pair("nor", "000000"),
    make_pair("div", "000000"),
    make_pair("divu", "000000"),
    make_pair("multu", "000000"),
    make_pair("sllv", "000000"),
    make_pair("srav", "000000"),
    make_pair("slt", "000000"),
    make_pair("sltu", "000000"),
    make_pair("jalr", "000000"),
    make_pair("mfhi", "000000"),
    make_pair("mflo", "000000"),
    make_pair("mthi", "000000"),
    make_pair("mtlo", "000000")
};


map<string, string> convert_reg {
    //the zero register!
    make_pair("$zero", "00000"),

    //Assembler temporary
    make_pair("$at", "00001"),

    //function results and expression evaluation
    make_pair("$v0", "00010"),
    make_pair("$v1", "00011"),

    //arguments
    make_pair("$a0", "00100"),
    make_pair("$a1", "00101"),
    make_pair("$a2", "00110"),
    make_pair("$a3", "00111"),

    //convert temporary registers
    make_pair("$t0", "01000"),
    make_pair("$t1", "01001"),
    make_pair("$t2", "01010"),
    make_pair("$t3", "01011"),
    make_pair("$t4", "01100"),
    make_pair("$t5", "01101"),
    make_pair("$t6", "01110"),
    make_pair("$t7", "01111"),

    //convert saved registers
    make_pair("$s0", "10000"),
    make_pair("$s1", "10001"),
    make_pair("$s2", "10010"),
    make_pair("$s3", "10011"),
    make_pair("$s4", "10100"),
    make_pair("$s5", "10101"),
    make_pair("$s6", "10110"),
    make_pair("$s7", "10111"),

    //more temporary!
    make_pair("$t8", "11000"),
    make_pair("$t9", "11001"),

    //registers used by os kernel :o wo
    make_pair("$k0", "11010"),
    make_pair("$k1", "11011"),

    make_pair("$gp", "11100"), //global pointer
    make_pair("$sp", "11101"), //stack pointer
    make_pair("$fp", "11110"), //frame-pointer
    make_pair("$ra", "11111")  //return address :o
};
