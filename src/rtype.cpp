#include <vector>
#include <string>

#include "rtype.h"

vector< vector<string> > mod_sets
{
    vector<string> {"sll", "srl", "sra"},
    vector<string> {"sllv", "srav"},
    vector<string> {"mult", "multu", "div", "divu"},
    vector<string> {"jr"},
    vector<string> {"jalr"},
    vector<string> {"mfhi", "mflo"},
    vector<string> {"mthi", "mtlo"}
};
