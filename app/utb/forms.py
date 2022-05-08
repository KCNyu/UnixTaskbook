from django import forms
from .models import File

# Model form


class FileUploadModelForm(forms.ModelForm):
    class Meta:
        model = File
        fields = ('file', 'username')
        widgets = {
            'file': forms.ClearableFileInput(attrs={'class': 'form-control'}),
        }

    def __init__(self, *args, **kwargs):
        self.request = kwargs.pop('request', None)
        super(FileUploadModelForm, self).__init__(*args, **kwargs)

    def clean_file(self):
        file = self.cleaned_data['file']
        # filename without extension
        filename = file.name.split('.')[0].lower()
        ext = file.name.split('.')[-1].lower()
        if ext not in ["c"] and filename not in ["dir", "text", "file", "shell", "thread"]:
            raise forms.ValidationError("Only C files are allowed and must be named as: file or dir or text or shell or thread")
        # return cleaned data is very important.
        return file
