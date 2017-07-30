#include <vector>
#include <string>
#include <memory>

#include "instruction.h"

#ifndef INTERPRETER_H
#define INTERPRETER_H

void perform(const std::vector<std::string>&, int& program_counter,
             std::vector<std::unique_ptr<Instruction>>&);

bool interpret(std::vector<std::unique_ptr<Instruction>>&);

bool step(std::vector<std::unique_ptr<Instruction>>& instruction);
#endif
