# Diff-Patch

## Table of Contents

- [Introduction](#introduction)
- [Algorithms](#algorithms)
- [Code](#code)
- [Usage](#usage)
- [Outputs](#outputs)
- [Future Work](#future-work)

## Introduction

This project contains two programs, diff and patch, that allow one to compare two files and use the output and one of the files to produce the other file, similar to the POSIX manual descriptions. The programs are run in the shell and compare two files line by line, producing a list of differences between the files. The patch program can then use the output of the diff program and one of the original files to produce the other file.

> diff, patch, unix, file, c++, recursion, algorithms

## Algorithms

The diff program uses the Longest Common Subsequence (LCS) algorithm to compare the two input files line for line and find the longest common subsequence of lines between the two sequences, which is then used to tell what lines are different between the two files.

The LCS function implements a recursive approach on two sequences a and b. The base case is when either of the two sequences is empty, in which case there is no common subsequence and an empty vector is returned. If the first elements of a and b are the same, the first element is added to the result, and the function is recursively called with the remaining elements of a and b. If the first elements are not the same, the function is called with a and the remaining elements of b, and also with b and the remaining elements of a. The longer of the two possible subsequences is returned.

```pseudo
function LCS(a, b)
    if a is empty or b is empty
        return empty vector

    if the first elements of a and b are equal
        result = LCS(a without first element, b without first element)
        add first element of a to the beginning of result
        return result

    a_ = LCS(a without first element, b)
    b_ = LCS(a, b without first element)
    if size of a_ is greater than size of b_
        return a_
    else
        return b_
```

The time complexity of the lcs function is O(2^(min(len(a), len(b)))), where len(a) and len(b) are the lengths of the sequences a and b. This is because the function performs a repeated calculation of the LCS between two sub-sequences, leading to an exponential number of calls. The space complexity is O(min(len(a), len(b))), as the function uses a recursive call stack that is proportional to the size of the smaller sequence.

I chose to use the recursive approach for this algorithm over the dynamic programming approach because it is more human-readable and intuitive. The dynamic programming approach is more efficient, but the recursive approach is still efficient enough for this application.

## Code

The diff program is contained in the diff.cpp file, the patch program in the patch.cpp file, and some helper functions such as the LCS algorithm in the helpers.h file. 

The diff function takes two sequences s1 and s2 and returns the difference between them in the form of a string with each line starting with -, +, or (whitespace) indicating if a line is removed, added, or unchanged respectively. The function starts by finding the LCS between s1 and s2. Then it traverses s1 and s2 to add the lines that are not in the LCS to the result string. Finally, it adds the remaining lines from s1 and s2 to the result.

Here is a snippet of the diff function:

```cpp
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
```

The patch function takes two files, the diff and one of the original files, and applies the changes specified in the diff with respect to the original file. It first identifies which file of the two is the diff. Then, it iterates through the diff and removes the lines that should not be in the original file, and removes the symbol character (+, -, or whitespace) from the rest of the lines. Finally, it writes the result to a new file with a ".patched" suffix.

Here's a look at the patch function:

```cpp
    // identify the diff between the two files from the header
    if (s1[0] == "--- " + filename2 || s1[1] == "+++ " + filename2){
        // s1 is the diff
        diff = vector<string>(s1.begin() + 3, s1.end());
    } else if (s2[0] == "--- " + filename1 || s2[1] == "+++ " + filename1){
        // s2 is the diff
        diff = vector<string>(s2.begin() + 3, s2.end());
    } else {
        throw invalid_argument("The files are not a diff of each other");
    }

    // apply the changes in the diff w.r.t. the original file
    for (int i = diff.size()-1; i >= 0; --i){
        if (diff[i][0] == '-')  // if this line should not be in the original file
            diff.erase(diff.begin() + i);   // remove the whole line
        else                    // for the rest of the lines   
            diff[i].erase(0, 1);            // remove the 1st character (+, -, or whitespace)
    }
```

## Usage

The diff and patch programs can be compiled with gcc or clang as shown:

```bash
g++ diff.cpp -o diff
g++ patch.cpp -o patch
```

Below is the syntax for running the programs:

```bash
./diff <filename1> <filename2>
./patch <diff_output> <filename>
```

## Outputs

Given the following files:

```text
Apple
Orange
Banana
Watermelon
Cherry
```

```text
Orange
Peach
Apple
Banana
Melon
Cherry
```

the diff program yields the following output:

```text
--- file1.txt
+++ file2.txt

+Orange
+Peach
 Apple
-Orange
 Banana
-Watermelon
+Melon
 Cherry
```

which can be redirected to a file:

```bash
./diff file1.txt file2.txt > diff_output.txt
```

The lines starting with a "-" are from the first file, the ones starting with "+" from the second file, and the rest from both.

The patch program can then use the diff output and one of the original files to produce the other file:

```bash
./patch diff_output.txt file1.txt
```

which would write a file "file1.txt.patched" with identical contents to file2.txt.

## Future Work

The diff program can be improved by using a more efficient algorithm to find the LCS, such as the Needleman-Wunsch algorithm. The patch program can be improved by allowing the user to specify the output file name.
