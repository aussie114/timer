#!/usr/bin/env python
import sys
from os import system
from tkinter import *
from time import time, strftime, gmtime

class Widgets:
    pass
widgets = Widgets()

class Global:
    pass
globals = Global()

def main(argc, argv):

    if argc > 1:
        globals.end_time = time() + hms_to_seconds(argv[1])
    else:
        print("no time specified")
        quit()

    globals.flash = False
    globals.paused = False
    globals.alarm_sounded = False

    widgets.window = Tk()
    widgets.window.resizable(False, False)
    widgets.window.bind("<Escape>", kill)
    widgets.frame = Frame(background="#303446", highlightbackground="#525762", highlightthickness=2)
    widgets.frame.pack()

    widgets.output = Label(widgets.frame, font=("TkFixedFont", 48), background="#303446", foreground="#e0e2ea")
    widgets.output.grid(column = 0, row = 0, columnspan=3)

    widgets.reset_button = Button(widgets.frame, text="Reset", command=on_reset_button_pressed, **button_options)
    widgets.reset_button.grid(column=0, row=1)

    widgets.pause_button = Button(widgets.frame, text="Pause", command=on_paused_pressed, **button_options)
    widgets.pause_button.grid(column=1, row=1)

    widgets.quit_button = Button(widgets.frame, text="Quit", command=kill, **button_options)
    widgets.quit_button.grid(column=2, row=1)

    update()
    widgets.window.mainloop()

def update():
    if globals.paused:
        globals.end_time += 0.5
    seconds_remaining = globals.end_time - time()
    if seconds_remaining > 0:
        widgets.output.configure(text=seconds_to_hms(seconds_remaining))
    else:
        if not globals.alarm_sounded:
            system("mpv /usr/share/sounds/freedesktop/stereo/alarm-clock-elapsed.oga &")
            globals.alarm_sounded = True
        if globals.flash:
            widgets.output.configure(text="")
        else:
            widgets.output.configure(text="00:00:00")
        globals.flash = not globals.flash
        
    widgets.window.after(500, update)

def on_reset_button_pressed():
    globals.end_time = time() + hms_to_seconds(sys.argv[1])
    globals.paused = False
    widgets.output.configure(text=seconds_to_hms(globals.end_time - time()))
    globals.alarm_sounded = False

def on_paused_pressed():
    if globals.paused == False:
        widgets.pause_button.configure(text="Resume")
        globals.paused = True
    else:
        widgets.pause_button.configure(text="Pause ")
        globals.paused = False

def kill(key=None):
    widgets.window.destroy()

def hms_to_seconds(text):
    text = text.split(":")

    match (len(text)):
        case 3:
            return int(text[0]) * 3600 + int(text[1]) * 60 + int(text[2])
        case 2:
            return int(text[0]) * 60 + int(text[1])
        case 1:
            return int(text[0])

def seconds_to_hms(seconds):
    return strftime("%H:%M:%S", gmtime(seconds))

button_options = {
    "activebackground": "#505666",
    "activeforeground": "#c7ced8",
    "background": "#444a58",
    "borderwidth": 0,
    "foreground": "#c6cdd6",
    "highlightbackground": "#2b2e39",
    "highlightcolor": "#6f7582",
    "highlightthickness": 1,
    "relief": "flat",
    "width" : 8
}

if __name__ == "__main__":
    main(len(sys.argv), sys.argv)
