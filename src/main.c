
#include <stdio.h>
#include <stdlib.h>
#include "pcaphelper.h"

#ifndef WIN32
#include <sys/socket.h>
#include <netinet/in.h>
#else
#include <winsock2.h>
#include <windows.h>
#include <process.h>
#pragma comment(lib, "ws2_32.lib")
#endif



//log work
extern char logbuffer[100] = ""; //store the log 
static int isReaded = 1;
extern _declspec(dllexport) char *read_log();
void write_log();

//auth thread work
DWORD WINAPI auth_thread_func();
static 	char sUserName[100];
static 	char sPassword[100];
static 	char sDeviceName[100];
extern int stop_flag = 1;
extern _declspec(dllexport) void start_auth_thread(const char *UserName, const char *Password, const char *DeviceName);
extern _declspec(dllexport) void stop_auth_thread();
//from auth.c
extern int Authentication(const char *UserName, const char *Password, const char *DeviceName);


DWORD WINAPI auth_thread_func()
{
	Authentication(sUserName, sPassword, sDeviceName);
	return 0;
}
void start_auth_thread(const char *UserName, const char *Password, const char *DeviceName)
{
	stop_flag = 0;
	strcpy(sUserName, UserName);
	strcpy(sPassword, Password);
	strcpy(sDeviceName, DeviceName);
	printf("device = %s\n", sDeviceName);
	CreateThread(NULL, 0, auth_thread_func, NULL, 0, NULL);
	return;
}
void stop_auth_thread()
{
	stop_flag = 1;
	printf("\nstoped!\n");
	return;
}

char *read_log()
{
	if (!isReaded)
	{
		isReaded = 1;
		return logbuffer;	
	}
	else return "";
}
void write_log(char* info)
{
	if (strlen(info) < 99)
	{
		strcpy(logbuffer, info);
		isReaded = 0;
	}
	return;
}