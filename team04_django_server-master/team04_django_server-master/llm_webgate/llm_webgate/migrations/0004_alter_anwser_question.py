# Generated by Django 4.2.1 on 2023-05-07 13:39

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('llm_webgate', '0003_anwser_question_delete_message_anwser_question'),
    ]

    operations = [
        migrations.AlterField(
            model_name='anwser',
            name='question',
            field=models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, related_name='anwser', to='llm_webgate.question'),
        ),
    ]