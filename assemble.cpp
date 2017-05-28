
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
bool assemble(ifstream& file) 
{
    if( !file.is_open() ) return false;
    vector< vector<string> > split_lines = parse_file(file);
    label_indices = get_labels(); // var in table.h, function in parse.h

    vector<unique_ptr<Instruction>> instructions;

    for(const auto& sl : split_lines) 
    {
        // put instructions in container.
        // break pseudo (probably just 'la') into parts and convert each.
        if(instr_type[*sl.begin()] == 'p') 
        {
            vector<vector<string>> commands = break_p(sl);
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

//breaks apart pseudo commands
//basically just for la...
static vector< vector<string> > break_p(const vector<string>& splitLine) 
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
            address = "0";
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
