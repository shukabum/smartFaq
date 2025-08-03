import sys
import os
import csv
import json

# Add the build directory to Python path
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "../build")))

import faqengine
import importlib.util

class FAQEngine:
    def __init__(self, faq_list):
        self.preprocessor = faqengine.Prepocessor()
        self.vectorizer = faqengine.TFIDFVectorizer()
        self.similarity = faqengine.SimilarityEngine()
        self.tagger = faqengine.Tagger()

        self.raw_faqs = faq_list
        self.tokenized = [self.preprocessor.preprocess(faq) for faq in faq_list]
        self.vectorizer.fit(self.tokenized)
        self.vectors = [self.vectorizer.transform(t) for t in self.tokenized]

    def answer_query(self, query):
        query_tokens = self.preprocessor.preprocess(query)
        query_vector = self.vectorizer.transform(query_tokens)
        index, score = self.similarity.find_most_similar(query_vector, self.vectors)

        if score < 0.2:
            return "No relevant FAQ found", []
        return self.raw_faqs[index], self.tagger.generate_tags(query_vector, 3)

def load_faqs_from_file(filepath):
    ext = os.path.splitext(filepath)[1].lower()
    if ext == ".py":
        return load_faqs_from_py(filepath)
    elif ext == ".csv":
        return load_faqs_from_csv(filepath)
    elif ext == ".json":
        return load_faqs_from_json(filepath)
    else:
        raise ValueError("Unsupported file type")

def load_faqs_from_csv(filepath):
    with open(filepath, encoding="utf-8") as f:
        reader = csv.reader(f)
        return [row[0] for row in reader if row]

def load_faqs_from_json(filepath):
    with open(filepath, encoding="utf-8") as f:
        data = json.load(f)
        return data["faqs"] if "faqs" in data else data  # accepts both dict or list

def load_faqs_from_py(filepath):
    spec = importlib.util.spec_from_file_location("data", filepath)
    data = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(data)
    return data.faqs
