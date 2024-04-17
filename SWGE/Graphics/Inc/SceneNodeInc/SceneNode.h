#ifndef INCLUDED_GRAPHICS_SCENENODE_H
#define INCLUDED_GRAPHICS_SCENENODE_H
#include "Math\Inc\QMath.h"

namespace SWGE {
namespace Graphics {

class SceneNode
{
public:

	SceneNode();
	SceneNode(const char* name);
	virtual ~SceneNode();
	bool AddChild(SceneNode* child);
	bool RemoveChild(const char* name);
	bool RemoveChild(uint32_t id);

	void Update(float deltaTime);
	void Render();

	void SetName(const char* name) { mName = name; }
	void SetId(uint32_t id) { mId = id; }

	const char* GetName() const { return mName.c_str(); }
	uint32_t GetId() const { return mId; }

protected:
	typedef std::vector<SceneNode*> SceneNodeList;

	virtual void OnUpdate(float deltaTime) {}
	virtual void OnPreRender() {}
	virtual void OnRender() {}
	virtual void OnPostRender() {}

	SceneNode* mParent;
	SceneNodeList mChildren;

	std::string mName;	
	uint32_t mId;
};

} // namespace graphics
} // namespace SWGE
#endif //GRAPHICS_INCLUDED_SCENENODE_H