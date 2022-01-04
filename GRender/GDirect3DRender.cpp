#include "GDirect3DRender.h"
using namespace GEngine::GSystem;
using namespace GEngine::GRender;

const int GDirect3DRender::ms_SwapChainBufferCount;

bool GEngine::GRender::GDirect3DRender::Get4xMsaaState() const { return m_4xMsaaState; }
void GEngine::GRender::GDirect3DRender::Set4xMsaaState(bool value) { m_4xMsaaState = value; }

bool GDirect3DRender::Initialize()
{
	//--------------------------------------------启用DEBUG调试层----------------------------------------------
    #if defined(DEBUG) || defined(_DEBUG)
	ComPtr<ID3D12Debug> debugController;
	D3D_THROW_IF_FAILED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)));
	debugController->EnableDebugLayer();
    #endif
	//--------------------------------------------启用DEBUG调试层----------------------------------------------




	//--------------------------------------------D3D12初始化过程----------------------------------------------
	// 1. 创建设备：m_d3dDevice的初始化
	// 2. 创建栅栏并获取描述符大小：m_d3dFence、m_rtvDescriptorSize、m_dsvDescriptorSize、m_cbvDescriptorSize的初始化
	// 3. 检测对4X MSAA质量级别的支持
	// 4. 创建命令队列和命令列表
	// 5. 描述并创建交换链
	// 6. 创建描述符堆
	// 7. 为交换链的每个缓冲区创建RTV
	// 8. 创建深度/模板缓冲区及视图
	// 9. 设置视口
	// 10.设置裁剪区域

	D3D_THROW_IF_FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&m_d3dGIFactory)));

	//1.
	HRESULT hardwareResult = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_d3dDevice));
	if (FAILED(hardwareResult))//硬件设备创建尝试失败，转软适配器
	{
		ComPtr<IDXGIAdapter> pWarpAdapter;
		D3D_THROW_IF_FAILED(m_d3dGIFactory->EnumWarpAdapter(IID_PPV_ARGS(&pWarpAdapter)));
		D3D_THROW_IF_FAILED(D3D12CreateDevice(pWarpAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_d3dDevice)));
	}

	//2.
	D3D_THROW_IF_FAILED(m_d3dDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_d3dFence)));
	m_rtvDescriptorSize = m_d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	m_dsvDescriptorSize = m_d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	m_cbvDescriptorSize = m_d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	//3.
	D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS msQualityLevels;
	msQualityLevels.Format = m_backBufferFormat;
	msQualityLevels.SampleCount = 4;
	msQualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
	msQualityLevels.NumQualityLevels = 0;
	D3D_THROW_IF_FAILED(m_d3dDevice->CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, &msQualityLevels, sizeof(msQualityLevels)));
	m_4xMsaaQuality = msQualityLevels.NumQualityLevels;
	assert(m_4xMsaaQuality > 0 && "Unexpected MSAA quality level");


	//4.
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	D3D_THROW_IF_FAILED(m_d3dDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_commandQueue)));
	D3D_THROW_IF_FAILED(m_d3dDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(m_directCmdListAlloc.GetAddressOf())));
	D3D_THROW_IF_FAILED(m_d3dDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_directCmdListAlloc.Get(), nullptr, IID_PPV_ARGS(m_commandList.GetAddressOf())));
	m_commandList->Close();

	//5.
	m_swapChain.Reset();
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = m_clientWidth;
	sd.BufferDesc.Height = m_clientHeight;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.Format = m_backBufferFormat;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.SampleDesc.Count = m_4xMsaaState ? 4 : 1;
	sd.SampleDesc.Quality = m_4xMsaaState ? m_4xMsaaQuality - 1 : 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = m_hMainWnd;
	sd.Windowed = m_bWindow;
	sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	D3D_THROW_IF_FAILED(m_d3dGIFactory->CreateSwapChain(m_commandQueue.Get(), &sd, m_swapChain.GetAddressOf()));


	//6.
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc;
	rtvHeapDesc.NumDescriptors = ms_SwapChainBufferCount;
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	rtvHeapDesc.NodeMask = 0;
	D3D_THROW_IF_FAILED(m_d3dDevice->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(m_rtvHeap.GetAddressOf())));

	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc;
	dsvHeapDesc.NumDescriptors = 1;
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	dsvHeapDesc.NodeMask = 0;
	D3D_THROW_IF_FAILED(m_d3dDevice->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(m_dsvHeap.GetAddressOf())));

	//7,8
	CreateRtvAndDsvDescriptorHeaps();

	//9.
	D3D12_VIEWPORT vp;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	vp.Width = static_cast<float>(m_clientWidth);
	vp.Height = static_cast<float>(m_clientHeight);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	m_commandList->RSSetViewports(1, &vp);

	//10.
	m_scissorRect = { 0,0,static_cast<long>(m_clientWidth) / 2,static_cast<long>(m_clientHeight) / 2 };
	m_commandList->RSSetScissorRects(1, &m_scissorRect);
	//--------------------------------------------D3D12初始化过程----------------------------------------------
	return true;

}

void GEngine::GRender::GDirect3DRender::CreateRtvAndDsvDescriptorHeaps()
{
	//7.
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHepHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart());
	for (UINT i = 0; i < ms_SwapChainBufferCount; i++)
	{
		//获得交换链内的第i个缓冲区
		D3D_THROW_IF_FAILED(m_swapChain->GetBuffer(i, IID_PPV_ARGS(&m_swapChainBuffer[i])));
		m_d3dDevice->CreateRenderTargetView(m_swapChainBuffer[i].Get(), nullptr, rtvHepHandle);
		rtvHepHandle.Offset(1, m_rtvDescriptorSize);
	}

	//8.
	D3D12_RESOURCE_DESC depthStencilDesc;
	depthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthStencilDesc.Alignment = 0;
	depthStencilDesc.Width = m_clientWidth;
	depthStencilDesc.Height = m_clientHeight;
	depthStencilDesc.DepthOrArraySize = 1;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.Format = m_depthStencilFormat;
	depthStencilDesc.SampleDesc.Count = m_4xMsaaState ? 4 : 1;
	depthStencilDesc.SampleDesc.Quality = m_4xMsaaState ? m_4xMsaaQuality - 1 : 0;
	depthStencilDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	depthStencilDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	D3D12_CLEAR_VALUE optClear;
	optClear.Format = m_depthStencilFormat;
	optClear.DepthStencil.Depth = 1.0f;
	optClear.DepthStencil.Stencil = 0;

	D3D_THROW_IF_FAILED(m_d3dDevice->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
		D3D12_HEAP_FLAG_NONE,
		&depthStencilDesc,
		D3D12_RESOURCE_STATE_COMMON,
		&optClear,
		IID_PPV_ARGS(m_depthStencilBuffer.GetAddressOf())
	));

	m_d3dDevice->CreateDepthStencilView(  //为整个资源的第0 mip层创建描述符
		m_depthStencilBuffer.Get(),
		nullptr,
		DepthStencilView()
	);

	m_commandList->ResourceBarrier(
		1,
		&CD3DX12_RESOURCE_BARRIER::Transition(
			m_depthStencilBuffer.Get(),
			D3D12_RESOURCE_STATE_COMMON,
			D3D12_RESOURCE_STATE_DEPTH_WRITE)
	);
}
