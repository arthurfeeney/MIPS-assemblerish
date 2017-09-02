

#include <vector>
#include <string>
#include <memory>
#include <map>
#include <iostream>

#include "rtype.h"
#include "jtype.h"
#include "itype.h"
#include "otype.h"
#include "table.h"
#include "parse.h"
#include "registers.h"
#include "instruction.h"
#include "assemble.h"
#include "interpreter.h"

#include "repl.h"

using std::vector;
using std::cin;
using std::cout;
using std::string;
using std::unique_ptr;

static const vector<string> break_coms {
    "quit",
    "exit",
    "q",
    "e"
};
                
// does not work with pseudo commands
void repl() {

    vector<unique_ptr<Instruction>> old(0);

    bool is_running = true;
    
    while(is_running) {
        string user_input;
        std::cin >> user_input;
        if(find(break_coms.begin(), break_coms.end(), 
                user_input) != break_coms.end())
        {
            is_running = false;
            break;
        } 
        else {
            auto&& split_line = parse_line(user_input);
            unique_ptr<Instruction> instr_ptr = convert_line(split_line);
            
            Instruction instr = *instr_ptr;
            //perform(instr,
        }
    }
}
