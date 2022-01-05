#ifndef GAPP_MACR_H
#define GAPP_MACR_H

#define GAPPLICATION_EXPORTS
#ifdef GAPPLICATION_EXPORTS
#define GAPPLICATION_API __declspec(dllexport) 
#else 
#define GAPPLICATION_API __declspec(dllimport) 
#endif

#include<Windows.h>
#include<GMain.h>
#include<GDirect3DRender.h>

namespace GEngine {
	namespace GApp {
	}
}

#endif // !GAPP_MACR_H
