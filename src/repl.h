

#include <vector>
#include <string>
#include <memory>
#include <map>
#include <iostream>

#include "rtype.h"
#include "jtype.h"
#include "itype.h"
#include "table.h"
#include "parse.h"
#include "registers.h"
#include "instruction.h"

#ifndef REPL_H
#define REPL_H

void repl() {
    bool is_running_flag = true;
    registers["$s0"];
    while(is_running_flag) {
        std::string user_input;
        std::cin >> user_input;
        if(user_input == "quit" || user_input == "exit" || user_input == "q"
           || user_input == "e") 
        {
            is_running_flag = false;
            break;
        }
        else {
            // parse_line of the input.
            // create instruction out of it. 
            // interpret the instruction.
        }
    }
}

#endif
