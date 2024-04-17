#ifndef INCLUDED_SIEGE_MATERIALNODE_H
#define INCLUDED_SIEGE_MATERIALNODE_H

//====================================================================================================
// Filename:	MaterialNode.h
// Created by:	Peter Chan
// Description:	Class for a material node.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "ConstantBuffer.h"
#include "Material.h"
#include "SceneNode.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class MaterialNode : public SceneNode
{
public:
	struct ConstantBuffer
	{
		XMVECTOR ambient;
		XMVECTOR diffuse;
		XMVECTOR specular;
		XMVECTOR emissive;
		f32 power;
	};

	MaterialNode(GraphicsSystem& gs);
	virtual ~MaterialNode();

	void Initialize();
	void Terminate();

	Material& GetMaterial()	{ return mMaterial; }

protected:
	virtual void OnRender();

protected:
	TypedConstantBuffer<ConstantBuffer> mConstantBuffer;

	Material mMaterial;
};

#endif // #ifndef INCLUDED_SIEGE_TRANSFORMNODE_H