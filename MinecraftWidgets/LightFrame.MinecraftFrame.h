#pragma once

#include <Shlwapi.h>
#include <ShlObj_core.h>
#include <algorithm>
#include "LightFrame.Interface.h"
#include "framework.h"
#include "LightFrame.AA.h"
#include "LightFrame.DevLab.h"
#include "resource.h"
#include "VertexUI/vui.parser/vui.parser.hpp"
#include <vector>

#pragma warning(disable:4996)

#define MINECRAFT_BGCOLOR_BK RGB(198,198,198) //主要背景

#define MINECRAFT_BGCOLOR_BORDER_H RGB(255,255,255) //边框高光

#define MINECRAFT_BGCOLOR_BORDER_D RGB(0,0,0) //边框

#define MINECRAFT_BGCOLOR_UIITEM RGB(70,69,70) //控件

#define MINECRAFT_BGCOLOR_SHADOW RGB(85,85,85) //窗体阴影

#define MINECRAFT_BGCOLOR_ITEM RGB(139,139,139) //物品背景

#define MINECRAFT_BGCOLOR_HIGHLIGHT RGB(255,255,255) //物品高光

#define MINECRAFT_BGCOLOR_ITEMSHADOW RGB(55,55,55) //物品阴影

#define MINECRAFT_P_C1 RGB(184,148,95)
#define MINECRAFT_P_C2 RGB(175,143,85)
#define MINECRAFT_P_C3 RGB(194,157,98)

#define MINECRAFT_P_C4 RGB(150,116,65)
#define MINECRAFT_P_C5 RGB(184,148,95)
#define MINECRAFT_P_C6 RGB(159,132,77)
#define MINECRAFT_P_C7 RGB(103,80,44)//木板深
#define MINECRAFT_P_C8 RGB(126,98,55)//木板深(淡)


typedef struct chestitemslot {
	const wchar_t* dirToChange = L"";
	const wchar_t* dirDest = L"";
	std::vector<const wchar_t*>dirs;
	int dirid = 0;
	int id = 0;
	int exid = 0;
};

chestitemslot mcis;
#include "LightFrame.Window.h"
HINSTANCE MinecraftFramehInst;                                // 当前实例
const wchar_t* MCFrameszTitle = L"LightFrame.MinecraftFrame";                  // 标题栏文本
const wchar_t* MCFrameWindowClass = L"LightFrame.MinecraftWidget";            // 主窗口类名
// 此代码模块中包含的函数的前向声明:
ATOM                MinecraftFrameRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK    MinecraftFrameWndProc(HWND, UINT, WPARAM, LPARAM);
ATOM MinecraftFrameRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = MinecraftFrameWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MIN_ICON));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	//wcex.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(47, 52, 61));
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = MCFrameWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_MIN_ICON));

	return RegisterClassExW(&wcex);
}

int CreateMinecraftFrame()
{
	int scrx = GetSystemMetrics(SM_CXSCREEN); int scry = GetSystemMetrics(SM_CYSCREEN);
	MinecraftFrameRegisterClass(MinecraftFramehInst);
	HWND hWnd = CreateWindow(MCFrameWindowClass, MCFrameszTitle, WS_OVERLAPPEDWINDOW | WS_THICKFRAME,
		(scrx / 2) - (364 / 2), (scry / 2) - (338 / 2), 364, 338, nullptr, nullptr, MinecraftFramehInst, nullptr);

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
	CreateMaskBox(hWnd, 1);

	XSleep(5); //Hide frameless delay
	ShowWindow(hWnd, SW_SHOW);
	EaseInAnimationTest(hWnd);
	UpdateWindow(hWnd);

	return TRUE;
}
RECT prevrc = { 0 };
int GetAreaPtInfoEx(HWND hWnd, int x, int y, int sizex, int sizey, RECT& rc2, RECT& prc, LPARAM lParam)
{

	POINT pt;
	pt.x = LOWORD(lParam);
	pt.y = HIWORD(lParam);
	RECT rect;
	GetClientRect(hWnd, &rect);
	RECT  rc = { x,y,x + sizex,y + sizey };

	if (PtInRect(&rc, pt))
	{
		rc2 = { x,y,x + sizex,y + sizey };
		return 1;
	}
	else
	{
		/*
		prc = rc;
		if (ClickMsg == 1)
		{
			InvalidateRect(hWnd, &prevrc, 0);
			ClickMsg = 0;
			return 0;
		}
		*/
		return 0;
	}
	return -1;
}
HBITMAP ConvertIconToBitmap(HWND h, RECT rc, HICON  hIcon)
{
	HBITMAP   hBmp;
	BITMAP   bmp;
	HDC   bmpDC;
	HDC  iconDC;
	ICONINFO         csII;
	int bRetValue = ::GetIconInfo(hIcon, &csII);
	if (bRetValue == FALSE)   return   NULL;
	bmpDC = ::GetDC(h);
	iconDC = CreateCompatibleDC(bmpDC);

	if (::GetObject(csII.hbmColor, sizeof(BITMAP), &bmp))
	{
		DWORD       dwWidth = csII.xHotspot * 2;
		DWORD       dwHeight = csII.yHotspot * 2;
		hBmp = ::CreateBitmap(dwWidth, dwHeight, bmp.bmPlanes,
			bmp.bmBitsPixel, NULL);

		SelectObject(iconDC, csII.hbmColor);
		CreateRect(h, iconDC, rc.left + 2, rc.top + 2, 32, 32, MINECRAFT_BGCOLOR_ITEM);
		SelectObject(bmpDC, hBmp);

		BitBlt(bmpDC, rc.left + 2, rc.top + 2, 32, 32, iconDC, 0, 0, SRCCOPY);
		return   hBmp;
	}
	return NULL;
}
#define SAFE_DELETE(a) if( (a) != NULL ) delete (a); (a) = NULL;
#define SAFE_RELEASE(p) { if ( (p) ) { (p)->Release(); (p) = 0; } }
HBITMAP ExtractFileIcon(LPCTSTR pszPath, UINT nWidth, UINT nHeight)
{
	HBITMAP hBitmap = NULL;
	if ((NULL != pszPath) && (nWidth > 0.0) && (nHeight > 0.0))
	{
		IShellItemImageFactory* psif = NULL;
		SIZE size = { nWidth, nHeight };
		HRESULT hr = ::SHCreateItemFromParsingName(pszPath, NULL, IID_PPV_ARGS(&psif));
		if (SUCCEEDED(hr) && (NULL != psif))
		{
			psif->GetImage(size, SIIGBF_ICONONLY, &hBitmap);
			//OutputDebugString(L"114514");//测试完成
		}
		//psif->Release();
		SAFE_RELEASE(psif);
	}

	return hBitmap;
}
void GetIco(HICON& hico)
{
	hico = ExtractIcon(0, mcis.dirs[1], 0);
}
void DisplayIco(HDC hdc, RECT rc, HBITMAP hb)
{
	HDC hMemDC = CreateCompatibleDC(hdc);               // 创建一个兼容内存DC
	HGDIOBJ hOldObj = SelectObject(hMemDC, hb);   // 将g_bitmap选入到这个内存DC

	//BitBlt(hdc, x, y, ICON_WIDTH, ICON_HEIGHT, hMemDC, 0, 0, SRCCOPY);

	BLENDFUNCTION ftn = { 0 };
	ftn.BlendOp = AC_SRC_OVER;                           // 目前只能设置这个值
	ftn.AlphaFormat = AC_SRC_ALPHA;                      // 也只能设置这个值
	ftn.BlendFlags = 0;                                  // 必须为0
	ftn.SourceConstantAlpha = 255;                       // 指定源图片的alpha

	// 调用这个函数来进行Alpha混合
	AlphaBlend(hdc, rc.left + 2, rc.top + 2, 32, 32, hMemDC, 0, 0, 32, 32, ftn);

	SelectObject(hMemDC, hOldObj);
	DeleteObject(hMemDC);
	DeleteObject(hb);
}
void MCTextPreDraw(HDC hdc, int x, int y, int sizex, int sizey, const wchar_t* txt, COLORREF cl)
{
	RECT rc;
	RectTypeConvert(rc, x, y, sizex, sizey);
	LOGFONT lf;
	HFONT hFont = 0;
	SetTextColor(hdc, cl);
	SetBkMode(hdc, TRANSPARENT);
	if (hFont == 0)
	{
		memset(&lf, 0, sizeof(LOGFONT));
		lf.lfHeight = -18;
		wcscpy_s(lf.lfFaceName, L"System");
		hFont = CreateFontIndirect(&lf);  // create the font
	}
	HFONT old = (HFONT)SelectObject(hdc, hFont);
	DrawText(hdc, txt, wcslen(txt), &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	DeleteObject(hFont);
	SelectObject(hdc, old);
}
void WriteTESTUserData()
{
	wchar_t MCinventory[MAX_PATH] = L"";
	wcscpy(MCinventory, LocalData);
	wcscat(MCinventory, L"\\LightFrame_MC_Chest.vui");
	
	for (int i = 1; i <= 63; i++)
	{
		SetTagWW(mcis.dirs[i], L" ", L"%20");
	}
	
	FILE* fp = _wfopen(MCinventory, L"wt");
	if (!fp)
	{
		TipBox(0, 200,200,L"缓存失败啦,检查权限和空间是否足够哦qwq");
	}
	if (fp)
	{
		
		fwprintf(fp,
			L"##Inventory\n"
			L"Object{d1(%s),d2(%s),d3(%s),d4(%s),d5(%s),d6(%s),d7(%s),d8(%s),d9(%s),d10(%s),d11(%s),d12(%s),d13(%s),d14(%s),d15(%s),d16(%s),d17(%s),d18(%s),d19(%s),d20(%s),d21(%s),d22(%s),d23(%s),d24(%s),d25(%s),d26(%s),d27(%s),d28(%s),d29(%s),d30(%s),d31(%s),d32(%s),d33(%s),d34(%s),d35(%s),d36(%s),d37(%s),d38(%s),d39(%s),d40(%s),d41(%s),d42(%s),d43(%s),d44(%s),d45(%s),d46(%s),d47(%s),d48(%s),d49(%s),d50(%s),d51(%s),d52(%s),d53(%s),d54(%s),d55(%s),d56(%s),d57(%s),d58(%s),d59(%s),d60(%s),d61(%s),d62(%s),d63(%s)}\n###",
			mcis.dirs[1],mcis.dirs[2], mcis.dirs[3], mcis.dirs[4], mcis.dirs[5], mcis.dirs[6], mcis.dirs[7], mcis.dirs[8], mcis.dirs[9], mcis.dirs[10], mcis.dirs[11], mcis.dirs[12], mcis.dirs[13], mcis.dirs[14], mcis.dirs[15], mcis.dirs[16], mcis.dirs[17], mcis.dirs[18], mcis.dirs[19], mcis.dirs[20], mcis.dirs[21], mcis.dirs[22], mcis.dirs[23], mcis.dirs[24], mcis.dirs[25], mcis.dirs[26], mcis.dirs[27],  mcis.dirs[28], mcis.dirs[29], mcis.dirs[30], mcis.dirs[31], mcis.dirs[32], mcis.dirs[33], mcis.dirs[34], mcis.dirs[35], mcis.dirs[36], mcis.dirs[37], mcis.dirs[38], mcis.dirs[39], mcis.dirs[40], mcis.dirs[41], mcis.dirs[42], mcis.dirs[43], mcis.dirs[44], mcis.dirs[45], mcis.dirs[46], mcis.dirs[47], mcis.dirs[48], mcis.dirs[49], mcis.dirs[50], mcis.dirs[51], mcis.dirs[52], mcis.dirs[53], mcis.dirs[54], mcis.dirs[55], mcis.dirs[56], mcis.dirs[57], mcis.dirs[58], mcis.dirs[59], mcis.dirs[60], mcis.dirs[61], mcis.dirs[62], mcis.dirs[63]
		);
		fclose(fp);
	}
}
namespace mcrect
{
	std::vector<RECT>rc_ch = { 63,{0} };
	std::vector<HBITMAP>hbmp = {63 ,(0)};
	RECT g_rc;
	RECT rt;
	int msg = 0; //当一次Click后,设置为1,等待第二次click,条件符合则对这两个区域进行交换
	int msgc = 0;
	int cst = 0;
}

void MinecraftCheckChestItem(const wchar_t* dir, HDC hdc, RECT rc)
{
	using namespace::mcrect;
	/*
	RectTypeConvert(rc1, 16, 40, 37, 37);
	RectTypeConvert(rc2, 16 + 37, 40, 37, 37);
	RectTypeConvert(rc3, 16 + 37 * 2, 40, 37, 37);
	RectTypeConvert(rc4, 16 + 37 * 3, 40, 37, 37);
	RectTypeConvert(rc5, 16 + 37 * 4, 40, 37, 37);
	RectTypeConvert(rc6, 16 + 37 * 5, 40, 37, 37);
	HBITMAP hbmp1 = ExtractFileIcon(mcis.dirs[1], 32, 32); DisplayIco(hdc, rc1, hbmp1);
	HBITMAP hbmp2 = ExtractFileIcon(mcis.dirs[2], 32, 32); DisplayIco(hdc, rc2, hbmp2);
	HBITMAP hbmp3 = ExtractFileIcon(mcis.dirs[3], 32, 32); DisplayIco(hdc, rc3, hbmp3);
	HBITMAP hbmp4 = ExtractFileIcon(mcis.dirs[4], 32, 32); DisplayIco(hdc, rc4, hbmp4);
	HBITMAP hbmp5 = ExtractFileIcon(mcis.dirs[5], 32, 32); DisplayIco(hdc, rc5, hbmp5);
	HBITMAP hbmp6 = ExtractFileIcon(mcis.dirs[6], 32, 32); DisplayIco(hdc, rc6, hbmp6);
	*/
	int x;
	for (int i = 0; i <= 9; i++)
	{
		int x = 16 + 37 * (i - 1);
		RectTypeConvert(rc_ch[i], x, 40, 37, 37);
		hbmp[i] = ExtractFileIcon(mcis.dirs[i], 32, 32); DisplayIco(hdc, rc_ch[i], hbmp[i]);
	}
	for (int i = 10; i <= 18; i++)
	{
		int x = 16 + 37 * (i -9- 1);
		RectTypeConvert(rc_ch[i], x, 40 + 37, 37, 37);
		hbmp[i] = ExtractFileIcon(mcis.dirs[i], 32, 32); DisplayIco(hdc, rc_ch[i], hbmp[i]);
	}
	for (int i = 19; i <= 27; i++)
	{
		int x = 16 + 37 * (i -18- 1);
		RectTypeConvert(rc_ch[i], x, 40 + 37*2, 37, 37);
		hbmp[i] = ExtractFileIcon(mcis.dirs[i], 32, 32); DisplayIco(hdc, rc_ch[i], hbmp[i]);
	}//
	for (int i = 28; i <= 36; i++)
	{
		int x = 16 + 37 * (i - 27 - 1);
		RectTypeConvert(rc_ch[i], x, 172, 37, 37);
		hbmp[i] = ExtractFileIcon(mcis.dirs[i], 32, 32); DisplayIco(hdc, rc_ch[i], hbmp[i]);
	}
	for (int i = 37; i <= 45; i++)
	{
		int x = 16 + 37 * (i - 36 - 1);
		RectTypeConvert(rc_ch[i], x, 172 + 37, 37, 37);
		hbmp[i] = ExtractFileIcon(mcis.dirs[i], 32, 32); DisplayIco(hdc, rc_ch[i], hbmp[i]);
	}
	for (int i = 46; i <= 54; i++)
	{
		int x = 16 + 37 * (i - 45 - 1);
		RectTypeConvert(rc_ch[i], x, 172 + 37*2, 37, 37);
		hbmp[i] = ExtractFileIcon(mcis.dirs[i], 32, 32); DisplayIco(hdc, rc_ch[i], hbmp[i]);
	}
	for (int i = 55; i <= 63; i++)
	{
		int x = 16 + 37 * (i - 54 - 1);
		RectTypeConvert(rc_ch[i], x, 172 + 37 * 2 + 44, 37, 37);
		hbmp[i] = ExtractFileIcon(mcis.dirs[i], 32, 32); DisplayIco(hdc, rc_ch[i], hbmp[i]);
	}
}
void MinecraftChestDisplayItem(HDC hdc, int x, int y)
{

	//实在不行只能每一格单独画啦
	const wchar_t* dir = 0;
	/*
	if (mcrect::cst == 0)
	{
		mcis.id = -1;
		mcrect::cst = 1;
		for (int x = 16 - 37; x < (350 - 12); x += 37)
		{
			mcis.id++;
			RECT rc;
			RectTypeConvert(rc, x, y, 37, 37);

			MinecraftCheckChestItem(dir, hdc, rc);
		}
	}
	*/
	MinecraftCheckChestItem(dir, hdc, mcrect::g_rc);
}
void MinecraftDrawItem(HWND h, HDC hdc, int x, int y, int cx, int cy)
{
	CreateRect(h, hdc, x, y, cx, cy, MINECRAFT_BGCOLOR_ITEM);
	CreateRect(h, hdc, x, y, 2, cy, MINECRAFT_BGCOLOR_ITEMSHADOW);
	CreateRect(h, hdc, x, y, cx, 2, MINECRAFT_BGCOLOR_ITEMSHADOW);
	CreateRect(h, hdc, x, (y + cy) - 2, cx, 2, MINECRAFT_BGCOLOR_HIGHLIGHT);
	CreateRect(h, hdc, (x + cx) - 2, y, 2, cy, MINECRAFT_BGCOLOR_HIGHLIGHT);
}
void MinecraftSelectBox(HWND h, int x, int y, int cx, int cy)
{
	HDC hdc;
	hdc = GetDC(h);
	CreateRect(h, hdc, x, y, 2, cy, VERTEXUICOLOR_FOREST);
	CreateRect(h, hdc, x, y, cx, 2, VERTEXUICOLOR_FOREST);
	CreateRect(h, hdc, x, (y + cy) - 2, cx, 2, VERTEXUICOLOR_FOREST);
	CreateRect(h, hdc, (x + cx) - 2, y, 2, cy, VERTEXUICOLOR_FOREST);
	ReleaseDC(h, hdc);
}
//加油qwq awa
#define MinecraftUIRectOutput \
wsprintf(output1, L"%d", rt.left); \
OutputDebugString(output1); \
OutputDebugString(L" | "); \
wsprintf(output2, L"%d", prevrc.left); \
OutputDebugString(output2); \
wsprintf(output3, L"%d", mcis.id); \
OutputDebugString(L" | ItemID: "); \
OutputDebugString(output3); \
OutputDebugString(L" | EX: "); wsprintf(output4, L"%d", mcis.exid); OutputDebugString(output4);\
OutputDebugString(L" | Info: "); \
OutputDebugString(mcis.dirs[mcis.exid]); OutputDebugString(L" -> ");OutputDebugString(mcis.dirs[mcis.id]);OutputDebugString(L"  |1~3|  ");OutputDebugString(mcis.dirs[1]);OutputDebugString(L" - ");OutputDebugString(mcis.dirs[2]);OutputDebugString(L" - ");OutputDebugString(mcis.dirs[3]);     \
OutputDebugString(L"\n");
//实现:从另一个区域复制图标
//得到prevrc,将这个区域拷贝.
void swaps(const wchar_t*& a, const wchar_t*& b) {
	const wchar_t* temp = a;
	a = b;
	b = temp;
}
void MinecraftSetItem(HWND hWnd, int i, RECT rc)   // 触发:第二次点击
{
	mcrect::g_rc = rc;
	//HDC hdc = GetDC(hWnd);
	//mcis.exid = mcis.id;
	mcis.id = i;
	int Desttmp;
	swaps(mcis.dirs[mcis.exid], mcis.dirs[i]);
	InvalidateRect(hWnd, &rc, 0);
	InvalidateRect(hWnd, &prevrc, 0);
	XSleep(1);//重绘延迟1ms而已
}
void MinecraftTradeItem(HWND hWnd, int i)
{

}
int MinecraftUIArea(HWND hWnd, LPARAM lParam, int x, int y, int i)
{
	using namespace::mcrect;
	RECT rc;
	if (GetAreaPtInfo(hWnd, 16 + 37 * x, y, 37, 37, rc, lParam) == 1)
	{

		if (RDClickMsg == 1) { RDClickMsg = 0; msg = 0; if (mcis.dirs[i] == L" " || mcis.dirs[i] == L"NULL") { CreateOuterEditBox(hWnd,0,1); mcis.dirs[i] = EditReturnText;  InvalidateRect(hWnd, &rc, 0); } else { mcis.dirs[i] = L"NULL"; }InvalidateRect(hWnd, &rc, 0); /*MinecraftUIRectOutput;*/  return 0; }
		if (RClickMsg == 1)
		{
			RClickMsg = 0;
			prevrc = rt;
			GetAreaPtInfo(hWnd, 16 + 37 * x, y, 37, 37, rt, lParam);
			if (msg == 0) { msg = 1;  mcis.exid = i; MinecraftSelectBox(hWnd, rc.left, rc.top, 37, 37); return 0; }
			if (msg == 1) { msg = 0; msgc = 0;  MinecraftSetItem(hWnd, i, rc); }
			if (prevrc.left != rt.left)InvalidateRect(hWnd, &prevrc, 0);
			//MinecraftUIRectOutput;
		}
		if (ClickMsg == 1)
		{
			ClickMsg = 0;
			if (wcsstr(mcis.dirs[i], L".lnk"))
			{
				ShellExecute(hWnd, L"open", L"explorer.exe", mcis.dirs[i], 0, SW_SHOW);
				EaseOutAnimationTest(hWnd);
				SetDoubleClickTime(0);
				DestroyWindow(hWnd);
			}
			else
			{
				ShellExecute(hWnd, L"open", mcis.dirs[i], 0, 0, SW_SHOW);
			}
			if (mcis.dirs[i] != L" " || mcis.dirs[i] != L"NULL")
			{
				EaseOutAnimationTest(hWnd);
				SetDoubleClickTime(0);
				DestroyWindow(hWnd);
			}
			//ShellExecute(hWnd, L"open", mcis.dirs[2], 0, 0, SW_SHOW);
		}
		return 0;
	}
}
int MinecraftFrameAreaEvent(HWND hWnd, LPARAM lParam)
{
	using namespace::mcrect;
	RECT rc;
	RECT winrc;
	GetClientRect(hWnd, &winrc);
	/*
	for (int x = 16; x < (350 - 12); x += 37)
	{

		//MinecraftDrawItem(hWnd, hdc, x, 40, 37, 37);
	}
	*/
	wchar_t output1[100];
	wchar_t output2[100];
	wchar_t output3[100];
	wchar_t output4[100];
	if (GetAreaPtInfo(hWnd, 330, 20, 20, 10, rc, lParam) == 1)
	{
		if (ClickMsg == 1)
		{
			ClickMsg = 0;
			EaseOutAnimationTest(hWnd);
			WriteTESTUserData();
			mcis.dirs.clear();
			SetDoubleClickTime(0);
			DestroyWindow(hWnd);
		}

		return 0;
	}

	for (int i = 1; i <= 9; i++)
	{
		MinecraftUIArea(hWnd, lParam, i - 1, 40, i);
	}
	for (int i = 10; i <= 18; i++)
	{
		MinecraftUIArea(hWnd, lParam, i -9- 1, 40 + 37, i);
	}
	for (int i = 19; i <= 27; i++)
	{
		MinecraftUIArea(hWnd, lParam, i - 18-1, 40 + 37 * 2, i);
	}
	for (int i = 28; i <= 36; i++)
	{
		MinecraftUIArea(hWnd, lParam, i - 27 - 1, 172, i);
	}
	for (int i = 37; i <= 45; i++)
	{
		MinecraftUIArea(hWnd, lParam, i - 36 - 1, 172 + 37, i);
	}
	for (int i = 46; i <= 54; i++)
	{
		MinecraftUIArea(hWnd, lParam, i - 45 - 1, 172 + 37*2, i);
	}

	for (int i = 55; i <= 63; i++)
	{
		MinecraftUIArea(hWnd, lParam, i - 54 - 1, 172 + 37 * 2  + 44, i);
	}
	return 0;
}
void MinecraftUIInitDirs()
{
	
	
	char MCinventory[MAX_PATH] = "";
	strcpy(MCinventory, LocalDataA);
	strcat(MCinventory, "\\LightFrame\\LightFrame_MC_Chest.vui");
	if (_access(MCinventory, 0) == -1)
	{
		for(int i = 0;i<=63;i++)
		{
			mcis.dirs.push_back(L"NULL");
		}
	}
	else
	{
		auto obj = vui::parser::fparser(MCinventory, "Inventory");
		
		mcis.dirs.push_back(L" ");
		for (int i = 1; i <= 63; i++)
		{
			char dirstr[20] = "d";
			char dirid[20];
			itoa(i, dirid, 10);
			strcat(dirstr, dirid);
			mcis.dirs.push_back((VUIGetObject(obj, dirstr)));
		}


		
		for (int i = 1; i <= 63; i++)
		{
			SetTagWW(mcis.dirs[i], L"%20", L" ");
		}
		
	}
}
int nClickMsg = 0;
int LightFrame_Num_MinecraftFrame = 0;
LRESULT CALLBACK MinecraftFrameWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
		MinecraftUIInitDirs();
		SetDoubleClickTime(200);
		LightFrame_Num_MinecraftFrame += 1;
		HRGN hRgn = CreateRoundRectRgn(0, 0, 364, 338, 10, 10);
		SetWindowRgn(hWnd, hRgn, 0);
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
		HDC         hADC;
		HBITMAP     hBmpMem;
		HBITMAP     hPreBmp;
		RECT rc;
		GetClientRect(hWnd, &rc);
		//InvalidateRect(h, &rc, 1);
		hMemDC = CreateCompatibleDC(hdc);

		hADC = CreateCompatibleDC(hdc);

		hBmpMem = CreateCompatibleBitmap(hdc, rc.right - rc.left, rc.bottom - rc.top);

		hPreBmp = (HBITMAP)SelectObject(hMemDC, hBmpMem);
		//On hMemDC.
		SetWindowLong(hWnd, GWL_EXSTYLE,
			GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);


		CreateFillArea(hWnd, hMemDC, MINECRAFT_BGCOLOR_BK);
		//Do things there border = 12,ToTop = 40 item = 35x35(With border 37x37)
		//24 ||| 12
		//9 * 3

		MCTextPreDraw(hMemDC, 16, 20, 36, 18, L"箱子", MINECRAFT_BGCOLOR_UIITEM);
		for (int x = 16; x < (350 - 12); x += 37)
		{
			MinecraftDrawItem(hWnd, hMemDC, x, 40, 37, 37);
		}
		for (int x = 16; x < (350 - 12); x += 37)
		{
			MinecraftDrawItem(hWnd, hMemDC, x, 40 + 37, 37, 37);
		}
		for (int x = 16; x < (350 - 12); x += 37)
		{
			MinecraftDrawItem(hWnd, hMemDC, x, 40 + 37 + 37, 37, 37);
		}
		MCTextPreDraw(hMemDC, 16, 153, 36 + 18, 18, L"物品栏", MINECRAFT_BGCOLOR_UIITEM);
		for (int x = 16; x < (350 - 12); x += 37)
		{
			MinecraftDrawItem(hWnd, hMemDC, x, 172, 37, 37);
		}
		for (int x = 16; x < (350 - 12); x += 37)
		{
			MinecraftDrawItem(hWnd, hMemDC, x, 172 + 37, 37, 37);
		}
		for (int x = 16; x < (350 - 12); x += 37)
		{
			MinecraftDrawItem(hWnd, hMemDC, x, 172 + 37 + 37, 37, 37);
		}
		//hotbar
		for (int x = 16; x < (350 - 12); x += 37)
		{
			MinecraftDrawItem(hWnd, hMemDC, x, 172 + 37 + 37 + 44, 37, 37);
		}

		//
		for (int y = 18, x = 330; y < 10 + 20, x < 10 + 330; x += 2, y += 2)
		{
			CreateRect(hWnd, hMemDC, x, y, 2, 2, MINECRAFT_BGCOLOR_SHADOW);
		}
		for (int y = 26, x = 330; y < 18, x < 10 + 330; x += 2, y -= 2)
		{
			CreateRect(hWnd, hMemDC, x, y, 2, 2, MINECRAFT_BGCOLOR_SHADOW);
		}
		//
		CreateRect(hWnd, hMemDC, 0, 0, 366, 5, MINECRAFT_BGCOLOR_BORDER_H);
		CreateRect(hWnd, hMemDC, 0, 0, 5, 338, MINECRAFT_BGCOLOR_BORDER_H);
		CreateRect(hWnd, hMemDC, 5, 5, 2, 2, MINECRAFT_BGCOLOR_BORDER_H);

		//Right Bottom
		CreateRect(hWnd, hMemDC, 0, rc.bottom - 8, (rc.right - rc.left), 8, MINECRAFT_BGCOLOR_SHADOW);
		CreateRect(hWnd, hMemDC, rc.right - 8, 0, 8, (rc.bottom - rc.top), MINECRAFT_BGCOLOR_SHADOW);
		CreateRect(hWnd, hMemDC, rc.right - 8, rc.bottom - 8, 2, 2, MINECRAFT_BGCOLOR_SHADOW);
		//border
		CreateRect(hWnd, hMemDC, 0, 0, 366, 2, MINECRAFT_BGCOLOR_BORDER_D);
		CreateRect(hWnd, hMemDC, 0, 0, 2, 338, MINECRAFT_BGCOLOR_BORDER_D);
		CreateRect(hWnd, hMemDC, 2, 2, 2, 2, MINECRAFT_BGCOLOR_BORDER_D);
		CreateRect(hWnd, hMemDC, 0, rc.bottom - 4, (rc.right - rc.left), 4, MINECRAFT_BGCOLOR_BORDER_D);
		CreateRect(hWnd, hMemDC, rc.right - 4, 0, 4, (rc.bottom - rc.top), MINECRAFT_BGCOLOR_BORDER_D);
		CreateRect(hWnd, hMemDC, rc.right - 4, rc.bottom - 4, 2, 2, MINECRAFT_BGCOLOR_BORDER_D);
		BitBlt(hdc, 0, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
		//item
		//很烂的实现思路qwq
		MinecraftChestDisplayItem(hdc, 16, 40);

		SelectObject(hMemDC, hPreBmp);


		DeleteObject(hBmpMem);

		DeleteDC(hMemDC);
		EndPaint(hWnd, &ps);

		break;
	}

	case WM_SIZE:
	{

		break;
	}
	case WM_LBUTTONUP:
	{
		SnedClickEvent(hWnd, wParam, lParam);
		break;
	}
	case WM_RBUTTONUP:
	{
		SendRClickEvent(hWnd, wParam, lParam);
		break;
	}
	case WM_RBUTTONDBLCLK:
	{
		SendRDClickEvent(hWnd, wParam, lParam);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		RECT rc;
		if (GetAreaPtInfo(hWnd, 0, 0, 330, 40, rc, lParam) == 1)
		{
			SendMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
		}
		break;
	}
	case WM_MOUSEMOVE:
	{
		MinecraftFrameAreaEvent(hWnd, lParam);
		break;
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
			//pPos->hwndInsertAfter = HWND_BOTTOM;
			pPos->hwndInsertAfter = HWND_TOPMOST;
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
		LightFrame_Num_MinecraftFrame -= 1;
		SetDoubleClickTime(0);
		DestroyWindow(hWnd);
	}
	case WM_DESTROY:
	{
		DestroyWindow(hWnd);
		SetDoubleClickTime(0);
		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
