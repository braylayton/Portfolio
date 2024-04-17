#ifndef  INCLUDED_GRAPHICS_MATERIAL_H
#define INCLUDED_GRAPHICS_MATERIAL_H

#include <Math/Inc/QMath.h>
//3dgep.com/texturing-lighting-direct

namespace SWGE {
namespace Graphics {

	struct Material
	{
	
		Math::Vector4 GetAmbient() { return ambient; }
		Math::Vector4 GetDiffuse() { return diffuse; }
		Math::Vector4 GetSpecular() { return specular; }
		Math::Vector4 GetEmissive() { return emissive; }
		float GetPower() { return power; }
		float GetDisplacementFactor() { return displacementFactor; }

		Math::Vector4 ambient = Math::Vector4::White();
		Math::Vector4 diffuse = Math::Vector4::White();
		Math::Vector4 specular = Math::Vector4::White();
		Math::Vector4 emissive = Math::Vector4::Black();
		float power = 1.0f;
		float displacementFactor = 0.0f;
	};

} // Graphics
} // SWGE

#endif // INCLUDED_GRAPHICS_MATERIAL_H