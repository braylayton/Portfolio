//====================================================================================================
// Filename:	Texture.h
// Created by:	Peter Chan
//====================================================================================================

#ifndef INCLUDED_GRAPHICS_TEXTURE_H
#define INCLUDED_GRAPHICS_TEXTURE_H

namespace SWGE{
namespace Graphics {

class Texture
{
public:
	Texture();
	~Texture();
	
	Texture(const Texture& other) = delete;
	Texture& operator=(const Texture&) = delete;

	Texture(Texture&& other) = default;
	Texture& operator=(Texture&&) = default;

	void Initialize(const char* filename);
	void Initialize(class DepthMap& depthMap);
	void Initialize(class RenderTarget& renderTarget);
	void Initialize(const void* data, uint32_t width, uint32_t height);
	void Terminate();

	void BindVS(uint32_t slot) const;
	void BindPS(uint32_t slot) const;
	void UnbindVS(uint32_t slot) const;
	void UnbindPS(uint32_t slot) const;
private:

	ID3D11ShaderResourceView* mShaderResourceView;
};

} // namespace Graphics
} // namespace SWGE

#endif // #ifndef INCLUDED_GRAPHICS_TEXTURE_H