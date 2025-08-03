#include<pybind11/pybind11.h>
#include<pybind11/stl.h>
#include<mutex>
#include<cstring>
#include"preprocessor.hpp"
#include"tf_idf.hpp"
#include"similarity.hpp"
#include"tagger.hpp"

namespace py = pybind11;

PYBIND11_MODULE (faqengine,m){
    m.doc() = "Hybrid c++ FAQ Engine expose to python";

    py::class_<Preprocessor>(m,"Prepocessor").def(py::init<>()).def("preprocess",&Preprocessor::preprocess);
    
    py::class_<TFIDFVectorizer>(m,"TFIDFVectorizer").def(py::init<>()).def("fit",&TFIDFVectorizer::fit).def("transform",&TFIDFVectorizer::transform);

    py::class_<SimilarityEngine>(m,"SimilarityEngine").def(py::init<>()).def("cosine_similarity",&SimilarityEngine::cosine_similarity).def("find_most_similar",&SimilarityEngine::find_most_similar);

    py::class_<Tagger>(m,"Tagger").def(py::init<>()).def("generate_tags",&Tagger::generate_tags);

}
