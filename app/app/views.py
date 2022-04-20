from app import app
from flask import render_template

@app.route("/")
def index():
    return render_template("public/index.html")
    
@app.route("/docs/<path:path>")
def docs(path):
    return render_template("public/docs/" + path + "/index.html")
    