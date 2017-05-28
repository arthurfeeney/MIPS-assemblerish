
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>

#include "instruction.h"

bool assemble(std::ifstream& file);
static bool is_instr(std::string& word);
static std::unique_ptr<Instruction>
    convert_line(const std::vector<std::string>& splitLine);
static std::vector< std::vector<std::string> > break_p(
    const std::vector<std::string>& splitLine
);
