#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#include <Windows.h>
#ifdef _DEBUG
#include <iostream>
#include <tchar.h>
#endif // _DEBUG

using namespace std;

// @brief �R���\�[������ʂɃt�H�[�}�b�g�t���������\��
// @param format �t�H�[�}�b�g(%d�Ƃ�%f�Ȃǂ�)
// @param �ϒ�����
// @remarks ���̊֐��̓f�o�b�O�p�ł��B�f�o�b�O�̎��ɂ������삵�܂���
void DebugOutputFormatString(const char *format,...);
//�E�B���h�E�v���V�[�W���֐�(��Ώ����Ȃ���΂����Ȃ��֐�)
LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

#ifdef _DEBUG
int main()
{
	/*--- 1.�E�B���h�E�N���X�̐���&�o�^ ---*/
	WNDCLASSEX w = {};

	w.cbSize = sizeof(WNDCLASSEX);
	//�R�[���o�b�N�֐��̎w��
	w.lpfnWndProc = (WNDPROC)WindowProcedure;
	//�A�v���P�[�V�����̃N���X��(�K���ł�k)
	w.lpszClassName = _T("DirectX12_Initialize");
	//�n���h���̎擾
	w.hInstance = GetModuleHandle(nullptr);

	//�A�v���P�[�V�����N���X(�E�B���h�E�N���X�̎w���OS�ɓ`����)
	RegisterClassEx(&w);
	//�E�B���h�E�T�C�Y�����߂�
	RECT wrc = { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT };
	//�֐����g���ăE�B���h�E�̃T�C�Y��␳����
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	/*--- 2.�E�B���h�E�I�u�W�F�N�g�̍쐬 ---*/
	HWND hwnd = CreateWindow(w.lpszClassName,//�N���X���w��
		_T("DirectX12������"),	//�^�C�g���o�[�̕���
		WS_OVERLAPPEDWINDOW,	//�^�C�g���o�[�Ƌ��E��������E�B���h�E
		CW_USEDEFAULT,			//�\��x���W��OS�ɂ��C��
		CW_USEDEFAULT,			//�\��x���W��OS�ɂ��C��
		wrc.right - wrc.left,	//�E�B���h�E��
		wrc.bottom - wrc.top,	//�E�B���h�E��
		nullptr,				//�e�E�B���h�E�n���h��
		nullptr,				//���j���[�n���h��
		w.hInstance,			//�Ăяo���A�v���P�[�V�����n���h��
		nullptr);				//�ǉ��p�����[�^�[

	/*--- 3.�E�B���h�E�\�� ---*/
	ShowWindow(hwnd, SW_SHOW);

	MSG msg = {};

	while (true)
	{
		if (PeekMessage(&msg,nullptr,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//�A�v���P�[�V�������I���Ƃ���massage��WM_QUIT�ɂȂ�
		if (msg.message == WM_QUIT)
		{
			break;
		}
	}
	//�����N���X�͎g��Ȃ��̂œo�^����������
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
	//�E�B���h�E���j�����ꂽ��Ă΂��
	if (msg == WM_DESTROY)
	{
		PostQuitMessage(0);//OS�ɑ΂��āu�������̃A�v���͏I���v�Ɠ`����
		return 0;
	}
	//���̏������s��
	return DefWindowProcW(hwnd,msg,wparam,lparam);
}