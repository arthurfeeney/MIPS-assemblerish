#include <string>

#ifndef INSTRUCTION_H
#define INSTRUCTION_H 

class Instruction {
public:
    Instruction() = default;

    ~Instruction() = default;

    virtual std::string to_binary() {}
    virtual std::string get_string() {}
};

#endif
