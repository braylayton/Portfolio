 //====================================================================================================
// Filename:	ShadowMapping.fx
// Created by:	Peter Chan
// Description:	Shader performing shadow mapping.
//====================================================================================================

//====================================================================================================
// Constant Buffers
//====================================================================================================

#include "ConstantBuffers.fx"

Texture2D diffuseMap : register(t0);
//Texture2D specularMap : register(t1);
//Texture2D normalMap : register(t2);
//Texture2D displacementMap : register(t3);
Texture2D depthMap : register(t4);
SamplerState textureSampler : register(s0);
SamplerState depthSampler : register(s1);

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

//----------------------------------------------------------------------------------------------------

struct VS_OUTPUT
{
    float4 position		: SV_POSITION;
    float3 normal		: NORMAL;
    float3 tangent		: TANGENT;
    float3 binormal		: BINORMAL;
    float3 dirToLight	: TEXCOORD0;
    float3 dirToView	: TEXCOORD1;
    float2 texCoord		: TEXCOORD2;
    float4 depthCoord	: TEXCOORD3;
};

//====================================================================================================
// Vertex Shader
//====================================================================================================

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;

    //float displacement = displacementMap.SampleLevel(textureSampler, input.texCoord, 0).x;
    float4 position = input.position; //(float4(input.normal, 0.0f) *displacementScale * displacement);

    float4 posWorld = mul(position, World);
    float4 posProj = mul(posWorld, matView);
    posProj = mul(posProj, matProjection);

    float4 lightPosProj = mul(posWorld, lightCameraMatView);
    lightPosProj = mul(lightPosProj, lightCameraProjection);

    float3 normal = mul(float4(input.normal, 0.0f),World).xyz;
    float3 tangent = mul(float4(input.tangent, 0.0f), World).xyz;
    float3 binormal = cross(normal, tangent);
	
    float3 dirToLight = -normalize(lightDirection.xyz);
    float3 dirToView = normalize(cameraPosition.xyz - posWorld.xyz);

    output.position = posProj;
    output.normal = normal;
    output.tangent = tangent;
    output.binormal = binormal;
    output.dirToLight = dirToLight;
    output.dirToView = dirToView;
    output.texCoord = input.texCoord;
    output.depthCoord = lightPosProj;
	
    return output;
}

//====================================================================================================
// Pixel Shader
//====================================================================================================

float4 PS(VS_OUTPUT input) : SV_Target
{
	// Sample normal from normal map
    //float4 normalColor = normalMap.Sample(textureSampler, input.texCoord);
    //float3 sampledNormal = float3((2.0f * normalColor.xy) - 1.0f, normalColor.z);

	// Transform to world space
    float3 t = normalize(input.tangent);
    float3 b = normalize(input.binormal);
    float3 n = normalize(input.normal);
    float3x3 tbn = float3x3(t, b, n);
    float3 normal = normalize(input.normal); //mul(sampledNormal, tbn);

    float3 dirToLight = normalize(input.dirToLight);
    float3 dirToView = normalize(input.dirToView);
	
	// Ambient
    float4 ambient = lightAmbient * materialAmbient;
	
	// Diffuse
    float d = saturate(dot(dirToLight, normal));
    float4 diffuse = d * lightDiffuse * materialDiffuse;
		
	// Specular
    float3 h = normalize((dirToLight + dirToView) * 0.5f);
    float s = saturate(dot(h, normal));
    float4 specular = pow(s, materialPower) * lightSpecular * materialSpecular;

    //float4 specularColor = specularMap.Sample(textureSampler, input.texCoord).rrrr;
    float4 diffuseColor = diffuseMap.Sample(textureSampler, input.texCoord);

    if (input.depthCoord.w <= 0.0f)
    {
        return ambient * diffuseColor;
    }

    float3 depthCoord = input.depthCoord.xyz / input.depthCoord.w;

    if (abs(depthCoord.x) > 1.0f || abs(depthCoord.y) > 1.0f)
    {
        return ((ambient + diffuse) * diffuseColor) + specular;
    }

    float pixelDepth = depthCoord.z;
    float2 depthUV = (depthCoord.xy + 1.0f) * 0.5f;
    depthUV.y = 1.0f - depthUV.y;
    float sampledDepth = depthMap.Sample(depthSampler, depthUV).r + 0.01f;
    if (pixelDepth > sampledDepth)
    {
        //return float4(1, 0, 0, 1);
        return ambient * diffuseColor;
    }
    return ((ambient + diffuse) * diffuseColor) + specular;


}
















