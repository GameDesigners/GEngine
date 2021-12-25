#ifndef GDIRECT3D_VECTOR_SAMPLE
#define GDIRECT3D_VECTOR_SAMPLE

#include <Windows.h>
#include <direct.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <iostream>

#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"D3D12.lib")
#pragma comment(lib,"dxgi.lib")

using namespace std;
using namespace DirectX;
using namespace DirectX::PackedVector;
using Microsoft::WRL::ComPtr;

ostream& XM_CALLCONV operator<<(ostream& os, FXMVECTOR v)
{
	XMFLOAT3 dest;
	XMStoreFloat3(&dest, v);
	os << "(" << dest.x << "," << dest.y << "," << dest.z << ")";
	return os;
}

void UseDirect3DSample()
{
	cout.setf(ios_base::boolalpha);
	if (!XMVerifyCPUSupport())
	{
		cout << "directx math not supported" << endl;
		return;
	}

	XMVECTOR p = XMVectorZero();
	XMVECTOR q = XMVectorSplatOne();
	XMVECTOR u = XMVectorSet(1.0f, 2.0f, 3.0f, 0.0f);
	XMVECTOR v = XMVectorReplicate(-2.0f);
	XMVECTOR w = XMVectorSplatZ(u);

	cout << "p=" << p << endl;
	cout << "q=" << q << endl;
	cout << "u=" << u << endl;
	cout << "v=" << v << endl;
	cout << "w=" << w << endl;

	XMVECTOR x = XMVectorSet(1.0f, 2.0f, 3.0f, 0.0f);
	XMVECTOR y = XMVectorSet(-2.0f, 1.0f, -3.0f, 0.0f);
	XMVECTOR z = XMVectorSet(0.707f, 0.707f, 0.0f, 0.0f);
	cout << "ÔËËãÒò×Ó£º" << endl;
	cout << "x:" << x << endl;
	cout << "y:" << y << endl;
	cout << endl;
	cout << "x+y=" << x + y << endl;
	cout << "x-y=" << x - y << endl;
	cout << "10*x=" << 10.0f*x << endl;
	cout << "length(x)" << XMVector3Length(x) << endl;
	cout << "normalize(x)" << XMVector3Normalize(x) << endl;
	cout << "dot(x,y)" << XMVector3Dot(x, y) << endl;
}

void Init()
{
	
}
#endif // !GDIRECT3D_VECTOR_SAMPLE
