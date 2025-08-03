#include<iostream>
#include"preprocessor.hpp"
#include "tf_idf.hpp"
#include "similarity.hpp"
#include "tagger.hpp"

using namespace std;

int main(){
    Preprocessor pre;
    TFIDFVectorizer vectorizer;
    SimilarityEngine sim;
    Tagger tagger;

    vector<string> doc1 = pre.preprocess("How do i reset my password ?");
    vector<string> doc2 = pre.preprocess("How do i change my email address ? ");
    vector<string> doc3 = pre.preprocess("What is the best feature of fasthelpseries and fastanswers");
    vector<string> doc4 = pre.preprocess("What is the fastanswer");
    vector<vector<string>> corpus = {doc1,doc2,doc3,doc4};
    
    vector<string> raw_corpus = {
        "How do i reset my password ?",
        "How do i change my email address ? ",
        "What is the best feature of fasthelpseries and fastanswers",
        "What is the fastanswer"
    };

    vectorizer.fit(corpus);
    
    vector<unordered_map<string,double>>doc_vectors;
    for(const auto& doc:corpus){
        doc_vectors.push_back(vectorizer.transform(doc));
    }
    
    string query= "What is the fast ";
    vector<string> processed_query  = pre.preprocess(query);
    auto query_vec = vectorizer.transform(processed_query);
    
    auto tags = tagger.generate_tags(query_vec);
    cout<<"\nGenerated Tags: \n";
    for(const auto & tag:tags){
        
        cout<<"- "<<tag<<endl;
    } 

    int best_match_index = sim.find_most_similar(query_vec,doc_vectors).first;
    
    cout<<"\nQuery:"<<query<<endl;
    if(best_match_index!=-1){
        cout<<"Best matching FAQ: "<< raw_corpus[best_match_index]<<endl;
    }else{
        cout<<"no similar FAQ found"<<endl;
    }
    return 0;
}