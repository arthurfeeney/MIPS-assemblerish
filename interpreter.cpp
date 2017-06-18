#include <vector>
#include <string>
#include <memory>

#include <iostream>

#include "interpret_table.h"
#include "instruction.h"
#include "rtype.h"
#include "itype.h"
#include "jtype.h"

using std::vector;
using std::string;
using std::unique_ptr;
using std::stoi;

// registers are saved in interpret_table.h

void addi(vector<string>& instr)
{
    string rs = instr[2];
    string rt = instr[1];
    string i = instr[3];
    registers[rt] = registers[rs] + stoi(i);
}

bool interpret(const vector<unique_ptr<Instruction>>& commands)
{
    for(const auto& instr : commands)
    {
        vector<string> com = instr->get_original();
        addi(com);
        std::cout << registers["$t2"];
    }
}
