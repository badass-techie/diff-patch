# Diff-Patch

## Introduction

This project contains two programs, diff and patch, that allow one to compare two files and use the output and one of the files to produce the other file, similar to the POSIX manual descriptions. The programs are run in the shell and compare two files line by line, producing a list of differences between the files. The patch program can then use the output of the diff program and one of the original files to produce the other file.

## Algorithms

The diff program uses the Longest Common Subsequence (LCS) recursive algorithm to compare the two input files line for line and find the longest common subsequence of lines between the two sequences, which is then used to tell what lines are different between the two files.

## Code Structure

The diff program is contained in the diff.cpp file, the patch program in the patch.cpp file, and some helper functions such as the LCS algorithm in the helpers.h file. Here is a snippet of the diff program:

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

Here's a look at the patch program:

```cpp
    for (int i = diff.size()-1; i >= 0; --i){
        if (diff[i][0] == '-')  // if this line starts with - (should not be in the original file)
            diff.erase(diff.begin() + i);   // remove it
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
