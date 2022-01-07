#ifndef GAPPLICATION_H
#define GAPPLICATION_H
#include <GTimer.h>
#include <GMemManager.h>
#include <GStrings.h>
#include <GInput.h>
#include <GDirect3DRender.h>
#include "GCommand.h"

namespace GEngine {
	namespace GApp {
		using namespace GEngine::GSystem;
		using namespace GEngine::GInput;
		using namespace GEngine::GRender;

		class GAPPLICATION_API GApplication : public GMemObject
		{

		public:
			static GApplication* ms_pApplication;
			static GApplication*& GetApplication();

			virtual bool Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow);
			virtual bool Main(int argc, char* argv[]);
			virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

		public:
			GApplication() {}
			~GApplication() {}

		public:
			GCommand*     m_pCommand;
			RenderAPIType m_renderApiType= RenderAPIType::Direct3D;
			unsigned int  m_uiScreenWidth;
			unsigned int  m_uiScreenHeight;
			unsigned int  m_uiAnisotroty;    //异向过滤
			unsigned int  m_uiMultiSample;
			unsigned int  m_UpdateThreadNum; //多线程更新CPU个数


			//框架函数(顺序->)
			//**********************************************************************************************************************************************

			virtual bool PreInitial();
			virtual bool CreateGEngine();
			virtual bool OnInitial();
			virtual bool Run();
			virtual bool OnTerminal();
			virtual bool ReleaseGEngine();


			//Run()的子函数
            //**********************************************************************************************************************************************

			virtual bool PreUpdate();
			virtual bool Update();
			virtual bool OnDraw();
			virtual bool PostUpdate();

			virtual void OnMove(int xPos, int yPos);
			virtual void OnResizeWindow(int iWidth, int iHeight);

			//鼠标键盘事件函数
			//**********************************************************************************************************************************************
			
			virtual void GEngineInputProc(GInputDevices dt, KeyCode key,GMouseButton mb, GInputAction action, int xPos, int yPos, int zDet);
			virtual void OnKeyDown(KeyCode uiKey);
			virtual void OnKeyUp(KeyCode uiKey);
			virtual void OnLButtonDown(int xPos, int yPos);
			virtual void OnLButtonUp(int xPos, int yPos);
			virtual void OnRButtonDown(int xPos, int yPos);
			virtual void OnRButtonUp(int xPos, int yPos);
			virtual void OnMButtonDown(int xPos, int yPos);
			virtual void OnMButtonUp(int xPos, int yPos);
			virtual void OnMouseMove(WPARAM btnState, int xPos, int yPos);
			virtual void OnMouseWheel(int xPos, int yPos, int zDet);

			//更改分辨率
			virtual void ChangeScreenSize(unsigned int uiWidth, unsigned int uiHeight, bool bWindow, bool isMaxScreen = false);

			bool m_bIsActive;
			bool m_bIsRunning;
			GStl::GTString m_WndClassName;
			GStl::GTString m_ApplicationTitle;
			GTimer* m_pGlobalTimer;
		};
	}
}

#endif // !GAPPLICATION_H
