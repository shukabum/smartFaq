#ifndef SIMILARITY_HPP
#define SIMILARITY_HPP

#include<vector>
#include<string>
#include<unordered_map>
using namespace std;

class SimilarityEngine{
    public:
    pair<int, double> find_most_similar(
        const unordered_map<string,double>& query_vec,
        const vector<unordered_map<string,double>>& doc_vecs
    );

    double cosine_similarity(
        const unordered_map<string,double>& vec1,
        const unordered_map<string,double>& vec2
    );
};


#endif