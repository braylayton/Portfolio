#ifndef INCLUDED_GRAPHICS_CAMERANODE_H
#define INCLUDED_GRAPHICS_CAMERANODE_H

#include "SceneNode.h"
#include "ConstantBuffer.h"
#include "Camera.h"

namespace SWGE{
namespace Graphics{

class CameraNode : public SceneNode
{
public:
	struct ConstantBuffer
	{
		Math::Matrix4 matView;
		Math::Matrix4 matProjection;
		Math::Vector4 viewPosition;
	};

	CameraNode(const Camera& cam, const bool Orthographic, const bool LightCamera);
	virtual ~CameraNode();

	void Initialize();
	void Terminate();
	void SetIndex(uint32_t index = 0) { mIndex = index; }

	Camera& GetCamera() { return mCamera; }
	const Camera& GetCamera() const { return mCamera; }


protected:
	virtual void OnUpdate(float deltaTime);
	virtual void OnRender();

protected:
	TypedConstantBuffer<ConstantBuffer> mConstantBuffer;
	Camera mCamera;
	bool isOrthographic;
	bool isLightCamera;
	uint32_t mIndex;
};


} // Graphics
} // SWGE


#endif // !INCLUDED_GRAPHICS_CAMERANODE_H
