//---------------------Shader 常量---------------------
cbuffer cbPerObject : register(b0)
{
	float4x4 gWorldViewProj;
};



//---------------------Shader 数据---------------------
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


//---------------------顶点 Shader---------------------
VertexOut VS(VertexIn vin)
{
	VertexOut vout;
	vout.PosH = mul(float4(vin.PosL, 1.0f), gWorldViewProj);
	vout.Color = vin.Color;
	return vout;
}


//---------------------片元 Shader---------------------
float4 PS(VertexOut pin) : SV_Target
{
	return pin.Color;
}