#include <GWindowApplication.h>
#include <DirectXMath.h>
#include <GArray.h>
#include <GVector.h>
#include <GMemory.h>
#include <GMath.h>
using namespace GEngine::GApp;
using namespace DirectX;
using namespace GEngine::GStl;
using namespace GEngine::GRender;
using namespace GEngine::GMath;



class CustomWindowApplication : public GWindowApplication
{
	~CustomWindowApplication() 
	{

	}
private:
	MeshGeometry mBoxGeo;

	DECLARE_WINDOW_APPLICATION(CustomWindowApplication)

	virtual bool OnInitial();
	virtual bool Update();
	virtual bool OnDraw();
	virtual void OnKeyDown(KeyCode uiKey);

	virtual void OnLButtonDown(int xPos, int yPos);
	virtual void OnMouseMove(WPARAM btnState, int xPos, int yPos);
	virtual void OnLButtonUp(int xPos, int yPos);

	void BuildDescriptorHeaps();
	void BuildConstantBuffers();
	void BuildBoxGeometry();
	void BuildShadersAndInputLayout();
	void BuildRootSignature();
	void BuildPSO();

private:
	ComPtr<ID3DBlob> mvsByteCode = nullptr;
	ComPtr<ID3DBlob> mpsByteCode = nullptr;
	GEngine::GStl::GVector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;

	ComPtr<ID3D12RootSignature> mRootSignature = nullptr;
	ComPtr<ID3D12DescriptorHeap> mCbvHeap = nullptr;
	GSharedPtr<GUploadBuffer<ObjectConstants>> mObjectCB;

	ComPtr<ID3D12PipelineState> mPSO = nullptr;

	XMFLOAT4X4 mWorld = MathHelper::Identity4x4();
	XMFLOAT4X4 mView = MathHelper::Identity4x4();
	XMFLOAT4X4 mProj = MathHelper::Identity4x4();

	float mTheta = 1.5f * XM_PI;
	float mPhi = XM_PIDIV4;
	float mRadius = 5.0f;

	POINT mLastMousePos;

	GDirect3DRender* pRender = nullptr;
};

REGIST_WINDOW_APPLICATION(CustomWindowApplication, L"GENGINE")

bool CustomWindowApplication::OnInitial()
{
	pRender = static_cast<GDirect3DRender*>(GRenderSystem::GetRenderSystem());
	D3D_THROW_IF_FAILED(pRender->m_commandList->Reset(pRender->m_directCmdListAlloc.Get(), nullptr));
	BuildDescriptorHeaps();
	BuildConstantBuffers();
	BuildRootSignature();
	BuildShadersAndInputLayout();
	BuildBoxGeometry();
	BuildPSO();

	// Execute the initialization commands.
	D3D_THROW_IF_FAILED(pRender->m_commandList->Close());
	ID3D12CommandList* cmdsLists[] = { pRender->m_commandList.Get() };
	pRender->m_commandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	// Wait until initialization is complete.
	pRender->FlushCommandQueue();

	XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f * GPI, pRender->AspectRatio(), 1.0f, 1000.0f);
	XMStoreFloat4x4(&mProj, P);

	return true;
}

bool CustomWindowApplication::Update()
{
	float x = mRadius * GSin(mPhi) * GCos(mTheta);
	float z = mRadius * GSinf(mPhi) * GSinf(mTheta);
	float y = mRadius * GCosf(mPhi);

	XMVECTOR pos = XMVectorSet(x, y, z, 1.0f);
	XMVECTOR target = XMVectorZero();
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMMATRIX view = XMMatrixLookAtLH(pos, target, up);
	XMStoreFloat4x4(&mView, view);

	XMMATRIX world = XMLoadFloat4x4(&mWorld);
	XMMATRIX proj = XMLoadFloat4x4(&mProj);
	XMMATRIX worldViewProj = world * view * proj;

	// Update the constant buffer with the latest worldViewProj matrix.
	ObjectConstants objConstants;
	XMStoreFloat4x4(&objConstants.WorldViewProj, XMMatrixTranspose(worldViewProj));
	mObjectCB->CopyData(0, objConstants);
	return true;
}

bool CustomWindowApplication::OnDraw()
{
	//初始化窗口示例
	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	/*
	D3D_THROW_IF_FAILED(pRender->m_directCmdListAlloc->Reset());
	D3D_THROW_IF_FAILED(pRender->m_commandList->Reset(pRender->m_directCmdListAlloc.Get(), nullptr));

	pRender->m_commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(pRender->CurrentBackBuffer(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));
	pRender->m_commandList->RSSetViewports(1, &pRender->m_viewport);
	pRender->m_commandList->RSSetScissorRects(1, &pRender->m_scissorRect);
	pRender->m_commandList->ClearRenderTargetView(pRender->CurrentBackBufferView(), Colors::Black, 0, nullptr);
	pRender->m_commandList->ClearDepthStencilView(pRender->DepthStencilView(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);
	pRender->m_commandList->OMSetRenderTargets(1, &pRender->CurrentBackBufferView(), true, &pRender->DepthStencilView());
	pRender->m_commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(pRender->CurrentBackBuffer(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));
	D3D_THROW_IF_FAILED(pRender->m_commandList->Close());

	ID3D12CommandList* cmdsLists[] = { pRender->m_commandList.Get() };
	pRender->m_commandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);
	D3D_THROW_IF_FAILED(pRender->m_swapChain->Present(0, 0));
	pRender->m_curBackBuffer = (pRender->m_curBackBuffer + 1) % pRender->ms_SwapChainBufferCount;
	pRender->FlushCommandQueue();
	*/
	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	D3D_THROW_IF_FAILED(pRender->m_directCmdListAlloc->Reset());
	D3D_THROW_IF_FAILED(pRender->m_commandList->Reset(pRender->m_directCmdListAlloc.Get(), mPSO.Get()));
	
	pRender->m_commandList->RSSetViewports(1, &pRender->m_viewport);
	pRender->m_commandList->RSSetScissorRects(1, &pRender->m_scissorRect);
	
	pRender->m_commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(pRender->CurrentBackBuffer(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));
	pRender->m_commandList->ClearRenderTargetView(pRender->CurrentBackBufferView(), Colors::Black, 0, nullptr);
	pRender->m_commandList->ClearDepthStencilView(pRender->DepthStencilView(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);
	pRender->m_commandList->OMSetRenderTargets(1, &pRender->CurrentBackBufferView(), true, &pRender->DepthStencilView());

	ID3D12DescriptorHeap* descriptorHeaps[] = { mCbvHeap.Get() };
	pRender->m_commandList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);
	pRender->m_commandList->SetGraphicsRootSignature(mRootSignature.Get());
	pRender->m_commandList->IASetVertexBuffers(0, 1, &mBoxGeo.VertexBufferView());
	pRender->m_commandList->IASetIndexBuffer(&mBoxGeo.IndexBufferView());
	pRender->m_commandList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pRender->m_commandList->SetGraphicsRootDescriptorTable(0, mCbvHeap->GetGPUDescriptorHandleForHeapStart());
	pRender->m_commandList->DrawIndexedInstanced(mBoxGeo.DrawArgs["box"].IndexCount, 1, 0, 0, 0);

	pRender->m_commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(pRender->CurrentBackBuffer(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));
	D3D_THROW_IF_FAILED(pRender->m_commandList->Close());
	ID3D12CommandList* cmdsLists[] = { pRender->m_commandList.Get() };
	pRender->m_commandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);
	D3D_THROW_IF_FAILED(pRender->m_swapChain->Present(0, 0));
	pRender->m_curBackBuffer = (pRender->m_curBackBuffer + 1) % pRender->ms_SwapChainBufferCount;
	pRender->FlushCommandQueue();

	return true;
}

void CustomWindowApplication::OnKeyDown(KeyCode uiKey)
{
	if (uiKey == KeyCode::A)
	{
		MessageBox(m_hwnd, L"Hello GEngine.", L"Hello", MB_OK);
	}
}

void CustomWindowApplication::OnLButtonDown(int xPos, int yPos)
{
	mLastMousePos.x = xPos;
	mLastMousePos.y = yPos;
	SetCapture(m_hwnd);
}

void CustomWindowApplication::OnMouseMove(WPARAM btnState, int xPos, int yPos)
{
	if ((btnState & MK_LBUTTON) != 0)
	{
		// Make each pixel correspond to a quarter of a degree.
		float dx = XMConvertToRadians(0.25f * static_cast<float>(xPos - mLastMousePos.x));
		float dy = XMConvertToRadians(0.25f * static_cast<float>(yPos - mLastMousePos.y));

		// Update angles based on input to orbit camera around box.
		mTheta += dx;
		mPhi += dy;

		// Restrict the angle mPhi.
		mPhi = GClamp(mPhi, 0.1f, GPI - 0.1f);
	}
	else if ((btnState & MK_RBUTTON) != 0)
	{
		// Make each pixel correspond to 0.005 unit in the scene.
		float dx = 0.005f * static_cast<float>(xPos - mLastMousePos.x);
		float dy = 0.005f * static_cast<float>(yPos - mLastMousePos.y);

		// Update the camera radius based on input.
		mRadius += dx - dy;

		// Restrict the radius.
		mRadius = GClamp(mRadius, 3.0f, 15.0f);
	}

	mLastMousePos.x = xPos;
	mLastMousePos.y = yPos;
}

void CustomWindowApplication::OnLButtonUp(int xPos, int yPos)
{
	ReleaseCapture();
}

void CustomWindowApplication::BuildDescriptorHeaps()
{
	D3D12_DESCRIPTOR_HEAP_DESC cbvHeapDesc;
	cbvHeapDesc.NumDescriptors = 1;
	cbvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	cbvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	cbvHeapDesc.NodeMask = 0;
	
	
	D3D_THROW_IF_FAILED(pRender->m_d3dDevice->CreateDescriptorHeap(&cbvHeapDesc, IID_PPV_ARGS(&mCbvHeap)));
}

void CustomWindowApplication::BuildConstantBuffers()
{
	
	mObjectCB = g_make_shared<GUploadBuffer<ObjectConstants>>(pRender->m_d3dDevice.Get(), 1, true);
	unsigned int objCBByteSize = CaculateConstantBufferByteSize(sizeof(ObjectConstants));
	D3D12_GPU_VIRTUAL_ADDRESS cbAddress = mObjectCB->Resource()->GetGPUVirtualAddress();
	int boxCBufIndex = 0;
	cbAddress += boxCBufIndex * objCBByteSize;

	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
	cbvDesc.BufferLocation = cbAddress;
	cbvDesc.SizeInBytes = CaculateConstantBufferByteSize(sizeof(ObjectConstants));

	pRender->m_d3dDevice->CreateConstantBufferView(
		&cbvDesc,
		mCbvHeap->GetCPUDescriptorHandleForHeapStart());
}

void CustomWindowApplication::BuildBoxGeometry()
{
	GArray<GVertex, 8> vertices =
	{
		GVertex({ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(Colors::White) }),
		GVertex({ XMFLOAT3(-1.0f, +1.0f, -1.0f), XMFLOAT4(Colors::Black) }),
		GVertex({ XMFLOAT3(+1.0f, +1.0f, -1.0f), XMFLOAT4(Colors::Red) }),
		GVertex({ XMFLOAT3(+1.0f, -1.0f, -1.0f), XMFLOAT4(Colors::Green) }),
		GVertex({ XMFLOAT3(-1.0f, -1.0f, +1.0f), XMFLOAT4(Colors::Blue) }),
		GVertex({ XMFLOAT3(-1.0f, +1.0f, +1.0f), XMFLOAT4(Colors::Yellow) }),
		GVertex({ XMFLOAT3(+1.0f, +1.0f, +1.0f), XMFLOAT4(Colors::Cyan) }),
		GVertex({ XMFLOAT3(+1.0f, -1.0f, +1.0f), XMFLOAT4(Colors::Magenta) })
	};

	GArray<unsigned short, 36> indices =
	{
		// front face
		0, 1, 2,
		0, 2, 3,

		// back face
		4, 6, 5,
		4, 7, 6,

		// left face
		4, 5, 1,
		4, 1, 0,

		// right face
		3, 2, 6,
		3, 6, 7,

		// top face
		1, 5, 6,
		1, 6, 2,

		// bottom face
		4, 0, 3,
		4, 3, 7
	};

	const unsigned int vbByteSize = sizeof(GVertex) * vertices.size();
	const unsigned int ibByteSize = sizeof(unsigned short) * indices.size();

	

	mBoxGeo.Name = "boxGeo";
	D3DCreateBlob(vbByteSize, &mBoxGeo.VertexBufferCPU);
	CopyMemory(mBoxGeo.VertexBufferCPU->GetBufferPointer(), vertices.data(), vbByteSize);

	D3DCreateBlob(ibByteSize, &mBoxGeo.IndexBufferCPU);
	CopyMemory(mBoxGeo.IndexBufferCPU->GetBufferPointer(), indices.data(), ibByteSize);

	mBoxGeo.VertexBufferGPU = CreateDefaultBuffer(pRender->m_d3dDevice.Get(), pRender->m_commandList.Get(), vertices.data(), vbByteSize, mBoxGeo.VertexBufferUploader);
	mBoxGeo.IndexBufferGPU = CreateDefaultBuffer(pRender->m_d3dDevice.Get(), pRender->m_commandList.Get(), indices.data(), ibByteSize, mBoxGeo.IndexBufferUploader);

	mBoxGeo.VertexByteStride = sizeof(GVertex);
	mBoxGeo.VertexBufferByteSize = vbByteSize;
	mBoxGeo.IndexFormat = DXGI_FORMAT_R16_UINT;
	mBoxGeo.IndexBufferByteSize = ibByteSize;

	SubmeshGeometry submesh;
	submesh.IndexCount = (UINT)indices.size();
	submesh.StartIndexLocation = 0;
	submesh.BaseVertexLocation = 0;
	mBoxGeo.DrawArgs.insert("box", submesh);
}

void CustomWindowApplication::BuildShadersAndInputLayout()
{
	HRESULT hr = S_OK;

	mvsByteCode = CompileShader(L"Shaders\\BoxShader.hlsl", nullptr, "VS", "vs_5_0");
	mpsByteCode = CompileShader(L"Shaders\\BoxShader.hlsl", nullptr, "PS", "ps_5_0");
	
	mInputLayout =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0},
		{"COLOR",0,DXGI_FORMAT_R32G32B32_FLOAT,0,sizeof(XMFLOAT3),D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0}
	};
}

void CustomWindowApplication::BuildRootSignature()
{
	CD3DX12_ROOT_PARAMETER slotRootParameter[1];
	CD3DX12_DESCRIPTOR_RANGE cbvTable;
	cbvTable.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);
	slotRootParameter[0].InitAsDescriptorTable(1,&cbvTable);

	CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(1, slotRootParameter, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
	Microsoft::WRL::ComPtr<ID3DBlob> serializedRootSig = nullptr;
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;
	HRESULT hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1, serializedRootSig.GetAddressOf(), errorBlob.GetAddressOf());
	if (errorBlob != nullptr)
		GOutputDebugStringA((char*)errorBlob->GetBufferPointer());

	
	D3D_THROW_IF_FAILED(hr);
	D3D_THROW_IF_FAILED(pRender->m_d3dDevice->CreateRootSignature(
		0,
		serializedRootSig->GetBufferPointer(),
		serializedRootSig->GetBufferSize(),
		IID_PPV_ARGS(&mRootSignature)
	));
}

void CustomWindowApplication::BuildPSO()
{
	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc;
	ZeroMemory(&psoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	psoDesc.InputLayout = { mInputLayout.data(), (UINT)mInputLayout.size() };
	psoDesc.pRootSignature = mRootSignature.Get();
	psoDesc.VS =
	{
		reinterpret_cast<BYTE*>(mvsByteCode->GetBufferPointer()),
		mvsByteCode->GetBufferSize()
	};
	psoDesc.PS =
	{
		reinterpret_cast<BYTE*>(mpsByteCode->GetBufferPointer()),
		mpsByteCode->GetBufferSize()
	};
	

	psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	psoDesc.SampleMask = UINT_MAX;
	psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	psoDesc.NumRenderTargets = 1;
	psoDesc.RTVFormats[0] = pRender->m_backBufferFormat;
	psoDesc.SampleDesc.Count = pRender->m_4xMsaaState ? 4 : 1;
	psoDesc.SampleDesc.Quality = pRender->m_4xMsaaState ? (pRender->m_4xMsaaQuality - 1) : 0;
	psoDesc.DSVFormat = pRender->m_depthStencilFormat;
	D3D_THROW_IF_FAILED(pRender->m_d3dDevice->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&mPSO)));
}
