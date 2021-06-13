#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
#include <vector>
#include <bits/stdc++.h>
using namespace std;
//nuamrul maxim de noduri
const int maximumnodes = 3000;
//numarul maxim de caractere
const int maxcharacter = 3000;

int out[maximumnodes];

int f[maximumnodes];

int g[maximumnodes][maxcharacter];

int AutonomBuilder(string dictionaryofwards[] , int numberofwords){

    memset(out,0,sizeof out);
    memset(g,-1,sizeof g);

    int conditions = 1 ;
    //Se realziaeaza constructia Trie ului
    for(int i = 0 ; i < numberofwords ; i++){

        const string &wordtofind = dictionaryofwards[i];
        int currentcondition = 0;
        // Se insereaza toate literele cuvantului respectiv in trie
        for(int j = 0 ; (unsigned)j < wordtofind.size() ; j++){

            int ch = wordtofind[j] - 'a';

            if(g[currentcondition][ch] == -1){
                g[currentcondition][ch] = conditions++;
            }

            currentcondition = g[currentcondition][ch];

        }
        //Se adauga cuvantul in output
        out[currentcondition] |= (1<<i);
    }
    //Penru toate caracterele care nu au o munchie catre root , se adauga o munchie catre el insusi
    for(int ch = 0 ; ch < maxcharacter ; ch++)
        if(g[0][ch] == -1)
            g[0][ch] = 0;

    memset(f,-1,sizeof f);
    queue<int> intqueue;

    //Toate nodurile care au inaltimea 1 trebuie sa contina valoarea functiei failure 1
    for(int ch = 0 ; ch < maxcharacter ; ch++){
        if(g[0][ch] != 0){
            f[g[0][ch]] = 0;
            intqueue.push(g[0][ch]);
        }
    }

    while(intqueue.size()){
        int condition = intqueue.front();
        //se face pop la ce se afla coada
        intqueue.pop();
        /*Pentru conditia care a fost selectata anterior , se gaseste functia failure pentru
          taote caracterele pentru care functia goto nu este definita
        */
        for(int ch = 0; ch <= maxcharacter ; ch ++){
            if(g[condition][ch] != -1){
                int fail = f[condition];
                /*
                    Pentru stringul memorat in nodurile care incep la radacina si se termina
                    la condition se cauta sufixul care este prefixul unui altui cuvant din dictionar
                    Daca acest caz nu se remarca failure va avea valoarea 0
                */
                while(g[fail][ch] == -1)
                    fail = f[fail];
                fail = g[fail][ch];
                f[g[condition][ch]] = fail;

                out[g[condition][ch]] |= out[fail];
                // se insereaza urmatorul nod pentru a fi posibila calcularea funciei failure
                intqueue.push(g[condition][ch]);
            }
        }
    }
    return conditions;
}

int findNextCondition(int currentcondition ,char nextchar){
    int ok = currentcondition;
    int ch = nextchar -'a';

    while(g[ok][ch] == -1)
        ok = f[ok];
    return g[ok][ch];
}

map <string, vector<string>> Aho_Corasick(string dictionary[], int length , string text)
{
    AutonomBuilder(dictionary,length);

    int currentcondition = 0 ;
    map<string,vector<string>> occurencemap;
    string convertor;

    for(int i = 0 ; (unsigned)i < text.size() ; i++){
        currentcondition = findNextCondition(currentcondition,text[i]);

        if(out[currentcondition] == 0)
            continue;

        for(int j = 0  ; j < length ; j++){
            if(out[currentcondition] & (1<<j) ){
            //se retine in map de unde pana unde se regaseste cuvantul in text
            convertor = "appears from " + to_string(i - dictionary[j].size() + 1) + " to " + to_string(i) ;
            occurencemap[dictionary[j]].push_back(convertor);
            }
        }
    }
    return occurencemap;
}
