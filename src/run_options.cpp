
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <fstream>

#include "run_options.h"

using std::vector;
using std::string;
using std::ifstream;

vector<string> parse_options(string input) {
    vector<string> split_input;
    boost::split(split_input, input, boost::is_any_of(" "));
    return split_input;
}

ifstream load_file(string file_name) {
    return ifstream(file_name);
}

