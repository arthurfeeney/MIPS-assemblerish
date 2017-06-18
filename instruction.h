#include <string>
#include <vector>

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

class Instruction {
public:
    Instruction() = default;

    ~Instruction() = default;

    virtual std::string to_binary() {}
    virtual std::string get_string() {}
    virtual std::vector<std::string> get_original() {}
};

#endif
