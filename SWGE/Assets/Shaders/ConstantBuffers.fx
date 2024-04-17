 

//====================================================================================================
// Filename:	ConstantBuffers.fx
// Created by:	Brayden Layton
// Description:	Standard shader for texturing.
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
cbuffer DepthCameraBuffer : register(b7)
{
    matrix lightCameraMatView;
    matrix lightCameraProjection;
    vector lightCameraPosition;
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

 