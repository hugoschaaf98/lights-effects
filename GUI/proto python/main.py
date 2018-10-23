from tkinter import *
import tkinter.font as tkFont # It may be useless but I let it in case of
from functools import partial # To use functions with settings for buttons 
from fonctions import *

def main():
    """-----------------------------------------------To init the window------------------------------------------------------------- """

    win = Tk()
    #x, y = 800, 600
    #win.geometry('{0}x{1}'.format(x,y))
    win.resizable(False, False)
    win.configure(bg="#F0F0F0")
    win.title("ComInter")

    """ -----------------------------------------------Behind are widgets------------------------------------------------------------ """

    # This object displays the time and the date
    clock = Clock(win)
    clock.configure(bg='#F0F0F0')
    clock.grid(column=0, row=0)

    # This canvas will take on it the colour scale and the yellow and blue canvases
    can=Canvas(win,bg="#F0F0F0",width=20,height=450)
    can.grid(column=0, row=2)

    # Yellow canvas
    can2=Canvas(can,bg="#FFFF00",width=15,height=15)
    can2.grid(column=0, row=0)

    # Blue canvas
    can3=Canvas(can,bg="#0000FF",width=15,height=15)
    can3.grid(column=2, row=0)

    # Brightness scale
    clock.brightness = IntVar(win)
    scale= Scale(win, orient='horizontal', from_=0, to=100,
      resolution=1, tickinterval=10, length=350,
      label='Brightness (%)', variable=clock.brightness)
    scale.grid(column=0, row=1)

    # Colour scale (from yellow to blue)
    clock.colour = IntVar(win)
    scale2= Scale(can, orient='horizontal', from_=-100, to=100,
      resolution=1, tickinterval=20, length=350,
      label='Colour (%)', variable=clock.colour)
    scale2.grid(column=1, row=0)
    
    win.mainloop()

main()
