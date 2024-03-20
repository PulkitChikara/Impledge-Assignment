#include <iostream>
#include <fstream>
#include <chrono>
#include<bits/stdc++.h>

using namespace std;

struct TrieNode {
    TrieNode* children[26];
    bool EndOfWord;
    TrieNode() {
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
        EndOfWord = false;
    }
};


void insertWord(TrieNode* root, const string& word) {  // Function to insert a word into the Trie
    TrieNode* node = root;
    for (char c : word) {
        int index = c - 'a';
        if (node->children[index] == nullptr) {
            node->children[index] = new TrieNode();
        }
        node = node->children[index];
    }
    node->EndOfWord = true;
}

bool isWordInTrie(TrieNode* root, const string& word) {   // Function to check if a word is present in the Trie
    TrieNode* node = root;
    for (char c : word) {
        int index = c - 'a';
        if (node->children[index] == nullptr) {
            return false;
        }
        node = node->children[index];
    }
    return node->EndOfWord;
}

bool isCompoundWord(const string& word, TrieNode* root, unordered_set<string>& compoundSet, unordered_map<string, bool>& memo) {
    if (word.length() == 0) {
        return true;
    }

    if (compoundSet.find(word) != compoundSet.end()) {
        return true;
    }

    if (memo.find(word) != memo.end()) {
        return memo[word];
    }

    for (int i = 1; i < word.length(); i++) {
        string prefix = word.substr(0, i);
        string suffix = word.substr(i);

        if (isWordInTrie(root, prefix) &&
            (isWordInTrie(root, suffix) || isCompoundWord(suffix, root, compoundSet, memo))) {
            compoundSet.insert(word);
            memo[word] = true;
            return true;
        }
    }

    memo[word] = false;
    return false;
}

vector<string> readFromFile(string filename) {
    vector<string> words;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        words.push_back(line);
    }
    file.close();
    return words;
}

int main() {
    auto start = chrono::steady_clock::now();
    vector<string> words = readFromFile("Input_02.txt");
    TrieNode* root = new TrieNode();
    unordered_set<string> compoundSet;
    unordered_map<string, bool> memo;
    unordered_map<int, vector<string>> compoundWordsByLen;

  
    for (const string& word : words) {   // Insert words into the Trie
        insertWord(root, word);
    }
   
    for (const string& word : words) {   // Find compound words
        isCompoundWord(word, root, compoundSet, memo);
    }

    for (const string& word : compoundSet) {        // Store compound words by length in a map
        compoundWordsByLen[word.length()].push_back(word);
    }

    vector<pair<int, vector<string>>> sortedCompoundWords;
    for (const auto& pair : compoundWordsByLen) {  
        sortedCompoundWords.emplace_back(pair.first, pair.second);
    }

    sort(sortedCompoundWords.begin(), sortedCompoundWords.end(), [](const pair<int, vector<string>>& a, const pair<int, vector<string>>& b) {
        if (a.first == b.first) {
            return a.second < b.second;
        }
        return a.first > b.first;
    });

    auto end = chrono::steady_clock::now();
    auto timeTaken = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    cout << "Longest Compound Word: " << sortedCompoundWords[0].second[0] << endl;
    cout << "Second Longest Compound Word: " << (sortedCompoundWords.size() > 1 && sortedCompoundWords[0].second.size() > 1 ? sortedCompoundWords[0].second[1] : (sortedCompoundWords.size() > 1 ? sortedCompoundWords[1].second[0] : "")) << endl;
    cout << "Time taken to process file Input_02.txt: " << timeTaken << " milliseconds" << endl;

    return 0;
}