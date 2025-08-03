#include "tagger.hpp"
#include<algorithm>

using namespace std;

vector<string>Tagger::generate_tags(
    const unordered_map<string, double>& tfidf_vec,
    int top_k
){
    vector<pair<string,double>> vec(tfidf_vec.begin(),tfidf_vec.end());
    sort(vec.begin(),vec.end(),[](const auto& a,const auto& b){
        return a.second>b.second; //descending order
    });
    vector<string>tags;
    for(size_t i = 0; i < static_cast<size_t>(top_k) && i < vec.size(); ++i){
        tags.push_back(vec[i].first);
    }
    return tags;
}