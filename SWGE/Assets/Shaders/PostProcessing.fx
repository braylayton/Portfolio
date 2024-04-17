 

//====================================================================================================
// Filename:	PostProcessing.fx
// Created by:	Brayden Layton
// Description:	Standard shader for PostProcessing.
//====================================================================================================

//====================================================================================================
// Constant Buffers
//====================================================================================================

#include "ConstantBuffers.fx"

cbuffer postBuffer : register(b8)
{
    //float time;
    float screenWidth;
    float screenHeight;
    float lineThickness;
    float4 lineColor;

}

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
    float4 position	: SV_POSITION;
    float2 texCoord	: TEXCOORD2;
};


//====================================================================================================
// Vertex Shader
//====================================================================================================

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;

    //float3 normal = mul(float4(input.normal, 0.0f), World).xyz;
    output.position = input.position;
    output.texCoord = input.texCoord;
    return output;
}

VS_OUTPUT OutlineVertexShader(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;
 
    // Calculate where the vertex ought to be.  This line is equivalent
    // to the transformations in the CelVertexShader.
    float4 original = mul(mul(mul(input.position, World), matView), matProjection);
	
    float4 normalPosition = normalize(input.position);
    // Calculates the normal of the vertex like it ought to be.
    float4 normal = mul(mul(mul(normalPosition,World),matView), matProjection);

    // Take the correct "original" location and translate the vertex a little
    // bit in the direction of the normal to draw a slightly expanded object.
    // Later, we will draw over most of this with the right color, except the expanded
    // part, which will leave the outline that we want.
    output.position = original + (mul(lineThickness, normal));
 
    return output;
}


//====================================================================================================
// Pixel Shader
//====================================================================================================
float3 Greyscale(float3 rgb)
{
    float val = dot(rgb, float3(0.3, 0.59, 0.11));
    return float3(val, val, val);

}

float FlattenColorChannel(float val)
{
	if (val < 0.0f)
	{
	    return 0.0f;
	}
    else if (val < 0.2f)
    {
        return 0.2f;

    }
    else if (val < 0.4f)
    {
        return 0.4f;
    }
    else if (val < 0.6f)
    {
        return 0.6f;
    }
    else if (val < 0.8f)
    {
        return 0.8f;
    }

    else
    {
        return 1.0f;
    }
}


//float4 FlattenColorChannel(float4 val)
//{
//    if (val.r < 0.0f || val.g < 0.0f || val.b < 0.0f)
//    {
//        return mul(0.0f, val);
//    }
//    else if (val.r < 0.3f || val.g < 0.3f || val.b < 0.3f)
//    {
//        return mul(0.3f, val);

//    }
//    else if (val.r < 0.6f || val.g < 0.6f || val.b < 0.6f)
//    {
//        return mul(0.6f, val);
//    }
//    else
//    {
//        return mul(1.0f, val);
//    }
//}
	

 float4 PS (VS_OUTPUT input): SV_Target
{
    float4 color = rTextureMap.Sample(textureSampler, input.texCoord);
    float4 normalPos = normalize(input.position);
    // Calculates the normal of the vertex like it ought to be.
    float diffIntensity = dot(normalize(lightDirection), normalize(lightDiffuse));
    float2 offset = frac(input.texCoord * float2(screenWidth, screenHeight) - 0.5);
    offset /= float2(screenWidth, screenHeight);
    float3 cx = rTextureMap.Sample(textureSampler, input.texCoord - offset).xyz;
    float3 cy = rTextureMap.Sample(textureSampler, input.texCoord).xyz;
    float3 cz = float3(7 * Greyscale(abs(cx - cy)));
    color *= float4(1 - clamp(cz, 0.0, 1.0), 1.0);

    //if (diffIntensity < 0)
    //{
    //    diffIntensity = 0.0f;
    //}

    //if (diffIntensity > 0.95)
    //    color = float4(1.0, 1, 1, 1.0) * color;
    //else if (diffIntensity > 0.5)
    //    color = float4(0.7, 0.7, 0.7, 1.0) * color;
    //else if (diffIntensity > 0.05)
    //    color = float4(0.35, 0.35, 0.35, 1.0) * color;
    //else
    //    color = float4(0.1, 0.1, 0.1, 1.0) * color;

    color.r = FlattenColorChannel(color.r);
    color.g = FlattenColorChannel(color.g);
    color.b = FlattenColorChannel(color.b);
	//color = 1.0f - color; // Inverse Colors
        return color;
    }



float4 OutlinePixelShader (VS_OUTPUT input) : SV_Target
{
        return lineColor;
}



//technique Toon
//{
    // The first pass will go through and draw the back-facing triangles with the outline shader,
    // which will draw a slightly larger version of the model with the outline color.  Later, the
    // model will get drawn normally, and draw over the top most of this, leaving only an outline.
    //pass Pass1
    //{
    //    SetVertexShader(CompileShader(vs_5_0, OutlineVertexShader()));
    //    SetPixelShader(CompileShader(ps_5_0, OutlinePixelShader()));
    //}
 
    // The second pass will draw the model like normal, but with the cel pixel shader, which will
    // color the model with certain colors, giving us the cel/toon effect that we are looking for.
    //pass Pass2
    //{
    //    SetVertexShader(CompileShader(vs_2_0, VS()));
    //    SetPixelShader(CompileShader(ps_2_0, PS()));
    //}
//}
