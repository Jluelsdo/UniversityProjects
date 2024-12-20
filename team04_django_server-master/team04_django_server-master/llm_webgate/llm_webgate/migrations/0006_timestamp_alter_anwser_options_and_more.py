# Generated by Django 4.2.1 on 2023-07-19 07:21

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('llm_webgate', '0005_remove_anwser_question_question_anwser'),
    ]

    operations = [
        migrations.CreateModel(
            name='Timestamp',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('timestamp', models.DateTimeField(auto_now_add=True)),
            ],
        ),
        migrations.AlterModelOptions(
            name='anwser',
            options={'ordering': ('ttlb',)},
        ),
        migrations.RemoveField(
            model_name='anwser',
            name='timestamp',
        ),
        migrations.AddField(
            model_name='anwser',
            name='error_message',
            field=models.TextField(blank=True, null=True),
        ),
        migrations.AddField(
            model_name='anwser',
            name='ttlb',
            field=models.DateTimeField(blank=True, null=True),
        ),
        migrations.AlterField(
            model_name='anwser',
            name='content',
            field=models.TextField(blank=True, null=True),
        ),
        migrations.AddField(
            model_name='anwser',
            name='timestamps',
            field=models.ManyToManyField(to='llm_webgate.timestamp'),
        ),
    ]
