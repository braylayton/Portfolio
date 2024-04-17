#ifndef INCLUDED_SIEGE_LIGHTNODE_H
#define INCLUDED_SIEGE_LIGHTNODE_H

//====================================================================================================
// Filename:	LightNode.h
// Created by:	Peter Chan
// Description:	Class for a light node.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "ConstantBuffer.h"
#include "Light.h"
#include "SceneNode.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class LightNode : public SceneNode
{
public:
	struct ConstantBuffer
	{
		XMVECTOR direction;
		XMVECTOR ambient;
		XMVECTOR diffuse;
		XMVECTOR specular;
	};

	LightNode(GraphicsSystem& gs);
	virtual ~LightNode();

	void Initialize();
	void Terminate();

	Light& GetLight()	{ return mLight; }

protected:
	virtual void OnRender();

protected:
	TypedConstantBuffer<ConstantBuffer> mConstantBuffer;

	Light mLight;
};

#endif // #ifndef INCLUDED_SIEGE_LIGHTNODE_H