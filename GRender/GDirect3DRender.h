#ifndef GDIRECT3D_RENDER_H
#define GDIRECT3D_RENDER_H
#include <GSystem.h>
#include <GVector.h>
#include <GStrings.h>
#include "GRender.h"
#include "GDirect3DUtil.h"

namespace GEngine {
	namespace GRender{
		using namespace Microsoft::WRL;
		using namespace GEngine::GSystem;


		class GRENDER_API GDirect3DRender : public GRenderSystem
		{
		public:
			GDirect3DRender(HINSTANCE hInstance, HWND hwnd, UINT width = DEFAULT_SCREEN_WIDTH, UINT height = DEFAULT_SCREEN_HEIGHT, bool bWindow = true);
			virtual ~GDirect3DRender();
		public:
			virtual void Draw();
		public:
			bool Get4xMsaaState() const;
			void Set4xMsaaState(bool value);

			virtual bool RenderAPIInitialze();

			void CreateRtvAndDsvDescriptorHeaps();
			void CreateSwapChain();
			void CreateCommandObjects();
			void BuildFrameResources();
			void OnResize();
			void FlushCommandQueue();
			void LogAdapters();
			void LogdAdapterOutputs(IDXGIAdapter* adapter);
			void LogOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format);




		public:
			inline D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView() const {
				return CD3DX12_CPU_DESCRIPTOR_HANDLE(m_rtvHeap->GetCPUDescriptorHandleForHeapStart(), m_curBackBuffer, m_rtvDescriptorSize);
			}

			inline D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView() const {
				return m_dsvHeap->GetCPUDescriptorHandleForHeapStart();
			}

			inline ID3D12Resource* CurrentBackBuffer()const
			{
				return m_swapChainBuffer[m_curBackBuffer].Get();
			}



		public:
			static const int ms_SwapChainBufferCount = 2;

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

			DXGI_FORMAT m_backBufferFormat= DXGI_FORMAT_R8G8B8A8_UNORM;
			DXGI_FORMAT m_depthStencilFormat= DXGI_FORMAT_D24_UNORM_S8_UINT;
			UINT        m_4xMsaaQuality;

			D3D12_VIEWPORT m_viewport;

			bool        m_4xMsaaState = false;
			int         m_curBackBuffer = 0;

			const int gNumFrameResourceCount = GDirect3DSetting::gNumFrameResources;
			GStl::GVector<GStl::GSharedPtr<FrameResource>> mFrameResources;
			FrameResource* currentFrameResource = nullptr;

			GStl::GVector<GStl::GSharedPtr<GRenderItem>> mAllRitems;
			GStl::GVector<GRenderItem*> mOpaqueRitems;
		};
	}
}
#endif // !GDIRECT3D_RENDER_H
