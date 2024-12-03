from django.urls import path
from llm_webgate.views import ChatView, LoginView, QuestionHandler, DeleteAnswersAndQuestions

urlpatterns = [
    path('', ChatView.as_view(), name='chat'),
    path('reset', DeleteAnswersAndQuestions.as_view(), name='reset_chat'),
    path('accounts/login/', LoginView.as_view(), name='login'),
    path('ask/', QuestionHandler.as_view(), name='send_question')
]
