#ifndef INCLUDED_GRAPHICS_RASTERIZERSTATENODE_H
#define INCLUDED_GRAPHICS_RASTERIZERSTATENODE_H

#include "SceneNode.h"
#include "RasterizerState.h"


namespace SWGE {
namespace Graphics {

class RasterizerStateNode : public SceneNode
{
public:

	RasterizerStateNode();
	~RasterizerStateNode();

	void Initialize(CullMode cullMode, FillMode fillMode);
	RasterizerState& GetRasterizerState() { return mRasterizerState; }
protected:
	void OnRender() override;
	void OnPostRender() override;
private:
	RasterizerState mRasterizerState;
};

}
}
#endif 
