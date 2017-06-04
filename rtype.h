
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>

#include "instruction.h"
#include "table.h"

#ifndef RTYPE_H
#define RTYPE_H

namespace rtype_assist{
    vector< vector<string> > mod_sets
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

    bool binary_constructed = false;
    std::string binary;

    int instr_is_set()
    {
        const vector< vector<string> >& read_sets = rtype_assist::mod_sets;
        for(int i = 0; i < read_sets.size(); ++i)
        {
            const vector<string>& cur_set = read_sets[i];
            if(std::find(cur_set.begin(), cur_set.end(), instr)!=cur_set.end())
            {
                return i; // returns which conditional should be called.
            }
        }
        return -1; // command not found in rtype.
    }

    void order_instr()
    {
        instr = original[0];
        shift = "0";
        const int id = instr_is_set();
        switch(id) {
            case -1: // default command.
            {
                rs = original[2];
                rt = original[3];
                rd = original[1];
                break;
            }
            case 0:
            {
                rs = "$zero";
                rt = original[2];
                rd = original[1];
                shift = original[3];
                break;
            }
            case 1:
            {
                //std::swap(rs, rt);
                rs = original[3];
                rt = original[2];
                rd = original[1];
                break;
            }
            case 2:
            {
                rt = original[2];
                rs = original[1];
                rd = "$zero";
                break;
            }
            case 3:
            {
                rs = original[1];
                rt = "$zero";
                rd = "$zero";
                break;
            }
            case 4:
            {
                rs = original[2];
                rt = "$zero";
                rd = original[1];
                break;
            }
            case 5:
            {
                rs = "$zero";
                rt = "$zero";
                rd = original[1];
                break;
            }
            case 6:
            {
                rs = original[1];
                rd = "$zero";
                rt = "$zero";
                break;
            }
        }
    }

public:
    RType(const std::vector<std::string> line): original(line) { }

    // copy
    RType(const RType &r):
        instr(r.instr), rs(r.rs), rt(r.rt), rd(r.rd), shift(r.shift),
        func(r.func), binary(r.binary) {}

    // converts the line to binary.
    std::string to_binary()
    {
        if(!binary_constructed)
        {
            binary.clear();
            order_instr();
            binary.append(instr_opcode[instr]);
            binary.append(convert_reg[rs]);
            binary.append(convert_reg[rt]);
            binary.append(convert_reg[rd]);
            binary.append(std::bitset<5>(std::stoi(shift)).to_string());
            binary.append(convert_instr[instr]);
            binary_constructed = true;
        }
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
