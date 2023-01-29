#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

namespace helpers {
    // longest common subsequence (LCS) algorithm
    // this problem involves finding the longest subsequence of elements that appear in the same order in both sequences
    // they do not have to be contiguous
    template <typename T>
    vector<T> lcs(vector<T> a, vector<T> b) {
        if (a.empty() || b.empty()) // base case (if either sequence is empty, there is no common subsequence)
            return vector<T>();

        if (a[0] == b[0]){          // if the first elements of both sequences are the same, add it to the result
            vector<T> result = lcs(vector<T>(a.begin() + 1, a.end()), vector<T>(b.begin() + 1, b.end()));
            result.insert(result.begin(), a[0]);
            return result;
        }

        vector<T> a_ = lcs(vector<T>(a.begin() + 1, a.end()), b);
        vector<T> b_ = lcs(a, vector<T>(b.begin() + 1, b.end()));
        return a_.size() > b_.size() ? a_ : b_; // otherwise return the longer of the two possible subsequences at this point
    }

    // reads a file into a vector of strings, where each string is a line of the file
    vector<string> read_file(string path){
        ifstream file(path, ios::in);
        if(file.is_open()){
            vector<string> lines;
            string line;
            while (getline(file, line))
                lines.push_back(line);
            
            file.close();
            return lines;
        }
        else {
            throw std::runtime_error("Unable to open file");
        }
    }

    // writes to a file
    void write_file(string path, vector<string> contents){
        ofstream file(path, ios::out);
        if(file.is_open()){
            for (string line : contents)
                file << line << endl;
            file.close();
        }
        else {
            throw std::runtime_error("Unable to open file");
        }
    }
};
