#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<pair<string, int>> getWordCounts(vector<string>& words);
string cleanword(string word);
void getwords(vector<string> &words, ifstream &file);
void sortwords(vector<string> &words);

int main (){
    ifstream text ("homes.txt");

    if (!text.is_open()){
        cout << "Error opening file" << endl;
        return 1;
    }

    vector <string> words;
    getwords(words, text);

    text.close();

    sortwords(words);

    vector<pair<string, int>> counts = getWordCounts(words);

    for (auto& p : counts) {
        cout << p.first << " : " << p.second << endl;
    }
    
    return 0;
}


string cleanword(string word){
    string cleaned = "";
    for (char c : word){
        if (isalpha(c)){
            cleaned += tolower(c);
        }
    }
    return cleaned;
}

void getwords(vector<string> &words, ifstream &file){
 string word;

    while (file >> word) {
        string cleaned = cleanword(word);

        if (!cleaned.empty()) {   // avoid empty strings
            words.push_back(cleaned);
        }
    }
}

void sortwords(vector<string> &words){
    sort(words.begin(), words.end());
}

vector<pair<string, int>> getWordCounts(vector<string>& words) {
    vector<pair<string, int>> counts;

    if (words.empty()) return counts;

    string current = words[0];
    int count = 1;

    for (int i = 1; i < words.size(); i++) {
        if (words[i] == current) {
            count++;
        } else {
            counts.push_back({current, count});
            current = words[i];
            count = 1;
        }
    }

    counts.push_back({current, count});
    return counts;
}

