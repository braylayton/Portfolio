#ifndef INCLUDED_GRAPHICS_CAMERA_H
#define INCLUDED_GRAPHICS_CAMERA_H

#include "Math\Inc\QMath.h"
#include "Core\Inc\Meta.h"

namespace SWGE {
namespace Graphics {

// This camera assumes YAxis as up direction always
// Quarternions don't cause gimbel lock

class Camera
{
public:
	//META_CLASS_DECLARE;

	Camera();
	~Camera();

	void SetPosition(const Math::Vector3& position);
	void SetDirection(const Math::Vector3& direction);
	void SetLookAt(const Math::Vector3& target);

	void Walk(float distance);
	void Strafe(float distance);
	void Rise(float distance);

	void Yaw(float degree);
	void Pitch(float degree);

	void SetFOV(float fov);
	void SetNearPlane(float nearPlane);
	void SetFarPlane(float farPlane);

	Math::Vector3 GetPosition();
	
	Math::Matrix4 GetViewMatrix() const;
	Math::Matrix4 GetPerspectiveMatrix(float aspectRatio = 0) const;
	Math::Matrix4 GetOrthographicMatrix(uint32_t width = 0, uint32_t height = 0) const;

	Math::Ray ScreenPointToRay(int screenX, int screenY) const;

private:
	Math::Vector3 mPosition;
	Math::Vector3 mDirection;
	Math::Vector3 mRight;

	float mFOV;
	float mAspectRatio; // TODO: Setter
	float mNearPlane;
	float mFarPlane;

};

} //namespace SWGE
} //namespace Graphics


#endif//INCLUDED_GRAPHICS_CAMERA_H