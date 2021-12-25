#ifndef GAPPLICATION_H
#define GAPPLICATION_H
#include <GTimer.h>
#include <GMemManager.h>
#include <GStrings.h>
#include "GCommand.h"

namespace GEngine {
	namespace GApp {
		using namespace GEngine::GSystem;

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
			RenderAPIType m_renderApiType;
			unsigned int  m_uiScreenWidth;
			unsigned int  m_uiScreenHeight;
			unsigned int  m_uiAnisotroty;    //�������
			unsigned int  m_uiMultiSample;
			unsigned int  m_UpdateThreadNum; //���̸߳���CPU����


			//��ܺ���(˳��->)
			//**********************************************************************************************************************************************

			virtual bool PreInitial();
			virtual bool CreateGEngine();
			virtual bool OnInitial();
			virtual bool Run();
			virtual bool OnTerminal();
			virtual bool ReleaseGEngine();


			//Run()���Ӻ���
            //**********************************************************************************************************************************************

			virtual bool PreUpdate();
			virtual bool PostUpdate();
			virtual bool OnDraw();

			//�������¼�����
			//**********************************************************************************************************************************************
			
			virtual void OnMove(int xPos, int yPos);
			virtual void OnResizeWindow(int iWidth, int iHeight);
			virtual void OnKeyDown(unsigned int uiKey);
			virtual void OnKeyUp(unsigned int uiKey);
			virtual void OnLButtonDown(int xPos, int yPos);
			virtual void OnLButtonUp(int xPos, int yPos);
			virtual void OnRButtonDown(int xPos, int yPos);
			virtual void OnRButtonUp(int xPos, int yPos);
			virtual void OnMButtonDown(int xPos, int yPos);
			virtual void OnMButtonUp(int xPos, int yPos);
			virtual void OnMouseMove(int xPos, int yPos);
			virtual void OnMouseWheel(int xPos, int yPos, int zDet);

			//���ķֱ���
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
