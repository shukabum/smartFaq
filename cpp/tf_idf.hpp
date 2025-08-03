#ifndef TFIDF_HPP
#define TFIDF_HPP

#include<vector>
#include<string>
#include<unordered_map>
#include<unordered_set>

using namespace std;

class TFIDFVectorizer{
    public:
    void fit(const vector<vector<string>>& corpus);
    unordered_map<string,double> transform(const vector<string>& doc)const;

    private:
    unordered_map<string,double> idf_scores;
    unordered_set<string> vocabulary;
    int corpus_size =0;
};

#endif