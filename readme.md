# 🤖 Hybrid FAQ Engine (C++ + Python)

This project is a **high-performance AI-based FAQ engine** that allows users to upload their FAQ dataset (`.csv`, `.json`, `.py`), ask natural language questions, and receive relevant answers with **auto-generated tags**.

It uses:
- ⚙️ **C++** for efficient TF-IDF, cosine similarity, and tagging (via Pybind11)
- 🐍 **Python (Flask)** for frontend and orchestration
- 🌐 **Web UI** for uploading FAQs and querying
- 🧠 Future-ready for sentence embeddings / LLM integration

---

## 🚀 Features

- Upload FAQs from `.csv`, `.json`, or `.py` files
- Ask natural language queries
- Get the most relevant FAQ using TF-IDF + Cosine similarity
- Auto-generate 3 tags per query
- Responsive dark mode UI

---

## 📁 Project Structure
```bash
FAQS/
├── cpp/
│ ├── binding.cpp # Pybind11 bindings
│ ├── preprocessor.cpp/hpp
│ ├── tf_idf.cpp/hpp
│ ├── similarity.cpp/hpp
│ ├── tagger.cpp/hpp
│ └── (build output) ➜ ../build/faqengine.pyd
│
├── python/
│ ├── app.py # Flask Web App
│ ├── inference.py # Handles FAQ search and tagging
│ ├── templates/
│ │ └── index.html # Frontend UI
│ ├── static/ # CSS, JS
│ └── test_faq.py # CLI-based test
│
├── data/
│ ├── faqs.csv # Sample 40 FAQs
│ └── faqs.json # Same in JSON format
│
├── build/ # Pybind11 compiled module (.pyd)
│
├── .gitignore
└── README.md

```
---

## 🛠️ Setup Instructions

### 1. Clone the repo

```bash
git clone https://github.com/your-username/faqengine.git
cd smartFaq
```

## 2. 🧱 Compile C++ with Pybind11
Ensure you have:

Python 3.11+

MSYS2 (with g++ 15+)

Pybind11 installed (pip install pybind11)

Run in MSYS2 UCRT64 terminal:
```bash
cd cpp
g++ -O3 -Wall -shared -std=c++17 -fPIC \
binding.cpp preprocessor.cpp tf_idf.cpp similarity.cpp tagger.cpp \
-I"/c/Users/YOURNAME/AppData/Local/Programs/Python/Python311/include" \
-I"/c/Users/YOURNAME/AppData/Local/Programs/Python/Python311/Lib/site-packages/pybind11/include" \
-L"/c/Users/YOURNAME/AppData/Local/Programs/Python/Python311/libs" \
-lpython311 -o ../build/faqengine.pyd
```
## 3. 🧪 Test the CLI version
```bash
cd ../python
python test_faq.py
```
##4. 🌐 Launch the Flask App
```bash
Copy
Edit
pip install flask
python app.py
```
