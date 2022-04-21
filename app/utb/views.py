from django.shortcuts import render
from django.http import HttpResponse

def main(request):
    return render(request, "utb/main.html")

def download(request):
    return render(request, "utb/download.html")

def tasks(request, task_group_name=""):
    if task_group_name == "":
        return render(request, "utb/tasks.html")
    return render(request, "utb/tasks/" + task_group_name + ".html")