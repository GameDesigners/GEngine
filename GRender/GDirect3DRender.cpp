#include "GDirect3DRender.h"
using namespace GEngine::GSystem;
using namespace GEngine::GRender;
using namespace DirectX;

const int GDirect3DRender::ms_SwapChainBufferCount;

GEngine::GRender::GDirect3DRender::GDirect3DRender(HINSTANCE hInstance, HWND hwnd, UINT width, UINT height, bool bWindow)
	: GRenderSystem(hInstance, hwnd, width, height, bWindow) {}

GEngine::GRender::GDirect3DRender::~GDirect3DRender()
{
	if (m_d3dDevice != nullptr)
		FlushCommandQueue();

	GSAFE_DELETE(m_pRender);
}

bool GEngine::GRender::GDirect3DRender::Get4xMsaaState() const { return m_4xMsaaState; }
void GEngine::GRender::GDirect3DRender::Set4xMsaaState(bool value) { m_4xMsaaState = value; }

bool GDirect3DRender::RenderAPIInitialze()
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
	CreateCommandObjects();
	CreateSwapChain();
	CreateRtvAndDsvDescriptorHeaps();

	//--------------------------------------------D3D12初始化过程----------------------------------------------
	OnResize();
#ifdef _DEBUG
	LogAdapters();
#endif

	return true;
}

void GEngine::GRender::GDirect3DRender::CreateRtvAndDsvDescriptorHeaps()
{
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
}

void GEngine::GRender::GDirect3DRender::CreateCommandObjects()
{
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	D3D_THROW_IF_FAILED(m_d3dDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_commandQueue)));
	D3D_THROW_IF_FAILED(m_d3dDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(m_directCmdListAlloc.GetAddressOf())));
	D3D_THROW_IF_FAILED(m_d3dDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_directCmdListAlloc.Get(), nullptr, IID_PPV_ARGS(m_commandList.GetAddressOf())));
	m_commandList->Close();
}

void GEngine::GRender::GDirect3DRender::CreateSwapChain()
{
	m_swapChain.Reset();

	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = m_clientWidth;
	sd.BufferDesc.Height = m_clientHeight;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = m_backBufferFormat;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.SampleDesc.Count = m_4xMsaaState ? 4 : 1;
	sd.SampleDesc.Quality = m_4xMsaaState ? m_4xMsaaQuality - 1 : 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = ms_SwapChainBufferCount;
	sd.OutputWindow = m_hMainWnd;
	sd.Windowed = m_bWindow;
	sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	D3D_THROW_IF_FAILED(m_d3dGIFactory->CreateSwapChain(m_commandQueue.Get(), &sd, m_swapChain.GetAddressOf()));
}

void GEngine::GRender::GDirect3DRender::OnResize()
{
	GASSERT(m_d3dDevice);
	GASSERT(m_swapChain);
	GASSERT(m_directCmdListAlloc);

	FlushCommandQueue();

	D3D_THROW_IF_FAILED(m_commandList->Reset(m_directCmdListAlloc.Get(), nullptr));
	for (int i = 0; i < ms_SwapChainBufferCount; ++i)
		m_swapChainBuffer[i].Reset();
	m_depthStencilBuffer.Reset();

	D3D_THROW_IF_FAILED(m_swapChain->ResizeBuffers(ms_SwapChainBufferCount, m_clientWidth, m_clientHeight, m_backBufferFormat, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH));
	m_curBackBuffer = 0;

	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart());
	for (UINT i = 0; i < ms_SwapChainBufferCount; i++)
	{
		D3D_THROW_IF_FAILED(m_swapChain->GetBuffer(i, IID_PPV_ARGS(&m_swapChainBuffer[i])));
		m_d3dDevice->CreateRenderTargetView(m_swapChainBuffer[i].Get(), nullptr, rtvHeapHandle);
		rtvHeapHandle.Offset(1, m_rtvDescriptorSize);
	}

	// Create the depth/stencil buffer and view.
	D3D12_RESOURCE_DESC depthStencilDesc;
	depthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthStencilDesc.Alignment = 0;
	depthStencilDesc.Width = m_clientWidth;
	depthStencilDesc.Height = m_clientHeight;
	depthStencilDesc.DepthOrArraySize = 1;
	depthStencilDesc.MipLevels = 1;

	// Correction 11/12/2016: SSAO chapter requires an SRV to the depth buffer to read from 
	// the depth buffer.  Therefore, because we need to create two views to the same resource:
	//   1. SRV format: DXGI_FORMAT_R24_UNORM_X8_TYPELESS
	//   2. DSV Format: DXGI_FORMAT_D24_UNORM_S8_UINT
	// we need to create the depth buffer resource with a typeless format.  
	depthStencilDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;

	depthStencilDesc.SampleDesc.Count = m_4xMsaaState ? 4 : 1;
	depthStencilDesc.SampleDesc.Quality = m_d3dDevice ? (m_4xMsaaQuality - 1) : 0;
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
		IID_PPV_ARGS(m_depthStencilBuffer.GetAddressOf())));

	// Create descriptor to mip level 0 of entire resource using the format of the resource.
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	dsvDesc.Flags = D3D12_DSV_FLAG_NONE;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Format = m_depthStencilFormat;
	dsvDesc.Texture2D.MipSlice = 0;
	m_d3dDevice->CreateDepthStencilView(m_depthStencilBuffer.Get(), &dsvDesc, DepthStencilView());

	// Transition the resource from its initial state to be used as a depth buffer.
	m_commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(m_depthStencilBuffer.Get(),
		D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_DEPTH_WRITE));

	// Execute the resize commands.
	D3D_THROW_IF_FAILED(m_commandList->Close());
	ID3D12CommandList* cmdsLists[] = { m_commandList.Get() };
	m_commandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	// Wait until resize is complete.
	FlushCommandQueue();

	// Update the viewport transform to cover the client area.
	m_viewport.TopLeftX = 0;
	m_viewport.TopLeftY = 0;
	m_viewport.Width = static_cast<float>(m_clientWidth);
	m_viewport.Height = static_cast<float>(m_clientHeight);
	m_viewport.MinDepth = 0.0f;
	m_viewport.MaxDepth = 1.0f;

	m_scissorRect = { 0, 0, static_cast<long>(m_clientWidth), static_cast<long>(m_clientHeight) };
}

void GEngine::GRender::GDirect3DRender::Draw()
{
	D3D_THROW_IF_FAILED(m_directCmdListAlloc->Reset());
	D3D_THROW_IF_FAILED(m_commandList->Reset(m_directCmdListAlloc.Get(), nullptr));

	m_commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));
	m_commandList->RSSetViewports(1, &m_viewport);
	m_commandList->RSSetScissorRects(1, &m_scissorRect);
	m_commandList->ClearRenderTargetView(CurrentBackBufferView(), Colors::Black, 0, nullptr);
	m_commandList->ClearDepthStencilView(DepthStencilView(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);
	m_commandList->OMSetRenderTargets(1, &CurrentBackBufferView(), true, &DepthStencilView());
	m_commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));
	D3D_THROW_IF_FAILED(m_commandList->Close());

	ID3D12CommandList* cmdsLists[] = { m_commandList.Get() };
	m_commandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);
	D3D_THROW_IF_FAILED(m_swapChain->Present(0, 0));
	m_curBackBuffer = (m_curBackBuffer + 1) % ms_SwapChainBufferCount;
	FlushCommandQueue();
}

void GEngine::GRender::GDirect3DRender::FlushCommandQueue()
{
	m_currentFence++;
	D3D_THROW_IF_FAILED(m_commandQueue->Signal(m_d3dFence.Get(), m_currentFence));
	if (m_d3dFence->GetCompletedValue() < m_currentFence)
	{
		HANDLE eventHandle = CreateEventEx(nullptr, false, false, EVENT_ALL_ACCESS);
		D3D_THROW_IF_FAILED(m_d3dFence->SetEventOnCompletion(m_currentFence, eventHandle));
		WaitForSingleObject(eventHandle, INFINITE);
		CloseHandle(eventHandle);
	}
}


//Adapters Debug信息代码
//************************************************************************************************************************************************
void GEngine::GRender::GDirect3DRender::LogAdapters()
{
	UINT index = 0;
	IDXGIAdapter* adapter = nullptr;
	GStl::GVector<IDXGIAdapter*> adapterList;
	while (m_d3dGIFactory->EnumAdapters(index,&adapter)!= DXGI_ERROR_NOT_FOUND)
	{
		DXGI_ADAPTER_DESC desc;
		adapter->GetDesc(&desc);
		GStl::GTString text = L"***Adapter: ";
		text += desc.Description;
		text += L"\n";
		GOutputDebugStringW(text.c_str());
		adapterList.push_back(adapter);
		++index;
	}

	for (size_t index = 0; index < adapterList.size(); index++)
	{
		LogdAdapterOutputs(adapterList[index]);
		if (adapterList[index])
		{
			adapterList[index]->Release();
			adapterList[index] = nullptr;
		}
	}
}

void GEngine::GRender::GDirect3DRender::LogdAdapterOutputs(IDXGIAdapter* adapter)
{
	UINT index = 0;
	IDXGIOutput* output = nullptr;
	while (adapter->EnumOutputs(index, &output) != DXGI_ERROR_NOT_FOUND)
	{
		DXGI_OUTPUT_DESC desc;
		output->GetDesc(&desc);

		GStl::GTString text = L"***Output: ";
		text += desc.DeviceName;
		text += L"\n";
		GOutputDebugStringW(text.c_str());

		LogOutputDisplayModes(output, m_backBufferFormat);

		if (output)
		{
			output->Release();
			output = nullptr;
		}
		++index;
	}
}

void GEngine::GRender::GDirect3DRender::LogOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format)
{
	UINT count = 0;
	UINT flags = 0;

	// Call with nullptr to get list count.
	output->GetDisplayModeList(format, flags, &count, nullptr);

	GStl::GVector<DXGI_MODE_DESC> modeList(count);
	output->GetDisplayModeList(format, flags, &count, &modeList[0]);

	for (auto& x : modeList)
	{
		UINT n = x.RefreshRate.Numerator;
		UINT d = x.RefreshRate.Denominator;
		GStl::GTString text = L"Width =%d Height =%d Refresh = %d/%d\n";
		GOutputDebugStringW(text.c_str(), x.Width, x.Height, n, d);
	}
}
