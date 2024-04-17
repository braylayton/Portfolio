#ifndef INCLUDED_GRAPHICS_MESHNODE_H
#define INCLUDED_GRAPHICS_MESHNODE_H

#include "SceneNode.h"

namespace SWGE {
namespace Graphics {

class MeshBuffer;

class MeshNode : public SceneNode
{
public:
	MeshNode();
	virtual ~MeshNode();

	void SetRenderMesh(MeshBuffer* mesh) { mMesh = mesh; }
	MeshBuffer* GetRenderMesh() const { return mMesh; }

protected:
	virtual void OnRender();

protected:
	MeshBuffer* mMesh;
};

}
}
#endif // !INCLUDED_GRAPHICS_MESHNODE_H
