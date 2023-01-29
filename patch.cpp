#include <iostream>
#include <vector>
#include "helpers.h"

using namespace std;
using namespace helpers;

void patch(string filename1, string filename2){
    // read the lines of each file
    vector<string> s1 = read_file(filename1);
    vector<string> s2 = read_file(filename2);
    vector<string> diff;
    string original;
    bool reverse;

    // identify the diff between the two files from the header
    if (s1[0] == "--- " + filename2 || s1[1] == "+++ " + filename2){
        // s1 is the diff
        diff = vector<string>(s1.begin() + 3, s1.end());
        original = filename2;
        reverse = s1[1] == "+++ " + filename2;
    } else if (s2[0] == "--- " + filename1 || s2[1] == "+++ " + filename1){
        // s2 is the diff
        original = filename1;
        diff = vector<string>(s2.begin() + 3, s2.end());
        reverse = s2[1] == "+++ " + filename1;
    } else {
        throw invalid_argument("The files are not a diff of each other");
    }

    // apply the changes in the diff w.r.t. the original file
    for (int i = diff.size()-1; i >= 0; --i){
        if (diff[i][0] == '-' && !reverse || diff[i][0] == '+' && reverse)  // if this line should not be in the original file
            diff.erase(diff.begin() + i);   // remove it
        else
            diff[i].erase(0, 1);            // remove the 1st character (+, -, or whitespace) from the rest of the lines
    }

    // write the result to a file
    write_file(original + ".patched", diff);
    cout << "Patched file written to " << original << ".patched" << endl;
}

int main(int argc, char* argv[]){
    if (argc != 3){
        cout << "Usage: patch <filename1> <filename2>" << endl;
        return 1;
    }

    string filename1 = argv[1];
    string filename2 = argv[2];

    patch(filename1, filename2);

    return 0;
}
