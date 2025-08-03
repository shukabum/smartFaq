#include "tf_idf.hpp"
#include <cmath>
#include<unordered_set>

using namespace std;

void TFIDFVectorizer::fit(const vector<vector<string>>& corpus){
    corpus_size = corpus.size();
    unordered_map<string,int> doc_freq;
    for(const auto& doc:corpus){
        unordered_set<string>seen;
        for(const auto& word:doc){
            if(!seen.count(word)){
                doc_freq[word]++;
                seen.insert(word);
            }
            vocabulary.insert(word);
        }

    }
    for(const auto& item:doc_freq){
        idf_scores[item.first]= log((double)corpus_size/1+item.second);
    }

}

unordered_map<string,double>TFIDFVectorizer::transform(const vector<string>& doc)const {
    unordered_map<string,int>tf;
    for(const auto& word:doc){
        tf[word]++;
    }

    unordered_map<string,double>tfidf;
    for(const auto& item:tf){
        double tf_score = (double) item.second/doc.size();
        double idf_score = idf_scores.count(item.first) ? idf_scores.at(item.first):log((double)corpus_size +1); 
        tfidf[item.first] =tf_score* idf_score;
    }

    return tfidf;
}

