
#include <map>
#include <utility>
#include <string>
#include <vector>
#include <algorithm>

using std::vector;
using std::string;
using std::map;
using std::make_pair;

//this file just stores maps to convert things (instructions, registers, etc)

#ifndef TABLE_H
#define TABLE_H

extern map<string, int> label_indices; // stores the locations of labels.

bool is_num(const string& word);

extern map<string, char> instr_type;

extern map<string, vector<string> > convert_pseudo;

extern map<string, string> convert_instr;

extern map<string, string> instr_opcode;

extern map<string, string> convert_reg;

#endif
