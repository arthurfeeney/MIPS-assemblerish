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

using std::vector;
using std::string;
using std::unique_ptr;
using std::shared_ptr;
using std::stoi;
using std::find;
using std::array;
using std::make_shared;

// registers are saved in interpret_table.h

void la(const vector<string>& instr)
{
    string reg = instr[1];
    string address_label = instr[2];
    auto spot = words.find(address_label);
    int* address = spot == words.end() ? &labels[address_label]
                                        : words[address_label].data();
    registers[reg] = address;
}

void lw(const vector<string>& instr)
{
    string rt = instr[1];
    string offset = instr[2];
    string base = instr[3];
    *registers[rt] = *(registers[base] + (stoi(offset) / 4));
}

void sw(const vector<string>& instr)
{
    string rt = instr[1];
    string offset = instr[2];
    string base = instr[3];
    *(registers[base] + (stoi(offset) / 4)) = *registers[rt];
}

void ori(const vector<string>& instr)
{
    string rs = instr[2];
    string rt = instr[1];
    string i = instr[3];
    *registers[rt] = *registers[rs] | stoi(i);
}

void andi(const vector<string>& instr)
{
    string rs = instr[2];
    string rt = instr[1];
    string i = instr[3];
    *registers[rt] = *registers[rs] & stoi(i);
}

void and_(const vector<string>& instr)
{
    string rd = instr[1];
    string rs = instr[2];
    string rt = instr[3];
    *registers[rd] = *registers[rs] & *registers[rt];
}

void lui(const vector<string>& instr)
{
    string rt = instr[1];
    string i = instr[2];
    int conv;
    conv = stoi(i) << 16;
    *registers[rt] = conv; // shift left 16 to get top 16 bits.
}

void addi(const vector<string>& instr)
{
    string rs = instr[2];
    string rt = instr[1];
    string i = instr[3];
    *registers[rt] = *registers[rs] + stoi(i);
}

void add(const vector<string>& instr)
{
    string rd = instr[1];
    string rs = instr[2];
    string rt = instr[3];
    *registers[rd] = *registers[rs] + *registers[rt];
}

void addu(const vector<string>& instr)
{
    string rd = instr[1];
    string rs = instr[2];
    string rt = instr[3];
    *registers[rd] = *registers[rs] + *registers[rt];
}

void addiu(const vector<string>& instr)
{
    string rt = instr[1];
    string rs = instr[2];
    string i = instr[3];
    *registers[rt] = *registers[rs] + stoi(i);
}

void sub(const vector<string>& instr)
{
    string rd = instr[1];
    string rs = instr[2];
    string rt = instr[3];
    *registers[rd] = *registers[rs] - *registers[rt];
}

void subi(const vector<string>& instr)
{
    string rt = instr[1];
    string rs = instr[2];
    string i = instr[3];
    *registers[rt] = *registers[rs] - stoi(i);
}

int j(const vector<string>& instr)
{
    string offset = instr[1];
    if(is_num(offset))
    {
        return stoi(offset);
    }
    return label_indices[offset];
}

// saves the return address in $ra. But idk if I need to do that...
int jal(const vector<string>& instr)
{
    return j(instr);
}

int jr(const vector<string>& instr)
{
    string rs = instr[1];
    return *registers[rs];
}

int beq(const vector<string>& instr, int pc)
{
    string rs = instr[1];
    string rt = instr[2];
    string offset = instr[3];

    if(registers[rs] == registers[rt]) {
        if(is_num(offset))
        {
            pc += (stoi(offset) / 4);
        }
        else
        {
            pc = label_indices[offset];
        }
    }
    return pc;
}

int bne(const vector<string>& instr, int pc)
{
    string rs = instr[1];
    string rt = instr[2];
    string offset = instr[3];

    if(registers[rs] != registers[rt]) {
        if(is_num(offset))
        {
            pc += (stoi(offset) / 4);
        }
        else
        {
            pc = label_indices[offset];
        }
    }
    return pc;
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

    int return_index = 0;

    for( ; program_counter < final_pc; ++program_counter )
    {
        const vector<string> com = instructions[program_counter]
                                                    ->
                                                    get_original();
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
        else if(com[0] == "subi")
        {
            subi(com);
        }
        else if(com[0] == "lui")
        {
            vector<string> next = instructions[program_counter + 1]
                                                    ->
                                                    get_original();
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
        else if(com[0] == "lw")
        {
            lw(com);
        }
        else if(com[0] == "sw")
        {
            sw(com);
        }
        else if(com[0] == "andi")
        {
            andi(com);
        }
        else if(com[0] == "j")
        {
            program_counter = j(com);
        }
        else if(com[0] == "beq")
        {
            program_counter = beq(com, program_counter);
        }
        else if(com[0] == "bne")
        {
            program_counter = bne(com, program_counter);
        }
        else if(com[0] == "addiu")
        {
            addiu(com);
        }
        else if(com[0] == "addu")
        {
            addu(com);
        }
        else if(com[0] == "and")
        {
            and_(com);
        }
        else if(com[0] == "jal")
        {
            return_index = program_counter + 1;
            program_counter = jal(com);
        }
        else if(com[0] == "jr")
        {
            program_counter = jr(com);
        }
    }
    std::cout << "register $t5: " << *registers["$t5"] << '\n';
    std::cout << "register $s1: " << *registers["$s1"] << '\n';
    std::cout << "register $t0: " << *registers["$t0"] << '\n';
    for(int i : words["A"]) {
        std::cout << i << ", ";
    }
    return true; // successful.
}
