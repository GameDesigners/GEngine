#ifndef GCONSOLE_APPLICATION_H
#define GCONSOLE_APPLICATION_H
#include "GApplication.h"
namespace GEngine {
	namespace GApp {
		class GAPPLICATION_API GConsoleApplication : public GApplication
		{
		public:
			GConsoleApplication();
			~GConsoleApplication();

		protected:
			virtual bool Main(int argc, char* argv[]);
			
			virtual bool PreInitial();
			virtual bool CreateGEngine();
			virtual bool OnInitial();
			virtual bool Run();
			virtual bool OnTerminal();
			virtual bool ReleaseGEngine();
		};
#include "GConsoleApplication.marc"
	}
}

#endif // !GCONSOLE_APPLICATION_H


