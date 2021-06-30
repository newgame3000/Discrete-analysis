#include<iostream>
#include <cstdio>
#include <vector>
#include <locale>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

struct TWord {

string Word;
unsigned long long NumberWord;
unsigned long long NumberString;

    TWord (string c, unsigned long long nw, unsigned long long ns) {
        Word = c;
        NumberWord = nw;
        NumberString = ns;
    }

    bool operator == (const TWord &a) {

        if (Word.size() != a.Word.size()) {
            return false;
        }

        for (int i = 0; i < Word.size(); ++ i) {
            if (a.Word[i] != Word[i]) {
                return false;
            }
        }
        return true;
    }

    char operator[] (unsigned long long i) {
        return Word[i];
    }

};

void ToLower (char &c) {
    if ('A' <= c && c <= 'Z') {
        c = c - 'A' + 'a';
    } 
}

void Z(vector<unsigned long long> &z, vector<TWord> &patternText) {

    unsigned long long left = 0, right = 0;
    unsigned long long count = 0;
    unsigned long long j;

    for (unsigned long long i = 1; i < patternText.size(); ++i) {

        j = i;
        if (i <= right) {
            z[i] = min(z[i - left], right - i);
            j = i + z[i];
            count += z[i];
        } 

        while ((j < patternText.size()) && (patternText[count] == patternText[j])) {
            j += 1;
            count += 1;
        }

        z[i] = count;
        if (j >= right) {
            left = i;
            right = j;
        }

        count = 0;

    }
}

int main() {
    vector<TWord> patternText;
    char c;
    string c2 = "";
    unsigned long long numberWord = 1, numberString = 0;
    unsigned long long sizeWord = 0;
    int first = 0;

    while ((c = getchar()) != EOF) {

        ToLower(c);

        if (c == ' ' && c2 == "") {
            continue;
        }

        if (c == '\n' && c2 == "") {
            if (first == 0) {
                first = 1;
                c2 = "$";
                patternText.push_back({c2, 0, 0});
                c2 = "";
            } 
            numberString += 1;
            numberWord = 1;
            continue;
        }

        if ((c == ' ') && (c2 != "")) {
            patternText.push_back({c2, numberWord, numberString});
            c2 = "";
            if (first == 0) {
                sizeWord += 1;
            } else {
                numberWord += 1;
            }
        }

        if ((c == '\n') && (c2 != "")) {
            if (first == 0) {
                patternText.push_back({c2, 0, 0});
                c2 = "";
                sizeWord += 1;
                c2 = "$";
                patternText.push_back({c2, 0, 0});
                c2 = "";
                first = 1;
                numberString += 1;
            } else {
                patternText.push_back({c2, numberWord, numberString});
                c2 = "";
                numberString += 1;
                numberWord = 1; 
            }
        }

        if ((c != EOF) && (c != '\n') && (c != ' ')) {
            c2 += c;
        }
    } 

    if (c2 != "") {
        patternText.push_back({c2, numberWord, numberString});  
        c2 = "";
    }

    if (sizeWord == 0) {
        return 0;
    }

    if (patternText.size() == sizeWord + 1) {
        return 0;
    }

    vector<unsigned long long> z(patternText.size());
    Z(z,patternText);

    for (unsigned long long i = sizeWord + 1; i < patternText.size() ; ++i) {
        if (z[i] == sizeWord) {
            printf("%llu, %llu\n", (patternText[i]).NumberString, (patternText[i]).NumberWord);
        }
    }
}