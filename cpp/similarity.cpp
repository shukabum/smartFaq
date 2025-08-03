#include "similarity.hpp"
#include<cmath>

using namespace std;

double SimilarityEngine::cosine_similarity(
    const unordered_map<string,double>& vec1,
    const unordered_map<string,double>& vec2
){
    double dot = 0.0, mag1 = 0.0, mag2= 0.0;

    for(const auto& item:vec1){
        dot+=item.second*(vec2.count(item.first)?vec2.at(item.first):0.0);
        mag1+= item.second*item.second;
    }
    for(const auto& item :vec2 ){
        mag2 +=item.second*item.second;
    }

    if(mag1==0||mag2==0) return 0.0;
    
    return dot/(sqrt(mag1)* sqrt(mag2));
}

pair<int, double> SimilarityEngine::find_most_similar(
    const unordered_map<string,double>& query_vec,
    const vector<unordered_map<string,double>>& doc_vecs
){
    int best_index = -1;
    double best_score = 0.0;
    for( size_t i=0;i<doc_vecs.size();++i){
        double score = cosine_similarity(query_vec,doc_vecs[i]);
        if(score>best_score){
            best_score = score;
            best_index = i;
        }
    }
    return {best_index, best_score};
}