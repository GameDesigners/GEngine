#ifndef GDirect3DUTIL_H
#define GDirect3DUTIL_H
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>
#include "GRender.h"
namespace GEngine {
	namespace GRender {

		using namespace DirectX;
		struct GVertex
		{
			XMFLOAT3 Pos;
			XMFLOAT4 Color;
		};

		class GRENDER_API DxException
		{
		public:
			DxException() = default;
			DxException(HRESULT hr, const GStl::GTString& functionName, const GStl::GTString& filename, int lineNumber)
				: ErrorCode(hr), FunctionName(functionName), FileName(filename), LineNumber(lineNumber) {}

			GStl::GTString ToString() const
			{
				GStl::GTString str = FunctionName;
				str += L"\nFail In:";
				str += FileName;
				str += L"LineNumber:";
				str += GStl::to_tstring(LineNumber);
				return str;
			}

			HRESULT        ErrorCode = S_OK;
			GStl::GTString FunctionName;
			GStl::GTString FileName;
			int            LineNumber;
		};

		inline GStl::GTString AnsiToTString(const char* str)
		{
			TCHAR buffer[512];
			GPConstChar_To_PTCHAR(str, buffer, 512);
			return GStl::GTString(buffer);
		}

		//Debugºê
#ifndef D3D_THROW_IF_FAILED
#define D3D_THROW_IF_FAILED(x) \
        { \
            HRESULT hr__=(x); \
            GStl::GTString wfn=AnsiToTString(__FILE__); \
            if(FAILED(hr__)) \
		        throw DxException(hr__,L#x,wfn,__LINE__); \
		}
#endif // !D3D_THROW_IF_FAILED

		struct SubmeshGeometry
		{
			UINT IndexCount = 0;
			UINT StartIndexLocation = 0;
			INT BaseVertexLocation = 0;

			// Bounding box of the geometry defined by this submesh. 
			// This is used in later chapters of the book.
			DirectX::BoundingBox Bounds;
		};

		struct MeshGeometry
		{
			GStl::GString Name;
			Microsoft::WRL::ComPtr<ID3DBlob> VertexBufferCPU = nullptr;
			Microsoft::WRL::ComPtr<ID3DBlob> IndexBufferCPU = nullptr;
			Microsoft::WRL::ComPtr<ID3D12Resource> VertexBufferGPU = nullptr;
			Microsoft::WRL::ComPtr<ID3D12Resource> IndexBufferGPU = nullptr;
			Microsoft::WRL::ComPtr<ID3D12Resource> VertexBufferUploader = nullptr;
			Microsoft::WRL::ComPtr<ID3D12Resource> IndexBufferUploader = nullptr;

			unsigned int VertexByteStride = 0;
			unsigned int VertexBufferByteSize = 0;
			DXGI_FORMAT  IndexFormat = DXGI_FORMAT_R16_UINT;
			unsigned int IndexBufferByteSize = 0;

			GStl::GMap<GStl::GString, SubmeshGeometry> DrawArgs;

			D3D12_VERTEX_BUFFER_VIEW VertexBufferView() const
			{
				D3D12_VERTEX_BUFFER_VIEW vbv;
				vbv.BufferLocation = VertexBufferGPU->GetGPUVirtualAddress();
				vbv.StrideInBytes = VertexByteStride;
				vbv.SizeInBytes = VertexBufferByteSize;

				return vbv;
			}

			D3D12_INDEX_BUFFER_VIEW IndexBufferView()const
			{
				D3D12_INDEX_BUFFER_VIEW ibv;
				ibv.BufferLocation = IndexBufferGPU->GetGPUVirtualAddress();
				ibv.Format = IndexFormat;
				ibv.SizeInBytes = IndexBufferByteSize;

				return ibv;
			}

			void DisposeUploaders()
			{
				VertexBufferUploader = nullptr;
				IndexBufferUploader = nullptr;
			}
		};



		inline Microsoft::WRL::ComPtr<ID3D12Resource> CreateDefaultBuffer(
			ID3D12Device* device,
			ID3D12GraphicsCommandList* cmdList,
			const void* initData,
			UINT64 byteSize,
			Microsoft::WRL::ComPtr<ID3D12Resource>& uploadBuffer)
		{
			Microsoft::WRL::ComPtr<ID3D12Resource> defaultBuffer;

			D3D_THROW_IF_FAILED(device->CreateCommittedResource(
				&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
				D3D12_HEAP_FLAG_NONE,
				&CD3DX12_RESOURCE_DESC::Buffer(byteSize),
				D3D12_RESOURCE_STATE_COMMON,
				nullptr,
				IID_PPV_ARGS(defaultBuffer.GetAddressOf())
			));

			D3D_THROW_IF_FAILED(device->CreateCommittedResource(
				&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
				D3D12_HEAP_FLAG_NONE,
				&CD3DX12_RESOURCE_DESC::Buffer(byteSize),
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(uploadBuffer.GetAddressOf())
			));

			D3D12_SUBRESOURCE_DATA subResourceData = {};
			subResourceData.pData = initData;
			subResourceData.RowPitch = byteSize;
			subResourceData.SlicePitch = subResourceData.RowPitch;

			cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(defaultBuffer.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST));
			UpdateSubresources<1>(cmdList, defaultBuffer.Get(), uploadBuffer.Get(), 0, 0, 1, &subResourceData);
			cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(defaultBuffer.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ));

			return defaultBuffer;
		}
	}
}

#endif // !GDirect3DUTIL_H
