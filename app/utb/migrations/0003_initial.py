# Generated by Django 4.0.4 on 2022-04-21 14:43

from django.db import migrations, models
import utb.models


class Migration(migrations.Migration):

    initial = True

    dependencies = [
        ('utb', '0002_delete_uploadfile'),
    ]

    operations = [
        migrations.CreateModel(
            name='File',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('file', models.FileField(null=True, upload_to=utb.models.user_directory_path)),
            ],
        ),
    ]
