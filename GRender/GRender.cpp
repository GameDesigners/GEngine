#include "GRender.h"
#include "GDirect3DRender.h"
#include "GOpenGLRender.h"
using namespace GEngine::GRender;

GEngine::GRender::GRenderSystem::GRenderSystem(HINSTANCE hInstance, HWND hwnd, UINT width, UINT height, bool bWindow)
{
	m_AppInstance = hInstance;
	m_hMainWnd = hwnd;
	m_clientWidth = width;
	m_clientHeight = height;
	m_bWindow = bWindow;
	m_pTimer = &GEngine::GSystem::GTimer::GetTimer();
}
GEngine::GRender::GRenderSystem::~GRenderSystem() {}

GRenderSystem*  GEngine::GRender::GRenderSystem::m_pRender = nullptr;
GRenderSystem*  GEngine::GRender::GRenderSystem::GetRenderSystem() { return m_pRender; }

bool GEngine::GRender::GRenderSystem::Initialize(RenderAPIType type, HINSTANCE hInstance, HWND hwnd, UINT width, UINT height, bool bWindow)
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

bool GEngine::GRender::GRenderSystem::Terminal(RenderAPIType type)
{
	if (type == RenderAPIType::Direct3D)
	{
		GDirect3DRender* p = static_cast<GDirect3DRender*>(m_pRender);
		if (p->m_d3dDevice != nullptr)
			p->FlushCommandQueue();

		GSAFE_DELETE(m_pRender);
		return true;
	}
	else if (type == RenderAPIType::OpenGL)
	{
		GOpenGLRender* p = static_cast<GOpenGLRender*>(m_pRender);
		GSAFE_DELETE(p);
		return true;
	}
	else
		return false;

}

HINSTANCE GEngine::GRender::GRenderSystem::AppInstance() const { return m_AppInstance; }
HWND      GEngine::GRender::GRenderSystem::MainWnd() const { return m_hMainWnd; }
float     GEngine::GRender::GRenderSystem::AspectRatio() const { return static_cast<float>(m_clientWidth) / m_clientHeight; }
bool      GEngine::GRender::GRenderSystem::RenderAPIInitialze() { return true; }
void      GEngine::GRender::GRenderSystem::OnResize() {}
void      GEngine::GRender::GRenderSystem::Draw() {}

void GEngine::GRender::GRenderSystem::PauseRenderSystem()
{
	m_AppPaused = true;
	m_pTimer->Pause();
}

void GEngine::GRender::GRenderSystem::ResumeRenderSystem()
{
	m_AppPaused = true;
	m_pTimer->Start();
}

void GEngine::GRender::GRenderSystem::StartResize()
{
	PauseRenderSystem();
	m_Resizing = true;
}

void GEngine::GRender::GRenderSystem::FinishResize()
{
	ResumeRenderSystem();
	m_Resizing = false;
	OnResize();
}

void GEngine::GRender::GRenderSystem::MaximizeScreen()
{
	PauseRenderSystem();
	m_Minimized = true;
	m_Maximized = false;
}

void GEngine::GRender::GRenderSystem::MinimizeScreen()
{
	ResumeRenderSystem();
	m_Minimized = true;
	m_Maximized = false;
}

void GEngine::GRender::GRenderSystem::SetRenderClientSize(UINT width, UINT height)
{
	m_clientWidth = width;
	m_clientHeight = height;
}

bool GEngine::GRender::GRenderSystem::IsMaximizeScreenState()
{
	return m_Maximized;
}

bool GEngine::GRender::GRenderSystem::IsMinimizeScreenState()
{
	return m_Minimized;
}

bool GEngine::GRender::GRenderSystem::IsResizing()
{
	return m_Resizing;
}
