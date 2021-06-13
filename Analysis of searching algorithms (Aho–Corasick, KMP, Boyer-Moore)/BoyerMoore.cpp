#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;

map<char,int> preprocessOfTabelShifts(string pattern ){


    int length = pattern.length();
    /*se construieste un map in care vom tine litera si daca
    nu este match de cate ori trebuie sa se realizeze siftarea
    */
    map<char,int> shifttable;

    for(int i = 0 ; i < length ; i++){
        //se preia in variabila character fiecare litera din pattern
        char character =  pattern.at(i);
        /*se determina numarul cu care trebuie sa se sifteze patternul
        la dreapta corespunzator literei*/
        int maxshift = max(1,length-i-1);
        /*dr pune in map perechia corespunzatoare daca aceasta a mai fost
        prezenta valoarea numarului cu care se sifteaza este modificat */
        shifttable[character] = maxshift;

    }
    return shifttable;
}

vector<int> BoyerMoore(string text , string pattern )
{
    int textsize = text.length();
    int patternsize = pattern.length();
    map<char,int> shifttabel = preprocessOfTabelShifts(pattern);
    std::vector<int> index;
    int skips = 0;

    //incepem parcurgerea textului in care cautam patternul
    for(int i = 0 ; i<= textsize - patternsize ; i+= skips ){

        skips = 0;
        /*Stim ca aloritmul verifica de la dreapta ls stanga asa ca incepem
        cu finalul patternului*/
        for(int j = patternsize -1 ; j >= 0 ; j--){
            /*daca litera din pattern nu corespunde cu litera din text avem
            nevoie de o siftare */
            if(pattern.at(j) != text.at(i+j)){
                /*daca litera din text care a facut missmatch se regaseste in tabela
                vom avansa in text cu numarul regasit in map*/
                if( shifttabel[text.at(i+j)] != 0 ){
                    skips = shifttabel[text.at(i+j)];
                    break;
                }
                /*daca nu se afla in tabela asta inseamna ca putem pune inceputul patternului
                dupa pozitia care a facut mismatch*/
                else{
                    skips = patternsize - 1;
                    break;
                }

            }

        }
        //s-a gasit patternul in text asa ca salvam indexul si trecem mai departe
        if(skips == 0){
            index.push_back(i);
            skips = 1;
        }
    }
    return index;
}
