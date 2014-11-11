
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
static char logbuffer[5][100] = { "", "", "", "", "" }; //store the log
static char outputbuffer[500] = "";
static int writer_ptr = 0;
static int log_is_readed = 1;
extern _declspec(dllexport) char *read_log();
void write_log(char *info);

//auth thread work
DWORD WINAPI auth_thread_func();
static 	char sUserName[100];
static 	char sPassword[100];
static 	char sDeviceName[100];
static HANDLE authThread = NULL;
extern int stop_flag = 1;
extern _declspec(dllexport) void start_auth_thread(const char *UserName, const char *Password, const char *DeviceName);
extern _declspec(dllexport) void stop_auth_thread();
extern _declspec(dllexport) void exit_dll();
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
	authThread = CreateThread(NULL, 0, auth_thread_func, NULL, 0, NULL);
	return;
}
void stop_auth_thread()
{
	printf("stop it!");
	if (authThread == NULL)
	{
		printf("authThread == NULL");
		return;
	}
	stop_flag = 1;
	if (WaitForSingleObject(authThread, 10000) != WAIT_OBJECT_0) //等待进程自然退出
	{
		//ExitThread(authThread);//超时后手动退出进程
		printf("进程退出失败\n");
	}
	CloseHandle(authThread);//销毁句柄
	authThread = NULL;
	printf("\nstoped!\n");
	return;
}

char *read_log()
{
	//循环读取缓存的消息
	if (log_is_readed == 0)
	{
		memset(outputbuffer, 0, 500);
		strcat(outputbuffer, logbuffer[0]);
		for (int i = 1; i < 5; i++)
		{
			if (strlen(logbuffer[i]) > 0)
			{
				strcat(outputbuffer, "\r\n");
				strcat(outputbuffer, logbuffer[i]);
			}
		}
		memset(logbuffer, 0, 500);
		log_is_readed = 1;
		return outputbuffer;
	}
	else
	{
		return "";
	}

}
void write_log(char* info)
{
	//循环写入缓存的消息
	if (strlen(info) < 99)
	{
		strcpy(logbuffer[writer_ptr], info);
		if (writer_ptr == 4)
			writer_ptr = 0;
		else
			writer_ptr++;
	}
	log_is_readed = 0;
	return;
}

void exit_dll()
{
	exit(0);
}