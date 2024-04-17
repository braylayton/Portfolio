#ifndef INCLUDED_SIEGE_SCENENODE_H
#define INCLUDED_SIEGE_SCENENODE_H

//====================================================================================================
// Filename:	SceneNode.h
// Created by:	Peter Chan
// Description:	Class for a 3D scene node.
//====================================================================================================

//====================================================================================================
// Forward Declarations
//====================================================================================================

class GraphicsSystem;

//====================================================================================================
// Class Declarations
//====================================================================================================

class SceneNode
{
public:
	SceneNode(GraphicsSystem& gs);
	virtual ~SceneNode();

	bool AddChild(SceneNode* child);
	bool RemoveChild(const char* name);
	bool RemoveChild(u32 id);

	void Update(f32 deltaTime);
	void Render();
	
	void SetName(const char* name)					{ mName = name; }
	void SetId(u32 id)								{ mId = id; }
	
	const char* GetName() const						{ return mName.c_str(); }
	u32 GetId() const								{ return mId; }

protected:
	typedef std::vector<SceneNode*> SceneNodeList;

	virtual void OnUpdate(f32 deltaTime) {}
	virtual void OnPreRender() {}
	virtual void OnRender() {}
	virtual void OnPostRender() {}

	GraphicsSystem& mGraphicsSystem;

	SceneNode* mpParent;
	SceneNodeList mChildren;

	std::string mName;		// pchan: TODO - Combine name/id into something like Util::Name
	u32 mId;
};

#endif // #ifndef INCLUDED_SIEGE_SCENENODE_H