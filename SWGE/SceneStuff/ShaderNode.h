#ifndef INCLUDED_SIEGE_SHADERNODE_H
#define INCLUDED_SIEGE_SHADERNODE_H

//====================================================================================================
// Filename:	ShaderNode.h
// Created by:	Peter Chan
// Description:	Class for a shader node.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "SceneNode.h"

//====================================================================================================
// Forward Declarations
//====================================================================================================

class PixelShader;
class VertexShader;

//====================================================================================================
// Class Declarations
//====================================================================================================

class ShaderNode : public SceneNode
{
public:
	ShaderNode(GraphicsSystem& gs);
	virtual ~ShaderNode();
	
	void SetVertexShader(VertexShader* vertexShader)	{ mpVertexShader = vertexShader; }
	void SetPixelShader(PixelShader* pixelShader)		{ mpPixelShader = pixelShader; }

protected:
	virtual void OnRender();

protected:
	VertexShader* mpVertexShader;
	PixelShader* mpPixelShader;
};

#endif // #ifndef INCLUDED_SIEGE_SHADERNODE_H