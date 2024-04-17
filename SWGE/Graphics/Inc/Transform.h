#ifndef INCLUDED_GRAPHICS_TRANSFORM_H
#define INCLUDED_GRAPHICS_TRANSFORM_H

namespace SWGE {
namespace Graphics {

	class Transform
	{
	public:
		Math::Vector3 GetPosition() { return mPosition; }
		Math::Vector3 GetScale() { return mScale; }
		Math::Vector3 GetRotation() { return mRotation; }

		void SetPosition(Math::Vector3 pos) { mPosition = pos; }
		void SetScale(Math::Vector3 scale) { mScale = scale; }
		void SetRotation(Math::Vector3 rot) { mRotation = rot; }
		void SetQuatRotation(Math::Quaternion quat) { mQuatRotation = quat; }
	void SetWorldMatrix(Math::Matrix4 world) { mPosition = world.Position(); mScale = world.Scale();  }

	Math::Matrix4& GetTransform();

private:

	Math::Matrix4 mWorld;
	Math::Vector3 mPosition = { 0.0f,0.0f,0.0f };
	Math::Vector3 mScale = { 1.0f,1.0f,1.0f };
	Math::Vector3 mRotation = { 0.0f,0.0f,0.0f };
	Math::Quaternion mQuatRotation;
};

}
}
#endif //INCLUDED_GRAPHICS_TRANSFORM_H