#include <iostream>
#include <vector>
#include "helpers.h"

using namespace std;
using namespace helpers;

string diff(string filename1, string filename2){
    // to begin with, add a header to the diff indicating the files being compared
    string result = "--- " + filename1 + "\n+++ " + filename2 + "\n\n";

    // read the lines of each file
    vector<string> s1 = read_file(filename1);
    vector<string> s2 = read_file(filename2);

    // find the longest common subsequence
    vector<string> sequence = lcs<string>(s1, s2);
    

    int i = 0, j = 0;
    for (string element : sequence){
        // add the lines from s1 that are not in the sequence
        while (s1[i] != element){
            result += "-" + s1[i] + "\n";
            i++;
        }
        // add the lines from s2 that are not in the sequence
        while (s2[j] != element){
            result += "+" + s2[j] + "\n";
            j++;
        }
        // add the line from the sequence
        result += " " + element + "\n";
        i++;
        j++;
    }

    // add the remaining lines from s1 and s2
    while (i < s1.size()){
        result += "-" + s1[i] + "\n";
        i++;
    }
    while (j < s2.size()){
        result += "+" + s2[j] + "\n";
        j++;
    }

    return result;
}

int main(int argc, char* argv[]){
    if (argc != 3){
        cout << "Usage: diff <filename1> <filename2>" << endl;
        return 1;
    }

    string filename1 = argv[1];
    string filename2 = argv[2];

    string result = diff(filename1, filename2);

    cout << result << endl;

    return 0;
}
