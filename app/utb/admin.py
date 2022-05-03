from django.contrib import admin
from django.utils.translation import ngettext
from django.contrib import messages

from utb.models import File

# Register your models here.
class FileAdmin(admin.ModelAdmin):
    list_display = ('filename', 'username', 'commitcount', 'success', 'modified')
    
    @admin.action(description='Mark selected task as success')
    def make_success(self, request, queryset):
        updated = queryset.update(success=True)
        self.message_user(request, ngettext(
            '%d task was successfully marked as success.',
            '%d tasks were successfully marked as success.',
            updated,
        ) % updated, messages.SUCCESS)
    
    @admin.action(description='Mark selected task as unsuccess')
    def make_unsuccess(self, request, queryset):
        updated = queryset.update(status=False)
        self.message_user(request, ngettext(
            '%d task was successfully marked as success.',
            '%d tasks were successfully marked as success.',
            updated,
        ) % updated, messages.SUCCESS)
    actions = [make_success, make_unsuccess]
    list_filter = ('username',)

admin.site.register(File, FileAdmin)