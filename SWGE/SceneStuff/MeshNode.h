#ifndef INCLUDED_SIEGE_MESHNODE_H
#define INCLUDED_SIEGE_MESHNODE_H

//====================================================================================================
// Filename:	MeshNode.h
// Created by:	Peter Chan
// Description:	Class for a mesh node.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "SceneNode.h"

//====================================================================================================
// Forward Declarations
//====================================================================================================

class RenderMesh;

//====================================================================================================
// Class Declarations
//====================================================================================================

class MeshNode : public SceneNode
{
public:
	MeshNode(GraphicsSystem& gs);
	virtual ~MeshNode();

	void SetRenderMesh(RenderMesh* mesh)	{ mpMesh = mesh; }
	RenderMesh* GetRenderMesh() const		{ return mpMesh; }

protected:
	virtual void OnRender();

protected:
	RenderMesh* mpMesh;
};

#endif // #ifndef INCLUDED_SIEGE_SHADERNODE_H