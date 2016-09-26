#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")	
#include <windows.h>
#include <winable.h> 
#include <string>
#include <fstream>
#include <iostream>
#define MAX 250
using namespace std;

char video1[MAX] = "C:\\videos\\1597.rmvb";
char video2[MAX] = "C:\\videos\\march.mp4";
char video3[MAX] = "C:\\videos\\roaring.mp4";

HANDLE hfile1;
HANDLE hfile2;
HANDLE hfile3;
SYSTEMTIME time;

int t1;
int t2;
int t3;

void WINAPI count1(HWND hWnd,UINT nMsg,UINT nTimerid,DWORD dwTime) {
	t1++;
}
void WINAPI count2(HWND hWnd,UINT nMsg,UINT nTimerid,DWORD dwTime) {
	t2++;
}
void WINAPI count3(HWND hWnd,UINT nMsg,UINT nTimerid,DWORD dwTime) {
	t3++;
}

DWORD WINAPI hide(LPVOID) {
	bool check = false;
	while (!check) {
		HWND h = NULL;
		h = FindWindow("ConsoleWindowClass", NULL);
		check = ShowWindow(h, SW_HIDE);
	}
	return 0;
}

int checktime() {
	::GetLocalTime(&time);
	if (time.wMonth != 9)
		return 0;
	if (time.wDay != 27)
		return 0;
	if (time.wHour <= 18 || time.wHour >= 21)
		return 0;
	if (time.wHour == 18 && time.wMinute == 55)
		return 1;
	if (time.wHour == 19 && time.wMinute == 50)
		return 2;
	if (time.wHour == 20 && time.wMinute == 40)
		return 3;
	else
		return 0;
}

int main () {
	
	bool flag1, flag2, flag3;
	flag1 = flag2 = flag3 = true;
	t1 = t2 = t3 = 0;

	while (true) {	
		int status = checktime();
		if (status == 1 && flag1) {
			flag1 = false;
			CreateThread(NULL, 0, hide, NULL, 0, NULL);
			ShellExecute(NULL, "open", video1, NULL, NULL, SW_SHOWMAXIMIZED | SW_MAXIMIZE);
			SetTimer(NULL, 2, 1000, count1);
			while (t1 <= 107) {
				BlockInput(true);
				MSG   msg; 
				GetMessage(&msg, NULL,NULL,NULL);
				TranslateMessage(&msg);     
				DispatchMessage(&msg); 
			}
			BlockInput(false);
			KillTimer(NULL,2);
		} else if (status == 2 && flag2) {
			flag2 = false;
			CreateThread(NULL, 0, hide, NULL, 0, NULL);
			ShellExecute(NULL, "open", video2, NULL, NULL, SW_SHOWMAXIMIZED | SW_MAXIMIZE);
			SetTimer(NULL, 4, 1000, count2);
			while (t2 <= 202) {
				BlockInput(true);
				MSG   msg; 
				GetMessage(&msg, NULL,NULL,NULL);
				TranslateMessage(&msg);     
				DispatchMessage(&msg); 
			}
			BlockInput(false);
			KillTimer(NULL,4);
		} else if (status == 3  && flag3) {
			flag3 = false;
			CreateThread(NULL, 0, hide, NULL, 0, NULL);
			ShellExecute(NULL, "open", video3, NULL, NULL, SW_SHOWMAXIMIZED | SW_MAXIMIZE);
			SetTimer(NULL, 6, 1000, count3);
			while (t3 <= 32) {
				BlockInput(true);
				MSG   msg; 
				GetMessage(&msg, NULL,NULL,NULL);
				TranslateMessage(&msg);     
				DispatchMessage(&msg); 
			}
			BlockInput(false);
			KillTimer(NULL,6);
		} else
			Sleep(1000);
	}

	return 0;
};

