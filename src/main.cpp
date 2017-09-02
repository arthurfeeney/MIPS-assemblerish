

/*
 * Arthur Feeney
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <bitset>
#include <vector>
#include <memory>

#include "assemble.h"
#include "interpreter.h"
#include "run_options.h"
#include "instruction.h"
#include "itype.h"
#include "rtype.h"
#include "jtype.h"
#include "repl.h"

using std::string;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::cin;
using std::vector;
using std::unique_ptr;

int main(int argc, char** argv)
{
    std::cout << '\n' << "********************************" << '\n';
    std::cout << "mips-ish interpreter: \n\n";

    // my test file
    ifstream strm("../TestPrograms/test.s");
    bool has_file = true;
    ofstream out("output.txt");
    bool go = true;
    vector<unique_ptr<Instruction>> instructions;
    while(go) {
        string input;
        std::getline(cin, input);
        vector<string> got = parse_options(input);
        if(got.size() == 1) {
            if(got[0] == "run" || got[0] == "go" || got[0] == "execute") {
                if(has_file) {
                    interpret(instructions);
                    go = false;
                }
                else {
                    std::cout << "no file loaded" << '\n';
                    go = false;
                }
            }
            else if(got[0] == "repl" || got[0] == "play") {
                /* work in progress */
                repl();

            }
            else if(got[0] == "stc" || got[0] == "complete") {
                step_to_complete(instructions);
            }
            else if(got[0] == "step") {
                step(instructions);
            }
            else if(got[0] == "reset") {
                reset();
            }
            else if(got[0] == "quit") {
                go = false;
            }
            else {
                std::cout << "user input invalid command" << '\n';
            }
        }
        else {
            if(got[0] == "load" || got[0] == "read" ||
                got[0] == "l" || got[0] == "r") {
                strm = load_file(got[1]);
                has_file = true;
                // binary auto loaded to out when "assembled".
                instructions = assemble(strm, out);
            }
            else {
                std::cout << "user input invalid command" << '\n';
            }
        }
    }

    strm.close();
    out.close();
    return 0;
}
