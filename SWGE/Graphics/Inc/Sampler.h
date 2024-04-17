//====================================================================================================
// Filename:	Sampler.h
// Created by:	Peter Chan
//====================================================================================================

#ifndef INCLUDED_GRAPHICS_SAMPLER_H
#define INCLUDED_GRAPHICS_SAMPLER_H

namespace SWGE{
namespace Graphics {

class Sampler
{
public:
	enum class Filter { Point, Linear, Anisotropic };
	enum class AddressMode { Border, Clamp, Mirror, Wrap, };

	Sampler();
	~Sampler();
	
	void Initialize(Filter filter, AddressMode addressMode);
	void Terminate();

	void BindVS(uint32_t slot) const;
	void BindGS(uint32_t slot) const;
	void BindPS(uint32_t slot) const;

private:
	Sampler(const Sampler&) = delete;
	Sampler& operator=(const Sampler&) = delete;

	ID3D11SamplerState* mSampler;
};

} // namespace Graphics
} // namespace SWGE
#endif // #ifndef INCLUDED_GRAPHICS_SAMPLER_H