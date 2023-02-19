#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#include <Windows.h>
#ifdef _DEBUG
#include <iostream>
#include <tchar.h>
#endif // _DEBUG

using namespace std;

// @brief コンソールを画面にフォーマット付き文字列を表示
// @param format フォーマット(%dとか%fなどの)
// @param 可変長引数
// @remarks この関数はデバッグ用です。デバッグの時にしか動作しません
void DebugOutputFormatString(const char *format,...);
//ウィンドウプロシージャ関数(絶対書かなければいけない関数)
LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

#ifdef _DEBUG
int main()
{
	/*--- 1.ウィンドウクラスの生成&登録 ---*/
	WNDCLASSEX w = {};

	w.cbSize = sizeof(WNDCLASSEX);
	//コールバック関数の指定
	w.lpfnWndProc = (WNDPROC)WindowProcedure;
	//アプリケーションのクラス名(適当でおk)
	w.lpszClassName = _T("DirectX12_Initialize");
	//ハンドルの取得
	w.hInstance = GetModuleHandle(nullptr);

	//アプリケーションクラス(ウィンドウクラスの指定をOSに伝える)
	RegisterClassEx(&w);
	//ウィンドウサイズを決める
	RECT wrc = { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT };
	//関数を使ってウィンドウのサイズを補正する
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	/*--- 2.ウィンドウオブジェクトの作成 ---*/
	HWND hwnd = CreateWindow(w.lpszClassName,//クラス名指定
		_T("DirectX12初期化"),	//タイトルバーの文字
		WS_OVERLAPPEDWINDOW,	//タイトルバーと境界線があるウィンドウ
		CW_USEDEFAULT,			//表示x座標はOSにお任せ
		CW_USEDEFAULT,			//表示x座標はOSにお任せ
		wrc.right - wrc.left,	//ウィンドウ幅
		wrc.bottom - wrc.top,	//ウィンドウ高
		nullptr,				//親ウィンドウハンドル
		nullptr,				//メニューハンドル
		w.hInstance,			//呼び出しアプリケーションハンドル
		nullptr);				//追加パラメーター

	/*--- 3.ウィンドウ表示 ---*/
	ShowWindow(hwnd, SW_SHOW);

	MSG msg = {};

	while (true)
	{
		if (PeekMessage(&msg,nullptr,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//アプリケーションが終わるときにmassageがWM_QUITになる
		if (msg.message == WM_QUIT)
		{
			break;
		}
	}
	//もうクラスは使わないので登録を解除する
	UnregisterClass(w.lpszClassName, w.hInstance);
#else
int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
{
#endif // _DEBUG
	DebugOutputFormatString("Show window test.");
	getchar();
	return 0;
}

void DebugOutputFormatString(const char *format,...)
{
#ifdef _DEBUG
	va_list valist;
	va_start(valist, format);
	vprintf(format, valist);
	va_end(valist);
#endif // _DEBUG
}

LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//ウィンドウが破棄されたら呼ばれる
	if (msg == WM_DESTROY)
	{
		PostQuitMessage(0);//OSに対して「もうこのアプリは終わる」と伝える
		return 0;
	}
	//基底の処理を行う
	return DefWindowProcW(hwnd,msg,wparam,lparam);
}