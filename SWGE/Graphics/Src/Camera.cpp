#include "Precompiled.h"
#include "Camera.h"
#include "GraphicsSystem.h"

using namespace SWGE;
using namespace Graphics;

//META_CLASS_BEGIN(Camera)
//META_FIELD_BEGIN
//	META_FIELD(mPosition, "Position")
//	META_FIELD(mDirection, "Direction")
//	META_FIELD(mRight, "Right")
//	META_FIELD(mFOV, "FOV")
//	META_FIELD(mAspectRatio, "AspectRatio")
//	META_FIELD(mNearPlane, "NearPlane")
//	META_FIELD(mFarPlane, "FarPlane")
//META_FIELD_END
//META_CLASS_END


Camera::Camera()
	: mPosition(0.0f, 0.0f, 0.0f)
	, mDirection(0.0f, 0.0f, 1.0f)
	, mRight(1.0f, 0.0f, 0.0f)
	, mFOV(60.0f * Math::kDegToRad)
	, mNearPlane(0.01f)
	, mFarPlane(1000000.0f)

{
}
Camera::~Camera()
{

}
Math::Vector3 Camera::GetPosition()
{
	return mPosition;
}
void Camera::SetPosition(const Math::Vector3& position)
{
	mPosition = position;
}
void Camera::SetDirection(const Math::Vector3& direction)
{
	mDirection = Normalize(direction);
}
void Camera::SetLookAt(const Math::Vector3& target)
{
	mDirection = Normalize(target - mPosition);
}
void Camera::SetFOV(float fov)
{
	const float kMinFOV = 10.0f * Math::kDegToRad;
	const float kMaxFOV = 150.0f * Math::kDegToRad;
	mFOV = Math::Clamp(fov, kMinFOV, kMaxFOV);
}
void Camera::SetNearPlane(float nearPlane)
{
	mNearPlane = nearPlane;
}
void Camera::SetFarPlane(float farPlane)
{
	mFarPlane = farPlane;
}

void Camera::Walk(float distance)
{
	mPosition += mDirection * distance;
}
void Camera::Strafe(float distance)
{
	Math::Vector3 vect = Normalize(Cross(Math::Vector3::YAxis(), mDirection));
	mPosition += vect * distance;
}
void Camera::Rise(float distance)
{
	mPosition += Math::Vector3::YAxis() * distance;
}

void Camera::Yaw(float degree)
{
	float rad = degree * Math::kDegToRad;
	Math::Matrix4 vRotate = Math::Matrix4::RotationY(rad);
	mDirection = TransformNormal(mDirection, vRotate);
}
void Camera::Pitch(float degree)
{
	mRight = Normalize(Cross(Math::Vector3::YAxis(), mDirection));
	const Math::Matrix4 matRotate = Math::MatrixRotationAxis(mRight, degree * Math::kDegToRad);
	const Math::Vector3 newLook = TransformNormal(mDirection, matRotate);
	const float dot = Dot(newLook, Math::Vector3::YAxis());

	// Avoid looking straight up or down
	if(Math::Abs(dot) < 0.995f)
	{
		mDirection = newLook;
	}
}

Math::Matrix4 Camera::GetViewMatrix() const
{
	const Math::Vector3 l = mDirection;
	const Math::Vector3 r = Math::Normalize(Math::Cross(Math::Vector3::YAxis(), mDirection));
	const Math::Vector3 u = Math::Normalize(Math::Cross(l, r));
	const float dx = -Math::Dot(r, mPosition);
	const float dy = -Math::Dot(u, mPosition);
	const float dz = -Math::Dot(l, mPosition);
	return
	{
		r.x, u.x, l.x, 0.0f,
		r.y, u.y, l.y, 0.0f,
		r.z, u.z, l.z, 0.0f,
		dx,  dy,  dz,  1.0f
	};
}
Math::Matrix4 Camera::GetPerspectiveMatrix(float aspectRatio) const
{/*
	const float screenWidth = (width == 0) ? (float)GraphicsSystem::Get()->GetWidth() : (float)width;
	const float screenHeight = (height == 0) ? (float)GraphicsSystem::Get()->GetHeight() : (float)height;*/
	const float Aspect = (aspectRatio == 0) ? (float)GraphicsSystem::Get()->GetAspectRatio() : aspectRatio;
	const float h = 1 / tan(mFOV * 0.5f);
	const float w = h / Aspect;
	const float f = mFarPlane;
	const float n = mNearPlane;
	const float d = f / (f - n);
	
	return
	{
		w, 0.0f, 0.0f, 0.0f,
		0.0f, h, 0.0f, 0.0f,
		0.0f, 0.0f, d, 1.0f,
		0.0f, 0.0f, -n * d, 0.0f
	};

}

Math::Matrix4 SWGE::Graphics::Camera::GetOrthographicMatrix(uint32_t width, uint32_t height) const
{

	const float h = (float)height;

	const float w = (float)width;
	const float zf = mFarPlane;
	const float zn = mNearPlane;
	const float d = zn/(zn - zf);

	return Math::Matrix4
	(
		2.0f/w, 0.0f ,  0.0f,			0.0f,
		0.0f,	2.0f/h, 0.0f,			0.0f,
		0.0f,   0.0f,   1.0f/(zf-zn),	0.0f,
		0.0f,	0.0f,	d,				1.0f
	);

}

// Grabs mouse position and gives you World Ray
Math::Ray Camera::ScreenPointToRay(int screenX, int screenY) const
{
	const float screenWidth = static_cast<float>(GraphicsSystem::Get()->GetWidth());
	const float screenHeight = static_cast<float>(GraphicsSystem::Get()->GetHeight());
	const float aspect = screenWidth / screenHeight;
	const float halfWidth = screenWidth * 0.5f;
	const float halfHeight = screenHeight * 0.5f;
	const float tanFOV = tanf(mFOV * 0.5);
	const float dx = tanFOV * (static_cast<float>(screenX / halfWidth - 1.0f) * aspect);
	const float dy = tanFOV * (1.0f - static_cast<float>(screenY / halfHeight));

	Math::Ray ray;

	ray.org = Math::Vector3::Zero();
	ray.dir = Math::Normalize(Math::Vector3(dx, dy, 1.0f));

	Math::Matrix4 invMatView = Math::Inverse(GetViewMatrix());
	ray.org = Math::TransformCoord(ray.org, invMatView);
	ray.dir = Math::TransformNormal(ray.dir, invMatView);
	return ray;
}