#pragma once
/*LightFrame Extension Loader API
* By VertexStudio-EnderMo
* Copyright 2022
* All rights reserved
*/
#include <Windows.h>
typedef int RUNFUN;
#define LFM_EXTENSION 0xff1
#define LFM_ONCREATEEXTENSION 0xff2
class LightFrameExtensions
{
public:
    HINSTANCE hInst;                            
    const wchar_t* szTitle = L"LightFrame.Unknown";           
    const wchar_t* szWindowClass = L"LightFrame.Unknown";     
    LRESULT (*WndProc)(HWND, UINT, WPARAM, LPARAM) = 0;
    LPTSTR hIcon;
    COLORREF BkColor = RGB(244,244,244);
    int Width = 400;
    int Height = 200;
    int NoOuterFrame = 0;
    HWND hWnd;//A Copy of hWnd.
    RUNFUN (*OnCreateCmd)() = __noop;//Add some function such as animation and so on.
    bool CheckExtension = true;//Extension will be not avaliable anymore if never check it.Only can be used for LightFrame components inner core.
    bool DependOnLightFrameMain = true;//Extension will lost it's sign if disable this option.
    ATOM __RegisterClass(){WNDCLASSEXW wcex;wcex.cbSize = sizeof(WNDCLASSEX);wcex.style = CS_HREDRAW | CS_VREDRAW;wcex.lpfnWndProc = this->WndProc;wcex.cbClsExtra = 0;wcex.cbWndExtra = 0;wcex.hInstance = this->hInst;wcex.hIcon = LoadIcon(this->hInst, this->hIcon);wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);wcex.hbrBackground = (HBRUSH)CreateSolidBrush(this->BkColor);wcex.lpszMenuName = 0;wcex.lpszClassName = this->szWindowClass;wcex.hIconSm = LoadIcon(wcex.hInstance, this->hIcon);return RegisterClassExW(&wcex);}

    int CreateExtensionMain()
    {
        if (this->WndProc != 0) { __RegisterClass(); }
        else { MessageBox(0, 0, 0, 0); return -1; }; if (this->CheckExtension != false) { if (FindWindow(L"LIGHTFRAME", L"LightFrame")) { HWND h = FindWindow(L"LIGHTFRAME", L"LightFrame"); SendMessage(h, LFM_EXTENSION, 0, 0); } else { if ((this->DependOnLightFrameMain == true))return -1; } }HWND hWnd = CreateWindow(this->szWindowClass, this->szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, this->Width, this->Height, nullptr, nullptr, this->hInst, nullptr); this->hWnd = hWnd; 
        if (!hWnd){return FALSE;}
        if (this->NoOuterFrame == 1) { LONG_PTR Style = ::GetWindowLongPtr(hWnd, GWL_STYLE); Style = Style & ~WS_CAPTION & ~WS_SYSMENU & ~WS_SIZEBOX; ::SetWindowLongPtr(hWnd, GWL_STYLE, Style); ::SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) & ~WS_EX_APPWINDOW | WS_EX_TOOLWINDOW); ::SetWindowPos(hWnd, 0, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE); }ShowWindow(hWnd, SW_SHOW); if (this->OnCreateCmd != __noop) { OnCreateCmd(); SendMessage(hWnd, LFM_ONCREATEEXTENSION, 0, 0);}else{  SendMessage(hWnd, LFM_ONCREATEEXTENSION, 0, 0);} return TRUE;
    }
private:
};

int LightFrameCreateExtension(LightFrameExtensions lfe){if (!lfe.CreateExtensionMain()){return FALSE;} MSG msg;while (GetMessage(&msg, nullptr, 0, 0)){{TranslateMessage(&msg);DispatchMessage(&msg);}}return (int)msg.wParam;}