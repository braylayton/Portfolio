#ifndef INCLUDED_GRAPHICS_SCENEMANAGER_H
#define INCLUDED_GRAPHICS_SCENEMANAGER_H

#include "Graphics\Inc\MatrixStack.h"
#include "Camera.h"
#include "Sampler.h"
#include "Light.h"
#include "Material.h"

namespace SWGE{
namespace Graphics{

class GraphicsSystem;
class MatrixStack;

class CameraNode;
class ConstantBufferNode;
class DepthMapNode;
class LightNode;
class MaterialNode;
class MeshNode;
class RasterizerStateNode;
class RenderTargetNode;
class SamplerNode;
class SceneNode;
class ShaderNode;
class TerrainNode;
class TextureNode;
class TransformNode;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	/*
	only generate code based on this template, if T is a child of SceneNode.
	Also, utilizing perfect forwarding so the constructor can have any number of arguements.

		template<class t, class... Arggs>
		typename std::enable_if<std::is_base_of<SceneNode, T>::value, T*>::type 
	*/
	SceneNode* CreateEmptySceneNode();
	CameraNode* CreateCameraNode(const Camera& camera, bool isOrthographic = false, bool isLightCamera = false);
	ConstantBufferNode* CreateConstantBufferNode();
	DepthMapNode* CreateDepthMapNode();
	LightNode* CreateLightNode(const Light& light);
	MaterialNode* CreateMaterialNode(const Material& material);
	MeshNode* CreateMeshNode();
	RenderTargetNode* CreateRenderTargetNode();
	RasterizerStateNode* CreateRasterizerStateNode();
	SamplerNode* CreateSamplerNode(Graphics::Sampler::Filter filter, Graphics::Sampler::AddressMode addressMode, uint32_t index);
	ShaderNode* CreateShaderNode();
	TextureNode* CreateTextureNode();
	TransformNode* CreateTransformNode();

	void SetRoot(SceneNode* root);
	void Purge();

	void Update(float deltaTime);
	void Render();

private:
	std::vector<SceneNode*> mNodes;

	MatrixStack mMatrixStack;
	SceneNode* mpRoot;
};
} // namespace Graphics
} // namespace SWGE


#endif // INCLUDED_GRAPHICS_SCENEMANAGER_H
