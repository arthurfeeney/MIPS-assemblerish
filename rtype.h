
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>

#include "instruction.h"
#include "table.h"

#ifndef RTYPE_H
#define RTYPE_H

namespace rtype_compare{
    vector< vector<string> > sets
    {
        vector<string> {"sll", "srl", "sra"},
        vector<string> {"sllv", "srav"},
        vector<string> {"mult", "multu", "div", "divu"},
        vector<string> {"jr"},
        vector<string> {"jalr"},
        vector<string> {"mfhi", "mflo"},
        vector<string> {"mthi", "mtlo"}
    };
    const int error = 420; // some thing indicating an error.
};

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

    int instr_is_set()
    {
        const vector< vector<string> >& read_sets = rtype_compare::sets;
        for(int i = 0; i < read_sets.size(); ++i)
        {
            const vector<string>& cur_set = read_sets[i];
            if(std::find(cur_set.begin(), cur_set.end(), instr)!=cur_set.end())
            {
                return i; // returns which conditional should be called.
            }
        }
        return rtype_compare::error;
    }

public:
    RType(const std::vector<std::string> line):
        original(line), instr(line[0]), rs(line[2]), rt(line[3]),
        rd(line[1]), shift("0")
    {
        // determines which condition to use.
        // change to switch statement?
        // move to to_binary() and make constructor only assign original.
        // have boolean indicating if the binary has been constructed?
        const int id = instr_is_set();
        if(id == 0)
        {
            rs = "$zero";
            rt = line[2];
            shift = line[3];
        }
        else if(id == 1)
        {
            std::swap(rs, rt);
        }
        else if(id == 2)
        {
            rt = rs;
            rs = rd;
            rd = "$zero";
        }
        else if(id == 3)
        {
            rs = line[1];
            rt = "$zero";
            rd = "$zero";
        }
        else if(id == 4)
        {
            rt = "$zero";
        }
        else if(id == 5)
        {
            rs = "$zero";
            rt = "$zero";
        }
        else if(id == 6)
        {
            rs = rd;
            rd = "$zero";
            rt = "$zero";
        }
    }

    // copy
    RType(const RType &r):
        instr(r.instr), rs(r.rs), rt(r.rt), rd(r.rd), shift(r.shift),
        func(r.func), binary(r.binary) {}

    // converts the line to binary.
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

    // outputs the original string.
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
