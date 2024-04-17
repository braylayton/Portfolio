#ifndef INCLUDED_GRAPHICS_SAMPLERNODE_H
#define INCLUDED_GRAPHICS_SAMPLERNODE_H
#include "SceneNode.h"
#include "../Sampler.h"

namespace SWGE {
namespace Graphics {

	class SamplerNode : public SceneNode
	{
	public:
		SamplerNode(Graphics::Sampler::Filter filter, Graphics::Sampler::AddressMode addressMode, uint32_t index);
		virtual ~SamplerNode();
		void Initialize();
		void Terminate();

	protected:
	virtual void OnRender() override;

	protected:
		Sampler mSampler;
		Sampler::Filter mFilter;
		Sampler::AddressMode mAddressMode;
		//stage
		//slot
		uint32_t mIndex;
	};

}
}
#endif // !INCLUDED_GRAPHICS_SAMPLERNODE_H
