

//====================================================================================================
// Filename:	Texturing.fx
// Created by:	Peter Chan
// Description:	Simple shader for texturing.
//====================================================================================================

//====================================================================================================
// Constant Buffers
//====================================================================================================

cbuffer CameraBuffer : register(b0)
{
	matrix	matView;
	matrix	matProjection;
	vector	cameraPosition;
}
cbuffer LightBuffer : register(b1)
{
	vector	lightDirection;
	vector	lightAmbient;
	vector	lightDiffuse;
	vector	lightSpecular;
	vector	lightPosition;
	float	lightRange;
	float	lightFalloff;
	float	lightConstAttenuation;
	float	lightLinAttenuation;
	float	lightQuadAttenuation;
	float	lightTheta;
	float	lightPhi;
	int		lightType;
}

cbuffer MaterialBuffer : register(b2)
{
	vector	materialAmbient;
	vector	materialDiffuse;
	vector	materialSpecular;
	vector	materialEmissive;
	float	materialPower;
	float	displacementFactor;
}

cbuffer WorldBuffer : register(b3)
{
	matrix	World;
}

Texture2D diffuseMap : register(t0);
SamplerState textureSampler : register(s0);

//====================================================================================================
// Structs
//====================================================================================================

struct VS_INPUT
{
	float4 position	: POSITION;
	float3 normal	: NORMAL;
	float3 tangent	: TANGENT;
	float2 texCoord	: TEXCOORD;
};

struct VS_OUTPUT
{
	float4 position		: SV_POSITION;
	float3 normal		: NORMAL;
	float3 dirToLight	: TEXCOORD0;
	float3 dirToView	: TEXCOORD1;
	float2 texCoord		: TEXCOORD2;
};

//====================================================================================================
// Vertex Shader
//====================================================================================================

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	float4 position = input.position;
	float4 posWorld = mul(position, World);

	float4 posProj = mul(posWorld, matView);
	posProj = mul(posProj, matProjection);

	float3 normal = mul(float4(input.normal, 0.0f), World).xyz;

	float3 dirToLight = -normalize(lightDirection.xyz);
	float3 dirToView = normalize(cameraPosition - posWorld).xyz; // world space minus a world space

	output.position = posProj;
	output.normal = normal;
	output.dirToLight = dirToLight;
	output.dirToView = dirToView;
	output.texCoord = input.texCoord;
	return output;
}

//====================================================================================================
// Pixel Shader
//====================================================================================================

float4 PS(VS_OUTPUT input) : SV_Target
{
    float3 normal = normalize(input.normal);
    float3 DirToLight = normalize(input.dirToLight);
    float3 DirToView = normalize(input.dirToView);

	//switch (lightType)
	//{
	//case 0:
	//{
	//	DirectionalLight();
	//}
	//break;
	//case 1:
	//{
	//	PointLight();
	//}
	//break;
	//case 2:
	//{
	//	SpotLight(float lightTheta);
	//}
	//break;
	//default:
	//{
	//	DirectionalLight();
	//}
	//break;
	//}

	//Re-normalize normals

	//Ambient
    float4 ambient = lightAmbient * materialAmbient;

	//Difuse
    float d = saturate(dot(DirToLight, normal));
    float diffuse = d * lightDiffuse * materialDiffuse;

	//Specular
    float3 h = normalize((DirToLight + DirToView));
    float s = saturate(dot(normal, h));
	float4 specular = pow(s, materialPower) * materialSpecular * lightSpecular;
	float4 diffuseColor = { 1,1,1,1 };
	
	diffuseColor = diffuseMap.Sample(textureSampler, input.texCoord);
	
    return (ambient + diffuse) * diffuseColor + specular;

}

float4 DirectionalLight()
{

}

float4 PointLight()
{

}

float4 SpotLight(float theta)
{
	float cosTheta = cos(theta);

}



