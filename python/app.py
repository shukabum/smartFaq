from flask import Flask, request, render_template
import os
from inference import FAQEngine, load_faqs_from_file

app = Flask(__name__)
app.config["UPLOAD_FOLDER"] = "uploads"

# Global instance to retain state across requests
engine = {"instance": None}
ALLOWED_EXTENSIONS = {'.py', '.csv', '.json'}

def is_allowed_file(filename):
    return os.path.splitext(filename)[1].lower() in ALLOWED_EXTENSIONS

@app.route("/", methods=["GET", "POST"])
def index():
    query=""
    result = ""
    tags = []

    if request.method == "POST":
        if "datafile" in request.files and request.files["datafile"].filename != "":
            f = request.files["datafile"]
            if not is_allowed_file(f.filename):
                result = "❌ Unsupported file type. Please upload a .py, .csv, or .json file."
            else:
                filepath = os.path.join(app.config["UPLOAD_FOLDER"], f.filename)
                f.save(filepath)
                try:
                    faqs = load_faqs_from_file(filepath)  # handles py/csv/json
                    engine["instance"] = FAQEngine(faqs)
                    result = "✅ FAQ file "+f.filename+" uploaded and processed successfully."
                except Exception as e:
                    result = f"❌ Failed to load FAQs: {e}"


        elif "query" in request.form:
            query = request.form["query"]
            if engine["instance"]:
                try:
                    result, tags = engine["instance"].answer_query(query)
                except Exception as e:
                    result = f"❌ Error processing query: {e}"
            else:
                result = "⚠️ Upload a FAQ file first."
    print("Engine is", "loaded" if engine["instance"] else "NOT loaded")
    return render_template("index.html",q=query, result=result, tags=tags)

if __name__ == "__main__":
    app.run(use_reloader=True, debug=False)
