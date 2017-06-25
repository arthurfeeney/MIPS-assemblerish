
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
static map<string, vector<int>> words;
static map<string, vector<char>> asciis;
static map<string, vector<double>> floats;

map<string, int> get_labels() { return labels; }

//parse the file.
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
        
        // parse if line is data
        if(is_data(line)){
            parse_data(line, index);
            ++index;
        }
        
        // check if line has a label, if it does, save its index
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

        //parses if anything exists on the line after removals.
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

// label should have been saved earlier, so I shouldn't have to save it here.
static void parse_data(string& line, int index)
{
    string l;
    if(is_label(line))
    {
        auto iter = line.begin();
        while(*iter != ':') ++iter;
        string label(line.begin(), iter);
        labels.insert(labels.end(), make_pair(label, index));
        line.erase(line.begin(), iter + 1);
        l = label;
    }
    if(boost::contains(line, ".word"))
    {
         
        vector<string> split_line;
        boost::split(split_line, line, boost::is_any_of(","));
        vector<int> push_line(0);
        for(auto&& word : split_line)
        {
            push_line.push_back(stoi(word));     
        }
        words.insert(make_pair(l, push_line));
    }
    else if(boost::contains(line, ".asciiz"))
    {
        vector<string> split_line;
        boost::split(split_line, line, boost::is_any_of(","));
        vector<int> push_line(0);
        for(auto&& word : split_line)
        {
            push_line.push_back(stoi(word));     
        }
        words.insert(make_pair(l, push_line)); 
    }
    else if(boost::contains(line, ".float"))
    {

    }
}

//if there is a colon, line has a label. Already removed comments.
static bool is_label(const string& line) {
    return boost::contains(line, ":");
}

/*
 * If the line contains a dot, it is a piece of data.
 * This is probably wrong, but it I can't think of a way to break this off the
 * top of my head, so I'm just going to stick with it for now...
 */
static bool is_data(const string& line)
{
    return boost::contains(line,  ".");
}

