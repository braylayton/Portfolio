#ifndef INCLUDED_GRAPHICS_DepthMap_H
#define INCLUDED_GRAPHICS_DepthMap_H

#include "Types.h"
#include "common.h"

namespace SWGE {
namespace Graphics {

class DepthMap
{
	friend class Texture;
public:
	DepthMap();
	~DepthMap();

	DepthMap(const DepthMap&) = delete;
	DepthMap& operator=(const DepthMap&) = delete;

	void Initialize(uint32_t width, uint32_t height);
	void Terminate();

	void BeginRender();
	void EndRender();

	void BindTexture(uint32_t index);
	void UnBindTexture(uint32_t index);


private:
	ID3D11ShaderResourceView* mShaderResourceView;
	ID3D11DepthStencilView* mDepthStencilView;
	D3D11_VIEWPORT mViewPort;
};

} // Graphics
} // SWGE


#endif // INCLUDED_GRAPHICS_DepthMap_H