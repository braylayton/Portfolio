#ifndef INCLUDED_SIEGE_SAMPLERNODE_H
#define INCLUDED_SIEGE_SAMPLERNODE_H

//====================================================================================================
// Filename:	SamplerNode.h
// Created by:	Peter Chan
// Description:	Class for a transform node.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "ConstantBuffer.h"
#include "SceneNode.h"
#include "Transform.h"

//====================================================================================================
// Forward Declarations
//====================================================================================================

class MatrixStack;

//====================================================================================================
// Class Declarations
//====================================================================================================

class SamplerNode : public SceneNode
{
public:
	SamplerNode(GraphicsSystem& gs);
	virtual ~SamplerNode();

	void Initialize();
	void Terminate();

protected:
	virtual void OnRender();

protected:
	ID3D11SamplerState* mpSampler;
};

#endif // #ifndef INCLUDED_SIEGE_SAMPLERNODE_H