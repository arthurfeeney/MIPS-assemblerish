#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <array>

#include <iostream>

#include "interpret_table.h"
#include "instruction.h"
#include "rtype.h"
#include "itype.h"
#include "jtype.h"
#include "table.h" // stores the labels of the indices.
#include "parse.h"

#include "register.h"

using std::vector;
using std::string;
using std::unique_ptr;
using std::stoi;
using std::find;
using std::array;

// registers are saved in interpret_table.h

void la(const vector<string>& instr)
{
    string reg = instr[1];
    string address_label = instr[2];    
    //int* address = words[address_label].data();
    //registers[reg] = address;
}

void ori(const vector<string>& instr)
{
    string rs = instr[2];
    string rt = instr[1];
    string i = instr[3];
    registers[rt] = registers[rs].get_val() | stoi(i);
}

void lui(const vector<string>& instr)
{
    string rt = instr[1];
    string i = instr[2];
    registers[rt] = stoi(i) << 16; // shift left 16 to get top 16 bits.
}

void addi(const vector<string>& instr)
{
    string rs = instr[2];
    string rt = instr[1];
    string i = instr[3];
    registers[rt] = registers[rs] + stoi(i);
}

void add(const vector<string>& instr)
{
    string rd = instr[1];
    string rs = instr[2];
    string rt = instr[3];
    registers[rd] = registers[rs] + registers[rt];
}

void sub(const vector<string>& instr)
{
    string rd = instr[1];
    string rs = instr[2];
    string rt = instr[3];
    registers[rd] = registers[rs] - registers[rt];
}

bool is_la(array<vector<string>, 2>& coms)
{
    vector<string> one = coms[0];
    vector<string> two = coms[1];
    return one[0] == "lui" && two[0] == "ori" && one[2] == two[3]; 
}

bool interpret(vector<unique_ptr<Instruction>>& instructions)
{
    int program_counter = 0;
    const int final_pc = instructions.size();

    for( ; program_counter < final_pc; ++program_counter )
    {
        const vector<string> com = instructions[program_counter]
                                        ->get_original();
        if(com[0] == "addi")
        {
            addi(com);
        }
        else if(com[0] == "add")
        {
            add(com);
        }
        else if(com[0] == "sub")
        {
            sub(com);
        }
        else if(com[0] == "lui")
        {
            vector<string> next = instructions[program_counter + 1]
                                    ->get_original();
            array<vector<string>, 2> coms {
                com,
                next
            };
            if(is_la(coms))
            {
                vector<string> real {
                    "la",
                    next[1],
                    com[2],
                };
                la(real);
                ++program_counter;
            }
            else {
                lui(com);
            }
        }
    }
    std::cout << "register $t5: " << registers["$t5"].get_val() << '\n';
    std::cout << "register $s1: " << registers["$s1"].get_val() << '\n';
    return true; // successful.
}
