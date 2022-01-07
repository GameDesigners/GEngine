#ifndef GDirect3DUTIL_H
#define GDirect3DUTIL_H
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>
#include "GRender.h"
namespace GEngine {
	namespace GRender {
		using namespace GEngine::GSystem;
		using namespace DirectX;
		
		//临时结构
		//*******************************************************************************************************
		class MathHelper
		{
		public:
			static DirectX::XMFLOAT4X4 Identity4x4()
			{
				static DirectX::XMFLOAT4X4 I(
					1.0f, 0.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);
				return I;
			}
		};
		
		struct GVertex
		{
			XMFLOAT3 Pos;
			XMFLOAT4 Color;
		};

		struct ObjectConstants
		{
			XMFLOAT4X4 WorldViewProj = MathHelper::Identity4x4();
		};

		//*******************************************************************************************************


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

		//Debug宏
#ifndef D3D_THROW_IF_FAILED
#define D3D_THROW_IF_FAILED(x) \
        { \
            HRESULT hr__=(x); \
            GEngine::GStl::GTString wfn=AnsiToTString(__FILE__); \
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


		//创建默认缓冲区（位于默认堆）
		//*******************************************************************************************************
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



		//计算常量缓冲堆需要的大小（因为常量缓冲区大小要求为256B的整倍数）
		//*******************************************************************************************************
		inline unsigned int CaculateConstantBufferByteSize(unsigned int byteSize)
		{
			return (byteSize + 255) & ~255;
		}

		template<class T>
		class GUploadBuffer
		{
		public:
			GUploadBuffer(ID3D12Device* device, unsigned int elementCount, bool isConstantBuffer)
			{
				m_isConstantBuffer = isConstantBuffer;
				m_elementByteSize = sizeof(T);
				if (isConstantBuffer)
					m_elementByteSize = CaculateConstantBufferByteSize(m_elementByteSize);

				D3D_THROW_IF_FAILED(
					device->CreateCommittedResource(
						&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
						D3D12_HEAP_FLAG_NONE,
						&CD3DX12_RESOURCE_DESC::Buffer(m_elementByteSize * elementCount),
						D3D12_RESOURCE_STATE_GENERIC_READ,
						nullptr, IID_PPV_ARGS(&m_uploadBuffer)
					));

				D3D_THROW_IF_FAILED(m_uploadBuffer->Map(0, nullptr, reinterpret_cast<void**>(&m_pMappedData)));
			}

			GUploadBuffer(const GUploadBuffer& rhs) = delete;
			GUploadBuffer& operator=(const GUploadBuffer& rhs) = delete;
			~GUploadBuffer()
			{
				if (m_uploadBuffer != nullptr)
					m_uploadBuffer->Unmap(0, nullptr);
				m_pMappedData = nullptr;
			}

			ID3D12Resource* Resource() const
			{
				return m_uploadBuffer.Get();
			}

			void CopyData(int elementIdx, const T& data)
			{
				GMemoryCpy(&m_pMappedData[elementIdx * m_elementByteSize], sizeof(T), const_cast<T*>(&data), sizeof(T));
			}

		private:
			Microsoft::WRL::ComPtr<ID3D12Resource> m_uploadBuffer;
			BYTE*        m_pMappedData = nullptr;
			unsigned int m_elementByteSize = 0;
			bool         m_isConstantBuffer = false;
		};

		//编译着色器
		//*******************************************************************************************************
		inline Microsoft::WRL::ComPtr<ID3DBlob> CompileShader(const GStl::GTString& fileName, const D3D_SHADER_MACRO* defines, const GStl::GString& entryPoint, const GStl::GString& target)
		{
			unsigned int compileFlags = 0;
            #if defined(DEBUG) || defined(_DEBUG)
			compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
            #endif

			HRESULT hr = S_OK;
			Microsoft::WRL::ComPtr<ID3DBlob> byteCode = nullptr;
			Microsoft::WRL::ComPtr<ID3DBlob> errors = nullptr;
			hr = D3DCompileFromFile(fileName.c_str(), defines, D3D_COMPILE_STANDARD_FILE_INCLUDE, (LPCSTR)entryPoint.c_str(), (LPCSTR)target.c_str(), compileFlags, 0, &byteCode, &errors);

			if (errors != nullptr)
				GOutputDebugStringA((char*)errors->GetBufferPointer());

			D3D_THROW_IF_FAILED(hr);
			return byteCode;
		}
	}
}

#endif // !GDirect3DUTIL_H
