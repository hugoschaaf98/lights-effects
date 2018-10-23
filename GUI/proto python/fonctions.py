import time
import tkinter

# This class has been taken from the website "https://gist.github.com/ian-weisser/9993210"
# Modifications from de raw class are spoted by "#"

class Clock(tkinter.Label):
    """ Class that contains the clock widget and clock refresh """

    def __init__(self, parent=None, seconds=True, colon=False):
        """
        Create and place the clock widget into the parent element
        It's an ordinary Label element with two additional features.
        """
        tkinter.Label.__init__(self, parent)

        self.display_seconds = seconds
        if self.display_seconds:
            self.time     = time.strftime('%H:%M:%S')
        else:
            self.time     = time.strftime('%I:%M %p').lstrip('0')
        self.display_time = self.time
        self.configure(text=self.display_time)

        if colon:
            self.blink_colon()

        self.after(200, self.tick)


    def tick(self):
        """ Updates the display clock every 200 milliseconds """
        if self.display_seconds:
            new_time = time.strftime('%H:%M:%S     %d/%m/%Y') # "     %d/%m/%Y" was added
            self.save()
        else:
            new_time = time.strftime('%I:%M %p').lstrip('0')
        if new_time != self.time:
            self.time = new_time
            self.display_time = self.time
            self.config(text=self.display_time)
        self.after(200, self.tick)


    def blink_colon(self):
        """ Blink the colon every second """
        if ':' in self.display_time:
            self.display_time = self.display_time.replace(':',' ')
        else:
            self.display_time = self.display_time.replace(' ',':',1)
        self.config(text=self.display_time)
        self.after(1000, self.blink_colon)

    # Below the whole was added
    def save(self):
        """ Write the flow in the text file, brightness and colour are converted from percent to Byte """
        brightness = round(self.brightness.get()*2.55)
        colour = self.colour.get()
        if colour < 0:
            rgb = (abs(round(colour*2.55)),abs(round(colour*2.55)),0)
        if colour > 0:
            rgb = (0,0,round(colour*2.55))
        if colour ==0 :
            rgb = (brightness,brightness,brightness)
        flow = "br:" + str(brightness) + ";rgb:"+ str(rgb)
        file = open("data.txt","w")
        file.write(flow)
        file.close()

        """ The flow (str) in the text file has the form of
            br:xxx;rgb:(xxx, xxx, xxx)
            - "br" for brightness (int)
            - "rgb" for red, green and blue, relating to the pixel colour (tuple who contains 3 int )
            - "xxx" is a number beetween 0 to 255 """
