 

//====================================================================================================
// Filename:	Standard.fx
// Created by:	Brayden Layton
// Description:	Standard shader for texturing.
//====================================================================================================

//====================================================================================================
// Constant Buffers
//====================================================================================================

cbuffer ConstantBuffer : register( b0 )
{
	matrix	World;
	matrix	wvp; // world view projection matrix captivated
	vector	cameraPosition;
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
	vector	materialAmbient;
	vector	materialDiffuse;
	vector	materialSpecular;
	vector	materialEmissive;
	float	materialPower;
	float	displacementFactor;
	bool	useTexture;

}

Texture2D diffuseMap : register(t0);
Texture2D specularMap : register(t1);
Texture2D normalMap : register(t2);
Texture2D displacementMap : register(t3);
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
	float3 tangent		: TANGENT;
	float3 binormal		: BINORMAL;
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
	float displacement = displacementMap.SampleLevel(textureSampler, input.texCoord, 0).r;
	float4 position = input.position + (float4(input.normal, 0.0f) * displacementFactor * displacement);
	float4 posWorld = mul(position, World);
	float4 posProj = mul(position, wvp);

	float3 normal = mul(float4(input.normal, 0.0f), World).xyz;
    float3 tangent = mul(float4(input.tangent, 0.0f), World).xyz;
	float3 binormal = cross(normal, tangent);


	float3 dirToLight = -normalize(lightDirection.xyz);
	float3 dirToView = normalize(cameraPosition - posWorld).xyz; // world space minus a world space

	output.position = posProj;
	output.normal = normal;
	output.tangent = tangent;
	output.binormal = binormal;
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
    //float3 normal = normalize(input.normal);

	//Sample normal from normal map
	float4 normalColor = normalMap.Sample(textureSampler, input.texCoord);
	float3 sampledNormal = float3((2.0f * normalColor.xy) - 1.0f, normalColor.z);
	
	//Transform to world space
	float3 t = normalize(input.tangent);
	float3 b = normalize(input.binormal);
	float3 n = normalize(input.normal);
	float3x3 tbnw = float3x3(t, b, n);
	float3 normal = mul(sampledNormal, tbnw);

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
	if (useTexture)
	{ 
		diffuseColor = diffuseMap.Sample(textureSampler, input.texCoord);
	}
	float specularColor = specularMap.Sample(textureSampler, input.texCoord).r;
    
    return (ambient + diffuse) * diffuseColor + (specular * specularColor);

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



