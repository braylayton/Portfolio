 

//====================================================================================================
// Filename:	PostProcessing.fx
// Created by:	Brayden Layton
// Description:	Standard shader for PostProcessing.
//====================================================================================================

//====================================================================================================
// Constant Buffers
//====================================================================================================
//
//cbuffer postBuffer : register(b0)
//{
//	float	time;
//	float	screenWidth;
//	float	screenHeight;
//}

Texture2D rTextureMap		: register(t0);
SamplerState textureSampler : register(s0);



//====================================================================================================
// Structs
//====================================================================================================

    struct VS_INPUT
    {
        float4 position : POSITION;
        float2 texCoord : TEXCOORD;
    };

    struct VS_OUTPUT
    {
        float4 position		: SV_POSITION;
        float2 texCoord		: TEXCOORD;
    };

//====================================================================================================
// Vertex Shader
//====================================================================================================

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;
 
	output.position = input.position;
	output.texCoord = input.texCoord;
	return output;
}

//====================================================================================================
// Pixel Shader
//====================================================================================================

float4 PS(VS_OUTPUT input) : SV_Target
{

	return rTextureMap.Sample;
}


