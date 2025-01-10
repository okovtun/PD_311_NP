#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<CommCtrl.h>
#include<cstdio>
#include<iostream>
#include"resource.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_MAIN_DIALOG), NULL, DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hIPaddress = GetDlgItem(hwnd, IDC_IPADDRESS);
	HWND hIPmask = GetDlgItem(hwnd, IDC_IPMASK);
	HWND hEditPrefix = GetDlgItem(hwnd, IDC_EDIT_PREFIX);
	DWORD dwIPaddress = 0;
	DWORD dwIPmask = 0;
	CHAR sz_prefix[3]{};
	CONST INT SIZE = 256;

	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		//InitCommonControls();
		HWND hUpDown = GetDlgItem(hwnd, IDC_SPIN_PREFIX);
		SendMessage(hUpDown, UDM_SETRANGE, 0, MAKELPARAM(30, 1));
		//https://learn.microsoft.com/en-us/windows/win32/controls/udm-setrange
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		SendMessage(hIPmask, IPM_GETADDRESS, 0, (LPARAM)&dwIPmask);
		std::cout << "WM_INITDIALOG:\n";
		std::cout << dwIPmask << std::endl;
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_IPADDRESS:
		{
			if (HIWORD(wParam) == EN_CHANGE)
			{
				SendMessage(hIPaddress, IPM_GETADDRESS, 0, (LPARAM)&dwIPaddress);
				BYTE first = FIRST_IPADDRESS(dwIPaddress);
				if (first < 128)dwIPmask = MAKEIPADDRESS(255, 0, 0, 0);
				else if (first < 192)dwIPmask = MAKEIPADDRESS(255, 255, 0, 0);
				else if (first < 224)dwIPmask = MAKEIPADDRESS(255, 255, 255, 0);
				SendMessage(hIPmask, IPM_SETADDRESS, 0, dwIPmask);
			}
		}
		break;
		case IDC_IPMASK:
		{
			if (HIWORD(wParam) == EN_CHANGE)
			{
				SendMessage(hIPmask, IPM_GETADDRESS, 0, (LPARAM)&dwIPmask);
				int i = 1;
				for (; dwIPmask <<= 1; i++);

				sprintf(sz_prefix, "%i", i);
				SendMessage(hEditPrefix, WM_SETTEXT, 0, (LPARAM)sz_prefix);
			}
		}
		break;
		case IDC_EDIT_PREFIX:
		{
			if (HIWORD(wParam) == EN_CHANGE)
			{
				SendMessage(hEditPrefix, WM_GETTEXT, 3, (LPARAM)sz_prefix);
				DWORD dwIPprefix = atoi(sz_prefix);
				UINT dwIPmask = UINT_MAX;
				//					1111 1111	1111 1111	1111 1111	1111 1111
				//TODO: 

				//dwIPmask >>= (32 - dwIPprefix);
				dwIPmask <<= (32 - dwIPprefix);
				std::cout << "IDC_EDIT_PREFIX:\n";
				std::cout << std::hex << dwIPmask << "\n";
				if (dwIPprefix != 0)SendMessage(hIPmask, IPM_SETADDRESS, 0, dwIPmask);
			}
		}
		break;
		case IDOK:
		{

			CHAR sz_info[SIZE] = "Info:\nЗдесь будет информация о сети";	//sz_ - String Zero (NULL-Terminated Line)
			HWND hInfo = GetDlgItem(hwnd, IDC_STATIC_INFO);
			SendMessage(hInfo, WM_SETTEXT, 0, (LPARAM)sz_info);
		}
		break;
		case IDCANCEL:EndDialog(hwnd, 0); break;
		}
	}
	break;
	case WM_CLOSE:
		FreeConsole();
		EndDialog(hwnd, 0);
	}
	return FALSE;
}