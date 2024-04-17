#ifndef INCLUDED_GRAPHICS_DEPTHMAPNODE_H
#define INCLUDED_GRAPHICS_DEPTHMAPNODE_H

#include "DepthMap.h"
#include "SceneNode.h"

namespace SWGE {
namespace Graphics {

class DepthMapNode : public SceneNode
{
public:
	DepthMapNode();
	virtual ~DepthMapNode();

	void Initialize(uint32_t width, uint32_t height);
	void OnRender() override;
	void OnPostRender() override;
	DepthMap& GetDepthMap() { return mDepthMap; }

private:
	DepthMap mDepthMap;

};


} // Graphics
} // SWGE


#endif // !INCLUDED_GRAPHICS_CAMERANODE_H
