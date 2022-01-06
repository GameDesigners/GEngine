//---------------------Shader ����---------------------
cbuffer cbPerObject : register(b0)
{
	float4x4 gWorldViewProj;
};



//---------------------Shader ����---------------------
struct VertexIn
{
	float PosL   : POSITION;
	float4 Color : COLOR;
};

struct VertexOut
{
	float4 PosH  : SV_POSITION;
	float4 Color : COLOR;
};


//---------------------���� Shader---------------------
VertexOut VS(VertexIn vin)
{
	VertexOut vout;
	vout.PosH = mul(float4(vin.PosL, 1.0f), gWorldViewProj);
	vout.Color = vin.Color;
	return vout;
}


//---------------------ƬԪ Shader---------------------
float4 PS(VertexOut pin) : SV_Target
{
	return pin.Color;
}