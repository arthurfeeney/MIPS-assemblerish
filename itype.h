#include <string>
#include <vector>
#include <bitset>
#include <algorithm>

#include "instruction.h"
#include "table.h"

#ifndef ITYPE_H
#define ITYPE_H

class IType : public Instruction {
private:
    int pc;
    std::vector<std::string> original;

    std::string instr;
    std::string rs;
    std::string rt;
    std::string immediate;

    std::string binary;

public:
    IType(const std::vector<std::string> line, const int p):
        original(line), instr(line[0]), pc(p)
    {
        int m = 2, n = 1, o = 3;
        if(instr == "sw" || instr == "lw" || instr == "lbu" ||
        instr == "lhu" || instr == "lui" || instr == "lb" || instr == "lh" ||
        instr == "sb")
        {
            std::swap(m, o);
        }
        else if(instr == "beq" || instr == "bne" || instr == "bgtz" ||
                instr == "blez")
        {
            std::swap(m, n);
        }

        immediate = line[o];

        if(!is_num(immediate))
        {
            immediate = std::to_string(label_indices[immediate] * 4);
        }

        // offset from current address.
        if(instr == "beq" || instr == "bne")
        {
            immediate = std::to_string(std::stoi(immediate) - (pc * 4));
        }

        rs = instr == "lui" ? "$zero" : line[m];
        rt = instr == "bgtz" || instr == "blez" ? "$zero" : line[n];
    }

    IType(const IType& i):
        instr(i.instr), rs(i.rs), rt(i.rt), immediate(i.immediate),
        binary(i.binary) {}

    std::string to_binary()
    {
        binary.append(convert_instr[instr]);
        binary.append(convert_reg[rs]);
        binary.append(convert_reg[rt]);
        // get the upper 16 bits of the immediate.
        if(instr == "lui") {
            std::string tmp = std::bitset<32>(std::stoi(immediate)).to_string();
            binary.append(tmp.begin(), tmp.begin()+16); // upper 16 bits
        }
        // get the lower 16 bits of the immediate.
        else if(instr == "ori") {
            std::string tmp = std::bitset<32>(std::stoi(immediate)).to_string();
            binary.append(tmp.begin()+16, tmp.end()); // lower 16 bits
        }
        else {
            binary.append(
                std::bitset<16>(std::stoi(immediate)).to_string()
            );
        }
        return binary;
    }

    std::string get_string()
    {
        std::string ret;
        for(const auto& s : original) {
            ret.append(s);
            ret.append(" ");
        }
        if(*original.begin() == "lui" && original.size() == 4) {
            ret.clear();
            ret.append(original[0]);
            ret.append(" ");
            ret.append(original[2]);
            ret.append(" ");
            ret.append(original[3]);
            ret.append(" ");
        }
        return ret;
    }

    std::vector<std::string> get_original()
    {
        return original;
    }
};

#endif
