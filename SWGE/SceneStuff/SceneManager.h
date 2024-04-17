#ifndef INCLUDED_SIEGE_SCENEMANAGER_H
#define INCLUDED_SIEGE_SCENEMANAGER_H

//====================================================================================================
// Filename:	SceneManager.h
// Created by:	Peter Chan
// Description:	Class for a scene manager.
//====================================================================================================

//====================================================================================================
// Forward Declarations
//====================================================================================================

class GraphicsSystem;
class MatrixStack;

class CameraNode;
class LightNode;
class MaterialNode;
class MeshNode;
class SamplerNode;
class SceneNode;
class ShaderNode;
class TerrainNode;
class TextureNode;
class TransformNode;

//====================================================================================================
// Class Declarations
//====================================================================================================

class SceneManager
{
public:
	SceneManager(GraphicsSystem& gs, MatrixStack& ms);
	~SceneManager();
	
	CameraNode* CreateCameraNode();
	LightNode* CreateLightNode();
	MaterialNode* CreateMaterialNode();
	MeshNode* CreateMeshNode();
	SamplerNode* CreateSamplerNode();
	ShaderNode* CreateShaderNode();
	TextureNode* CreateTextureNode();
	TransformNode* CreateTransformNode();

	void SetRoot(SceneNode* root);
	void Purge();

	void Update(f32 deltaTime);
	void Render();

private:
	std::vector<SceneNode*> mNodes;
	
	GraphicsSystem& mGraphicsSystem;
	MatrixStack& mMatrixStack;

	SceneNode* mpRoot;
};

#endif // #ifndef INCLUDED_SIEGE_SCENEMANAGER_H