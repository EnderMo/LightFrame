#pragma once
#include "VertexUI/VertexUI.ClickArea.h"
#include "VertexUI/vui.parser/vui.parser.hpp"
#include "LightFrame.Interface.h"
#include "framework.h"
#include "LightFrame.AA.h"
#include "LightFrame.DevLab.h"
#include "resource.h"
#include <windowsx.h>
#pragma warning(disable:4996)
// 全局变量:
HINSTANCE EventAreaFramehInst;                                // 当前实例
const wchar_t* EventAreaszTitle = L"LightFrame.EventAreaFrame";                  // 标题栏文本
const wchar_t* EventAreaszWindowClass = L"LightFrame.EventArea";            // 主窗口类名
// 此代码模块中包含的函数的前向声明:
ATOM                EventAreaFrameRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK    EventAreaFrameWndProc(HWND, UINT, WPARAM, LPARAM);


//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
typedef struct EventAreaType {
    int x = 100;
    int y = 100;
    int cx = 140;
    int cy = 100;
    wchar_t c_x[20];
    wchar_t c_y[20];
    wchar_t c_cx[20];
    wchar_t c_cy[20];
}TagEventArea;
EventAreaType lfea;
ATOM EventAreaFrameRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wcex.lpfnWndProc = EventAreaFrameWndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MIN_ICON));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    //wcex.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(47, 52, 61));
    wcex.lpszMenuName = 0;
    wcex.lpszClassName = EventAreaszWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_MIN_ICON));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
void CheckEventAreaData(int flag = 0)
{
    char MCinventory[MAX_PATH] = "";
    strcpy(MCinventory, LocalDataA);
    strcat(MCinventory, "\\LightFrame\\LightFrame_EventArea_Test.vui");
    if (_access(MCinventory, 0) == -1)
    {

    }
    else
    {
        using namespace::std;
        auto obj2 = vui::parser::fparser(MCinventory, "MC");

        obj2.get("x", lfea.x);
        obj2.get("y", lfea.y);
        obj2.get("cx", lfea.cx);
        obj2.get("cy", lfea.cy);

    }
}
int LightFrame_Num_EventFrame = 0;
int EventAreaStat = 0;
int EventAreaStat2 = 0;
int CreateEventAreaFrame(int mode)
{
    //现在我们只需要在创建窗口的时候解析文件获取数值就好啦!（*゜ー゜*）
    // 将实例句柄存储在全局变量中
    EventAreaFrameRegisterClass(EventAreaFramehInst);
    CheckEventAreaData();
    XSleep(1);
    HWND hWnd = CreateWindow(EventAreaszWindowClass, EventAreaszTitle, WS_OVERLAPPEDWINDOW | WS_THICKFRAME,
        lfea.x, lfea.y, lfea.cx, lfea.cy, nullptr, nullptr, EventAreaFramehInst, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }
    LONG_PTR Style = ::GetWindowLongPtr(hWnd, GWL_STYLE);
    Style = Style & ~WS_CAPTION & ~WS_SYSMENU & ~WS_SIZEBOX;
    ::SetWindowLongPtr(hWnd, GWL_STYLE, Style);
    ::SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE)
        & ~WS_EX_APPWINDOW | WS_EX_TOOLWINDOW);
    ::SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);


    XSleep(5); //Hide frameless delay
    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);
    if (mode == 1)
    {
        cfp.LayerFlag = 0;
        SetLayeredWindowAttributes(hWnd, RGB(255, 255, 255), 1, LWA_ALPHA);
    }
    return TRUE;
}
void WriteEventAreaUserData(int flag = 0)
{
    wchar_t MCinventory[MAX_PATH] = L"";
    wcscpy(MCinventory, LocalData);
    wcscat(MCinventory, L"\\LightFrame_EventArea_Test.vui");

    FILE* fp = _wfopen(MCinventory, L"wt");
    if (!fp)
    {
        TipBox(0, 200, 200, L"缓存失败啦,检查权限和空间是否足够哦qwq");
    }
    if (fp)
    {
        _itow(lfea.x, lfea.c_x, 10);
        _itow(lfea.y, lfea.c_y, 10);
        _itow(lfea.cx, lfea.c_cx, 10);
        _itow(lfea.cy, lfea.c_cy, 10);
        fwprintf(fp,
            L"##MC\n"
            L"Object{x(%s),y(%s),cx(%s),cy(%s)}\n###"
            ,lfea.c_x,lfea.c_y,lfea.c_cx,lfea.c_cy
        );
        fclose(fp);
    }
}
//


LRESULT CALLBACK EventAreaFrameWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    RECT rc;
    GetClientRect(hWnd, &rc);
    RECT Winrc;
    GetWindowRect(hWnd, &Winrc);
    SYSTEMTIME time;
    GetLocalTime(&time);
    switch (message)
    {

    case WM_CREATE:
    {
        LightFrame_Num_EventFrame += 1;
        //设置分层窗口
        SetWindowLong(hWnd, GWL_EXSTYLE,
            GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
        SetLayeredWindowAttributes(hWnd, RGB(255, 255, 255), 220, LWA_ALPHA);
        EventAreaStat = 1;
        SetDoubleClickTime(0);
        //GhWnd = hWnd;
        break;
    }
    case WM_PAINT:
    {
        RECT wrc;
        GetWindowRect(hWnd, &wrc);
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 在此处添加使用 hdc 的任何绘图代码...
        HDC         hMemDC;
        HBITMAP     hBmpMem;
        HBITMAP     hPreBmp;
        RECT rc;
        GetClientRect(hWnd, &rc);
        //InvalidateRect(h, &rc, 1);
        hMemDC = CreateCompatibleDC(hdc);

        hBmpMem = CreateCompatibleBitmap(hdc, rc.right - rc.left, rc.bottom - rc.top);

        hPreBmp = (HBITMAP)SelectObject(hMemDC, hBmpMem);
        //On hMemDC.
        //DeleteObject(hRgn2);
        if (EventAreaStat == 0)//区域模式
        {
            CreateFillArea(hWnd, hMemDC, RGB(255, 255, 255));
        }
        if (EventAreaStat == 1)//更改模式
        {
            CreateFillArea(hWnd, hMemDC, RGB(255, 255, 255));
            CreateRect(hWnd, hMemDC, 0, 0, rc.right, 20, VERTEXUICOLOR_GREENSEA);
            TextPreDrawEx(hMemDC, 0, 0, rc.right - rc.left, 20, L" ▲\n◀  ●  ▶\n ▼", 5, 3, VERTEXUICOLOR_WHITE);
            PanelDrawCloseBtn(hWnd, hMemDC, rc.right - 20, rc.top, 20, 20, 3, VERTEXUICOLOR_WHITE);
            TextPreDrawEx(hMemDC, 0, 0, rc.right - rc.left, rc.bottom - rc.top, L">点击域<", 20, 1, VERTEXUICOLOR_SEA);
        }


        BitBlt(hdc, 0, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
        SelectObject(hMemDC, hPreBmp);


        DeleteObject(hBmpMem);

        DeleteDC(hMemDC);
        EndPaint(hWnd, &ps);

        break;
    }
    case WM_LBUTTONUP:
    {
        if (EventAreaStat2 != 2)
        {
            CreateMinecraftFrame();
        }
        else
        {
            break;
        }
    }
    case WM_SIZE:
    {
        InvalidateRect(hWnd, &rc, 1);
        break;
    }
    
    case WM_NCHITTEST:
    {
        if (EventAreaStat == 1)
        {
            POINT pt;
            pt.x = GET_X_LPARAM(lParam);
            pt.y = GET_Y_LPARAM(lParam);
            ::ScreenToClient(hWnd, &pt);

            RECT rcClient;
            ::GetClientRect(hWnd, &rcClient);

            if (pt.x < rcClient.left + 5 && pt.y < rcClient.top + 5) {
                return HTTOPLEFT;
            }
            else if (pt.x > rcClient.right - 5 && pt.y < rcClient.top + 5)
            {
                return HTTOPRIGHT;
            }
            else if (pt.x<rcClient.left + 5 && pt.y>rcClient.bottom - 5)
            {
                return HTBOTTOMLEFT;
            }
            else if (pt.x > rcClient.right - 5 && pt.y > rcClient.bottom - 5)
            {
                return HTBOTTOMRIGHT;
            }

            else if (pt.x < rcClient.left + 5)
            {
                return HTLEFT;
            }
            else if (pt.x > rcClient.right - 5)
            {
                return HTRIGHT;
            }
            else if (pt.y < rcClient.top + 5)
            {
                return HTTOP;
            }if (pt.y > rcClient.bottom - 5)
            {
                return HTBOTTOM;
            }
            else
            {
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
            break;
        }
        else
        {
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    case WM_LBUTTONDOWN:
    {
        RECT rc2;
        if (EventAreaStat == 1)
        {
            int val = 0;
            ClickAreaPtInfo(hWnd, 0, rc.top, rc.right - rc.left - 20, 20, lParam, val);
            if (val == 1)
            {
                SendMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
            }
            if(GetAreaPtInfo(hWnd,rc.right - 20,rc.top,20,20,rc2,lParam) == 1)
            {
                EventAreaStat2 = 2;
                FadeOutAnimation(hWnd);
                EventAreaStat2 = 0;

                DestroyWindow(hWnd);
            }
        }
        break;
    }
    case WM_RBUTTONDBLCLK:
    {
        if (EventAreaStat == 0)//更改模式
        {
            EventAreaStat = 1;
            SetLayeredWindowAttributes(hWnd, RGB(255, 255, 255), 220, LWA_ALPHA);
            XSleep(1);
            InvalidateRect(hWnd, &rc, 0);
            break;
        }
        if (EventAreaStat == 1)//区域模式 //按照用户习惯,我将保存放在双击事件中
        {
            EventAreaStat = 0;
            SetLayeredWindowAttributes(hWnd, RGB(255, 255, 255), 1, LWA_ALPHA);
            XSleep(1);
            RECT rc; //获取坐标
            RECT rc2;
            GetWindowRect(hWnd, &rc);
            GetClientRect(hWnd, &rc2);
            lfea.x = rc.left;
            lfea.y = rc.top;
            lfea.cx = rc2.right - rc2.left;
            lfea.cy = rc2.bottom - rc2.top;
            WriteEventAreaUserData();

            InvalidateRect(hWnd, &rc, 0);
            break;
        }
        break;
    }
    case WM_NCLBUTTONDBLCLK:
    {
        break;//禁止最大化
    }
    case WM_ERASEBKGND:
    {
        break;
    }
    case WM_WINDOWPOSCHANGING:
    case WM_WINDOWPOSCHANGED:
    {
        if (cfp.LayerFlag == 0)
        {
            WINDOWPOS* pPos = (WINDOWPOS*)lParam;
            pPos->hwndInsertAfter = HWND_BOTTOM;
        }
        if (cfp.LayerFlag == 1)
        {
            WINDOWPOS* pPos = (WINDOWPOS*)lParam;
            pPos->hwndInsertAfter = HWND_TOPMOST;
        }

        //return DefWindowProc(hWnd, message, wParam, lParam);
    }

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 分析菜单选择:
        switch (wmId)
        {

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_CLOSE:
    {
        LightFrame_Num_EventFrame -= 1;
        DestroyWindow(hWnd);
    }
    case WM_DESTROY:
    {
        DestroyWindow(hWnd);

        break;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}