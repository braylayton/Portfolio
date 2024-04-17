#ifndef INCLUDED_GRAPHICS_MATERIALNODE_H
#define INCLUDED_GRAPHICS_MATERIALNODE_H

#include "SceneNode.h"
#include "ConstantBuffer.h"
#include "Material.h"

namespace SWGE {
namespace Graphics {


	class MaterialNode : public SceneNode
	{
	public:
	
		MaterialNode(const Material& material);
		virtual ~MaterialNode();

		void Initialize();
		void Terminate();

		Material& GetMaterial() { return mMaterial; }
		const Material& GetMaterial() const { return mMaterial; }
	protected:
		virtual void OnRender();

	protected:
		TypedConstantBuffer<Material> mConstantBuffer;

		Material mMaterial;
	};

}
}
#endif // !INCLUDED_GRAPHICS_MATERIALNODE_H
