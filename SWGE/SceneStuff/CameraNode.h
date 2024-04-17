#ifndef INCLUDED_SIEGE_CAMERANODE_H
#define INCLUDED_SIEGE_CAMERANODE_H

//====================================================================================================
// Filename:	CameraNode.h
// Created by:	Peter Chan
// Description:	Class for a camera node.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "ConstantBuffer.h"
#include "SceneNode.h"

//====================================================================================================
// Forward Declarations
//====================================================================================================

class Camera;

//====================================================================================================
// Class Declarations
//====================================================================================================

class CameraNode : public SceneNode
{
public:
	struct ConstantBuffer
	{
		XMMATRIX matView;
		XMMATRIX matProjection;
		XMVECTOR viewPosition;
	};

	CameraNode(GraphicsSystem& gs);
	virtual ~CameraNode();

	void Initialize();
	void Terminate();

	void SetCamera(Camera* camera)	{ mpCamera = camera; }
	Camera* GetCamera()				{ return mpCamera; }

protected:
	virtual void OnUpdate(f32 deltaTime);
	virtual void OnRender();

protected:
	TypedConstantBuffer<ConstantBuffer> mConstantBuffer;

	Camera* mpCamera;
};

#endif // #ifndef INCLUDED_SIEGE_CAMERANODE_H