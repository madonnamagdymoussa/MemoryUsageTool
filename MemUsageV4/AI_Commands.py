###########################################################################################################
#                                         Imports                                                         #
###########################################################################################################
import json
import re
import csv
import subprocess
import os
import spacy
import pyttsx3
import speech_recognition as sr
import threading
import warnings
import requests

warnings.filterwarnings("ignore", category=DeprecationWarning)

print(spacy.__file__)  # Check where spaCy is installed
nlp = spacy.load("en_core_web_sm")
print(nlp)  # Check if the model loads successfully

nlp = spacy.load("en_core_web_sm")
tts_engine = pyttsx3.init()
recognizer = sr.Recognizer()


def speak(text):
    tts_engine.say(text)
    tts_engine.runAndWait()


def listen():
    try:
        with sr.Microphone() as source:
            print("Listening...")
            recognizer.adjust_for_ambient_noise(source)
            audio = recognizer.listen(source)
            command = recognizer.recognize_google(audio)
            print(f"You said: {command}")
            return command.lower()
    except sr.UnknownValueError:
        speak("Sorry, I did not understand that.")
        return None
    except sr.RequestError:
        speak("Sorry, there seems to be a problem with the speech service.")
        return None



# Define intents with example phrases
intents = {
    "run_nm": ["run nm command", "execute nm", "start nm process"],
    "run_size": ["run size command", "size", "size command" ],
    "run_objdump": ["produce disassembly", "I need to view disassembly", "I want to view disassembly", "generate disassembly", "disassembly", "assembly code", "debugging", "disassembler", "low level code","my assembly code","my debugging code","assemble"],
    "generate_csv": ["generate csv", "create csv file", "produce report"],
    "exit": ["exit", "close the program", "quit"]
}

def match_intent(command):
    doc = nlp(command)
    for intent, phrases in intents.items():
        for phrase in phrases:
            if phrase in command:
                return intent
    return None

def execute_voice_command(command):
    intent = match_intent(command)
    if intent == "run_nm":
        speak("Running NM command.")
        #HighTech_run_nm_command(specific_flag_key='defined_only, print_size')
        # Add your existing function call for running the NM command here
    if intent == "run_size":
     #HighTech_run_Size_command(specific_flag_key='format, SizeDecimal')
     print("run size")
    if intent == "run_objdump":
     #HighTech_Run_Objdump_Command(specific_flag_key='Disassemble', binary_file_path=None)
     print("run obj dump")
    elif intent == "generate_csv":
        speak("Generating CSV file.")
        # Add your existing function call for generating CSV here
    elif intent == "exit":
        speak("Goodbye!")
        exit(0)
    else:
        speak("I am not sure what you mean. Can you rephrase?")


def learn_new_command(command):
    speak("I did not understand that. Would you like to teach me this command?")
    confirmation = listen()
    if confirmation and "yes" in confirmation:
        speak("What should I do when you say this command?")
        action = listen()
        if action:
            speak(f"Understood. I will now recognize '{command}' as '{action}'.")
            # Add this new phrase to the intents dictionary
            if action in intents:
                intents[action].append(command)
            else:
                intents[action] = [command]
            # Save to file if persistent learning is desired
        else:
            speak("I didn't catch that. Could you repeat?")
    else:
        speak("Okay, I won't learn this command.")

def listen_for_commands():
    recognizer = sr.Recognizer()
    with sr.Microphone() as source:
        print("Listening...")
        audio = recognizer.listen(source)
        try:
            command = recognizer.recognize_google(audio)
            print(f"You said: {command}")
            speak(command)
            execute_voice_command(command)
        except sr.UnknownValueError:
            print("Sorry, I did not understand that.")
        except sr.RequestError as e:
            print(f"Could not request results from Google Speech Recognition service; {e}")


def start_voice_assistant():
    while True:
        # Assume this function gets a voice command
        command = listen_for_commands()
        print(f"Voice command recognized: {command}")  # Debug output

        if command == "run nm command":
            #HighTech_run_nm_command(specific_flag_key='defined_only, print_size')
            print("run nm command")
        elif command == "run size command":
            #HighTech_run_Size_command(specific_flag_key='format, SizeDecimal')
            print("run size command")
        elif command == "run strip command":
            #HighTech_run_Strip_command(specific_flag_key='RemoveDebugging')############################## Functions for Json file #########################################
            print("run strip command")


if __name__ == "__main__":
    try:

        #execute_voice_command("run nm command")
        #voice_thread = threading.Thread(target=start_voice_assistant)
        #voice_thread.daemon = True
        #voice_thread.start()

        #listening for commands
        start_voice_assistant()
    except Exception as e:
       print(f"An error occurred during execution: {e}")
