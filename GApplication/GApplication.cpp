#include "GApplication.h"
using namespace GEngine::GApp;

GApplication* GApplication::ms_pApplication = nullptr;
GApplication*& GEngine::GApp::GApplication::GetApplication()
{
	return ms_pApplication;
}
bool GEngine::GApp::GApplication::Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow) { return true; }
bool GEngine::GApp::GApplication::Main(int argc, char* argv[]) { return true; }
LRESULT GEngine::GApp::GApplication::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){ return LRESULT();}
bool GEngine::GApp::GApplication::PreInitial() { return true; }
bool GEngine::GApp::GApplication::CreateGEngine() { return true; }
bool GEngine::GApp::GApplication::OnInitial() { return true; }
bool GEngine::GApp::GApplication::Run() { return true; }
bool GEngine::GApp::GApplication::OnTerminal() { return true; }
bool GEngine::GApp::GApplication::ReleaseGEngine() { return true; }
bool GEngine::GApp::GApplication::PreUpdate() { return true; }
bool GEngine::GApp::GApplication::PostUpdate() { return true; }
bool GEngine::GApp::GApplication::OnDraw() { return true; }


void GEngine::GApp::GApplication::GEngineInputProc(GInputDevices dt, KeyCode key, GMouseButton mb, GInputAction action, int xPos, int yPos, int zDet) {}
void GEngine::GApp::GApplication::OnMove(int xPos, int yPos) {}
void GEngine::GApp::GApplication::OnResizeWindow(int iWidth, int iHeight) {}
void GEngine::GApp::GApplication::OnKeyDown(KeyCode uiKey) {}
void GEngine::GApp::GApplication::OnKeyUp(KeyCode uiKey) {}
void GEngine::GApp::GApplication::OnLButtonDown(int xPos, int yPos) {}
void GEngine::GApp::GApplication::OnLButtonUp(int xPos, int yPos) {}
void GEngine::GApp::GApplication::OnRButtonDown(int xPos, int yPos) {}
void GEngine::GApp::GApplication::OnRButtonUp(int xPos, int yPos) {}
void GEngine::GApp::GApplication::OnMButtonDown(int xPos, int yPos) {}
void GEngine::GApp::GApplication::OnMButtonUp(int xPos, int yPos) {}
void GEngine::GApp::GApplication::OnMouseMove(int xPos, int yPos) {}
void GEngine::GApp::GApplication::OnMouseWheel(int xPos, int yPos, int zDet) {}
void GEngine::GApp::GApplication::ChangeScreenSize(unsigned int uiWidth, unsigned int uiHeight, bool bWindow, bool isMaxScreen) {}