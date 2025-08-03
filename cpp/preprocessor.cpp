#include "preprocessor.hpp"
#include<algorithm>
#include<cctype>
#include<sstream>

using namespace std;

Preprocessor::Preprocessor(){
    stop_words={"a","an","the","and","or","but","if","in","on","with","as","at","by","for","from","of","to","up","down","out","over","under","again","against","along","among","around","before","behind","below","beside","between","beyond","during","except","following","inside","into","near","off","on","onto","outside","since","through","throughout","till","toward","under","until","up","via","within","without","how","can","i","you","my","your","what","is"};
}


string Preprocessor::to_lowercase(const string& text){
    string  result =text;
    transform(result.begin(),result.end(),result.begin(),[](unsigned char c ){ return std::tolower(c);});

    return result;
}

string Preprocessor::remove_punctuation(const string& text){
    string result;
    for(char c : text){
        if(!ispunct(c)) result +=c;
    }
    return result;
}

vector<string> Preprocessor::tokenize(const string& text){
    istringstream iss(text);
    vector<string>tokens;
    string word;
    while(iss>>word){
        tokens.push_back(word);
    }
    return tokens;
}

vector<string> Preprocessor::remove_stop_words(const vector<string>& tokens){
    vector<string>filtered;
    for(const auto& word:tokens){
        if(stop_words.find(word)==stop_words.end()){
            filtered.push_back(word);
        }
    }
    return filtered;

}
vector<string> Preprocessor::preprocess(const string& text){
    string clean =  remove_punctuation(to_lowercase(text));
    auto tokens = tokenize(clean);
    return remove_stop_words(tokens);
}