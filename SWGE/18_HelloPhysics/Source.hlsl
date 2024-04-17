// Programming Meeting notes


struct PixelInput
{
	float4 Pos : SV_Position;
	float3 Normal;
	float3 Tangent;
	float2 Uv;
};

Texture2D DiffuseColor;
Texture2D SpecularMap;
Texture2D NormalMap;

struct GBuffer
{
	float4 Diffuse	: SV_Target0;
	float4 Specular : SV_Target1;
	float4 Normal	: SV_Target2;
	float4 WorldPos : SV_Target3;
};

GBuffer main(PixelInput pIn)
{
	GBuffer output = (GBuffer)0;
	float3x3 btn = getBinormalTangentNormal(pIn);

	output.Normal = GetNormal(pIn, btn); // code to get normal goes here
	output.WorldPos = GetPos(pIn); // etc
	output.Specular = GetSpecular(pIn);
	output.Diffuse = GetDiffuse(pIn);

	return output
}