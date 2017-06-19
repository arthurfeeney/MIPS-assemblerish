
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <utility>
#include <algorithm>
#include <boost/algorithm/string.hpp>

#include "parse.h"

using std::vector;
using std::string;
using std::ifstream;
using std::map;
using std::make_pair;
using std::swap;

static map<string, int> labels; //saves the locations of the labels.

map<string, int> get_labels() { return labels; }

//simple parse for the file.
vector< vector< string > >
parse_file(ifstream& file) {
    vector< vector< string > > lines(0);
    int index = 0;
    for(string line; std::getline(file, line); ) 
    {
        // remove comments
        for(auto iter = line.begin(); iter != line.end(); )
            if(*iter == '#') line.erase(iter, line.end());
            else ++iter;
        // check if line has a label, then save its index
        if(is_label(line)) 
        {
            auto iter = line.begin();
            while(*iter != ':') ++iter;
            string label(line.begin(), iter);
            labels.insert(labels.end(), make_pair(label, index));
            line.erase(line.begin(), iter + 1);
        }
        
        //remove tabs and spaces from the front of line.
        auto iter = line.begin();
        while(*iter == '\t' || *iter == ' ') ++iter;
        line.erase(line.begin(), iter);
        
        //parses if anything exists on the line.
        if(line.size() > 0) 
        {
            lines.push_back( parse_line(line) );
            ++index;
        }
    }
    return lines;
}

//parses a line of the input file.
static vector<string> parse_line(string& line)
{
    vector<string> splitLine;
    // change '(' to ',' and remove ')'. 
    for(auto iter = line.begin(); iter != line.end(); )
    {
        if(*iter == '(')
        {
            iter = line.erase(iter);
            line.insert(iter, ',');
        }
        else if(*iter == ')') iter = line.erase(iter);
        else ++iter;
    }
    // splits line on tabs, spaces, and commas.
    boost::split(splitLine, line, boost::is_any_of("\t ,")); 
    //removes empty parts from splitLine.
    for(auto iter = splitLine.begin(); iter != splitLine.end(); )
        if(*iter == "\0") iter = splitLine.erase(iter);
        else ++iter;
    return splitLine;
}

//if there is a colon, line has a label. Already removed comments.
static bool is_label(const string& line) {
    return boost::contains(line, ":");
}
