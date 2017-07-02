
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <map>

#ifndef PARSE_H
#define PARSE_H

extern std::map<std::string, int> labels;
extern std::map<std::string, std::vector<int>> words;
extern std::map<std::string, std::vector<char>> asciis;
extern std::map<std::string, std::vector<double>> floats;

std::vector< std::vector< std::string > >
parse_file(std::ifstream& file);

std::map<std::string, int> get_labels();

std::map<std::string, std::vector<int>>& get_words();
std::map<std::string, std::vector<char>>& get_asciis();
std::map<std::string, std::vector<double>>& get_floats();

static std::vector<std::string>
parse_line(std::string& line);

static bool is_label(const std::string& line);

static bool is_data(const std::string& line);

static void parse_data(std::string& line, const int index);

#endif
