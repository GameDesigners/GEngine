#include "GDirect3DUtil.h"
using namespace GEngine::GRender;

const int GDirect3DSetting::gNumFrameResources = 3;

GEngine::GRender::FrameResource::FrameResource(ID3D12Device* device, UINT passCount, unsigned int objCount)
{
	D3D_THROW_IF_FAILED(device->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(CmdListAlloc.GetAddressOf())));

	PassCB = GStl::g_make_shared<GUploadBuffer<PassConstants>>(device, passCount, true);
	ObjectCB = GStl::g_make_shared<GUploadBuffer<ObjectConstants>>(device, objCount, true);
}
