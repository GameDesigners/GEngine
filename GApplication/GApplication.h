#ifndef GAPPLICATION_H
#define GAPPLICATION_H

#define GAPPLICATION_EXPORTS
#ifdef GAPPLICATION_EXPORTS
#define GAPPLICATION_API __declspec(dllexport) 
#else 
#define GAPPLICATION_API __declspec(dllimport) 
#endif

#include <GMemManager.h>
namespace GEngine {
	namespace GApp {
		using namespace GEngine::GSystem;

		class GAPPLICATION_API GApplication : public GMemObject
		{

		private:
			static GApplication* ms_pApplication;
		};
	}
}

#endif // !GAPPLICATION_H
