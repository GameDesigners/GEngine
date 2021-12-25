#include "GConsoleApplication.h"
using namespace GEngine::GApp;

//应用程序入口
//**********************************************************************************************************************************************
//程序入口 [Console Application]
int main(int argc, char* argv[])
{
	GEngine::GGraphic::GMain::Initialize();
	if (GApplication::GetApplication() != nullptr)
	{
		if (!GApplication::GetApplication()->Main(argc, argv))
			GASSERT(0);
	}
	GEngine::GGraphic::GMain::Terminate();
	return 1;
}


GEngine::GApp::GConsoleApplication::GConsoleApplication() {}
GEngine::GApp::GConsoleApplication::~GConsoleApplication() {}

bool GEngine::GApp::GConsoleApplication::Main(int argc, char* argv[])
{
	m_pCommand = GNEW GCommand(argc, argv);
	if (m_pCommand == nullptr)
		return false;

	m_pGlobalTimer = &GTimer::GetTimer();
	GASSERT(m_pGlobalTimer != nullptr);

	//*引擎初始化工作*-------------------------
	if (!PreInitial())       return false;
	if (!CreateGEngine())    return false;
	if (!OnInitial())        return false;

	bool bError = false;
	if (!Run())              bError = true;

	//*引擎销毁工作*---------------------------
	if (!OnTerminal())       bError = true;
	if (!ReleaseGEngine())   bError = true;

	GSAFE_DELETE(m_pCommand);
	return !bError;
}

bool GEngine::GApp::GConsoleApplication::PreInitial()
{
	return true;
}

bool GEngine::GApp::GConsoleApplication::CreateGEngine()
{
	return true;
}

bool GEngine::GApp::GConsoleApplication::OnInitial()
{
	return true;
}

bool GEngine::GApp::GConsoleApplication::Run()
{
	return true;
}

bool GEngine::GApp::GConsoleApplication::OnTerminal()
{
	return true;
}

bool GEngine::GApp::GConsoleApplication::ReleaseGEngine()
{
	return true;
}
