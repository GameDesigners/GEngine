#include "GRender.h"
using namespace GEngine::GRender;

GEngine::GRender::GRender::GRender(HINSTANCE hInstance)
{
	m_AppInstance = hInstance;
	m_pTimer = &GEngine::GSystem::GTimer::GetTimer();
}
GEngine::GRender::GRender::~GRender() {}

GRender*  GEngine::GRender::GRender::m_pRender;
GRender*  GEngine::GRender::GRender::GetApp() { return m_pRender; }
HINSTANCE GEngine::GRender::GRender::AppInstance() const { return m_AppInstance; }
HWND      GEngine::GRender::GRender::MainWnd() const { return m_hMainWnd; }
float     GEngine::GRender::GRender::AspectRatio() const { return static_cast<float>(m_clientWidth) / m_clientHeight; }
bool      GEngine::GRender::GRender::Initialize() { return true; }
void      GEngine::GRender::GRender::OnResize() {}
void      GEngine::GRender::GRender::Draw(){}
