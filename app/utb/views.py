from django.shortcuts import render
from django.contrib.auth.forms import UserCreationForm
from django.urls import reverse_lazy
from django.views import generic


def main(request):
    return render(request, "utb/main.html")

def download(request):
    return render(request, "utb/download.html")

def tasks(request, task_group_name=""):
    if task_group_name == "":
        return render(request, "utb/tasks.html")
    return render(request, "utb/tasks/" + task_group_name + ".html")
class SignUpView(generic.CreateView):
    form_class = UserCreationForm
    success_url = reverse_lazy("login")
    template_name = "registration/signup.html"