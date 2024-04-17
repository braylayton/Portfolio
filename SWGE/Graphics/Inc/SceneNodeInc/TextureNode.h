#ifndef INCLUDED_GRAPHICS_TEXTURENODE_H
#define INCLUDED_GRAPHICS_TEXTURENODE_H

#include "SceneNode.h"

namespace SWGE {
namespace Graphics {

class Texture;

class TextureNode : public SceneNode
{
public:
	TextureNode();
	virtual ~TextureNode();


	TextureNode(const TextureNode&) = delete;
	TextureNode& operator=(const TextureNode&) = delete;

	void SetTexture(Texture* texture, bool resetOnPost = false) { mTexture = texture; bResetOnPost = resetOnPost; }
	Texture* GetTexture() const { return mTexture; }

	void SetIndex(uint32_t index) { mIndex = index; }
	uint32_t  GetIndex() const { return mIndex; }

protected:
	virtual void OnRender();
	virtual void OnPostRender() override;
protected:
	Texture* mTexture;
	uint32_t  mIndex;
	bool bResetOnPost = false;
};
}
}
#endif // !INCLUDED_GRAPHICS_TEXTURENODE_H
