#ifndef INCLUDED_PHYSICS_PHYSICSWORLD_H
#define INCLUDED_PHYSICS_PHYSICSWORLD_H

#include "Particle.h"
#include "Constraints.h"

namespace SWGE {
namespace Physics {


class PhysicsWorld
{
public:
	struct Settings
	{
		Math::Vector3 gravity{ 0.0f, -9.81f, 0.0f };
		float timeStep{ 1.0f / 60.0f };
		float drag{ 0.0f };
		uint32_t iterations{ 1 };
	};
	PhysicsWorld();
	~PhysicsWorld();

	void Setup(const Settings& settings);
	void Update(float deltaTime);

	void AddParticle(Particle* p);
	void AddConstraints(Constraint* c);

	/*void SatisfyConstraints();*/

	void ClearAll();

	void DebugDraw() const;

private:
	void AccumulateForces();
	void Integrate();
	void SatisfyConstraints();

	std::vector<Particle*> mParticles;
	std::vector<Constraint*> mConstraints;

	Settings mSettings;
	float mTimer{0.0f};
};

} // Physics
} // SWGE
#endif // !INCLUDED_PHYSICS_PHYSICSWORLD_H
