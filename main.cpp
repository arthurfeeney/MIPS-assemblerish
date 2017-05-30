

/*
 * Arthur Feeney
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <bitset>

#include "assemble.h"

using std::string;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::cin;

int main(void)
{
    // examples files are as.s and starter.s

    string fileName;
    cout << "enter a file name: ";
    cin >> fileName;

    ifstream strm(fileName);
    ofstream out("output.txt");
    if(assemble(strm, out))
    {
        cout << "assembling successful!" << '\n';
    }
    else
    {
        cout << "assembling failed." << '\n';
    }

    strm.close();
    out.close();
    return 0;
}
