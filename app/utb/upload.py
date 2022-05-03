
from dataclasses import fields
from fileinput import filename
from mimetypes import init
import subprocess
from django.shortcuts import render, redirect
from .models import File
from .forms import FileUploadModelForm
from django.http import HttpResponse
from ansi2html import Ansi2HTMLConverter
from django.views.decorators.csrf import csrf_protect
from django.contrib.auth.decorators import login_required
from django.utils import timezone


# Create your views here.
# Upload File with ModelForm
@login_required
@csrf_protect
def model_form_upload(request):
    if request.method == "POST":
        form = FileUploadModelForm(request.POST, request.FILES)
        if form.is_valid():
            if not (File.objects.filter(
                    filename=request.FILES['file'].name, username=request.user.username).exists()):
                file_instance = File(
                    file=request.FILES['file'], filename=request.FILES['file'].name, username=request.user.username)
            else:
                file_instance = File.objects.get(
                    filename=request.FILES['file'].name, username=request.user.username)
            file_instance.commitcount += 1
            file_instance.file = request.FILES['file']
            file_instance.modified = timezone.now()
            file_instance.save()
            return redirect("/file/")
    else:
        form = FileUploadModelForm()

    return render(request, 'utb/upload_form.html',
                  {'form': form})

# Show file list


@login_required
def file_list(request):
    files = File.objects.filter(username=request.user.username)
    return render(request, 'utb/file_list.html', {'files': files})


@login_required
@csrf_protect
def check(request):
    if request.method == "POST":
        form = FileUploadModelForm(request.POST, request.FILES)
        if form.is_valid():
            if not (File.objects.filter(
                filename=request.FILES['file'].name, username=request.user.username).exists()):
                file_instance = File(
                    file=request.FILES['file'], filename=request.FILES['file'].name, username=request.user.username)
            else:
                file_instance = File.objects.get(
                    filename=request.FILES['file'].name, username=request.user.username)
            file_instance.commitcount += 1
            file_instance.file = request.FILES['file']
            file_instance.modified = timezone.now()
            file_instance.save()
            return HttpResponse(Ansi2HTMLConverter(dark_bg=False).convert(subprocess.run(['firejail', 'unixTaskbook', '-t', './utb/media/files/' + request.user.username + '/' + request.FILES['file'].name], stdout=subprocess.PIPE).stdout.decode('utf-8')).replace('background-color: #AAAAAA', 'background-color: #FFFFFF'), content_type="text/html")
    else:
        form = FileUploadModelForm()

    return render(request, 'utb/check.html',
                  {'form': form})
