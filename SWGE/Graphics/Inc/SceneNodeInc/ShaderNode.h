#ifndef INCLUDED_GRAPHICS_SHADERNODE_H
#define INCLUDED_GRAPHICS_SHADERNODE_H


#include "SceneNode.h"

namespace SWGE {
namespace Graphics {
	class VertexShader;
	class PixelShader;
class ShaderNode : public SceneNode
{
public:
	ShaderNode();
	virtual ~ShaderNode();

	void SetVertexShader(VertexShader* vertexShader) { mVertexShader = vertexShader; }
	void SetPixelShader(PixelShader* pixelShader) { mPixelShader = pixelShader; }

protected:
	virtual void OnRender();

protected:
	VertexShader* mVertexShader;
	PixelShader* mPixelShader;
};
}
}
#endif // !INCLUDED_GRAPHICS_SHADERNODE_H
