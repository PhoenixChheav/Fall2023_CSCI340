#include "wordcount.h"

#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;

WordCount::WordCount(int sz) {
    // COMPLETE
    tableSize = sz; 
    hashTable.resize(sz);
}

int WordCount::hash(string s) {
    int val = hashFunction(s);
    int bounds = (val % tableSize + tableSize) % tableSize;
    return bounds;
}

int WordCount::count(string word) {
    // COMPLETE
    int value = hash(word);
    auto i = std::find_if(hashTable[value].begin(), hashTable[value].end(), 
    [&word](const auto &element) {
        return element.first == word;
    });

    if(i != hashTable[value].end()){
        return i->second;
    }
    return 0; // not correct
}

void WordCount::add(string word) {
    if (count(word) > 0) {
        find_if(hashTable[hash(word)].begin(), hashTable[hash(word)].end(), 
        [&word](auto &element) {
            if (element.first == word){
                element.second++;
                return true;
            }
            else{
                return false;
            }
        });
        
    }
    else {
        hashTable[hash(word)].push_back(std::make_pair(word, 1));
    }
}

void WordCount::print() {
    std::vector<std::pair<string, int>> words;
    for (auto entry: hashTable)
        for (auto pair: entry)
            words.push_back(pair);
    sort(words.begin(), words.end());
    for (auto pair: words)
        std::cout << pair.first << ": " << pair.second << std::endl;
}

void printFileWordCount(string filename, int tableSize) {
    ifstream file(filename);
    WordCount wc(tableSize);
    string word;
    while (file >> word){
        word.erase(find_if(word.begin(), word.end(), [](char c) { return !isalpha(c); } ), word.end());
        for(auto it = word.begin(); it != word.end(); it++){
            *it = tolower(*it);
        }
        wc.add(word);
    } 
    wc.print();
}