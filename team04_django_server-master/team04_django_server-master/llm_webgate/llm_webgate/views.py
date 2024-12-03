"""
LLM Webgate main functionality
"""
from django.shortcuts import render, redirect
from django.views import View
from django.views.generic import TemplateView, FormView, DeleteView
from django.contrib.auth.decorators import login_required
from django.utils.decorators import method_decorator
from django.db.models import Q
from django.contrib.auth import authenticate, login
from django.urls import reverse_lazy
from llm_webgate.models import Question, Anwser
from llm_webgate.forms.authentication_forms import LoginForm
from llm_webgate.LLM_Connector import LLMConnector
from django.http import StreamingHttpResponse

class LoginView(FormView):
    """View for login"""
    form_class = LoginForm
    success_url = reverse_lazy('chat')
    template_name = 'llm_webgate/login.html'

    def get(self, request):
        form = self.form_class()
        message = ''
        return render(request, self.template_name, context={"form": form, "message": message})

    def post(self, request):
        form = self.form_class(request.POST)
        if form.is_valid():
            username = form.cleaned_data.get('username')
            password = form.cleaned_data.get('password')
            user = authenticate(username=username, password=password)
            if user is not None:
                login(self.request, user)
                return redirect(self.success_url)
            form.add_error(None, 'Invalid username or password')
        return super().form_invalid(form)


@method_decorator(login_required, name='dispatch')
class ChatView(TemplateView):
    """View for handling logic of chat"""
    template_name = 'llm_webgate/chatbox.html'

    def get(self, request):
        user = request.user
        questions = Question.objects.filter(sender=user).exclude(
            Q(content=None)|Q(content="")
            )
        context = {
            'partner': 'ChatbotInstance',
            'questions' : questions
        }
        return render(request, self.template_name, context)
    
class QuestionHandler(View):

    def get(self, request):
        question_content = request.GET.get('question', '')
        sender = request.user
        question = Question.objects.create(content=question_content, sender=sender)

        llm_instance = LLMConnector()

        context_dict = llm_instance.buildTheContextDict(sender)
        response = StreamingHttpResponse(llm_instance.getAnwser(context_dict, question), content_type='text/plain')
        response['Content-Disposition'] = 'attachment'
        return response

class DeleteAnswersAndQuestions(View):
    def get(self, request):
        answers = Anwser.objects.filter(question__sender = request.user)
        for answer in answers:
            answer.delete()
        #Delete Questions without an answer
        questions = Question.objects.filter(sender = request.user)
        for question in questions:
            question.delete()
        return redirect(reverse_lazy('chat'))