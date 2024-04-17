#include "Precompiled.h"
#include "SceneNodeInc\MeshNode.h"
#include "MeshBuffer.h"

using namespace SWGE;
using namespace Graphics;

MeshNode::MeshNode()
	: SceneNode("MeshNode")
	, mMesh(nullptr)
{
}

MeshNode::~MeshNode()
{
}

void MeshNode::OnRender()
{
	if (mMesh != nullptr)
	{
		mMesh->Render();
	}
}