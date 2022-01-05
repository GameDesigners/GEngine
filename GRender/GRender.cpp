#include "GRender.h"
#include "GDirect3DRender.h"
#include "GOpenGLRender.h"
using namespace GEngine::GRender;

GEngine::GRender::GRender::GRender(HINSTANCE hInstance, HWND hwnd, UINT width, UINT height, bool bWindow)
{
	m_AppInstance = hInstance;
	m_hMainWnd = hwnd;
	m_clientWidth = width;
	m_clientHeight = height;
	m_bWindow = bWindow;
	m_pTimer = &GEngine::GSystem::GTimer::GetTimer();
}
GEngine::GRender::GRender::~GRender() {}

GRender*  GEngine::GRender::GRender::m_pRender = nullptr;
GRender*  GEngine::GRender::GRender::GetRenderSystem() { return m_pRender; }

bool GEngine::GRender::GRender::Initialize(RenderAPIType type, HINSTANCE hInstance, HWND hwnd, UINT width, UINT height, bool bWindow)
{
	switch (type)
	{
	case RenderAPIType::Direct3D:
		if (m_pRender == nullptr)
		{
			m_pRender = GNEW GDirect3DRender(hInstance, hwnd, width, height, bWindow);
			GASSERT(m_pRender != nullptr);
			return m_pRender->RenderAPIInitialze();
		}
		return true;

	case RenderAPIType::OpenGL:
		if (m_pRender == nullptr)
		{
			m_pRender = GNEW GOpenGLRender(hInstance, hwnd, width, height, bWindow);
			GASSERT(m_pRender != nullptr);
			return m_pRender->RenderAPIInitialze();
		}
		return true;
	default:
		return false;
	}
}

HINSTANCE GEngine::GRender::GRender::AppInstance() const { return m_AppInstance; }
HWND      GEngine::GRender::GRender::MainWnd() const { return m_hMainWnd; }
float     GEngine::GRender::GRender::AspectRatio() const { return static_cast<float>(m_clientWidth) / m_clientHeight; }
bool      GEngine::GRender::GRender::RenderAPIInitialze() { return true; }
void      GEngine::GRender::GRender::OnResize() {}
void      GEngine::GRender::GRender::Draw(){}

void GEngine::GRender::GRender::PauseRenderSystem()
{
	m_AppPaused = true;
	m_pTimer->Pause();
}

void GEngine::GRender::GRender::ResumeRenderSystem()
{
	m_AppPaused = true;
	m_pTimer->Start();
}

void GEngine::GRender::GRender::StartResize()
{
	PauseRenderSystem();
	m_Resizing = true;
}

void GEngine::GRender::GRender::FinishResize(UINT newWidth,UINT newHeight)
{
	ResumeRenderSystem();
	m_clientWidth = newWidth;
	m_clientHeight = newHeight;
	m_Resizing = false;
	OnResize();
}

void GEngine::GRender::GRender::MaximizeScreen()
{
	PauseRenderSystem();
	m_Minimized = true;
	m_Maximized = false;
}

void GEngine::GRender::GRender::MinimizeScreen()
{
	ResumeRenderSystem();
	m_Minimized = true;
	m_Maximized = false;
}
