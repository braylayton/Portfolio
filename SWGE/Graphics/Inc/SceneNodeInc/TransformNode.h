#ifndef INCLUDED_GRAPHICS_TRANSFORMNODE_H
#define INCLUDED_GRAPHICS_TRANSFORMNODE_H

#include "SceneNode.h"
#include "Transform.h"
#include "MatrixStack.h"
#include "ConstantBuffer.h"

namespace SWGE {
namespace Graphics {

class TransformNode : public SceneNode
{
public:
	struct ConstantBuffer
	{
		Math::Matrix4 matWorld;
		Math::Matrix4 matWVP;
	};

	TransformNode(MatrixStack& ms);
	virtual ~TransformNode();

	void Initialize();
	void Terminate();

	Transform& GetTransform() { return mTransform; }
	const Transform& GetTransform() const { return mTransform; }

protected:
	virtual void OnUpdate(float deltaTime);
	virtual void OnPreRender();
	virtual void OnRender();
	virtual void OnPostRender();

protected:
	TypedConstantBuffer<ConstantBuffer> mConstantBuffer;

	MatrixStack& mMatrixStack;
	Transform mTransform;
};

}
}
#endif // !INCLUDED_GRAPHICS_MATERIALNODE_H
