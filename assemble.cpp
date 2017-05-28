
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <bitset>
#include <memory>

#include "assemble.h"
#include "parse.h"
#include "table.h"
#include "instruction.h"
#include "rtype.h"
#include "itype.h"
#include "jtype.h"

using std::find;
using std::vector;
using std::string;
using std::ifstream;
using std::map;
using std::swap;
using std::to_string;
using std::unique_ptr;

static int program_counter = 0;

//"assembles" the input file.
bool assemble(ifstream& in_file)
{
    if( !in_file.is_open() ) return false;
    vector< vector<string> > split_lines = parse_file(in_file);
    label_indices = get_labels(); // var in table.h, function in parse.h

    vector<unique_ptr<Instruction>> instructions;

    for(const auto& sl : split_lines)
    {
        // put instructions in container.
        // break pseudo (probably just 'la') into parts and convert each.
        if(instr_type[*sl.begin()] == 'p')
        {
            vector<vector<string>> commands = break_la(sl);
            for(const auto& com : commands)
            {
                instructions.push_back(convert_line(com));
                ++program_counter;
            }
        }
        else
        {
            instructions.push_back(convert_line(sl));
            ++program_counter;
        }
    }

    for(auto& i : instructions)
        std::cout << i->to_binary() << '\t' << i->get_string() << "\n\n";

    return true; // means assembling completed.
}


// convert string to an instruction.
static unique_ptr<Instruction>
convert_line(const vector<string>& splitLine)
{
    const string instr = *splitLine.begin(); //first element in line.
    if(instr_type[instr] == 'i')
    {
        return unique_ptr<Instruction>(new IType(splitLine, program_counter));
    }
    else if(instr_type[instr] == 'r')
    {
        return unique_ptr<Instruction>(new RType(splitLine));
    }
    else if(instr_type[instr] == 'j')
    {
        return unique_ptr<Instruction>(new JType(splitLine));
    }
}

// gets the lower 16 bits of something.
static string get_lower(const string& address)
{
    return string(address.begin()+17, address.end());
}

// gets the upper 16 bits of something.
static string get_upper(const string& address)
{
    return string(address.begin(), address.begin()+16);
}

static string make_32_bit(const string& num)
{
    if(num.size() == 32)
    {
        return num;
    }

    string output(32, ' ');
    for(size_t i = 0; i < 32; ++i) {
        output[i] = i < 32 - num.size() ? '0' : num[i - num.size()];
    }
    return output;
}

// breaks la into lui and ori.
static vector< vector<string> > break_la(const vector<string>& splitLine)
{
    const string& instr = *splitLine.begin();
    const vector<string>& sub_instrs = convert_pseudo[instr];
    const string& reg = *(splitLine.begin() + 1);
    string address = *(splitLine.begin() + 2);

    vector< vector<string> > commands;

    string rs;
    string rt = "$at";

    for(const string& instruction : sub_instrs)
    {
        if(instruction == "ori")
        {
            rs = reg;
        }
        vector<string> command {
            instruction,
            rs,
            rt,
            address
        };
        if(command[1].size() == 0) command.erase(command.begin() + 1);
        commands.push_back(command);
    }
    return commands;
}
