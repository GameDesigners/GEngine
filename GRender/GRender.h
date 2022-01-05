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

		enum class RenderAPIType : unsigned char {
			Direct3D,
			OpenGL
		};

		class GDirect3DRender;
		class GOpenGLRender;

		class GRENDER_API GRender
		{
		protected:
			enum : UINT
			{
				DEFAULT_SCREEN_WIDTH  = 1280,
				DEFAULT_SCREEN_HEIGHT = 720
			};

		public:
			GRender(HINSTANCE hInstance, HWND hwnd, UINT width = DEFAULT_SCREEN_WIDTH, UINT height = DEFAULT_SCREEN_HEIGHT, bool bWindow = true);
			virtual ~GRender();

			GRender(const GRender& rhs) = delete;
			void operator=(const GRender& rhs) = delete;

		public:
			static GRender* m_pRender;
			static GRender* GetRenderSystem();
			static bool Initialize(RenderAPIType type, HINSTANCE hInstance, HWND hwnd, UINT width = DEFAULT_SCREEN_WIDTH, UINT height = DEFAULT_SCREEN_HEIGHT, bool bWindow = true);

			HINSTANCE AppInstance() const;
			HWND MainWnd() const;
			float AspectRatio() const;

			virtual bool RenderAPIInitialze();
			virtual void OnResize();
			virtual void Draw();

			void PauseRenderSystem();
			void ResumeRenderSystem();
			void StartResize();
			void FinishResize(UINT newWidth, UINT newHeight);
			void MaximizeScreen();
			void MinimizeScreen();

		protected:
			HINSTANCE m_AppInstance;
			HWND      m_hMainWnd;

			//State
			bool      m_AppPaused = false;
			bool      m_Minimized = false;
			bool      m_Maximized = false;
			bool      m_Resizing = false;
			bool      m_FullScreenState = false;
			
			UINT      m_clientWidth;
			UINT      m_clientHeight;
			bool      m_bWindow = true;
			GEngine::GSystem::GTimer* m_pTimer;
		};
	}
}
#endif // !GRENDER_H

