#ifndef INCLUDED_PHYSICS_PARTICAL_H
#define INCLUDED_PHYSICS_PARTICAL_H

namespace SWGE {
namespace Physics {

class Particle
{
public:
	Particle() = default;
	Particle(const Math::Vector3& position, float radius = 0.01f);

	void DebugDraw() const;

	void SetPosition(const Math::Vector3& position);
	void SetVelocity(const Math::Vector3& velocity);

	Math::Vector3 position;
	Math::Vector3 positionOld;
	Math::Vector3 acceleration;
	float radius{ 0.01f };
	float invMass{ 1.0f };
};

} // Physics
} // SWGE



#endif // !INCLUDED_PHYSICS_PARTICAL_H
