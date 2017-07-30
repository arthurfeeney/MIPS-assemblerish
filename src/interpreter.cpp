#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <array>
#include <cmath>
#include <bitset>
#include <iostream>
#include <map>

#include "registers.h"
#include "instruction.h"
#include "rtype.h"
#include "itype.h"
#include "jtype.h"
#include "table.h" // stores the labels of the indices.
#include "parse.h"
//#include "functions.h"

using std::vector;
using std::string;
using std::unique_ptr;
using std::shared_ptr;
using std::stoi;
using std::find;
using std::array;
using std::make_shared;
using std::abs;
using std::map;
using std::cout;

void print_reg(string reg)
{
    std::cout << reg << ": " << *registers[reg] << '\n';
}

// this function checks if something is pointing to a data segment.
// used to increment address and not add to the value its pointing to.
bool is_data_address(const int* reg)
{
    for(auto& data : words)
    {
        int* address = data.second.data();
        for(; *address < data.second.size(); ++address) {
            if(reg == address) return true;
        }
    }
    return false;
}

void syscall(const vector<string>& instr) {
    int v0 = *registers["$v0"];
    if(v0 == 1) {
        cout << *registers["$a0"];
    }
}

void la(const vector<string>& instr)
{
    string reg = instr[1];
    string address_label = instr[2];
    auto spot = words.find(address_label);
    int* address = spot == words.end() ? &labels[address_label]
                                        : words[address_label].data();
    registers[reg] = &*address;
}

void lw(const vector<string>& instr)
{
    string rt = instr[1];
    string offset = instr[2];
    string base = instr[3];
    *registers[rt] = *(registers[base] + stoi(offset));
}

void sw(const vector<string>& instr)
{
    string rt = instr[1];
    string offset = instr[2];
    string base = instr[3];
    *(registers[base] + stoi(offset)) = *registers[rt];
}

void ori(const vector<string>& instr)
{
    string rs = instr[2];
    string rt = instr[1];
    string i = instr[3];
    int conv = is_num(i) ? stoi(i) : label_indices[i];
    *registers[rt] = *registers[rs] | conv;
}

void or_(const vector<string>& instr)
{
    string rd = instr[1];
    string rs = instr[2];
    string rt = instr[3];
    *registers[rd] = *registers[rs] | *registers[rt];
}

void xor_(const vector<string>& instr)
{
    string rd = instr[1];
    string rs = instr[2];
    string rt = instr[3];
    *registers[rd] = *registers[rs] ^ *registers[rt];
}

void nor(const vector<string>& instr)
{
    string rd = instr[1];
    string rs = instr[2];
    string rt = instr[3];
    *registers[rd] = ~(*registers[rs] | *registers[rt]);
}

void xori(const vector<string>& instr)
{
    string rt = instr[1];
    string rs = instr[2];
    string immediate = instr[3];
    *registers[rt] = *registers[rs] | stoi(immediate);
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
    int conv = is_num(i) ? stoi(i) : label_indices[i];
    conv = stoi(i) & ~0xFFFF; // sets the bottom 16 bits to 0
    *registers[rt] = conv;
}

void addi(const vector<string>& instr)
{
    string rs = instr[2];
    string rt = instr[1];
    string i = instr[3];
    if(is_data_address(registers[rs]))
    {
        registers[rt] = registers[rs] + stoi(i);
    }
    else {
        *registers[rt] = *registers[rs] + stoi(i);
    }
}

void add(const vector<string>& instr)
{
    string rd = instr[1];
    string rs = instr[2];
    string rt = instr[3];
    if(is_data_address(registers[rs])) {
        registers[rd] = registers[rs] + *registers[rt];
    }
    else if(is_data_address(registers[rt])) {
        registers[rd] = *registers[rs] + registers[rt];
    }
    else {
        *registers[rd] = *registers[rs] + *registers[rt];
    }
}

void addu(const vector<string>& instr)
{
    string rd = instr[1];
    string rs = instr[2];
    string rt = instr[3];
    if(is_data_address(registers[rs])) {
        registers[rd] = registers[rs] + *registers[rt];
    }
    else if(is_data_address(registers[rt])) {
        registers[rd] = *registers[rs] + registers[rt];
    }
    else {
        *registers[rd] = *registers[rs] + *registers[rt];
    }
}

void addiu(const vector<string>& instr)
{
    string rt = instr[1];
    string rs = instr[2];
    string i = instr[3];
    if(is_data_address(registers[rs]))
    {
        registers[rt] = registers[rs] + stoi(i);
    }
    else {
        *registers[rt] = *registers[rs] + stoi(i);
    }
}

void sub(const vector<string>& instr)
{
    string rd = instr[1];
    string rs = instr[2];
    string rt = instr[3];
    if(is_data_address(registers[rs]))
    {
        registers[rd] = &*(registers[rs] - *registers[rt]);
    }
    else
    {
        *registers[rd] = *registers[rs] - *registers[rt];
    }
}

void subi(const vector<string>& instr)
{
    string rt = instr[1];
    string rs = instr[2];
    string i = instr[3];
    if(is_data_address(registers[rs])) {
        registers[rt] = registers[rs] - stoi(i);
    }
    else {
        *registers[rt] = *registers[rs] - stoi(i);
    }
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

// saves the return address in $ra.
int jal(const vector<string>& instr, int pc)
{
    *registers["ra"] = pc + 1;
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
    if(registers[rs] == registers[rt])
    {
        if(is_num(offset))
        {
            pc += stoi(offset);
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
            pc += stoi(offset);
        }
        else
        {
            pc = label_indices[offset];
        }
    }
    return pc;
}

//should be 0 extended by default?
void lbu(const vector<string>& instr)
{
    string rt = instr[1];
    string offset = instr[2];
    string base = instr[3];
    uint8_t byte = *(registers[base] + stoi(offset));
    *registers[rt] = static_cast<int>(byte);
}

void lb(const vector<string>& instr)
{
    string rt = instr[1];
    string offset = instr[2];
    string base = instr[3];
    int8_t byte = *(registers[base] + stoi(offset));
    *registers[rt] = static_cast<int>(byte);
}

void lhu(const vector<string>& instr)
{
    string rt = instr[1];
    string offset = instr[2];
    string base = instr[3];
    uint16_t half = *(registers[base] + stoi(offset));
    *registers[rt] = static_cast<int>(half);
}

void lh(const vector<string>& instr)
{
    string rt = instr[1];
    string offset = instr[2];
    string base = instr[3];
    int16_t half = *(registers[base] + stoi(offset));
    *registers[rt] = static_cast<int>(half);
}

void sll(const vector<string>& instr)
{
    string rd = instr[1];
    string rt = instr[2];
    string sa = instr[3];
    *registers[rd] = *registers[rt] << stoi(sa);
}

void sllv(const vector<string>& instr)
{
    string rd = instr[1];
    string rt = instr[2];
    string rs = instr[3];
    *registers[rd] = *registers[rt] << *registers[rs];
}

void sr_(const vector<string>& instr)
{
    string rd = instr[1];
    string rt = instr[2];
    string sa = instr[3];
    *registers[rd] = *registers[rt] >> stoi(sa);
}

void mult(const vector<string>& instr)
{
    string rs = instr[1];
    string rt = instr[2];
    const int val1 = *registers[rs];
    const int val2 = *registers[rt];
    std::bitset<64> prod(val1 * val2);
    string binary_s_prod = prod.to_string();
    string upper(32, '0');
    string lower(32, '0');
    for(int i = 0; i < 32; ++i)
    {
        upper[i] = binary_s_prod[i];
        lower[i] = binary_s_prod[i+32];
    }
    special_registers::hi = stoi(upper, nullptr, 2);
    special_registers::lo = stoi(lower, nullptr, 2);
}

void div(const vector<string>& instr)
{
    string rs = instr[1];
    string rt = instr[2];
    const int val1 = *registers[rs];
    const int val2 = *registers[rt];
    std::bitset<64> qout(val1 / val2);
    string binary_s_quot = qout.to_string();
    string upper(32, '0');
    string lower(32, '0');
    for(int i = 0; i < 32; ++i)
    {
        upper[i] = binary_s_quot[i];
        lower[i] = binary_s_quot[i+32];
    }
    special_registers::hi = stoi(upper, nullptr, 2);
    special_registers::lo = stoi(lower, nullptr, 2);
}

void slt(const vector<string>& instr)
{
    string rd = instr[1];
    string rs = instr[2];
    string rt = instr[3];
    *registers[rd] = *registers[rs] < *registers[rt] ? 1 : 0;
}

void sltu(const vector<string>& instr)
{
    string rd = instr[1];
    string rs = instr[2];
    string rt = instr[3];
    *registers[rd] = ((0 | *registers[rs]) < (0 | *registers[rt])) ? 1 : 0;
}

void slti(const vector<string>& instr)
{
    string rt = instr[1];
    string rs = instr[2];
    string immediate = instr[3];
    *registers[rt] = *registers[rs] < stoi(immediate) ? 1 : 0;
}

void sltiu(const vector<string>& instr)
{
    string rt = instr[1];
    string rs = instr[2];
    string immediate = instr[3];
    *registers[rt] = ((0 | *registers[rs]) < (0 | stoi(immediate))) ? 1 : 0;
}

int bgtz(const vector<string>& instr, int pc)
{
    string rs = instr[1];
    string offset = instr[2];
    if(*registers[rs] > 0)
        if(is_num(offset))
        {
            pc += stoi(offset);
        }
        else
        {
            pc = label_indices[offset];
        }
    return pc;
}

int blez(const vector<string>& instr, int pc)
{
    string rs = instr[1];
    string offset = instr[2];
    if(*registers[rs] <= 0)
        if(is_num(offset))
        {
            pc += stoi(offset);
        }
        else
        {
            pc = label_indices[offset];
        }
    return pc;
}

void mfhi(const vector<string>& instr)
{
    string rd = instr[1];
    *registers[rd] = special_registers::hi;
}

void mflo(const vector<string>& instr)
{
    string rd = instr[1];
    *registers[rd] = special_registers::lo;
}

void mthi(const vector<string>& instr)
{
    string rd = instr[1];
    special_registers::hi = *registers[rd];
}

void mtlo(const vector<string>& instr)
{
    string rd = instr[1];
    special_registers::lo = *registers[rd];
}

bool is_la(array<vector<string>, 2>& coms)
{
    vector<string> one = coms[0];
    vector<string> two = coms[1];
    return one[0] == "lui" && two[0] == "ori" && one[2] == two[3];
}

int program_counter = 0;

void perform(const vector<string>& com, int& program_counter,
             vector<unique_ptr<Instruction>>& instructions) {
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
        program_counter = jal(com, program_counter);
    }
    else if(com[0] == "jr")
    {
        program_counter = jr(com);
    }
    else if(com[0] == "ori")
    {
        ori(com);
    }
    else if(com[0] == "or")
    {
        or_(com);
    }
    else if(com[0] == "lbu")
    {
        lbu(com);
    }
    else if(com[0] == "lhu")
    {
        lhu(com);
    }
    else if(com[0] == "sll")
    {
        sll(com);
    }
    else if(com[0] == "srl")
    {
        // assuming c++ will choose srl or sra. Bad assumption.
        sr_(com);
    }
    else if(com[0] == "sra")
    {
        sr_(com);
    }
    else if(com[0] == "xor")
    {
        xor_(com);
    }
    else if(com[0] == "nor")
    {
        nor(com);
    }
    else if(com[0] == "mult")
    {
        mult(com);
    }
    else if(com[0] == "sllv")
    {
        sllv(com);
    }
    else if(com[0] == "xori")
    {
        xori(com);
    }
    else if(com[0] == "slt")
    {
        slt(com);
    }
    else if(com[0] == "sltu")
    {
        sltu(com);
    }
    else if(com[0] == "slti")
    {
        slti(com);
    }
    else if(com[0] == "sltiu")
    {
        sltiu(com);
    }
    else if(com[0] == "bgtz")
    {
        program_counter = bgtz(com, program_counter);
    }
    else if(com[0] == "blez")
    {
        program_counter = blez(com, program_counter);
    }
    else if(com[0] == "lb")
    {
        lb(com);
    }
    else if(com[0] == "lh")
    {
        lh(com);
    }
    else if(com[0] == "sb")
    {
        sw(com);
    }
}

bool step(vector<unique_ptr<Instruction>>& instructions) {
    if(program_counter < instructions.size()) {
        const vector<string> com = instructions[program_counter]
                                        ->get_original();
        string binary = instructions[program_counter]->to_binary();
        string instr = instructions[program_counter]->get_string();
        std::cout << binary << "    " << instr << '\n';
        perform(com, program_counter, instructions);
        ++program_counter;
    }
    else {
        cout << "program complete \n";
        return false;
    }
    return true;
}

bool interpret(vector<unique_ptr<Instruction>>& instructions)
{
    const int final_pc = instructions.size();

    int return_index = 0;

    for( ; program_counter < final_pc; ++program_counter )
    {
        const vector<string> com = instructions[program_counter]
                                                            ->get_original();
        perform(com, program_counter, instructions);
    }
    print_reg("$t1");
    print_reg("$t2");
    return true; // successful.
}
