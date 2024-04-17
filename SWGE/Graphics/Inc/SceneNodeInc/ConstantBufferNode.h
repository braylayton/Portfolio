#ifndef INCLUDED_GRAPHICS_CONSTANTBUFFERNODE_H
#define INCLUDED_GRAPHICS_CONSTANTBUFFERNODE_H

#include "ConstantBuffer.h"
#include "SceneNode.h"
#include "ShaderStage.h"

namespace SWGE {
namespace Graphics {

class ConstantBufferNode : public SceneNode
{
public:
	ConstantBufferNode();
	~ConstantBufferNode();

	void Initialize(uint32_t bufferSize, const ShaderStage shaderStages, const uint32_t slot, const void* initData = nullptr);
	
	void OnRender() override;
	void OnPostRender() override;

	void Set(const void* data) const;


private:
	ConstantBuffer mConstantBuffer;
	ShaderStage mShaderStages;
	uint32_t mSlot;
};


}
}

#endif //INCLUDED_GRAPHICS_CONSTANTBUFFERNODE_H