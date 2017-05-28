

/*
 * Arthur Feeney
 * Pledged. This assignment is entirely my own work! :o
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <bitset>

#include "assemble.h"

using std::string;
using std::ifstream;

int main(void) {

    /*
     * Some of my design decisions with this are REALLY bad...
     * And it's kind of incomplete.
     */
    
    // examples files are as.s and starter.s
    string fileName = "as.s";
    ifstream strm(fileName);
    assemble(strm); // assembles the file stream.
    strm.close();
    return 0;
}
