
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <map>

#ifndef PARSE_H
#define PARSE_H

std::vector< std::vector< std::string > >
parse_file(std::ifstream& file);

extern std::map<std::string, int> get_labels();

static std::vector<std::string>
parse_line(std::string& line);

static bool is_label(const std::string& line);

static bool is_data(const std::string& line);

static void parse_data(const std::string& line, const int index);


#endif
