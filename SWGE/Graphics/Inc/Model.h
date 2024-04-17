#ifndef INCLUDED_CORE_MODEL_H
#define INCLUDED_CORE_MODEL_H

#include <exception>
#include "Mesh.h"
#include "Material.h"
#include "MeshBuffer.h"
#include "Texture.h"
#include "SceneNodeInc\SceneManager.h"
#include "SceneNodeInc\MeshNode.h"
#include "SceneNodeInc\TransformNode.h"
#include "SceneNodeInc\TextureNode.h"
namespace SWGE {
namespace Graphics {

class Model
{
public:
	Model();
	~Model();
	void SaveModel(const char* filename);
	void LoadModel(const char* filename);
	void Destroy();
	void Initialize(SceneManager& mSceneManager);

	SceneNode* GetRootNode() { return rootNode; }

	std::vector<Mesh> mMesh;
	std::vector<Material> mMaterial;
	std::vector<int> mMaterialIndex;
	std::vector<std::string> mDiffuseTexture;

private:

	MeshBuffer* mMeshBuffer;
	SceneNode* rootNode;
	std::vector<Texture> mTexture;
};

} // Core
} // SWGE

#endif //INCLUDED_CORE_MODEL_H