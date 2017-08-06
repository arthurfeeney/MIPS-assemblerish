
#include <vector>
#include <string>

#include "instruction.h"

/*
 * otype stands for 'Other type', basically commands that I wasn't sure what
 * to do with. Like syscall. Because it always has the same binary and is easy.
 */


#ifndef OTYPE_H
#define OTYPE_H

class OType : public Instruction {
private:
    std::vector<std::string> original;
    std::string command;

    bool binary_constructed = false;
    std::string binary;
public:
    OType(const std::vector<std::string> line): original(line),
                                                command(line[0]) { }

    std::string to_binary() {
        if(binary_constructed) {
            return binary;
        }
        if(command == "syscall") {
            binary = "00000000000000000000000000001100";
        }
        binary_constructed = true;
        return binary;
    }

    std::string get_string() {
        std::string ret;
        for(const auto& s : original) {
            ret.append(s);
            ret.append(" ");
        }
        return ret;
    }

    const std::vector<std::string>& get_original() {
        return original;
    }
};

#endif
