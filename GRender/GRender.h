#ifndef GRENDER_H
#define GRENDER_H
#include <Windows.h>
#include <wrl.h>
#include <direct.h>
#include <dxgi1_4.h>

#include <GSystem.h>
#include <GTimer.h>
#include <GStrings.h>

#include "libs/d3dx12.h"

#define GRENDER_EXPORTS
#ifdef GRENDER_EXPORTS
#define GRENDER_API __declspec(dllexport) 
#else 
#define GRENDER_API __declspec(dllimport) 
#endif

#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"D3D12.lib")
#pragma comment(lib,"dxgi.lib")

namespace GEngine {
	namespace GRender {
		class GRENDER_API GRender
		{
		public:
			GRender(HINSTANCE hInstance);
			virtual ~GRender();

			GRender(const GRender& rhs) = delete;
			void operator=(const GRender& rhs) = delete;

		public:
			static GRender* GetApp();
			static GRender* m_pRender;

			HINSTANCE AppInstance() const;
			HWND MainWnd() const;
			float AspectRatio() const;

			virtual bool Initialize();
			virtual void OnResize();
			virtual void Draw();


		protected:
			HINSTANCE                     m_AppInstance;
			HWND                          m_hMainWnd;
			

			UINT                          m_clientWidth;
			UINT                          m_clientHeight;
			bool                          m_bWindow = true;
			GEngine::GSystem::GTimer*     m_pTimer;
		};
	}
}
#endif // !GRENDER_H

