#pragma once
#include "LightFrame.MinecraftFrame.h"
#include "framework.h"
#include "VertexUI/VertexUI.Panel.h"
#include "LightFrame.WindowAnimation.h"
#include <Windows.h>
#include <CommDlg.h>
#include <iostream>

#pragma warning(disable:4996);
namespace NormalPanel {
	HINSTANCE ti_hInstance;
	HWND c_tip1;
	HWND c_WB;
	HWND c_tip2;
	WNDPROC TipBoxProc;
	WNDPROC BTold;

	typedef struct TagTipBox
	{// 
		HWND hWnd;
		BOOL x1;
		BOOL x2;
		LPWSTR in;
		UINT style;
	} TIP_PARAM;
	int NormalTipHeight = 40;
	int nh = NormalTipHeight;
	HWND tibtnhwnd;
	HINSTANCE tibtnHINST;
	WNDPROC tiBToldProc;
	typedef struct tagCLOSE
	{// 
		HWND hWnd;          // 主窗口 handle of owner window
		BOOL x1; //x坐标 x axis
		BOOL x2; //y坐标 y axis
		LPWSTR in; //NO USE
		UINT style; //从定义里获取依赖,处理消息 Get Messages from define
	} CLOASE_PARAM;
	//
	//

}
//#define MAX_LOADSTRING 100 
// using namespace std;
static TCHAR     szFileName1[MAX_PATH], szTitleName1[MAX_PATH];
//const wchar_t* szOldName;
static OPENFILENAME ofn2;
void PopFileInitialize(HWND hwnd)//dir now is loaded by openfile dialog 
{
	TCHAR     szFileName1[MAX_PATH], szTitleName1[MAX_PATH];
	static TCHAR szFilter[1024] = TEXT("应用程序(*.exe)\0*.exe\0");
	//szOldName = szFileName1;
	_tcscpy(szFileName1, L"");
	ofn2.lStructSize = sizeof(OPENFILENAME);
	ofn2.hwndOwner = hwnd;
	ofn2.hInstance = NULL;
	ofn2.lpstrFilter = szFilter;
	ofn2.lpstrCustomFilter = NULL;
	ofn2.nMaxCustFilter = 0;
	ofn2.nFilterIndex = 0;
	ofn2.lpstrFile = szFileName1;
	ofn2.nMaxFile = MAX_PATH;
	ofn2.lpstrFileTitle = NULL;
	ofn2.nMaxFileTitle = MAX_PATH;
	ofn2.lpstrInitialDir = NULL;
	ofn2.lpstrTitle = NULL;
	ofn2.Flags = 0;
	ofn2.nFileOffset = 0;
	ofn2.nFileExtension = 0;
	ofn2.lpstrDefExt = TEXT("exe");
	ofn2.lCustData = 0L;
	ofn2.lpfnHook = NULL;
	ofn2.lpTemplateName = NULL;

	/*
	if (GetOpenFileName(&ofn))
	{
		MessageBox(hwnd, ofn.lpstrFile, ofn.lpstrFile, 0);
	}
	*/
}
void PopFileInitializex(HWND hwnd, int i)//dir now is loaded by openfile dialog 
{
	static TCHAR szFilter[1024] = TEXT("应用程序(*.exe)\0*.exe\0");
	//szOldName = szFileName1;
	_tcscpy(szFileName1, L"");
	ofn2.lStructSize = sizeof(OPENFILENAME);
	ofn2.hwndOwner = hwnd;
	ofn2.hInstance = NULL;
	ofn2.lpstrFilter = szFilter;
	ofn2.lpstrCustomFilter = NULL;
	ofn2.nMaxCustFilter = 0;
	ofn2.nFilterIndex = 0;
	ofn2.lpstrFile = szFileName1;
	ofn2.nMaxFile = MAX_PATH;
	ofn2.lpstrFileTitle = NULL;
	ofn2.nMaxFileTitle = MAX_PATH;
	ofn2.lpstrInitialDir = NULL;
	ofn2.lpstrTitle = NULL;
	ofn2.Flags = 0;
	ofn2.nFileOffset = 0;
	ofn2.nFileExtension = 0;
	ofn2.lpstrDefExt = TEXT("exe");
	ofn2.lCustData = 0L;
	ofn2.lpfnHook = NULL;
	ofn2.lpTemplateName = NULL;


	if (GetOpenFileName(&ofn2))
	{
		mcis.dirs[i] = ofn2.lpstrFile;
	}



}
BOOL PopFileOpenDlgx(HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName, int i)
{
	_tcscpy(szFileName1, L"");
	ofn2.hwndOwner = hwnd;
	ofn2.lpstrFile = pstrFileName;
	ofn2.lpstrFileTitle = pstrTitleName;
	ofn2.Flags = OFN_HIDEREADONLY | OFN_CREATEPROMPT;
	mcis.dirs[i] = ofn2.lpstrFile;
	return GetOpenFileName(&ofn2);
}
BOOL PopFileOpenDlg(HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName)
{
	TCHAR     szFileName1[MAX_PATH], szTitleName1[MAX_PATH];
	_tcscpy(szFileName1, L"");
	ofn2.hwndOwner = hwnd;
	ofn2.lpstrFile = pstrFileName;
	ofn2.lpstrFileTitle = pstrTitleName;
	ofn2.Flags = OFN_HIDEREADONLY | OFN_CREATEPROMPT;
	return GetOpenFileName(&ofn2);
}

/*
bool openfile()
{
	const std::wstring title = L"选择你的文件啦qwq";
	LPWSTR filename = L"";

	OPENFILENAMEW ofn = { };
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = L"应用程序\0*.exe\0所有\0*.*\0";
	ofn.lpstrFile = filename;  // use the std::wstring buffer directly
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = title.c_str();
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST | OFN_READONLY;

	if (GetOpenFileNameW(&ofn))
	{
		mcis.dirs[mcis.id] = filename;    //<----------Save filepath in global variable
		return true;
	}
	return false;
}
*/
const wchar_t* teststr(const wchar_t* a, const wchar_t* b)
{
	a = b;
	return a;
}
wchar_t* openfilename(HWND owner = NULL, const wchar_t* filter = L"应用程序 (*.exe)\0*.exe") {
	CoInitialize(openfilename);
	OPENFILENAME ofn;
	TCHAR fileName[MAX_PATH] = L"";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = owner;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = L"";
	//ofn.lpstrInitialDir = "Missions\\";
	wchar_t* NewName = new wchar_t[MAX_PATH];
	wsprintf(NewName, L"%s", fileName);
	if (GetOpenFileName(&ofn))
	{
		return NewName;
		//ZeroMemory(fileName, 0x00);
	}
	return 0;
}
void openfilename2(wchar_t*& ret, HWND owner = NULL, const wchar_t* filter = L"应用程序 (*.exe)\0*.exe\0快捷方式 (*.lnk)\0*.lnk") {
	CoInitialize(openfilename);
	OPENFILENAME ofn;
	TCHAR fileName[MAX_PATH] = L"";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = owner;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = L"";
	//ofn.lpstrInitialDir = "Missions\\";


	if (GetOpenFileName(&ofn))
	{
		wchar_t* NewName = new wchar_t[MAX_PATH];
		wsprintf(NewName, L"%s", fileName);
		ret = NewName;
		//ZeroMemory(fileName, 0x00);
	}
}
//PopFileInitialize(hWnd);  //初始化ofn
//PopFileOpenDlg(hWnd, szFileName, szTitleName);//打开文件对话框
int LightFrane_TipWindow_hState = 0;
int TipWindowAreaEvent(HWND hWnd, LPARAM lParam)
{

	int val = 0;

	int msg = 0;

	UINT pindex = 0;
	RECT winrc;
	GetClientRect(hWnd, &winrc);

	RECT rc = {};
	if ((GetAreaPtInfo(hWnd, winrc.right - 34, 5, 24, 24, rc, lParam)) == 1)
	{
		if (ClickMsg == 1)
		{
			ClickMsg = 0;
			FadeOutAnimation(hWnd);
			DestroyWindow(hWnd);
		}
		if (LightFrane_TipWindow_hState == 0)
		{
			HDC hdc = GetDC(hWnd);
			CreateRect(hWnd, hdc, rc.left + 3, rc.bottom - 2, (rc.right - rc.left) - 6, 2, VERTEXUICOLOR_GREENDEEPSEA);
			DeleteObject(hdc);
			ReleaseDC(hWnd, hdc);
			DeleteDC(hdc);
			LightFrane_TipWindow_hState = 1;
		}
		return 0;
	}
	else
	{
		if (LightFrane_TipWindow_hState == 1)
		{
			LightFrane_TipWindow_hState = 0;
			InvalidateRect(hWnd, &winrc, 0);
		}
		return 0;
	}



	return 0;
}
#define VERTEXUI_TIPBOX_CREATE 0x1c
LRESULT CALLBACK TipProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{// 
	using namespace::NormalPanel;
	RECT rc;
	GetClientRect(hWnd, &rc);
	RECT mrc;
	GetWindowRect(GhWnd, &mrc);
	RECT wrc;
	GetWindowRect(hWnd, &wrc);
	TCHAR txt[80];
	TIP_PARAM* pmmb = (TIP_PARAM*)lParam;
	UNREFERENCED_PARAMETER(lParam);

	switch (Msg)
	{//
	case VERTEXUI_TIPBOX_CREATE:
	{
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		LONG_PTR Style = ::GetWindowLongPtr(hWnd, GWL_STYLE);
		Style = Style & ~WS_CAPTION & ~WS_SYSMENU & ~WS_SIZEBOX;
		::SetWindowLongPtr(hWnd, GWL_STYLE, Style);
		XSleep(1);
		InvalidateRect(hWnd, &rc, 0);
		break;
	}
	case WM_PAINT:
	{
		GetWindowText(hWnd, txt, sizeof(txt));
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		HDC         hMemDC;
		HBITMAP     hBmpMem;
		HBITMAP     hPreBmp;
		//InvalidateRect(h, &rc, 1);
		hMemDC = CreateCompatibleDC(hdc);

		hBmpMem = CreateCompatibleBitmap(hdc, rc.right - rc.left, rc.bottom - rc.top);

		hPreBmp = (HBITMAP)SelectObject(hMemDC, hBmpMem);
		//On hMemDC.
		CreateFillArea(hWnd, hMemDC, VERTEXUICOLOR_MIDNIGHT);
		TextPreDraw(hMemDC, 0, 0, rc.right - rc.left, rc.bottom - rc.top, txt, VERTEXUICOLOR_WHITE);
		PanelDrawCloseBtn(hWnd, hMemDC, rc.right - 34, 6, 25, 25, 4, RGB(187, 192, 201));
		PanelDrawOutFrame(hWnd, hMemDC, VERTEXUICOLOR_DARKEN);

		BitBlt(hdc, 0, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);

		SelectObject(hMemDC, hPreBmp);


		DeleteObject(hBmpMem);

		DeleteDC(hMemDC);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		int val = 0;
		ClickAreaPtInfo(hWnd, rc.right - 30, 0, 30, 30, lParam, val);
		if (val == 0)
		{
			SendMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
		}
		break;
	}
	case WM_LBUTTONUP:
	{
		SnedClickEvent(hWnd, wParam, lParam);
		break;
	}
	case WM_MOUSEMOVE:
	{
		TipWindowAreaEvent(hWnd, lParam);
		break;
	}
	case WM_SIZE:
	{
		InvalidateRect(hWnd, &rc, 0);
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		}
		break;
	}
	case WM_CLOSE:
	{
		DestroyWindow(hWnd);
	}
	default: return DefWindowProc(hWnd, Msg, wParam, lParam);
	}
	//
	return 0;

}
int TipBox(
	HWND hWnd,         // handle of owner window
	BOOL x1,
	BOOL x2,
	const wchar_t* txt //
)
{
	using namespace::NormalPanel;

	RECT rc;
	GetClientRect(hWnd, &rc);
	TIP_PARAM tip;
	tip.hWnd = hWnd;
	c_WB = CreateWindow(L"#32770", txt, WS_POPUP | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,//TipBox
		x1, x2, 400, 200, hWnd, 0, ti_hInstance, NULL);
	ShowWindow(c_WB, SW_HIDE);
	TipBoxProc = (WNDPROC)SetWindowLongPtr(c_WB, GWLP_WNDPROC, (LONG_PTR)TipProc);

	SendMessage(c_WB, VERTEXUI_TIPBOX_CREATE, 0, 0);
	ShowWindow(c_WB, SW_SHOW);
	FadeInAnimation(c_WB);
	//SetParent(c_WB, hWnd);
	return -1;
}


#pragma once
#include "framework.h"

#define COMMANDCUBE_CTL_CLOSE 0x19c1
#define COMMANDCUBE_CTL_OK 0x19c2
#define COMMANDCUBE_CTL_FEDIT1 0x19c4

HWND hEditWnd = 0;
WNDPROC hEditProc = 0;
HINSTANCE hEditInst = 0;

int CreateFileEdit(
	HWND hWnd,          // handle 
	int x1, int y1, int x2, int y2, LPCTSTR chr
)
{
	hEditWnd = CreateWindow(L"EDIT", chr, WS_CHILD | WS_VISIBLE | ES_WANTRETURN | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,//TipBox
		x1, y1, x2, y2, hWnd, (HMENU)COMMANDCUBE_CTL_FEDIT1, hEditInst, NULL);
	//hEditProc = (WNDPROC)SetWindowLongPtr(hEditWnd, GWLP_WNDPROC, (LONG_PTR)CreateFileWindowEditProc);
	//SendMessage(hCFWnd, WM_CREATE, 0, 0);
	//SendMessage(hEditWnd,EM_SETLIMITTEXT,65535,0);
	//MoveInMenuNew(hMaskWnd);
	return -1;
}
int CreateFileEditEx(
	HWND hWnd, HWND cwnd,          // handle 
	int x1, int y1, int x2, int y2, LPCTSTR chr
)
{
	HWND nhEditWnd = CreateWindow(L"EDIT", chr, WS_CHILD | WS_VISIBLE | ES_WANTRETURN | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,//TipBox
		x1, y1, x2, y2, hWnd, (HMENU)COMMANDCUBE_CTL_FEDIT1, hEditInst, NULL);
	//hEditProc = (WNDPROC)SetWindowLongPtr(hEditWnd, GWLP_WNDPROC, (LONG_PTR)CreateFileWindowEditProc);
	//SendMessage(hCFWnd, WM_CREATE, 0, 0);
	//SendMessage(hEditWnd,EM_SETLIMITTEXT,65535,0);
	//MoveInMenuNew(hMaskWnd);
	cwnd = nhEditWnd;
	return -1;
}


HWND hCFWnd = 0;
WNDPROC hCFProc = 0;
HINSTANCE hCFInst = 0;
HWND hCFEditWnd1;
HWND hCFEditWnd2 = 0;
HWND hCFEditWnd3 = 0;
int hEditMode = 0;
typedef struct tagww
{// 
	HWND hWnd11w;          // handle 

	LPCTSTR lpText11w;     // text 

	LPCTSTR lpCaption11w;  //  title 

	UINT uType11w;         // style 

} EDIT_PARAM1w;
int hEditIsClosed = 0;
const wchar_t* EditReturnText;
int hEditWindowAreaEvent(HWND hWnd, LPARAM lParam)
{

	int val = 0;

	int msg = 0;

	UINT pindex = 0;
	RECT winrc;
	GetClientRect(hWnd, &winrc);
	RECT trc;
	GetWindowRect(hWnd, &trc);
	RECT rc = {};
	if ((GetAreaPtInfo(hWnd, winrc.right - 34, 5, 24, 24, rc, lParam)) == 1)
	{
		if (ClickMsg == 1)
		{
			ClickMsg = 0;
			FadeOutAnimation(hWnd);
			//DestroyWindow(hWnd);
			EditReturnText = L"NULL";
			hEditMode = 0;
			DestroyWindow(hWnd);
			PostQuitMessage(0);
		}
		if (LightFrane_TipWindow_hState == 0)
		{
			HDC hdc = GetDC(hWnd);
			CreateRect(hWnd, hdc, rc.left + 3, rc.bottom - 2, (rc.right - rc.left) - 6, 2, VERTEXUICOLOR_GREENDEEPSEA);
			DeleteObject(hdc);
			ReleaseDC(hWnd, hdc);
			DeleteDC(hdc);
			LightFrane_TipWindow_hState = 1;

		}
		return 0;
	}
	if (hEditMode == 1)
	{
		if ((GetAreaPtInfo(hWnd, winrc.right - 230, winrc.bottom - 40, 100, 25, rc, lParam)) == 1)
		{
			if (ClickMsg == 1)
			{
				ClickMsg = 0;
				wchar_t* txt = new wchar_t[MAX_PATH];
				openfilename2(txt, hWnd);
				HWND h2 = GetDlgItem(hWnd, COMMANDCUBE_CTL_FEDIT1);
				SendMessage(h2, WM_SETTEXT, 0, (LPARAM)txt);
			}
			if (LightFrane_TipWindow_hState == 0)
			{
				HDC hdc = GetDC(hWnd);
				//CreateRect(hWnd, hdc, x, rc.bottom - 2, rc.right - rc.left, 2, VERTEXUICOLOR_GREENDEEPSEA);
				CreateRect(hWnd, hdc, rc.left, rc.bottom - 2, rc.right - rc.left, 3, VERTEXUICOLOR_GREENDEEPSEA);
				DeleteObject(hdc);
				ReleaseDC(hWnd, hdc);
				DeleteDC(hdc);
				LightFrane_TipWindow_hState = 1;
			}
			return 0;
		}
	}
	if ((GetAreaPtInfo(hWnd, winrc.right - 120, winrc.bottom - 40, 100, 25, rc, lParam)) == 1)
	{
		if (ClickMsg == 1)
		{
			ClickMsg = 0;

			//DestroyWindow(hWnd);
			wchar_t Dest[260] = L"";

			GetDlgItemText(hWnd, COMMANDCUBE_CTL_FEDIT1, Dest, 260);
			std::wstring ws = Dest;
			if (std::isdigit(ws[0]) || std::isdigit(ws[1]))
			{
			    TipBox(hWnd, trc.left, trc.top + 20, L"不能输入纯数字哦qwq");

				EditReturnText = L"NULL";
				DestroyWindow(hWnd);
				PostQuitMessage(0);
				return 0;
			}
			if (Dest[0] == 0)
			{
				TipBox(hWnd, trc.left, trc.top + 20, L"请输入字符哦qwq");
			}
			else
			{
				FadeOutAnimation(hWnd);
				hEditMode = 0;
				wchar_t* Dest2 = new wchar_t[260];
				//std::shared_ptr<wchar_t> Dest2(new wchar_t[260]);
				wcscpy(Dest2, Dest);
				*Dest2 = *Dest;

				EditReturnText = Dest2;
				//delete Dest2;
				DestroyWindow(hWnd);
				PostQuitMessage(0);
			}
		}
		if (LightFrane_TipWindow_hState == 0)
		{
			HDC hdc = GetDC(hWnd);
			//CreateRect(hWnd, hdc, x, rc.bottom - 2, rc.right - rc.left, 2, VERTEXUICOLOR_GREENDEEPSEA);
			CreateRect(hWnd, hdc, rc.left, rc.bottom - 2, rc.right - rc.left, 3, VERTEXUICOLOR_GREENDEEPSEA);
			DeleteObject(hdc);
			ReleaseDC(hWnd, hdc);
			DeleteDC(hdc);
			LightFrane_TipWindow_hState = 1;
		}
		return 0;
	}
	else
	{
		if (LightFrane_TipWindow_hState == 1)
		{
			LightFrane_TipWindow_hState = 0;
			InvalidateRect(hWnd, &winrc, 0);
		}
		return 0;
	}



	return 0;
}
INT_PTR CALLBACK CreateManifestWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HBITMAP hBitmap;                  // 1 静态变量
	static HBITMAP hBitmap2;
	static HBITMAP hBitmap3;
	HINSTANCE dlg_h = NULL;
	static HFONT hFont;//定义静态字体变量
	static HFONT hFont2;//定义静态字体变量
	BITMAP         bitmap;
	static HWND close;
	HDC hdcMem = NULL;
	static int      bmWidth, bmHeight;       // 2 静态变量
	wchar_t txt[128];
	EDIT_PARAM1w* emmb = (EDIT_PARAM1w*)lParam;
	RECT rc;
	HBRUSH hbr = NULL;
	HPEN hpen = NULL;
	LOGFONT lf;
	GetClientRect(hWnd, &rc);
	UNREFERENCED_PARAMETER(lParam);
	switch (uMsg)
	{
	case WM_CREATE:
	{
		Alpha = 248; AlphaSet;
		OutputDebugString(L"Mask Created");
		CreateFileEditEx(hWnd, hCFEditWnd2, 20, 60, 350, 30, L"");
		return TRUE;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		HDC         hMemDC;
		HBITMAP     hBmpMem;
		HBITMAP     hPreBmp;
		//InvalidateRect(h, &rc, 1);
		hMemDC = CreateCompatibleDC(hdc);

		hBmpMem = CreateCompatibleBitmap(hdc, rc.right - rc.left, rc.bottom - rc.top);

		hPreBmp = (HBITMAP)SelectObject(hMemDC, hBmpMem);
		//On hMemDC.
		CreateFillArea(hWnd, hMemDC, VERTEXUICOLOR_MIDNIGHT);
		PanelDrawCloseBtn(hWnd, hMemDC, rc.right - 34, 6, 25, 25, 4, RGB(187, 192, 201));
		PanelDrawOutFrame(hWnd, hMemDC, VERTEXUICOLOR_DARKEN);
		if (hEditMode == 1)
		{
			CreateButton(hWnd, hMemDC, rc.right - 230, rc.bottom - 40, 100, 25, 0, L"选择目录");
		}
		CreateButton(hWnd, hMemDC, rc.right - 120, rc.bottom - 40, 100, 25, 0, L"确定");
		BitBlt(hdc, 0, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);

		SelectObject(hMemDC, hPreBmp);


		DeleteObject(hBmpMem);

		DeleteDC(hMemDC);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_CTLCOLOREDIT:
	{
		HDC hdc = (HDC)wParam;
		GetWindowText(hWnd, txt, 40);
		SetTextColor(hdc, VERTEXUICOLOR_WHITE);
		SetBkMode(hdc, TRANSPARENT);
		if (hFont == 0)
		{
			memset(&lf, 0, sizeof(LOGFONT));
			lf.lfHeight = -16;
			wcscpy(lf.lfFaceName, L"黑体");
			hFont = CreateFontIndirect(&lf);  // create the font
		}
		HFONT old = (HFONT)SelectObject(hdc, hFont);
		DrawText(hdc, txt, wcslen(txt), &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		//DrawText(hdc, txt, wcslen(txt), &ps.rcPaint, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		//ReleaseDC(hWnd, hdc);
		return (INT_PTR)CreateSolidBrush(VERTEXUICOLOR_MIDNIGHTPLUS);
	} //颜色
	case WM_LBUTTONDOWN:
	{
		int val = 0;
		ClickAreaPtInfo(hWnd, 0, 0, rc.right - 35, 40, lParam, val);
		if (val == 1)
		{
			SendMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
		}
		break;
	}
	case WM_LBUTTONUP:
	{
		SnedClickEvent(hWnd, wParam, lParam);
		break;
	}
	case WM_MOUSEMOVE:
	{
		hEditWindowAreaEvent(hWnd, lParam);
		break;
	}
	case WM_SIZE:
	{

		InvalidateRect(hWnd, &rc, 0);
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{

		}
	}
	//--消息处理不知道放这里吗?
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
//
const wchar_t* EditszWindowClass = L"LightFrame.editctl";            // 主窗口类名

ATOM EditBoxRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = CreateManifestWindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MIN_ICON));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	//wcex.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(47, 52, 61));
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = EditszWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_MIN_ICON));

	return RegisterClassExW(&wcex);
}
int CreateOuterEditBox(
	HWND hWnd, HWND mh = 0, int hmode = 0        // handle 
)
{

	EnableWindow(hWnd, FALSE);
	RECT rc;
	GetWindowRect(hWnd, &rc);
	RECT crc;
	GetClientRect(hWnd, &crc);
	EditBoxRegisterClass(hCFInst);
	hCFWnd = CreateWindow(EditszWindowClass, L"LightFrame_hEdit_legacy", WS_POPUP | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,//TipBox
		rc.left, rc.top + 1, 380, 230, mh, 0, hCFInst, NULL);
	SendMessage(hCFWnd, WM_CREATE, 0, 0);
	hEditMode = hmode;
	SetWindowPos(hCFWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	LONG_PTR Style = ::GetWindowLongPtr(hCFWnd, GWL_STYLE);
	Style = Style & ~WS_CAPTION & ~WS_SYSMENU & ~WS_SIZEBOX;
	::SetWindowLongPtr(hCFWnd, GWL_STYLE, Style);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	EnableWindow(hWnd, TRUE);
	SetForegroundWindow(hWnd);
	//MoveInMenuNew(hMaskWnd);
	return 0;
}

HWND hMaskWnd = 0;
WNDPROC hMaskProc = 0;
HINSTANCE hMaskInst = 0;
#define CUBEMSG_CLOSEMASK 1090
#define CUBEMSG_CLOSEMASK_NA 1091
#define CUBEMSG_REDRAW 1033
INT_PTR CALLBACK MaskProc(HWND hwndDlg11w1, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HBITMAP hBitmap;                  // 1 静态变量
	static HBITMAP hBitmap2;
	static HBITMAP hBitmap3;
	HINSTANCE dlg_h = NULL;
	static HFONT hFont;//定义静态字体变量
	BITMAP         bitmap;
	static HWND close;
	HDC hdcMem = NULL;
	static int      bmWidth, bmHeight;       // 2 静态变量
	char txt[40];
	EDIT_PARAM1w* emmb = (EDIT_PARAM1w*)lParam;
	RECT rect;
	HBRUSH hbr = NULL;
	HPEN hpen = NULL;
	GetClientRect(hwndDlg11w1, &rect);
	UNREFERENCED_PARAMETER(lParam);
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		FadeInAnimation(hwndDlg11w1);
		HWND hWnd = hwndDlg11w1;
		Alpha = 200; AlphaSet;
		OutputDebugString(L"Mask Created");
		return TRUE;
	}    case WM_PAINT:
	{
		HWND hWnd = hwndDlg11w1;
		RECT rc = rect;
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwndDlg11w1, &ps);
		HDC         hMemDC;
		HBITMAP     hBmpMem;
		HBITMAP     hPreBmp;
		//InvalidateRect(h, &rc, 1);
		hMemDC = CreateCompatibleDC(hdc);

		hBmpMem = CreateCompatibleBitmap(hdc, rect.right - rect.left, rect.bottom - rect.top);

		hPreBmp = (HBITMAP)SelectObject(hMemDC, hBmpMem);
		//On hMemDC.
		CreateFillArea(hWnd, hMemDC, RGB(0, 0, 0));
		BitBlt(hdc, 0, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);

		SelectObject(hMemDC, hPreBmp);


		DeleteObject(hBmpMem);

		DeleteDC(hMemDC);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_LBUTTONUP:
	{
		SendMessage(MCFramehWnd, 0xcc, 0, 0);
	}
	case CUBEMSG_CLOSEMASK:
	{
		FadeOutAnimation(hwndDlg11w1);
		DestroyWindow(hwndDlg11w1);
		break;
	}
	case CUBEMSG_CLOSEMASK_NA:
	{
		//FadeOutAnimationMask(hwndDlg11w1);
		DestroyWindow(hwndDlg11w1);
		break;
	}
	case WM_ACTIVATE:
	{
		BOOL fActive;
		fActive = LOWORD(wParam);
		if (fActive == WA_ACTIVE)
		{
			break;
		}
		else
		{
			//--
			//(hwndDlg11w1);
			//DestroyWindow(hwndDlg11w1);
			break;
		}
	}
	//--消息处理不知道放这里吗?
	}
	return DefWindowProc(hwndDlg11w1, uMsg, wParam, lParam);
}
//
int CreateMaskBox(
	HWND hWnd, int mode = 0        // handle 
)
{
	RECT rc;
	GetWindowRect(hWnd, &rc);
	RECT crc;
	GetClientRect(hWnd, &crc);
	int scrx = GetSystemMetrics(SM_CXSCREEN); int scry = GetSystemMetrics(SM_CYSCREEN);
	if (mode == 1)
	{
		hMaskWnd = CreateWindow(L"#32770", L"LightFrame_Mask", WS_POPUP | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,//TipBox
			0, 0, scrx, scry, hWnd, 0, hMaskInst, NULL);
	}
	else
	{
		hMaskWnd = CreateWindow(L"#32770", L"LightFrame_Mask", WS_POPUP | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,//TipBox
			rc.left, rc.top, rc.right - rc.left, crc.bottom - crc.top, hWnd, 0, hMaskInst, NULL);
	}
	hMaskProc = (WNDPROC)SetWindowLongPtr(hMaskWnd, GWLP_WNDPROC, (LONG_PTR)MaskProc);
	SendMessage(hMaskWnd, WM_INITDIALOG, 0, 0);

	//MoveInMenuNew(hMaskWnd);
	return -1;
}