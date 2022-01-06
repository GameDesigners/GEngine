#include <GWindowApplication.h>
#include <DirectXMath.h>
#include <GArray.h>
#include <GMemory.h>
using namespace GEngine::GApp;
using namespace DirectX;
using namespace GEngine::GStl;
using namespace GEngine::GRender;



class CustomWindowApplication : public GWindowApplication
{
private:
	MeshGeometry mBoxGeo;

	DECLARE_WINDOW_APPLICATION(CustomWindowApplication)

	virtual bool OnDraw();
	virtual void OnKeyDown(KeyCode uiKey);

	void BuildBoxGeometry();

};

REGIST_WINDOW_APPLICATION(CustomWindowApplication, L"GENGINE")

bool CustomWindowApplication::OnDraw()
{
	return false;
}

void CustomWindowApplication::OnKeyDown(KeyCode uiKey)
{
	if (uiKey == KeyCode::A)
	{
		MessageBox(m_hwnd, L"Hello GEngine.", L"Hello", MB_OK);
	}
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

	GDirect3DRender* pRender = static_cast<GDirect3DRender*>(GRenderSystem::GetRenderSystem());

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

	mBoxGeo.DrawArgs["box"] = submesh;
}
