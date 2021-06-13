#include "KMP.h"
#include<fstream>
#include<sstream>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>

//ps=longest proper prefix which is also a suffix
void makeLPS(std::string pattern, int m, int* lps) {
    // lungimea ultimului cel mai lung prefix care e si sufix

    int len = 0;
    lps[0] = 0;
    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                len = lps[len - 1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

std::vector<int> KMP(std::string pattern,std::string text) {

    std::vector<int> occurencearray;
    int n = text.length();
    int m = pattern.length();
    /*Lps retine date despre prefixul cel mai lung care este si sufix din
      pattern */
    int lps[m] = {0};
    makeLPS(pattern, m, lps);
    int i = 0; //index pentru text
    int j = 0; //index pentru pattern
    while (i < n) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }
        if (j == m) {
            occurencearray.push_back( i - j );
            j = lps[j - 1];
        }
        else if (i < n && pattern[j] != text[i]) {
            if (j > 0) {
                j = lps[j - 1];
            }
            else {
                i++;
            }
        }
    }

    return occurencearray;
}
