#ifndef INCLUDED_GRAPHICS_RENDERTARGET_H
#define INCLUDED_GRAPHICS_RENDERTARGET_H

#include "Types.h"
#include "common.h"

namespace SWGE {
namespace Graphics {

	class Texture;

	class RenderTarget
	{
	public: 
		RenderTarget();
		~RenderTarget();

		RenderTarget(const RenderTarget&) = delete;
		RenderTarget& operator=(const RenderTarget&) = delete;

		RenderTarget(RenderTarget&&) = default;
		RenderTarget& operator=(RenderTarget&&) = default;

		void Initialize(uint32_t width, uint32_t height, ColorFormat format);
		void Terminate();

		void BeginRender();
		void EndRender();

		void BindPS(uint32_t index);
		void UnBindPS(uint32_t index);

		void Copy(ID3D11Texture2D* texture);
	private:
		friend class Texture;
		ID3D11ShaderResourceView* mShaderResourceView;
		ID3D11RenderTargetView* mRenderTargetView;
		ID3D11DepthStencilView* mDepthStencilView;
		D3D11_VIEWPORT mViewPort;
		D3D11_MAPPED_SUBRESOURCE mMappedSub;
};

}
}

#endif //INCLUDED_GRAPHICS_RENDERTARGET_H