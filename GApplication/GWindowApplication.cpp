#include "GWindowApplication.h"
using namespace GEngine::GApp;

//应用程序入口
//**********************************************************************************************************************************************

// 程序入口 [Windows Application]

int WINAPI WinMain(
	HINSTANCE hInst,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	GEngine::GGraphic::GMain::Initialize();
	if (GApplication::GetApplication() != nullptr)
	{
		if (!GApplication::GetApplication()->Main(hInst, hPrevInstance, lpCmdLine, nCmdShow))
			GASSERT(0);
	}
	GEngine::GGraphic::GMain::Terminate();
	return 1;
}

#ifdef WINDOWS
//[Windows Application]  Windows消息泵
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (GWindowApplication::GetApplication())
		return GWindowApplication::GetApplication()->MsgProc(hwnd, msg, wParam, lParam);
	else
		return -1;
}
#endif



bool GEngine::GApp::GWindowApplication::Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
	m_hInstance = hInstance;
	m_hPreInstance = hPrevInstance;
	m_pCommand = GNEW GCommand(pCmdLine);
	if (m_pCommand == nullptr)
		return false;
	m_cmdShow = nCmdShow;

	m_pGlobalTimer = &GTimer::GetTimer();
	GASSERT(m_pGlobalTimer != nullptr);

	//*引擎初始化工作*-------------------------
	if (!PreInitial())       return false;
	if (!InitialWindow())    return false;
	if (!CreateGEngine())    return false;
	if (!OnInitial())        return false;

	//*游戏循环部分*---------------------------
	MSG  msg = { 0 };
	bool bError = false;
	while (msg.message!=WM_QUIT)
	{
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (m_bIsActive)//窗口处于焦点
		{
			if (!Run())
			{
				m_bIsRunning = false;
				bError = true;
			}
			else
			{
				//处理其他需要更新的内容
			}
		}
	}

	//*引擎销毁工作*---------------------------
	if (!OnTerminal())       bError = true;
	if (!ReleaseGEngine())   bError = true;
	if (!TerminalWindow())   bError = true;

	GSAFE_DELETE(m_pCommand);
	return !bError;
}

LRESULT GEngine::GApp::GWindowApplication::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		MessageBox(0, L"Hello ,GEngine...", L"Hello", MB_OK);
		return 0;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			DestroyWindow(m_hwnd);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

bool GEngine::GApp::GWindowApplication::Run()
{
	/*PreUpdate();
	OnDraw();
	PostUpdate();*/
	return true;
}

bool GEngine::GApp::GWindowApplication::InitialWindow()
{
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = MainWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInstance;
	wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = m_WndClassName.c_str();
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassExW(&wcex))
	{
		MessageBox(NULL,
			L"Call to RegisterClassEx failed!",
			L"Windows Desktop Guided Tour",
			NULL);
		return false;
	}

	m_hwnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		m_WndClassName.c_str(),
		m_ApplicationTitle.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		m_uiScreenWidth,
		m_uiScreenHeight,
		NULL,
		NULL,
		m_hInstance,
		NULL
	);

	if (!m_hwnd)
	{
		MessageBox(NULL,
			L"Call to CreateWindowEx failed!",
			L"Windows Desktop Guided Tour",
			NULL);
		return false;
	}

	ShowWindow(m_hwnd, m_cmdShow);
	UpdateWindow(m_hwnd);
	return true;
}

bool GEngine::GApp::GWindowApplication::TerminalWindow()
{
	return UnregisterClass(L"BasicWndClassName", m_hInstance);
}
