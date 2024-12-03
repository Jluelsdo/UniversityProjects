"""Within this class the Server forwards the Questions to a LLM and saves the Awnsers"""
from llm_webgate.models import Question, Anwser, Timestamp
import asyncio
import socket
from django.utils import timezone
import time
import json
class LLMConnector():

    def __init__(self):
        """TBD add fiels"""
        pass
    def getAnwser(self, llm_context_dict, question):
        HOST = '172.17.0.1' # Dockercontainer depends on the current container
        PORT = 8080
        timeout=30 # We need to find out the best timemout time. And we need to handle a timeout event

        anwser = Anwser.objects.create()
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((HOST, PORT))
            s.sendall(json.dumps(llm_context_dict).encode())
            
            response = ""
            start_time = time.time()
            s.settimeout(timeout)
            while True:
                try:
                    data = s.recv(4096).decode()
                    if not data:
                        if time.time() - start_time >= timeout:
                            break
                        continue
                    response += data # data has to be yielded
                    chunk_timestamp = Timestamp.objects.create()
                    anwser.timestamps.add(chunk_timestamp)
                    yield data
                    start_time = time.time()
                except socket.timeout as e:
                    anwser.error_message = str(e)
                    break
                except Exception as e:
                    anwser.error_message = str(e)
                    break
        anwser.ttlb = timezone.now()
        anwser.content = response
        anwser.save()
        question.anwser = anwser
        question.save()
        print("Got the response:\n{}".format(response))
        #return response


    def buildTheContextDict(self, user):
        question_list = Question.objects.filter(sender=user).exclude(anwser__isnull=True)
        buffer=[]
        for question in question_list:
            buffer.append({"role":"user", "content":question.content})
            buffer.append({"role":"assistant", "content":question.anwser.content})
        last_question = Question.objects.filter(sender=user).last()
        if last_question:
            buffer.append({"role":"user", "content":last_question.content})
        return buffer