#include <vector>
#include <string>
#include <memory>

#include "instruction.h"

#ifndef INTERPRETER_H
#define INTERPRETER_H


bool interpret(const std::vector<std::unique_ptr<Instruction>>& );


#endif
