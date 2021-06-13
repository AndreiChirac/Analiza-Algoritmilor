#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
#include <string>
#include <vector>
#include <fstream>
#include "Aho_Corasick.h"
#include "BoyerMoore.h"
#include "KMP.h"
#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

int main()
{

    string text;
    string pattern;
    int nr = 0;
    int total = 0 ;

    string infilename;
    string outfilename;
    string outfilename2;

    std::vector<int> index;
    std::vector<int> occurenceindex;
    std::map <string, vector<string>> occurencemap;

    for(int i = 0 ; i <= 9 ; i++){

        infilename = "in/BoyerMoore/Test" + std::to_string(i) + ".in";
        outfilename = "out/BoyerMoore/Test" + std::to_string(i) + ".out";
        std::ifstream infile(infilename.c_str());

        string parser;
        int ok = 0;
        while(getline(infile,parser)){
            if(ok == 0)
                pattern = parser;
            else if(ok == 1)
                text = parser;
            ok++;
        }
        infile.close();

        auto start = high_resolution_clock::now();
        index = BoyerMoore(text,pattern);
        auto stop = high_resolution_clock::now();
        std::ofstream outfile(outfilename.c_str());

        if(index.size() == 0 )
            outfile << "Pattern was not found !";
        else
            for(int i= 0 ; (unsigned)i < index.size() ;i++){
                if( i == 0 )
                    outfile<< "Found at index : " << index[i] << " ";
                else
                    outfile<< index[i] << " ";
            }
        auto duration = duration_cast<microseconds>(stop - start);
        outfile<< "\n" << "Time taken by function: " << duration.count() << " microseconds" << endl;
        outfile.close();
    }

    for(int i = 0 ; i <= 9 ; i++){

        infilename = "in/AhoChorasick/Test" + std::to_string(i) + ".in";
        outfilename = "out/AhoChorasick/Test" + std::to_string(i) + ".out";
        outfilename2 = "out/KMP/Test" + std::to_string(i) + ".out";
        std::ifstream infile(infilename.c_str());

        string parser;
        int ok = 0;

        while(getline(infile,parser)){
            if(ok == 0)
                nr = std::stoi(parser);
            else if(ok == 1)
                pattern = parser;
            else if (ok == 2)
                text = parser;
            ok++;
        }


        string arr[nr];
        stringstream ssin(pattern);
        int cnt = 0;
        while (ssin.good() && cnt< nr){
            ssin >> arr[cnt];
            ++cnt;
        }

        int length = sizeof(arr)/sizeof(arr[0]);
        auto start = high_resolution_clock::now();
        occurencemap = Aho_Corasick(arr,length,text);
        auto stop = high_resolution_clock::now();

        std::ofstream outfile(outfilename.c_str());
        if(occurencemap.empty())
            outfile << "None of the patterns were found !";
        else
            for (map<string, vector<string>>::iterator it = occurencemap.begin(); it != occurencemap.end(); it++ ){
                    outfile << it->first << ':';
                    for(int i = 0 ; (unsigned)i < it->second.size() ; i++)
                                outfile << it->second[i] << " ";
                    outfile << std::endl;
            }
        auto duration = duration_cast<microseconds>(stop - start);
        outfile<< "Time taken by function: " << duration.count() << " microseconds" << endl;

        outfile.close();

        std::ofstream outfile2(outfilename2.c_str());
        for(int i = 0 ; i < length ; i++){
            auto start = high_resolution_clock::now();
            occurenceindex = KMP(arr[i],text);
            auto stop = high_resolution_clock::now();

            auto duration = duration_cast<microseconds>(stop - start);
            total = total + duration.count();

            if(index.size() == 0 )
                outfile2 << "Pattern was not found !";
            else
                for(int j= 0 ; (unsigned)j < occurenceindex.size() ;j++){
                    if( j == 0 )
                        outfile2<< "Found "<< arr[i] <<" at index : " << occurenceindex[j] << " ";
                    else
                        outfile2<< occurenceindex[j] << " ";
                }
            outfile2<< "\n";
        }

        outfile2<< "\n"<<"Total time taken: " << total << " microseconds" << endl;
        outfile2.close();

    }

    return 0;
}
