#include <vector>
#include <string>
#include <memory>

#include "interpret_table.h"
#include "instruction.h"
#include "rtype.h"
#include "itype.h"
#include "jtype.h"

using std::vector;
using std::string;
using std::unique_ptr;

bool interpret(const vector<unique_ptr<instruction>>& commands)
{
    for(const auto& instr : commands)
    {
        
    }
}
