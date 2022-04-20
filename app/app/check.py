import os
import subprocess
from unittest import result
from flask import Flask, flash, request, redirect, url_for
from werkzeug.utils import secure_filename
from ansi2html import Ansi2HTMLConverter
from flask import render_template
from app import app

UPLOAD_FOLDER = './uploads'
ALLOWED_EXTENSIONS = {'txt', 'pdf', 'png', 'jpg', 'jpeg', 'gif', 'c'}
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

from flask import send_from_directory

@app.route('/uploads/<name>')
def download_file(name):
    return send_from_directory(app.config["UPLOAD_FOLDER"], name)

app.add_url_rule(
    "/uploads/<name>", endpoint="download_file", build_only=True
)

@app.route('/check', methods=['GET', 'POST'])
def upload_file():
    if request.method == 'POST':
        # check if the post request has the file part
        if 'file' not in request.files:
            flash('No file part')
            return redirect(request.url)
        file = request.files['file']
        # If the user does not select a file, the browser submits an
        # empty file without a filename.
        if file.filename == '':
            flash('No selected file')
            return redirect(request.url)
        if file and allowed_file(file.filename):
            filename = secure_filename(file.filename)
            file.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))
            return Ansi2HTMLConverter(dark_bg = False).convert(subprocess.run(['unixTaskbook', '-t', './uploads/'+filename], stdout=subprocess.PIPE).stdout.decode('utf-8')).replace('background-color: #AAAAAA', 'background-color: #FFFFFF')
    return render_template("public/check/index.html")