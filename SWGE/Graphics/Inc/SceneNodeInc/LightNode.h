#ifndef INCLUDED_GRAPHICS_LIGHTNODE_H
#define INCLUDED_GRAPHICS_LIGHTNODE_H

#include "Light.h"
#include "SceneNode.h"
#include "ConstantBuffer.h"
namespace SWGE {
namespace Graphics {

class LightNode : public SceneNode
{
public:
	struct ConstantBuffer
	{
		Math::Vector4 direction;
		Math::Vector4 ambient;
		Math::Vector4 diffuse;
		Math::Vector4 specular;
		Math::Vector4 position;
		float Range;
		float Falloff;
		float ConstAttenuation;
		float LinAttenuation;
		float QuadAttenuation;
		float Theta;
		float Phi;
		int typeOfLight;
	};

	LightNode(const Light& light);
	virtual ~LightNode();

	void Initialize();
	void Terminate();
	

	Light& GetLight() { return mLight; }
	const Light& GetLight() const { return mLight; 	}
protected:
	virtual void OnRender();

protected:
	TypedConstantBuffer<ConstantBuffer> mConstantBuffer;

	Light mLight;
};
} // SWGE
} // Graphics

#endif