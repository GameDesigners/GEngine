#include <GWindowApplication.h>
using namespace GEngine::GApp;

class CustomWindowApplication : public GWindowApplication
{
	DECLARE_WINDOW_APPLICATION(CustomWindowApplication)
};

REGIST_WINDOW_APPLICATION(CustomWindowApplication, L"GENGINE")