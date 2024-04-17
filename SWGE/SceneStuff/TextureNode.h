#ifndef INCLUDED_SIEGE_TEXTURENODE_H
#define INCLUDED_SIEGE_TEXTURENODE_H

//====================================================================================================
// Filename:	TextureNode.h
// Created by:	Peter Chan
// Description:	Class for a texture node.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "SceneNode.h"

//====================================================================================================
// Forward Declarations
//====================================================================================================

class Texture;

//====================================================================================================
// Class Declarations
//====================================================================================================

class TextureNode : public SceneNode
{
public:
	TextureNode(GraphicsSystem& gs);
	virtual ~TextureNode();

	void SetTexture(Texture* texture)	{ mpTexture = texture; }
	Texture* GetTexture() const			{ return mpTexture; }

	void SetIndex(u32 index)			{ mIndex = index; }
	u32 GetIndex() const				{ return mIndex; }

protected:
	virtual void OnRender();

protected:
	Texture* mpTexture;
	u32 mIndex;
};

#endif // #ifndef INCLUDED_SIEGE_TEXTURENODE_H