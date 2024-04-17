#ifndef INCLUDED_GRAPHICS_RENDERTARGETNODE_H
#define INCLUDED_GRAPHICS_RENDERTARGETNODE_H

#include "SceneNode.h"
#include "RenderTarget.h"

namespace SWGE {
namespace Graphics {

class RenderTargetNode : public SceneNode
{
public:
	RenderTargetNode();
	virtual ~RenderTargetNode();

	void Initialize(uint32_t width, uint32_t height, ColorFormat format);
	void OnRender() override;
	void OnPostRender() override;
	RenderTarget& GetRenderTarget() { return renderTarget; }


private:
	RenderTarget renderTarget;
};


} // Graphics
} // SWGE


#endif // !INCLUDED_GRAPHICS_RENDERTARGETNODE_H
