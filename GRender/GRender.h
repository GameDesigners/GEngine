#ifndef GRENDER_H
#define GRENDER_H
#include <Windows.h>
#include <wrl.h>
#include <direct.h>
#include <dxgi1_4.h>

#include <GSystem.h>

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
		using namespace Microsoft::WRL;
		using namespace GEngine::GSystem;

		class GRENDER_API GRender
		{
		public:
			GRender(HINSTANCE hInstance);
			~GRender();

			GRender(const GRender& rhs) = delete;
			void operator=(const GRender& rhs) = delete;

		public:
			static GRender* GetApp();

			HINSTANCE AppInstance() const;
			HWND MainWnd() const;
			float AspectRatio() const;
			bool Get4xMsaaState() const;
			void Set4xMsaaState(bool value);
			void Initialize();


		private:
			D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView() const {
				return CD3DX12_CPU_DESCRIPTOR_HANDLE(m_rtvHeap->GetCPUDescriptorHandleForHeapStart(), m_curBackBuffer, m_rtvDescriptorSize);
			}

			D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView() const {
				return m_dsvHeap->GetCPUDescriptorHandleForHeapStart();
			}	

		private:
			static const int ms_SwapChainBufferCount = 2;

			HINSTANCE m_AppInstance;
			HWND      m_hMainWnd;

			ComPtr<IDXGIFactory4> m_d3dGIFactory;
			ComPtr<ID3D12Device>  m_d3dDevice;
			ComPtr<ID3D12Fence>   m_d3dFence;
			UINT m_currentFence = 0;

			ComPtr<ID3D12CommandQueue> m_commandQueue;
			ComPtr<ID3D12CommandAllocator> m_directCmdListAlloc;
			ComPtr<ID3D12GraphicsCommandList> m_commandList;

			ComPtr<IDXGISwapChain> m_swapChain;
			ComPtr<ID3D12Resource> m_swapChainBuffer[ms_SwapChainBufferCount];

			size_t m_rtvDescriptorSize = 0;
			size_t m_dsvDescriptorSize = 0;
			size_t m_cbvDescriptorSize = 0;
			ComPtr<ID3D12DescriptorHeap> m_rtvHeap;
			ComPtr<ID3D12DescriptorHeap> m_dsvHeap;
			ComPtr<ID3D12Resource>       m_depthStencilBuffer;
			D3D12_RECT                   m_scissorRect;

			DXGI_FORMAT m_backBufferFormat;
			DXGI_FORMAT m_depthStencilFormat;
			UINT        m_4xMsaaQuality;
			UINT        m_clientWidth;
			UINT        m_clientHeight;

			bool        m_4xMsaaState = true;
			int         m_curBackBuffer = 0;
		};
	}
}
#endif // !GRENDER_H

