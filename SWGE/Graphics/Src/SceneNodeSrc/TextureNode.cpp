#include "Precompiled.h"
#include "SceneNodeInc\TextureNode.h"
#include "Texture.h"

using namespace SWGE;
using namespace Graphics;

TextureNode::TextureNode()
	: SceneNode("TextureNode")
	, mTexture(nullptr)
	, mIndex(0)
{
}


TextureNode::~TextureNode()
{
}

void TextureNode::OnRender()
{
	if (mTexture != nullptr)
	{
		mTexture->BindPS(mIndex);
		mTexture->BindVS(mIndex);
	}
}

void TextureNode::OnPostRender()
{
	if (bResetOnPost && mTexture != nullptr)
	{
		mTexture->UnbindPS(mIndex);
		mTexture->UnbindVS(mIndex);
	}
}