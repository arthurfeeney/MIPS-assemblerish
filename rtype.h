
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>

#include "instruction.h"
#include "table.h"

#ifndef RTYPE_H
#define RTYPE_H

class RType : public Instruction {
private:
    std::vector<std::string> original;

    std::string instr;
    std::string rs;
    std::string rt;
    std::string rd;
    std::string shift;
    std::string func;

    std::string binary;

public:
    RType(const std::vector<std::string> line):
        original(line), instr(line[0]), rs(line[2]), rt(line[3]),
        rd(line[1]), shift("0")
    {
        if(instr == "sll" || instr == "srl" || instr == "sra")
        {
            rs = "$zero";
            rt = line[2];
            shift = line[3];
        }
        else if(instr == "sllv" || instr == "srav")
        {
            std::swap(rs, rt);
        }
        else if(instr == "mult" ||
                instr == "multu" ||
                instr == "div" ||
                 instr == "divu")
        {
            rt = rs;
            rs = rd;
            rd = "$zero";

        }
        else if(instr == "jr")
        {
            rs = line[1];
            rt = "$zero";
            rd = "$zero";
        }
    }

    RType(const RType &r):
        instr(r.instr), rs(r.rs), rt(r.rt), rd(r.rd), shift(r.shift),
        func(r.func), binary(r.binary) {}

    std::string to_binary()
    {
        binary.clear();
        binary.append(instr_opcode[instr]);
        binary.append(convert_reg[rs]);
        binary.append(convert_reg[rt]);
        binary.append(convert_reg[rd]);
        binary.append(std::bitset<5>(std::stoi(shift)).to_string());
        binary.append(convert_instr[instr]);
        return binary;
    }

    std::string get_string()
    {
        std::string ret;
        for(const auto& s : original)
        {
            ret.append(s);
            ret.append(" ");
        }
        return ret;
    }
};

#endif
