#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <malloc.h>
#define I_WILL_WAIT 10


CRITICAL_SECTION section = { 0 }; //Критическая секция

VOID Crit(VOID);
VOID main(VOID);
DWORD WINAPI Thread1(DWORD param);
DWORD WINAPI Thread2(DWORD param);

int count = 0;
HANDLE h[3];

VOID Crit(VOID)
{
	DWORD tmp1 = 1;
	DWORD tmp2 = 2;
	DWORD tmp3 = 3;
	InitializeCriticalSection(&section);
	h[0] = CreateThread(NULL, 0, Thread1, tmp1, 0, 0);
	h[1] = CreateThread(NULL, 0, Thread1, tmp2, 0, 0);
	h[2] = CreateThread(NULL, 0, Thread1, tmp3, 0, 0);
	WaitForMultipleObjects(3, h, TRUE, INFINITE);
	DeleteCriticalSection(&section);
	printf("count = %d\n", count);
}
DWORD WINAPI Thread1(DWORD param)
{
	for (int i = 0; i < 10; i++)
	{
		Sleep(I_WILL_WAIT);
		count++;
		printf("count = %d, potok = %d\n", count, param);
	}
	ExitThread(0);
}
DWORD WINAPI Thread2(DWORD param)
{
	EnterCriticalSection(&section);
	for (int i = 0; i < 10; i++)
	{
		Sleep(I_WILL_WAIT);
		count++;
		printf("count = %d, potok = %d\n", count, param);
	}
	LeaveCriticalSection(&section);
	ExitThread(0);
}
VOID main(VOID)
{
	DWORD tmp1 = 1;
	DWORD tmp2 = 2;
	DWORD tmp3 = 3;
	InitializeCriticalSection(&section);
	h[0] = CreateThread(NULL, 0, Thread2, tmp1, 0, 0);
	h[1] = CreateThread(NULL, 0, Thread2, tmp2, 0, 0);
	h[2] = CreateThread(NULL, 0, Thread2, tmp3, 0, 0);
	WaitForMultipleObjects(3, h, TRUE, INFINITE);
	DeleteCriticalSection(&section);
	printf("count = %d\n", count);
}