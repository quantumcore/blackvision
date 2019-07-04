import os

import colorama
colorama.init()
def banner():
    banner_one =  colorama.Fore.LIGHTGREEN_EX + r"""
    _  _ ____ ____ ____ ___  ____ 
    |__| |__| |___ |__|   /  |__| 
    |  | |  | |    |  |  /__ |  | 
        The Guardian Angel                             
    """ + colorama.Style.RESET_ALL

    return banner_one

def clear():
    if(os.name == "nt"):
        os.system("cls")
    else:
        os.system("clear")