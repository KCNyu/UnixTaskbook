from django.urls import path
from utb import views
from utb import upload

urlpatterns = [
    path("", views.main, name="main"),
    path("download/", views.download, name="download"),
    path("tasks/", views.tasks, name="tasks"),
    path("tasks/<str:task_group_name>/", views.tasks, name="tasks"),
    path("file/", upload.file_list, name="file"),
    path("upload/", upload.model_form_upload, name="upload"),
    path("check/", upload.check, name="check"),
]
