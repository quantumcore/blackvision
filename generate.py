from server.core import *

try:
    import tkinter
except ImportError:
    print("Tkinter not found. Install tkinter and Re run.")
    exit(1)
    
from tkinter import *
from tkinter import messagebox
from tkinter import filedialog
import os

class GUI:
    def __init__(self, master):

        def create_file(file):
            filename = self.BinaryName.get()
            host = self.host.get()
            port = self.port.get()
            
            generate(host, port, filename)

            self.output = Entry(master, bg="gray9", fg="green", bd="1", width=30)
            self.output.configure(font=("monospace", 10))
            self.output.pack()

            try:
                test = open(filename+".exe")
                self.output.insert(0,"Compilation Succeded!")
            except FileNotFoundError:
                self.output.insert(0,"Compilation Failed!")


        self.heading = Label(master, text="BlackVision", fg="cornflowerblue", bg="gray9")
        self.heading.configure(font=("fixedsys", 30))
        self.heading.pack()

        self.update = Label(master, text="Remote Access.\n\nA wrapper around commands to make agent generation easy4u.", fg="light cyan", bg="gray9")
        self.update.configure(font=("fixedsys", 8))
        self.update.pack()

        self.browse = Label(master, text="Select Icon",  fg="purple", bg="gray9")
        self.browse.configure(font=("fixedsys", 8))
        self.browse.pack()

        self.path = Entry(master, width = 25)
        self.path.configure(font=("monospace", 8))
        self.path.pack()

        self.create = Label(master, text="A Wise choice.", fg="cornflowerblue", bg="gray9")
        self.create.configure(font=("monospace", 8))
        
        self.entfilname = Label(master, text="Enter Filename", fg="green", bg="gray9")
        self.entfilname.configure(font=("monospace", 8))

        self.BinaryName = Entry(master)
        self.BinaryName.configure(font=("fixedsys", 8))
        self.BinaryName.configure(font=("fixedsys", 8))
        
        self.srvhost = Label(master, text="Enter HOST", fg="green", bg="gray9")
        self.srvhost.configure(font=("monospace", 8))

        self.host = Entry(master)
        self.host.configure(font=("fixedsys", 8))
        self.host.configure(font=("fixedsys", 8))

        self.srvport = Label(master, text="Enter PORT", fg="green", bg="gray9")
        self.srvport.configure(font=("monospace", 8))

        self.port = Entry(master)
        self.port.configure(font=("fixedsys", 8))
        self.port.configure(font=("fixedsys", 8))

        self.comButton = Button(master, text="Compile", fg="dodgerblue", bg="gray9", bd="1", command = lambda: create_file(self.file.name))
        self.comButton.configure(font=("fixedsys", 8))

        def Browse():
            self.file = filedialog.askopenfile(initialdir="icons", mode="r+")
            try:
                self.path.insert(0, self.file.name)
            except AttributeError:
                print("Attribute Error. Maybe you pressed Cancel.")
            
            self.create.pack()
            self.entfilname.pack()
            self.BinaryName.pack()
            self.srvhost.pack()
            self.host.pack()
            self.srvport.pack()
            self.port.pack()
            self.comButton.pack()

        self.ButtonBrowse = Button(master, text="Browse", fg="dodgerblue", bg="gray9", bd="1", command= lambda: Browse())
        self.ButtonBrowse.configure(font=("fixedsys", 8))
        self.ButtonBrowse.pack()

def main():
    clear()

    root = Tk()
    root.title("BlackVision")
    root.configure(background="gray9")
    root.geometry("600x400")
    root.pack_propagate(0)
    app = GUI(root)
    root.mainloop()


if __name__ == "__main__":
    main()
    
