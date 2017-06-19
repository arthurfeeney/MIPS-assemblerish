#include <vector>
#include <string>
#include <memory>

#include <iostream>

#include "interpret_table.h"
#include "instruction.h"
#include "rtype.h"
#include "itype.h"
#include "jtype.h"
#include "table.h" // stores the labels of the indices.

using std::vector;
using std::string;
using std::unique_ptr;
using std::stoi;

// registers are saved in interpret_table.h

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
        std::cout << registers["$t5"];
    }
    return true;
}
