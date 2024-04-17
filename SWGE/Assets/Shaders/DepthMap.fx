//====================================================================================================
// Filename:	Standard2.fx
// Created by:	Brayden Layton
// Description:	Standard shader for texturing.
//====================================================================================================

//====================================================================================================
// Constant Buffers
//====================================================================================================

#include "ConstantBuffers.fx" 

cbuffer CBPerObject : register(b8)
{
    float nearPlane;
    float farPlane;
}

    Texture2D displacementMap	: register(t0);
    SamplerState textureSampler : register(s0);

//====================================================================================================
// Structs
//====================================================================================================

    struct VS_INPUT
    {
        float4 position : POSITION;
        float3 normal	: NORMAL;
        float3 tangent	: TANGENT;
        float2 texCoord : TEXCOORD;
    };

    struct VS_OUTPUT
    {
        float4 position		: SV_POSITION;
    };
	
	struct VS_DEBUG_INPUT
	{
		float4 position : POSITION;
		float2 texCoord : TEXCOORD;
	};
	struct VS_DEBUG_OUTPUT
	{
		float4 position : SV_POSITION;
		float2 texCoord : TEXCOORD;
	};	

//====================================================================================================
// Vertex Shader
//====================================================================================================

    VS_OUTPUT VS(VS_INPUT input)
    {
        VS_OUTPUT output = (VS_OUTPUT) 0;
       // float displacement = displacementMap.SampleLevel(textureSampler, input.texCoord, 0).r * 2.0f - 1.0f;
		float4 position = input.position; //+ (float4(input.normal, 0.0f) * displacement * displacementFactor);
		float4 posWorld = mul(position, World);
		 float4x4 wv = mul(World, lightCameraMatView);
		float4x4 wvp = mul(wv, lightCameraProjection);
		float4 posProj = mul(position, wvp);
		//posProj = mul(posProj, lightCameraProjection);
		 output.position = posProj;
        return output;
    }

//float4 PS(V2P input) : SV_Target
//{
//    float depth = depthMap.Sample(textureSampler, input.texcoord).r;
//    float near = 1.0f;
//    float far = 500.0f;
//    float linearDepth = (2.0f * near) / (far + near - depth * (far - near));
//    return linearDepth;
//}

VS_DEBUG_OUTPUT VSDebug(VS_DEBUG_INPUT input)
{
    VS_DEBUG_OUTPUT output = (VS_DEBUG_OUTPUT) 0;
    output.position = input.position;
    output.texCoord = input.texCoord;
    return output;

}

float4 PSDebug (VS_DEBUG_OUTPUT input) : SV_Target
{
    float depth = displacementMap.Sample(textureSampler, input.texCoord).r;
    float near = nearPlane;
    float far = farPlane;
    float linearDepth = (2.0 * near) / (far + near - depth * (far - near));
    return linearDepth;
}




