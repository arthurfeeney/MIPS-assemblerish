#include <string>
#include <vector>

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

class Instruction {
public:
    Instruction() = default;

    ~Instruction() = default;

    virtual Instruction& operator=(Instruction other) {
        return *this;
    }
    virtual std::string to_binary() { return std::string(); }
    virtual std::string get_string() { return std::string(); }
    virtual const std::vector<std::string>& get_original() 
    {
        std::vector<std::string>* tmp = new std::vector<std::string>();
        auto& ret = *tmp;
        return ret;
    }
};

#endif
