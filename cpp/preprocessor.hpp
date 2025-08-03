#ifndef PREPROCESSOR_HPP
#define PREPROCESSOR_HPP


#include<string>
#include<vector>
#include<unordered_set>
using namespace std;

class Preprocessor{
    public:
    Preprocessor();
    vector<string>preprocess(const string& text);
    private:
    unordered_set<string> stop_words;
    string to_lowercase(const string& text);
    string remove_punctuation(const string& text);
    vector<string>tokenize(const string& text);
    vector<string> remove_stop_words(const vector<string>& tokens);;
};

#endif 