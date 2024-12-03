from django.db import models
from django.contrib.auth.models import User

class Timestamp(models.Model):
    timestamp = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return str(self.timestamp)
class Anwser(models.Model):
    content = models.TextField(null=True, blank=True)
    timestamps = models.ManyToManyField(Timestamp)
    ttlb = models.DateTimeField(null=True, blank=True)
    error_message = models.TextField(blank=True, null=True)
    class Meta:
        ordering = ('ttlb',)

    @property
    def latest_timestamp(self):
        latest_ts = self.timestamps.order_by('-timestamp')[:1].values('timestamp')
        return latest_ts[0]['timestamp'] if latest_ts else None

class Question(models.Model):
    sender = models.ForeignKey(User, on_delete=models.CASCADE, related_name='question')
    anwser = models.OneToOneField(Anwser, on_delete=models.CASCADE, related_name='question', null=True, blank=True)
    content = models.TextField()
    timestamp = models.DateTimeField(auto_now_add=True)

    class Meta:
        ordering = ('timestamp',)