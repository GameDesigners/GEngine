#ifndef GWINDOW_APPLICATION_H
#define GWINDOW_APPLICATION_H
#include "GApplication.h"

namespace GEngine {
	namespace GApp {
#ifdef WINDOWS
		class GAPPLICATION_API GWindowApplication : public GApplication
		{
		public:
			GWindowApplication() {}
			~GWindowApplication() {}
		public:
			virtual bool Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow);
			virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

		protected:
			virtual bool InitialWindow();
			virtual bool TerminalWindow();

			virtual bool PreInitial();
			virtual bool CreateGEngine();
			virtual bool OnInitial();
			virtual bool Run();
			virtual bool OnTerminal();
			virtual bool ReleaseGEngine();
		
		protected:
			virtual void GEngineInputProc(GInputDevices dt, KeyCode key, GMouseButton mb, GInputAction action, int xPos, int yPos, int zDet);

			HWND m_hwnd;
			HINSTANCE m_hInstance;
			HINSTANCE m_hPreInstance;
			int m_cmdShow;
		};

#endif // WINDOWS
#include "GWindowApplication.marc"
	}
}
#endif // !GWINDOW_APPLICATION_H
