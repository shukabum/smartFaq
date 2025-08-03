#ifndef TAGGER_HPP
#define TAGGER_HPP

#include<vector>
#include<string>
#include<unordered_map>
using namespace std;

class Tagger{
    public:
    vector<string> generate_tags(
        const unordered_map<string, double>& tfidf_vec,
        int top_k = 3
    );
};

#endif