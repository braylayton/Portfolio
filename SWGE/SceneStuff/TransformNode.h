#ifndef INCLUDED_SIEGE_TRANSFORMNODE_H
#define INCLUDED_SIEGE_TRANSFORMNODE_H

//====================================================================================================
// Filename:	TransformNode.h
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

class TransformNode : public SceneNode
{
public:
	struct ConstantBuffer
	{
		XMMATRIX matWorld;
	};

	TransformNode(GraphicsSystem& gs, MatrixStack& ms);
	virtual ~TransformNode();

	void Initialize();
	void Terminate();

	Transform& GetTransform()				{ return mTransform; }

protected:
	virtual void OnUpdate(f32 deltaTime);
	virtual void OnPreRender();
	virtual void OnRender();
	virtual void OnPostRender();

protected:
	TypedConstantBuffer<ConstantBuffer> mConstantBuffer;

	MatrixStack& mMatrixStack;

	Transform mTransform;
};

#endif // #ifndef INCLUDED_SIEGE_TRANSFORMNODE_H