#ifndef INCLUDED_GRAPHICS_LIGHT_H
#define INCLUDED_GRAPHICS_LIGHT_H

#include <Math/Inc/QMath.h>

namespace SWGE {
namespace Graphics {

struct Light
{
	Light()
		: direction(Math::Vector3::ZAxis(), 0.0f)
		, ambient(Math::Vector4::White())
		, diffuse(Math::Vector4::White())
		, specular(Math::Vector4::White())
		, position(Math::Vector3::Zero(), 0.0f)
		, Range(0)
		, Falloff(0)
		, ConstAttenuation(0)
		, LinAttenuation(0)
		, QuadAttenuation(0)
		, Theta(0)
		, Phi(0)
		, typeOfLight(0)

	{}

	Math::Vector4 GetDirection() { return direction; }
	Math::Vector4 GetAmbient() { return ambient; }
	Math::Vector4 GetDiffuse() { return diffuse; }
	Math::Vector4 GetSpecular() { return specular; }



	Math::Vector4 direction;
	Math::Vector4 ambient;
	Math::Vector4 diffuse;
	Math::Vector4 specular;
	Math::Vector4 position;
	float Range;
	float Falloff;
	float ConstAttenuation;
	float LinAttenuation;
	float QuadAttenuation;
	float Theta;
	float Phi;
	int typeOfLight;
};

} // Graphics
} // SWGE
#endif // INCLUDED_GRAPHICS_LIGHT_H