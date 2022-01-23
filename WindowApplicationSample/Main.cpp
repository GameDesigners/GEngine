#include <GWindowApplication.h>
#include <DirectXMath.h>
#include <GDirect3DRender.h>
using namespace GEngine::GApp;
using namespace GEngine::GRender;
using namespace DirectX;



class CustomWindowApplication : public GWindowApplication
{
	DECLARE_WINDOW_APPLICATION(CustomWindowApplication)

	virtual bool OnInitial();
	virtual bool OnDraw();
	virtual void OnKeyDown(KeyCode uiKey);
	/*virtual void OnKeyUp(KeyCode uiKey);
	virtual void OnLButtonDown(int xPos, int yPos);
	virtual void OnLButtonUp(int xPos, int yPos);
	virtual void OnRButtonDown(int xPos, int yPos);
	virtual void OnRButtonUp(int xPos, int yPos);
	virtual void OnMButtonDown(int xPos, int yPos);
	virtual void OnMButtonUp(int xPos, int yPos);
	virtual void OnMouseMove(int xPos, int yPos);
	virtual void OnMouseWheel(int xPos, int yPos, int zDet);*/
	GDirect3DRender* pRender = nullptr;
};

REGIST_WINDOW_APPLICATION(CustomWindowApplication, L"GENGINE")

bool CustomWindowApplication::OnInitial()
{
	pRender = static_cast<GDirect3DRender*>(GRenderSystem::GetRenderSystem());
	return true;
}
bool CustomWindowApplication::OnDraw()
{
	//初始化窗口示例
	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
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
	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	return true;
}

void CustomWindowApplication::OnKeyDown(KeyCode uiKey)
{
	if (uiKey == KeyCode::A)
	{
		MessageBox(m_hwnd, L"Hello GEngine.", L"Hello", MB_OK);
	}
}
