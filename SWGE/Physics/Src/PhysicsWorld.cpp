#include "Precompiled.h"
#include "PhysicsWorld.h"

using namespace SWGE;
using namespace Physics;

PhysicsWorld::PhysicsWorld()
	:mTimer(0)
{

}

PhysicsWorld::~PhysicsWorld()
{

}

void PhysicsWorld::AddParticle(Particle* p)
{
	mParticles.push_back(p);
}

void PhysicsWorld::AddConstraints(Constraint* c)
{
	mConstraints.push_back(c);
}

void PhysicsWorld::Setup(const Settings& settings)
{
	mSettings = settings;
}

void PhysicsWorld::Update(float deltaTime)
{
	mTimer += deltaTime;
	while (mTimer >= mSettings.timeStep)
	{
		mTimer -= mSettings.timeStep;
		AccumulateForces();
		Integrate();
		SatisfyConstraints();
	}
}

void PhysicsWorld::ClearAll()
{
	std::for_each(mParticles.begin(), mParticles.end(), SafeDelete<Particle>);
	mParticles.clear();
	std::for_each(mConstraints.begin(), mConstraints.end(), SafeDelete<Constraint>);
	mConstraints.clear();
}

void PhysicsWorld::DebugDraw() const
{
	for (auto p : mParticles)
	{
		p->DebugDraw();
	}

	for (auto c : mConstraints)
	{
		c->DebugDraw();
	}

	// This is what a for auto loop actually does
	/*for (auto it = mConstraints.begin(); it != mConstraints.end(); ++it)
	{
	
	}*/
}
//------------------------------------------PRIVATE:

void PhysicsWorld::AccumulateForces()
{
	for (auto p : mParticles)
	{
		p->acceleration = mSettings.gravity;
	}
}

void PhysicsWorld::Integrate()
{
	const float timeStepSqr = Math::Sqr(mSettings.timeStep);
	for (auto p : mParticles)
	{
		Math::Vector3 displacement = (p->position - p->positionOld) + (p->acceleration* timeStepSqr);
		p->positionOld = p->position;
		p->position = p->position + displacement;
	}
}

void PhysicsWorld::SatisfyConstraints()
{
	for (uint32_t i = 0; i < mSettings.iterations; i++)
	{
		for (auto c : mConstraints)
		{
			c->Apply();
		}

		//Check Plane Collision








		//for (auto p : mParticles)
		//{
		//	if (Math::MagnitudeSqr(p->position - sphere))
		//	{
		//		Math::vector3 oldTonew 
		//		math::vector3 midpoint
		//		math::vector3 normal(midpoint - sphere.center); 
		//		vector3 valNew = math::reflect(oldToNew, normal)
		//		
		//	}
		//}

	}


}