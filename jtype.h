
#include <vector>
#include <string>
#include <bitset>

#include "instruction.h"
#include "table.h"


#ifndef JTYPE_H
#define JTYPE_H

class JType : public Instruction {
private:
    std::vector<std::string> original;

    std::string instr;
    std::string jump_location;

    std::string binary;

    void convert_jl()
    {
        if(!is_num(jump_location))
        {
            const int spot = label_indices[jump_location] * 4;
            jump_location = std::bitset<26>(spot).to_string();
        } 
        else
        {
            const int spot = std::stoi(jump_location);
            jump_location = std::bitset<26>(spot).to_string();
        }
    }

public:
    JType(const std::vector<std::string> line):
        original(line), instr(line[0]), jump_location(line[1]) { }

    JType(const JType& j):
        instr(j.instr), jump_location(j.jump_location), binary(j.binary) {}
    
    std::string to_binary()
    {
        binary.append(convert_instr[instr]);
        convert_jl();
        binary.append(jump_location);
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
