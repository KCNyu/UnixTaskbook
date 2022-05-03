from django.db import models
import os
from .storage import OverwriteStorage
from django.utils import timezone

# Create your models here.
# Define user directory path


def user_directory_path(instance, filename):
    #ext = filename.split('.')[-1]
    #filename = '{}.{}'.format(uuid.uuid4().hex[:10], ext)
    return os.path.join('files', instance.username, filename)


class File(models.Model):
    file = models.FileField(storage=OverwriteStorage,
                            upload_to=user_directory_path, null=True)
    filename = models.CharField(max_length=255, null=True)
    username = models.CharField(max_length=255, null=True)
    commitcount = models.IntegerField(default=0)
    created = models.DateTimeField(editable=False, default=timezone.now)
    modified = models.DateTimeField()
    success = models.BooleanField(default=False)

    def __str__(self):
        return self.filename
